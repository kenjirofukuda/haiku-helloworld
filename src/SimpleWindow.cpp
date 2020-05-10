#include <Window.h>
#include <Application.h>


const BRect kHotSpot(110, 30, 140, 60);

class SimpleView : public BView 
{
public:
    SimpleView(BRect frame, const char *name,
               uint32 resizeMask, uint32 flags);
    ~SimpleView();

private:
    void Draw(BRect updateRect);
    void MouseDown(BPoint where);
    void HotSpotAction(bool currInside, bool prevInside);
};

    
SimpleView::SimpleView(BRect frame, const char *name,
               uint32 resizeMask, uint32 flags)
    : BView(frame, name, resizeMask, flags)
{
    SetViewColor(0xDD, 0xDD, 0xDD);
}


SimpleView::~SimpleView()
{    
}


void
SimpleView::Draw(BRect updateRect)
{
    DrawString("This is the by 2nd app.", BPoint(10, 10));
    SetHighColor(255, 0, 0);
    FillRect(kHotSpot);    
}

void
SimpleView::MouseDown(BPoint where)
{
    int32 intReply;
    uint32 buttons;
    bool currInside = true;
    bool prevInside = false;
    
    this->Window()->CurrentMessage()->FindInt32("buttons", &intReply);
    buttons = intReply;
    if (buttons != B_PRIMARY_MOUSE_BUTTON)
	return;

    if (! kHotSpot.Contains(where))
	return;
    this->HotSpotAction(currInside, prevInside);

    while (buttons & B_PRIMARY_MOUSE_BUTTON) {
	::snooze(20 * 1000);
	GetMouse(&where, &buttons, true);
	prevInside = currInside;
	currInside = kHotSpot.Contains(where);
	HotSpotAction(currInside, prevInside);	
    }

    if (kHotSpot.Contains(where))
	be_app->PostMessage(B_QUIT_REQUESTED);
}


void
SimpleView::HotSpotAction(bool currInside, bool prevInside)
{
    if (currInside == prevInside)
	return;
    rgb_color orgColor = HighColor();
    if (currInside)
	SetHighColor(0, 255, 0);
    else
	SetHighColor(255, 0, 0);
    FillRect(kHotSpot);
    SetHighColor(orgColor);
}


class SimpleWindow : public BWindow
{
public:
    SimpleWindow(BRect frame);
    // virtual bool    QuitRequested();
    void InitContent(BView *content);
    void Quit();
};


SimpleWindow::SimpleWindow(BRect frame)
    : BWindow(frame, "Simple Window",
              B_TITLED_WINDOW,
              B_NOT_RESIZABLE | B_NOT_ZOOMABLE) 
{
    SimpleView* view;

    view = new SimpleView(Bounds(), "content",
                          B_FOLLOW_ALL_SIDES, B_WILL_DRAW);
    AddChild(view);    
}


// bool
// SimpleWindow::QuitRequested()
// {
//     be_app->PostMessage(B_QUIT_REQUESTED);
//     return true;
// }

void
SimpleWindow::Quit()
{
    be_app->PostMessage(B_QUIT_REQUESTED, be_app);
    BWindow::Quit();    
}


class App : public BApplication {
public:
    App();

private:
    virtual void    ReadyToRun();    
};


App::App() : BApplication("application/x-vnd.dw-TestApp")
{
}


void
App::ReadyToRun()
{
    SimpleWindow *window = new SimpleWindow(BRect(0, 0, 200, 120));
    window->CenterOnScreen();    // Haiku Only
    window->Show();
}

    
int
main(void)
{
    App app;
    app.Run();
    return 0;
}
