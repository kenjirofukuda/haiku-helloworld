#include "SimpleWindow.h"
#include <app/Application.h>
#include <interface/Alert.h>


const char kConfirmQuitMsg[] = "Quit OK?";


SimpleWindow::SimpleWindow(BRect frame)
    : RegularWindow(frame, "Simple Window",
		    B_TITLED_WINDOW, 0, B_QUIT_REQUESTED)
{
}


bool
SimpleWindow::QuitRequested()
{
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
