#include "TimedView.h"

#include <support/Debug.h>

#include "TimeKeeper.h"
#include "Utils.h"

TimedView::TimedView(BRect frame, const char* title,
					 uint32 resizeMask, uint32 flags, TimeKeeper* timeKeeper)

	: BView(frame, title, resizeMask, flags)
{
	ASSERT(timeKeeper != nullptr);
	fTimeKeeper = timeKeeper;
}


TimedView::~TimedView()
{
}


status_t
TimedView::AddSchedule(const ScheduleInfo& schedule)
{
	return fTimeKeeper->InsertSchedule(schedule);
}


status_t
TimedView::RemoveSchedule(uint32 code)
{
	return fTimeKeeper->RemoveSchedule(this, code);
}


// vim: set ai ts=4 sw=4 fenc=utf-8 ff=unix :
