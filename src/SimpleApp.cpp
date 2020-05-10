#ifndef _SIMPLE_APP_H_
#include "SimpleApp.h"
#endif
#ifndef _SIMPLE_WINDOW_H_
#include "SimpleWindow.h"
#endif

SimpleApp::SimpleApp() : BApplication("application/x-vnd.kenjirofukuda.SimpleApp")
{
}


void
SimpleApp::ReadyToRun()
{
    SimpleWindow *window = new SimpleWindow(BRect(0, 0, 200, 120));
    window->CenterOnScreen();    // Haiku Only
    window->Show();
}

    
