#ifndef _SIMPLE_APP_H_
#include "SimpleApp.h"
#endif
#include "SimpleWindow.h"
#include "ButtonView.h"

#include <interface/MenuBar.h>
#include <interface/MenuItem.h>
#include <interface/Alert.h>

const char kAboutMsg[] =
    "SimpleApp\n\n"
    "Copyright " B_UTF8_COPYRIGHT " 2020-2020 My Greate Comapy, Inc.\n"
    "Author: Unkown (unkown@unkown.com)";

#include <interface/MenuItem.h>

SimpleApp::SimpleApp() : BApplication("application/x-vnd.kenjirofukuda.SimpleApp")
{
}


void
SimpleApp::ReadyToRun()
{
    SimpleWindow* window; 
    BMenuBar* menuBar;
    ButtonView* view;

    window = new SimpleWindow(BRect(0, 0, 200, 120));
    menuBar = MakeMenuBar();
    view = new ButtonView(BRect(), "content",
                          B_FOLLOW_ALL_SIDES, B_WILL_DRAW);
    window->InitContent(menuBar, view);
    float minWidth;
    float maxWidth;
    float minHeight;
    float maxHeight;
    window->GetSizeLimits(&minWidth, &maxWidth, &minHeight, &maxHeight);
    window->SetSizeLimits(140, maxWidth, 185, maxHeight);
    window->CenterOnScreen();    // Haiku Only
    window->Show();
}


void SimpleApp::AboutRequested()
{
    BAlert* alert;

    alert = new BAlert("about box", kAboutMsg, "OK");
    alert->Go(nullptr);
}

  
BMenuBar* SimpleApp::MakeMenuBar()
{
    BMenuBar* menuBar;
    BMenu* fileMenu;

    menuBar = new BMenuBar(BRect(), B_EMPTY_STRING);
    fileMenu = new BMenu("File");
    menuBar->AddItem(fileMenu);
    fileMenu->AddItem(new BMenuItem("About SimpleApp" B_UTF8_ELLIPSIS ,
				    new BMessage(B_ABOUT_REQUESTED)));
    fileMenu->AddSeparatorItem();
    fileMenu->AddItem(new BMenuItem("Quit",
				    new BMessage(B_QUIT_REQUESTED),
				    'Q'));
    
    fileMenu->SetTargetForItems(this);
    return menuBar;
}
  

