#include "ClockworkWaveApp.h"
#include "ClockView.h"
#include "WaveView.h"
#include "TimeKeeper.h"
#include "RegularWindow.h"

#include <interface/MenuBar.h>
#include <interface/Alert.h>
#include <support/Autolock.h>
#include <stdio.h>

extern void Error(const char* message, status_t code);


enum {
    WINDOW_CLOSED = 'wcld',
    SHOW_CLOCK = 'sclk',
    SHOW_WAVE = 'swav'
};

const char kAboutMsg[] =
    "SimpleApp\n\n"
    "Copyright " B_UTF8_COPYRIGHT " 2020-2020 My Greate Comapy, Inc.\n"
    "Author: Unkown (unkown@unkown.com)";

ClockworkWaveApp::ClockworkWaveApp()
  : BApplication("application/x-vnd.kf-ClockworkWaveapp")
{
    fClockWin = nullptr;
    fWaveWin = nullptr;
    fTimeKeeper = nullptr;
}
    

void
ClockworkWaveApp::ReadyToRun()
{
    fTimeKeeper = new TimeKeeper();
    // fTimeKeeper->Run();
    MakeClockWin();
    MakeWaveWin();
}


void
ClockworkWaveApp::Quit()
{
    BApplication::Quit();
}


void
ClockworkWaveApp::MakeClockWin()
{
    BMenuBar* menuBar;
    BView* view;

    fClockWin = new RegularWindow(BRect(20, 20, 200, 140), "Clock Window",
				  B_TITLED_WINDOW, 0, WINDOW_CLOSED);
    menuBar = MakeMenuBar(true);
    view = new ClockView(BRect(0, 0, 0, 0), B_FOLLOW_ALL_SIDES, fTimeKeeper);
    view->SetViewColor(0xD0, 0xD0, 0xD0);
    fClockWin->InitContent(menuBar, view);
}


void
ClockworkWaveApp::MakeWaveWin()
{
}


BMenuBar*
ClockworkWaveApp::MakeMenuBar(bool forClock)
{
    return nullptr;
}


void
ClockworkWaveApp::MessageReceived(BMessage* message)
{
    switch (message->what) {
    case WINDOW_CLOSED:
	CheckWindow(message);
	break;
    case SHOW_CLOCK:
	ShowClock();
	break;
    case SHOW_WAVE:
	ShowWave();
	break;
    default:
	BApplication::MessageReceived(message);
    }
}


void ClockworkWaveApp::AboutRequested()
{
    BAlert* alert;

    alert = new BAlert("about box", kAboutMsg, "OK");
    alert->Go(nullptr);
}


void ClockworkWaveApp::CheckWindow(BMessage* message)
{
    status_t sts;
    BWindow* sender;

    sts = message->FindPointer(kSender, (void**) &sender);
    if (sts != B_OK)
	goto err;

    if (sender == fClockWin)
	fClockWin = nullptr;
    else if (sender == fWaveWin)
	fWaveWin = nullptr;
    else {
	sts = B_ERROR;
	goto err;
    }
    if (fClockWin == nullptr && fWaveWin == nullptr)
	PostMessage(B_QUIT_REQUESTED);
    return;
err:
    ::Error("ClockWaveApp::CheckWindow", sts);
}


void ClockworkWaveApp::ShowClock()
{
    if (fClockWin == nullptr)
	MakeClockWin();
    else
	ShowWindow(fClockWin);
}


void ClockworkWaveApp::ShowWave()
{
    if (fWaveWin == nullptr)
	MakeWaveWin();
    else
	ShowWindow(fWaveWin);
}

void ClockworkWaveApp::ShowWindow(BWindow* window)
{
    BAutolock lock(window);

    if (window->IsHidden())
	window->Show();
    else if (! window->IsActive())
	window->Active();
}


void Error(const char* message, status_t code)
{
    BAlert* alert;
    char buff[256];
    sprintf(buff, "%s : %d", message, code);
    alert = new BAlert("about box", buff, "OK");
    alert->Go(nullptr);
}
