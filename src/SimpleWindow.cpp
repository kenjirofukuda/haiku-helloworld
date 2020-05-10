#include <Window.h>
#include <Application.h>

const int32 kRectArea = 1;
const int32 kCircleArea = 2;

const BRect kHotSpotRect(110, 30, 140, 60);


class KGCircle
{
public:
    KGCircle(BPoint center, float radius);

    bool Contains(BPoint where) const;
    void DrawOn(BView* view) const;

private:
    BPoint fCenter;
    float fRadius;
};


KGCircle kHotSpotCircle(BPoint(30, 45), 15);

KGCircle::KGCircle(BPoint center, float radius)
    : fCenter(center), fRadius(radius)
{
}


bool
KGCircle::Contains(BPoint where) const
{
    float distance;

    distance = sqrt(pow(where.x - fCenter.x, 2) +
		    pow(where.y - fCenter.y, 2));    
    return distance <= fRadius;
}


void
KGCircle::DrawOn(BView* view) const
{
    view->FillEllipse(fCenter, fRadius, fRadius);
}

class SimpleView : public BView 
{
public:
    SimpleView(BRect frame, const char *name,
               uint32 resizeMask, uint32 flags);
    ~SimpleView();

private:
    void Draw(BRect updateRect);
    void MouseDown(BPoint where);
    void HotSpotAction(bool currInside, bool prevInside, int32 hotSpot);
    int32 FindHotSpot(BPoint where);
    void HotSpotResult(int32 hotSpot);
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
    SimpleView::Draw(BRect /* updateRect */)
{
    DrawString("This is the by 3rd app.", BPoint(10, 10));
    SetHighColor(255, 0, 0);
    FillRect(kHotSpotRect);
    kHotSpotCircle.DrawOn(this);
}

void
SimpleView::MouseDown(BPoint where)
{
    uint32 buttons = 0;
    int32 intReply = 0;
    bool currInside = true;
    bool prevInside = false;
    
    this->Window()->CurrentMessage()->FindInt32("buttons", &intReply);
    buttons = intReply;
    if (buttons != B_PRIMARY_MOUSE_BUTTON)
	return;

    int32 hotSpot;
    hotSpot = FindHotSpot(where);
    if (hotSpot < 0)
	return;
    this->HotSpotAction(currInside, prevInside, hotSpot);

    while (buttons & B_PRIMARY_MOUSE_BUTTON) {
	::snooze(20 * 1000);
	GetMouse(&where, &buttons, true);
	prevInside = currInside;
	currInside = FindHotSpot(where) == hotSpot;
	HotSpotAction(currInside, prevInside, hotSpot);	
    }
    if (currInside)
	HotSpotResult(hotSpot);
}


int32
SimpleView::FindHotSpot(BPoint where)
{
    if (kHotSpotRect.Contains(where))
	return kRectArea;
    if (kHotSpotCircle.Contains(where))
	return kCircleArea;
    return -1;
}


void
SimpleView::HotSpotAction(bool currInside, bool prevInside, int32 hotSpot)
{
    if (currInside == prevInside)
	return;
    rgb_color orgColor = HighColor();
    if (currInside)
	SetHighColor(0, 255, 0);
    else
	SetHighColor(255, 0, 0);
    if (hotSpot == kRectArea)
	FillRect(kHotSpotRect);
    if (hotSpot == kCircleArea)
	kHotSpotCircle.DrawOn(this);    
    SetHighColor(orgColor);
}


void
SimpleView::HotSpotResult(int32 hotSpot)
{
    BMessage message;

    message.what = 0;
    if (hotSpot == kRectArea)
	message.what = B_QUIT_REQUESTED;

    if (hotSpot == kCircleArea) {
	message.what = B_MINIMIZE;
	message.AddInt32("when", ::real_time_clock());
	message.AddBool("minimize", true);
    }
    if (hotSpot > 0)
	Window()->PostMessage(&message, Window());
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
