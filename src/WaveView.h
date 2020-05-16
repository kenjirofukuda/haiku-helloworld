#ifndef   WAVE_VIEW_H
#define WAVE_VIEW_H

#include "TimeKeeper.h"
#include <interface/View.h>

class WaveView : public BView {
public:
    WaveView(BRect frame, uint32 resizeMask, TimeKeeper* timeKeeper);
    ~WaveView();

    void AttachedToWindow();
    void DettachedFromWindow();
    void Pulse() override;

    void MessageReceived(BMessage* message) override;
    void UpdateColor();

private:
    TimeKeeper* fTimeKeeper;
    uint8 fCurrColor;
    float fWaveRadius;
    BPoint fWaveOrigin;
};

#endif // WAVE_VIEW_H
// vim: set ai ts=4 sw=4 fenc=utf-8 ff=unix :
