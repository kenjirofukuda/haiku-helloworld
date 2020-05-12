#ifndef _SIMPLE_WINDOW_H_
#define _SIMPLE_WINDOW_H_

#include "RegularWindow.h"

class SimpleWindow : public RegularWindow
{
public:
    SimpleWindow(BRect frame);

private:    
    bool QuitRequested() override;
};

#endif // _SIMPLE_WINDOW_H_
