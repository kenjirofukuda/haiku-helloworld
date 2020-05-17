#ifndef   TIMED_VIEW_H
#define TIMED_VIEW_H

#include <View.h>

class TimeKeeper;
struct ScheduleInfo;

class TimedView : public BView {
public:
	TimedView(BRect frame, const char* title,
			  uint32 resizeMask, uint32 flags, TimeKeeper* timeKeeper);
	virtual ~TimedView();

protected:
	status_t AddSchedule(const ScheduleInfo& schedule);
	status_t RemoveSchedule(uint32 code);

private:
	TimeKeeper* fTimeKeeper;
};

#endif // TIMED_VIEW_H
// vim: set ai ts=4 sw=4 fenc=utf-8 ff=unix :
