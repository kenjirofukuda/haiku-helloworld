#ifndef   WAVE_VIEW_H
#define WAVE_VIEW_H

#include "TimeKeeper.h"
#include "TimedView.h"

class WaveView : public TimedView {
public:
    WaveView(BRect frame, uint32 resizeMask, TimeKeeper* timeKeeper);
    virtual ~WaveView();

    void AttachedToWindow() override;
    void DetachedFromWindow() override;
    void Pulse() override;

    void MessageReceived(BMessage* message) override;
    void UpdateColor();

private:
    uint8 fCurrColor;
    float fWaveRadius;
    BPoint fWaveOrigin;
};

#endif // WAVE_VIEW_H
// vim: set ai ts=4 sw=4 fenc=utf-8 ff=unix :
