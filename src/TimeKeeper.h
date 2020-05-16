#ifndef TIME_KEEPER_H
#define TIME_KEEPER_H

#include <support/Locker.h>
#include <support/SupportDefs.h>

class BHandler;
class BMessage;
class BList;
struct TaskInfo;

typedef struct ScheduleInfo {
    BHandler* client;
    BMessage* message;
    int32 period;
    uint32 first_time;
} ScheduleInfo;


class TimeKeeper {
public:
    TimeKeeper();
    ~TimeKeeper();

    status_t InsertSchedule(const ScheduleInfo& schedule);
    status_t RemoveSchedule(const BHandler* client, uint32 code);

private:
    void CheckTask();

    static int32 WatchClients(void* data);
    static int CompareTasks(const void* taskA, const void* taskB);

    status_t ExecuteHeadTask();
    status_t AddTask(TaskInfo* task);
    int32 FindTask(const BHandler* client, uint32 code);

private:
    thread_id fWatcher;
    bigtime_t fWatcherPeriod;
    BList*    fTaskList;
    BLocker   fLoker;
};

#endif // TIME_KEEPER_H
// vim: set ai ts=4 sw=4 fenc=utf-8 ff=unix :
