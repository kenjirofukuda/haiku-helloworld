#ifndef   CLOCK_VIEW_H
#define CLOCK_VIEW_H

#include "TimeKeeper.h"
#include <interface/View.h>
#include <time.h>

class TimeKeeper;

class ClockView : public BView {
public:
    ClockView(BRect frame, uint32 resizeMask, TimeKeeper* timeKeeper);
    ~ClockView();

    void AttachedToWindow() override;
    void DetachedFromWindow() override;
    void Draw(BRect updateRect) override;

    void MessageReceived(BMessage* message) override;
    void UpdateTime();
    
private:
    TimeKeeper* fTimeKeeper;
    tm fTime;
};

#endif // CLOCK_VIEW_H
// vim: set ai ts=4 sw=4 fenc=utf-8 ff=unix :
