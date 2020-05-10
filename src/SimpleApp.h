#ifndef _SIMPLE_APP_H_
#define _SIMPLE_APP_H_
#include <app/Application.h>

class BMenuBar;

class SimpleApp : public BApplication {
public:
    SimpleApp();

private:
  void ReadyToRun() override;
  void AboutRequested() override;
  
  BMenuBar* MakeMenuBar();
};

#endif // _SIMPLE_APP_H_
