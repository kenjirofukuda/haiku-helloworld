#include <Window.h>
#include <Application.h>

class SimpleWindow : public BWindow {
public:
    SimpleWindow(BRect frame);
    // virtual bool    QuitRequested();
    void Quit();
    void Show();    
};


SimpleWindow::SimpleWindow(BRect frame)
    : BWindow(frame, "Simple Window",
              B_TITLED_WINDOW,
              B_NOT_RESIZABLE | B_NOT_ZOOMABLE) 
{
    BView* view;

    view = new BView(this->Bounds(), "content", B_FOLLOW_ALL_SIDES, 0);
    this->AddChild(view);    
}


void
SimpleWindow::Show()
{
    BView* view = this->FindView("content");
    rgb_color currColor = view->HighColor();

    BWindow::Show();
    ::snooze(40 * 1000);
    
    this->Lock();
    view->SetHighColor(0xDD, 0xDD, 0xDD);
    view->FillRect(view->Frame());
    view->SetHighColor(currColor);
    view->DrawString("This is the by first app", BPoint(10, 10));
    view->SetHighColor(255, 0, 0);
    view->FillRect(BRect(110, 30, 140, 60));
    this->Unlock();
    this->Flush();    
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
