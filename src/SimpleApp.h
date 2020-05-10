#ifndef _SIMPLE_APP_H_
#define _SIMPLE_APP_H_
#include <app/Application.h>

class SimpleApp : public BApplication {
public:
    SimpleApp();

private:
    virtual void    ReadyToRun();    
};

#endif // _SIMPLE_APP_H_
