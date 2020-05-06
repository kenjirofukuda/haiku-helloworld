#include <Window.h>
#include <Application.h>

class SimpleView : public BView 
{
public:
    SimpleView(BRect frame, const char *name,
               uint32 resizeMask, uint32 flags);
    ~SimpleView();

private:
    void Draw(BRect updateRect);    
};

    
SimpleView::SimpleView(BRect frame, const char *name,
               uint32 resizeMask, uint32 flags)
    : BView(frame, name, resizeMask, flags)
{
    this->SetViewColor(0xDD, 0xDD, 0xDD);
}


SimpleView::~SimpleView()
{
}


void
SimpleView::Draw(BRect updateRect)
{
    this->DrawString("This is the by first app", BPoint(10, 10));
    this->SetHighColor(255, 0, 0);
    this->FillRect(BRect(110, 30, 140, 60));
}


class SimpleWindow : public BWindow
{
public:
    SimpleWindow(BRect frame);
    // virtual bool    QuitRequested();
    void Quit();
};


SimpleWindow::SimpleWindow(BRect frame)
    : BWindow(frame, "Simple Window",
              B_TITLED_WINDOW,
              B_NOT_RESIZABLE | B_NOT_ZOOMABLE) 
{
    SimpleView* view;

    view = new SimpleView(this->Bounds(), "content",
                          B_FOLLOW_ALL_SIDES, B_WILL_DRAW);
    this->AddChild(view);    
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
