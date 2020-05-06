#include <Window.h>
#include <Application.h>

class SimpleWindow : public BWindow {
public:
                    SimpleWindow(BRect frame);
    // virtual bool    QuitRequested();    
};


SimpleWindow::SimpleWindow(BRect frame)
    : BWindow(frame, "Simple Window",
              B_TITLED_WINDOW,
              B_NOT_RESIZABLE | B_NOT_ZOOMABLE) 
{    
}


// bool
// SimpleWindow::QuitRequested()
// {
//     be_app->PostMessage(B_QUIT_REQUESTED);
//     return true;
// }


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
    SimpleWindow *window = new SimpleWindow(BRect(0, 0, 640, 480));
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
