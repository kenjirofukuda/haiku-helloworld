#include "WaveView.h"
#include "TimeKeeper.h"
#include "Utils.h"

#include <Screen.h>
#include <Window.h>
#include <Debug.h>
#include <Bitmap.h>
#include <View.h>

enum {
	UPDATE_COLOR = 'upcl'
};

const float kInitialRadius = 10;

WaveView::WaveView(BRect frame, uint32 resizeMask,
				   TimeKeeper* timeKeeper)
	: TimedView(frame, "Wave", resizeMask, B_WILL_DRAW | B_PULSE_NEEDED, timeKeeper)
{
	fCurrColor = 255;
	fWaveRadius = kInitialRadius;
	fOffscreen = nullptr;
}


WaveView::~WaveView()
{
	if (fOffscreen != nullptr)
		delete fOffscreen;
}


void
WaveView::AttachedToWindow()
{
	BRect bounds(Bounds());
	ScheduleInfo schedule;
	BView* offView = nullptr;
	schedule.client = this;
	schedule.message = new BMessage(UPDATE_COLOR);
	schedule.period = 4;
	schedule.first_time = ::real_time_clock() + 4;
	status_t sts = AddSchedule(schedule);
	if (sts != B_OK)
		goto bail;

	fOffscreen = new BBitmap(bounds, B_COLOR_8_BIT, true);
	offView = new BView(bounds, "", B_FOLLOW_ALL_SIDES, 0);
	offView->SetHighColor(HighColor());
	offView->SetViewColor(ViewColor());
	fOffscreen->AddChild(offView);
	
	UpdateColor();
	Window()->SetPulseRate(100 * 1000);

	fWaveOrigin.x = bounds.Width() / 2;
	fWaveOrigin.y = bounds.Height() / 2;
	return;
bail:
	::Error("WaveView::AttachedToWindow", sts);
}


void
WaveView::DetachedFromWindow()
{
	status_t sts = RemoveSchedule(UPDATE_COLOR);
	if (sts != B_OK)
		goto bail;
	delete fOffscreen;
	fOffscreen = nullptr;
	return;
bail:
	::Error("WaveView::DetachedFromWindow", sts);
}


void
WaveView::Draw(BRect updateRect)
{
	DrawBitmap(fOffscreen, updateRect, updateRect);
}


void
WaveView::DrawWave(BView* targetView, rgb_color waveColor, rgb_color backColor)
{
	rgb_color savedColor = targetView->HighColor();
	targetView->SetHighColor(waveColor);
	if (fWaveRadius == kInitialRadius)
		targetView->FillEllipse(fWaveOrigin, fWaveRadius * 2, fWaveRadius * 2);
	else {
		targetView->StrokeEllipse(fWaveOrigin,
								  kInitialRadius + fWaveRadius, kInitialRadius + fWaveRadius);
		targetView->SetHighColor(backColor);
		targetView->StrokeEllipse(fWaveOrigin,
								  fWaveRadius - kInitialRadius, fWaveRadius - kInitialRadius);
	}
	targetView->SetHighColor(savedColor);
}


void
WaveView::Pulse()
{
	BScreen screen = Window();
	uint8 waveColor = screen.InvertIndex(fCurrColor);
	if (fCurrColor == 247)
		waveColor += 1;
	else if (fCurrColor == 16)
		waveColor -= 2;

	rgb_color waveRGBColor = screen.ColorForIndex(waveColor);
	rgb_color backRGBColor = screen.ColorForIndex(fCurrColor);
	DrawWave(this, waveRGBColor, backRGBColor);
	
	fOffscreen->Lock();
	BView *offView = fOffscreen->ChildAt(0);
	DrawWave(offView, waveRGBColor, backRGBColor);
	offView->Window()->Flush();
	fOffscreen->Unlock();

	if ((fWaveOrigin.x * sqrt(2)) <= (fWaveRadius - kInitialRadius))
		fWaveRadius = kInitialRadius;
	else
		fWaveRadius += 1;
}



void
WaveView::MessageReceived(BMessage* message)
{
	switch (message->what) {
		case UPDATE_COLOR:
			UpdateColor();
			break;

		default:
			TimedView::MessageReceived(message);
	}
}


void
WaveView::UpdateColor()
{
	ASSERT(Window() != nullptr);
	BScreen screen = Window();
	rgb_color newColor = screen.ColorForIndex(fCurrColor--); // but not used
	if ((int16) fCurrColor < 0)
		fCurrColor = 255;
}


// vim: set ai ts=4 sw=4 fenc=utf-8 ff=unix :
