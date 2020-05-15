#ifndef SIMPLE_APP_H
#define SIMPLE_APP_H
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

#endif // SIMPLE_APP_H
