#include "ClockworkWaveApp.h"

ClockworkWaveApp::ClockworkWaveApp()
  : BApplication("application/x-vnd.dw-ClockworkWaveapp")
{
}
    

void
ClockworkWaveApp::ReadyToRun()
{
}


void
ClockworkWaveApp::Quit()
{
    BApplication::Quit();
}


void
ClockworkWaveApp::MessageReceived(BMessage* message)
{
    BApplication::MessageReceived(message);
}

