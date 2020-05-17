#ifndef SIMPLE_WINDOW_H
#define SIMPLE_WINDOW_H

#include "RegularWindow.h"

class SimpleWindow : public RegularWindow {
public:
	SimpleWindow(BRect frame);

private:
	bool QuitRequested() override;
};

#endif // SIMPLE_WINDOW_H
