#include <interface/Window.h>
#include <app/Application.h>
#include "KGCircle.h"
#include "SimpleWindow.h"
#include "ButtonView.h"

SimpleWindow::SimpleWindow(BRect frame)
    : BWindow(frame, "Simple Window",
              B_TITLED_WINDOW,
              B_NOT_RESIZABLE | B_NOT_ZOOMABLE) 
{
    ButtonView* view;

    view = new ButtonView(Bounds(), "content",
                          B_FOLLOW_ALL_SIDES, B_WILL_DRAW);
    AddChild(view);    
}


bool
SimpleWindow::QuitRequested()
{
    be_app->PostMessage(B_QUIT_REQUESTED);
    return true;
}
