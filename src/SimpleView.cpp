#include "SimpleView.h"

#include <Window.h>
#include "KGCircle.h"

const int32 kRectArea = 1;
const int32 kCircleArea = 2;

const BRect kHotSpotRect(110, 30, 140, 60);
KGCircle kHotSpotCircle(BPoint(30, 45), 15);

SimpleView::SimpleView(BRect frame, const char* name,
					   uint32 resizeMask, uint32 flags)
	: BView(frame, name, resizeMask, flags)
{
	SetViewColor(0xDD, 0xDD, 0xDD);
}


void
SimpleView::Draw(BRect /* updateRect */)
{
	DrawString("This is the by 3rd app.", BPoint(10, 10));
	SetHighColor(255, 0, 0);
	FillRect(kHotSpotRect);
	kHotSpotCircle.DrawOn(this);
}


void
SimpleView::MouseDown(BPoint where)
{
	uint32 buttons = 0;
	int32 intReply = 0;
	bool currInside = true;
	bool prevInside = false;

	this->Window()->CurrentMessage()->FindInt32("buttons", &intReply);
	buttons = intReply;
	if (buttons != B_PRIMARY_MOUSE_BUTTON)
		return;

	int32 hotSpot;
	hotSpot = FindHotSpot(where);
	if (hotSpot < 0)
		return;
	this->HotSpotAction(currInside, prevInside, hotSpot);

	while (buttons & B_PRIMARY_MOUSE_BUTTON) {
		::snooze(20 * 1000);
		GetMouse(&where, &buttons, true);
		prevInside = currInside;
		currInside = FindHotSpot(where) == hotSpot;
		HotSpotAction(currInside, prevInside, hotSpot);
	}
	if (currInside)
		HotSpotResult(hotSpot);
}


int32
SimpleView::FindHotSpot(BPoint where)
{
	if (kHotSpotRect.Contains(where))
		return kRectArea;
	if (kHotSpotCircle.Contains(where))
		return kCircleArea;
	return -1;
}


void
SimpleView::HotSpotAction(bool currInside, bool prevInside,
						  int32 hotSpot)
{
	if (currInside == prevInside)
		return;
	rgb_color orgColor = HighColor();
	if (currInside)
		SetHighColor(0, 255, 0);
	else
		SetHighColor(255, 0, 0);
	if (hotSpot == kRectArea)
		FillRect(kHotSpotRect);
	if (hotSpot == kCircleArea)
		kHotSpotCircle.DrawOn(this);
	SetHighColor(orgColor);
}


void
SimpleView::HotSpotResult(int32 hotSpot)
{
	BMessage message;

	message.what = 0;
	if (hotSpot == kRectArea)
		message.what = B_QUIT_REQUESTED;

	if (hotSpot == kCircleArea) {
		message.what = B_MINIMIZE;
		message.AddInt32("when", ::real_time_clock());
		message.AddBool("minimize", true);
	}
	if (hotSpot > 0)
		Window()->PostMessage(&message, Window());
}
