#include "WaveView.h"
#include "TimeKeeper.h"
#include "Utils.h"

#include <interface/Screen.h>
#include <interface/Window.h>
#include <support/Debug.h>

enum {
    UPDATE_COLOR = 'upcl'
};

const float kInitialRadius = 10;

WaveView::WaveView(BRect frame, uint32 resizeMask, TimeKeeper* timeKeeper)
    : BView(frame, "Wave", resizeMask, B_PULSE_NEEDED)
{
    fTimeKeeper = timeKeeper;
    fCurrColor = 255;
    fWaveRadius = kInitialRadius;
}


WaveView::~WaveView()
{
}


void WaveView::AttachedToWindow()
{
    BRect bounds(Bounds());
    ScheduleInfo schedule;
    schedule.client = this;
    schedule.message = new BMessage(UPDATE_COLOR);
    schedule.period = 4;
    schedule.first_time = ::real_time_clock() + 4;
    status_t sts = fTimeKeeper->InsertSchedule(schedule);
    if (sts != B_OK)
	goto bail;
    UpdateColor();
    Window()->SetPulseRate(100 * 1000);
    
    fWaveOrigin.x = bounds.Width() / 2;
    fWaveOrigin.y = bounds.Height() / 2;
    return;
bail:
    ::Error("WaveView::AttachedToWindow", sts);
}


void WaveView::DetachedFromWindow()
{
    status_t sts = fTimeKeeper->RemoveSchedule(this, UPDATE_COLOR);   
    if (sts != B_OK)
	goto bail; 
    return;
bail:
    ::Error("WaveView::DetachedFromWindow", sts);
}


void WaveView::Pulse()
{
    BScreen screen = Window();
    uint8 waveColor = screen.InvertIndex(fCurrColor);
    if (fCurrColor == 247)
	waveColor += 1;
    else if (fCurrColor == 16)
	waveColor -= 2;

    rgb_color savedColor = HighColor();
    SetHighColor(screen.ColorForIndex(waveColor));
    if (fWaveRadius == kInitialRadius) {
	FillEllipse(fWaveOrigin, fWaveRadius * 2, fWaveRadius * 2);
    }
    else {
	StrokeEllipse(fWaveOrigin,
		      kInitialRadius + fWaveRadius, kInitialRadius + fWaveRadius);
	SetHighColor(screen.ColorForIndex(fCurrColor));
	StrokeEllipse(fWaveOrigin,
		      fWaveRadius - kInitialRadius, fWaveRadius - kInitialRadius); 		        }
    SetHighColor(savedColor);

    if ((fWaveOrigin.x * sqrt(2)) <= (fWaveRadius - kInitialRadius))
	fWaveRadius = kInitialRadius;
    else
	fWaveRadius += 1;
}



void WaveView::MessageReceived(BMessage* message)
{
    switch (message->what) {
    case UPDATE_COLOR:
	UpdateColor();
	break;

    default:
	BView::MessageReceived(message);
    }
}


void WaveView::UpdateColor()
{
    ASSERT(Window() != nullptr);
    BScreen screen = Window();
    rgb_color newColor = screen.ColorForIndex(fCurrColor--);
    if ((int16) fCurrColor < 0)
	fCurrColor = 255;
}


// vim: set ai ts=4 sw=4 fenc=utf-8 ff=unix :
