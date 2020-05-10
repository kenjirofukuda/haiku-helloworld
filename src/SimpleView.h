#ifndef _SIMPLE_VIEW_H_
#define _SIMPLE_VIEW_H_
#include <interface/View.h>

class SimpleView : public BView 
{
public:
    SimpleView(BRect frame, const char *name,
               uint32 resizeMask, uint32 flags);

private:
    void Draw(BRect updateRect) override;
    void MouseDown(BPoint where) override;

private:
    void HotSpotAction(bool currInside, bool prevInside, int32 hotSpot);
    int32 FindHotSpot(BPoint where);
    void HotSpotResult(int32 hotSpot);
};

#endif // _SIMPLE_VIEW_H_
