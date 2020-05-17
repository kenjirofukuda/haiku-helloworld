#ifndef SIMPLE_VIEW_H
#define SIMPLE_VIEW_H
#include <View.h>

class ButtonView : public BView {
public:
	ButtonView(BRect frame, const char* name,
			   uint32 resizeMask, uint32 flags);

};

#endif // SIMPLE_VIEW_H
