#include "ClockView.h"

#include <stdio.h>

#include "TimeKeeper.h"
#include "Utils.h"

enum {
    UPDATE_TIME = 'uptm'
};


ClockView::ClockView(BRect frame, uint32 resizeMask, TimeKeeper* timeKeeper)
  : TimedView(frame, "ClockView", resizeMask, B_WILL_DRAW, timeKeeper)
{
    fTime.tm_hour = 0;
    fTime.tm_min = 0;
    fTime.tm_sec = 0;    
}


ClockView::~ClockView()
{
}


void ClockView::AttachedToWindow()
{
    ScheduleInfo schedule;
    schedule.client = this;
    schedule.message = new BMessage(UPDATE_TIME);
    schedule.period = 1;
    schedule.first_time = ::real_time_clock();
    status_t sts = AddSchedule(schedule);
    if (sts != B_OK)
	goto err;
    UpdateTime();
    return;
err:
    ::Error("ClockView::AttachedToWindow", sts);
}


void ClockView::DetachedFromWindow()
{
    status_t sts = RemoveSchedule(UPDATE_TIME);   
    if (sts != B_OK)
	goto err; 
    return;
err:
    ::Error("ClockView::DetachedFromWindow", sts);
}


void ClockView::Draw(BRect /* updateRect */)
{
    rgb_color savedColor = HighColor();
    SetHighColor(ViewColor());
    FillRect(Bounds());
    SetHighColor(savedColor);

    char timeStr[64];
    sprintf(timeStr, "%02d:%02d:%02d", fTime.tm_hour, fTime.tm_min, fTime.tm_sec);
    SetFontSize(30);
    DrawString(timeStr, BPoint(18, 40));
}



void ClockView::MessageReceived(BMessage* message)
{
    switch (message->what) {
    case UPDATE_TIME:
	UpdateTime();
	break;

    default:
	TimedView::MessageReceived(message);
    }
}


void ClockView::UpdateTime()
{
    time_t currTime = time(0);

    fTime = *(localtime(&currTime));
    Draw(Bounds());
}


// vim: set ai ts=4 sw=4 fenc=utf-8 ff=unix :
