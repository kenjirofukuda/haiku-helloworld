#ifndef _SIMPLE_WINDOW_H_
#define _SIMPLE_WINDOW_H_
#include <interface/Window.h>

class SimpleWindow : public BWindow
{
public:
    SimpleWindow(BRect frame);
    void Quit() override; 
    bool QuitRequested() override;

    void InitContent(BMenuBar* menuBar, BView* content);
};

#endif // _SIMPLE_WINDOW_H_
