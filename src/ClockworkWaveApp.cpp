#include "ClockworkWaveApp.h"
#include "ClockView.h"
#include "WaveView.h"
#include "TimeKeeper.h"
#include "RegularWindow.h"
#include "Utils.h"

#include <MenuBar.h>
#include <Menu.h>
#include <MenuItem.h>
#include <Alert.h>
#include <Autolock.h>
#include <stdio.h>

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
	fClockWin = new RegularWindow(BRect(20, 20, 200, 140), "Clock Window",
								  B_TITLED_WINDOW,
								  0,
								  WINDOW_CLOSED);
	BMenuBar* menuBar = MakeMenuBar(true);
	BView* view = new ClockView(BRect(0, 0, 0, 0), B_FOLLOW_ALL_SIDES,
								fTimeKeeper);
	view->SetViewColor(0xD0, 0xD0, 0xD0);
	fClockWin->InitContent(menuBar, view);
	fClockWin->Show();
}


void
ClockworkWaveApp::MakeWaveWin()
{
	fWaveWin = new RegularWindow(BRect(250, 200, 450, 400), "Wave Window",
								 B_TITLED_WINDOW,
								 B_NOT_RESIZABLE | B_NOT_ZOOMABLE,
								 WINDOW_CLOSED);
	BMenuBar* menuBar = MakeMenuBar(false);
	BView* view = new WaveView(BRect(0, 0, 0, 0), B_FOLLOW_ALL_SIDES,
							   fTimeKeeper);
	fWaveWin->InitContent(menuBar, view);
	fWaveWin->Show();
}


BMenuBar*
ClockworkWaveApp::MakeMenuBar(bool forClock)
{
	BMenuBar* menuBar = new BMenuBar(BRect(0, 0, 0, 0), B_EMPTY_STRING);
	BMenu* fileMenu = new BMenu("File");
	menuBar->AddItem(fileMenu);
	fileMenu->AddItem(new BMenuItem("About ClockworkWave" B_UTF8_ELLIPSIS,
									new BMessage(B_ABOUT_REQUESTED)));
	fileMenu->AddSeparatorItem();
	if (forClock) {
		fileMenu->AddItem(new BMenuItem("Show Wave",
										new BMessage(SHOW_WAVE)));
	}
	else {
		fileMenu->AddItem(new BMenuItem("Show Clock",
										new BMessage(SHOW_CLOCK)));
	}
	fileMenu->AddSeparatorItem();
	fileMenu->AddItem(new BMenuItem("Quit",
									new BMessage(B_QUIT_REQUESTED)));
	fileMenu->SetTargetForItems(this);
	return menuBar;
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


void
ClockworkWaveApp::AboutRequested()
{
	BAlert* alert;

	alert = new BAlert("about box", kAboutMsg, "OK");
	alert->Go(nullptr);
}


void
ClockworkWaveApp::CheckWindow(BMessage* message)
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


void
ClockworkWaveApp::ShowClock()
{
	if (fClockWin == nullptr)
		MakeClockWin();
	else
		ShowWindow(fClockWin);
}


void
ClockworkWaveApp::ShowWave()
{
	if (fWaveWin == nullptr)
		MakeWaveWin();
	else
		ShowWindow(fWaveWin);
}

void
ClockworkWaveApp::ShowWindow(BWindow* window)
{
	BAutolock lock(window);

	if (window->IsHidden())
		window->Show();
	else if (! window->IsActive())
		window->Activate();
}
