#include "TimeKeeper.h"

#include <support/Debug.h>
#include <app/Handler.h>
#include <support/List.h>

typedef struct TaskInfo {
    uint32 exec_time;
    ScheduleInfo schedule;
} TaskInfo;


TimeKeeper::TimeKeeper()
{
}

TimeKeeper::~TimeKeeper()
{
}


status_t TimeKeeper::InsertSchedule(const ScheduleInfo& schedule)
{
    return B_OK;
}


status_t TimeKeeper::RemoveSchedule(const BHandler* client, uint32 code)
{
    return B_OK;
}


void TimeKeeper::CheckTask()
{
}


int32
TimeKeeper::WatchClients(void* data)
{
    return 0;
}


int
TimeKeeper::CompareTasks(const void* taskA, const void* taskB)
{
    return 0;
}


status_t
TimeKeeper::ExecuteHeadTask()
{
    return B_OK;
}


status_t
TimeKeeper::AddTask(TaskInfo* task)
{
    return B_OK;
}


int32
TimeKeeper::FindTask(const BHandler* client, uint32 code)
{
    return 0;
}



// vim: set ai ts=4 sw=4 fenc=utf-8 ff=unix :
