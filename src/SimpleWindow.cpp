#include <interface/Window.h>
#include <app/Application.h>
#include "KGCircle.h"
#include "SimpleWindow.h"
#include <interface/MenuBar.h>
#include <interface/Alert.h>
#include "ButtonView.h"

const char kConfirmQuitMsg[] = "Quit OK?";

SimpleWindow::SimpleWindow(BRect frame)
    : BWindow(frame, "Simple Window",
              B_TITLED_WINDOW,
              /* B_NOT_RESIZABLE | B_NOT_ZOOMABLE */ 0) 
{
}


bool
SimpleWindow::QuitRequested()
{
    // be_app->PostMessage(B_QUIT_REQUESTED);
    BMessage* message;
    BAlert* alert;
    message = CurrentMessage();
    if (message == nullptr || message->what != B_QUIT_REQUESTED)
	return true;
    alert = new BAlert(B_EMPTY_STRING, kConfirmQuitMsg, "Cancel", "OK", nullptr,
		       B_WIDTH_FROM_WIDEST, B_WARNING_ALERT);
    alert->SetShortcut(0, B_ESCAPE);
    return alert->Go() == 1;
}


void
SimpleWindow::InitContent(BMenuBar* menuBar, BView* content)
{
    AddChild(menuBar);
    BRect menuBarBounds(menuBar->Frame());
    BRect bounds(Frame());
    content->ResizeTo(bounds.Width(), bounds.Height() - menuBarBounds.Height() - 1);
    content->MoveBy(0, menuBarBounds.Height() + 1);
    AddChild(content);        
}


void
SimpleWindow::Quit()
{
    be_app->PostMessage(B_QUIT_REQUESTED);
    BWindow::Quit();
}
