#ifndef CLOCKWORK_WAVE_APP_H
#define CLOCKWORK_WAVE_APP_H

#include <app/Application.h>

// class RegularWindow;
// class TimeKeeper;
// class BMenuBar;

class ClockworkWaveApp : BApplication
{
public:
    ClockworkWaveApp();
    
private:
    void ReadyToRun() override;
    void Quit() override;
    void MessageReceived(BMessage* message) override;
};


#endif //  CLOCKWORK_WAVE_APP_H
