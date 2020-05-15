#ifndef REGULAR_WINDOW_H
#define REGULAR_WINDOW_H
#include <interface/Window.h>

extern const char* kSender;

class RegularWindow : public BWindow
{
public:
    RegularWindow(BRect frame, const char* title, window_type type, uint32 flags, uint32 quitMsg);
  
    void Quit() override; 

    void InitContent(BView* content);
    void InitContent(BMenuBar* menuBar, BView* content);
private:
    uint32 fQuitMsg; 
};

#endif // REGULAR_WINDOW_H
