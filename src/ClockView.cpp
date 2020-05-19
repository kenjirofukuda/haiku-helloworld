#include "ClockView.h"

#include <Window.h>
#include <stdio.h>

#include "TimeKeeper.h"
#include "Utils.h"

enum {
	UPDATE_TIME = 'uptm'
};


ClockView::ClockView(BRect frame, uint32 resizeMask,
					 TimeKeeper* timeKeeper)
	: TimedView(frame, "ClockView", resizeMask, B_WILL_DRAW, timeKeeper)
{
	fTime.tm_hour = 0;
	fTime.tm_min = 0;
	fTime.tm_sec = 0;
	fOffscreen = nullptr;
	fUseOffscreen = true;
}


ClockView::~ClockView()
{
	if (fOffscreen != nullptr)
		delete fOffscreen;
}


void
ClockView::AttachedToWindow()
{
	ScheduleInfo schedule;
	BView* offView = nullptr;
	schedule.client = this;
	schedule.message = new BMessage(UPDATE_TIME);
	schedule.period = 1;
	schedule.first_time = ::real_time_clock();
	status_t sts = AddSchedule(schedule);
	if (sts != B_OK)
		goto err;

	if (fUseOffscreen) {
		fOffscreen = new BBitmap(Bounds(), B_COLOR_8_BIT, true);
		offView = new BView(Bounds(), "", B_FOLLOW_ALL_SIDES, 0);
		offView->SetViewColor(ViewColor());
		offView->SetHighColor(HighColor());
		fOffscreen->AddChild(offView);
	}
	UpdateTime();
	return;
err:
	::Error("ClockView::AttachedToWindow", sts);
}


void
ClockView::DetachedFromWindow()
{
	status_t sts = RemoveSchedule(UPDATE_TIME);
	if (sts != B_OK)
		goto err;
	if (fUseOffscreen) {
		delete fOffscreen;
		fOffscreen = nullptr;
	}
	return;
err:
	::Error("ClockView::DetachedFromWindow", sts);
}


void
ClockView::Draw(BRect updateRect)
{
	if (fUseOffscreen) {
		if (fOffscreen->Lock()) {
			DrawBitmap(fOffscreen, updateRect, updateRect);
			fOffscreen->Unlock();
		}
	}
	else
		DrawTime(this);
}



void
ClockView::MessageReceived(BMessage* message)
{
	switch (message->what) {
		case UPDATE_TIME:
			UpdateTime();
			break;

		default:
			TimedView::MessageReceived(message);
	}
}


void
ClockView::DrawTime(BView* view)
{
	char timeStr[64];
	sprintf(timeStr, "%02d:%02d:%02d", fTime.tm_hour, fTime.tm_min,
			fTime.tm_sec);
	rgb_color savedColor = view->HighColor();
	view->SetHighColor(view->ViewColor());
	view->FillRect(view->Bounds());
	view->SetHighColor(savedColor);
	view->SetFontSize(30);
	view->DrawString(timeStr, BPoint(18, 40));
}



void
ClockView::UpdateTime()
{
	time_t currTime = time(0);
	fTime = *(localtime(&currTime));
	if (fUseOffscreen) {
		fOffscreen->Lock();
		BView* offView = fOffscreen->ChildAt(0);
		DrawTime(offView);
		offView->Window()->Flush();
		fOffscreen->Unlock();
	}
	Invalidate(Bounds());
}


// vim: set ai ts=4 sw=4 fenc=utf-8 ff=unix :
