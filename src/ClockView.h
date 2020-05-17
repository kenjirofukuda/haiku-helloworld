#ifndef   CLOCK_VIEW_H
#define CLOCK_VIEW_H

#include "TimeKeeper.h"
#include "TimedView.h"

#include <Bitmap.h>
#include <time.h>

class TimeKeeper;

class ClockView : public TimedView {
public:
	ClockView(BRect frame, uint32 resizeMask, TimeKeeper* timeKeeper);
	virtual ~ClockView();

	void AttachedToWindow() override;
	void DetachedFromWindow() override;
	void Draw(BRect updateRect) override;
	void DrawTime(BView* view);

	void MessageReceived(BMessage* message) override;
	void UpdateTime();

private:
	bool fUseOffscreen;
	tm fTime;
	BBitmap* fOffscreen;
};

#endif // CLOCK_VIEW_H
// vim: set ai ts=4 sw=4 fenc=utf-8 ff=unix :
