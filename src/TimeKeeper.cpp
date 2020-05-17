#include "TimeKeeper.h"
#include "Utils.h"

#include <support/Debug.h>
#include <app/Handler.h>
#include <support/List.h>
#include <support/Autolock.h>

typedef struct TaskInfo {
	uint32 exec_time;
	ScheduleInfo schedule;
} TaskInfo;


TimeKeeper::TimeKeeper()
{
	fWatcher = -1;
	fTaskList = new BList();
	fWatchPeriod = 500 * 1000;
}

TimeKeeper::~TimeKeeper()
{
	BAutolock lock(fLocker);

	if (fWatcher >= 0)
		::kill_thread(fWatcher);

	while (! fTaskList->IsEmpty()) {
		TaskInfo* task = (TaskInfo*) fTaskList->RemoveItem(0);
		delete task->schedule.message;
		delete task;
	}
	delete fTaskList;
}


status_t
TimeKeeper::InsertSchedule(const ScheduleInfo& schedule)
{
	int32 index = FindTask(schedule.client, schedule.message->what);
	if (index > 0)
		fTaskList->RemoveItem(index);

	TaskInfo* newTask = new TaskInfo();
	newTask->exec_time = schedule.first_time;
	newTask->schedule = schedule;
	status_t sts = AddTask(newTask);
	if (sts != B_OK)
		goto bail;

	if (fWatcher < 0)
		fWatcher = ::spawn_thread(WatchClients, "watcher", B_NORMAL_PRIORITY,
								  this);
	sts = ::resume_thread(fWatcher);
	if (sts != B_OK)
		goto bail;

	return B_OK;
bail:
	::Error("TimeKeeper::InsertSchedule", sts);
	return sts;
}


status_t
TimeKeeper::RemoveSchedule(const BHandler* client, uint32 code)
{
	TaskInfo* task = (TaskInfo*)fTaskList->RemoveItem(FindTask(client,
															   code));
	status_t sts = B_OK;
	if (task == nullptr) {
		sts = B_ERROR;
		goto bail;
	}
	delete task->schedule.message;
	delete task;

	if (fTaskList->IsEmpty())
		::suspend_thread(fWatcher);
	return B_OK;
bail:
	::Error("TimeKeeper::RemoveSchedule", sts);
	return sts;
}


void
TimeKeeper::CheckTask()
{
	BAutolock lock(fLocker);
	while (! fTaskList->IsEmpty()) {
		TaskInfo* headTask = (TaskInfo*) fTaskList->FirstItem();
		if (headTask->exec_time > ::real_time_clock())
			break;
		ExecuteHeadTask();
	}
	if (fTaskList->IsEmpty())
		::suspend_thread(fWatcher);

}


int32
TimeKeeper::WatchClients(void* data)
{
	TimeKeeper* obj = (TimeKeeper*) data;
	while (true) {
		::snooze(obj->fWatchPeriod);
		obj->CheckTask();
	}
	return 0;
}


int
TimeKeeper::CompareTasks(const void* taskA, const void* taskB)
{
	int result = 0;
	uint32 timeA = (*(TaskInfo**) taskA)->exec_time;
	uint32 timeB = (*(TaskInfo**) taskB)->exec_time;
	if (timeA < timeB)
		result = -1;
	else if (timeA > timeB)
		result = 1;
	return result;
}


status_t
TimeKeeper::ExecuteHeadTask()
{
	ASSERT(! fTaskList->IsEmpty());
	TaskInfo* task = (TaskInfo*) fTaskList->FirstItem();
	BLooper* target = task->schedule.client->Looper();
	ASSERT(target != nullptr);
	ASSERT(task->exec_time <= ::real_time_clock());
	status_t sts = target->PostMessage(task->schedule.message,
									   task->schedule.client);
	if (sts != B_OK)
		goto bail;
	fTaskList->RemoveItem(task);

	if (task->schedule.period > 0) {
		task->exec_time += task->schedule.period;
		sts = AddTask(task);
		if (sts != B_OK)
			goto bail;
	}

	return B_OK;
bail:
	::Error("TimeKeeper::ExecuteHeadTask", sts);
	return sts;
}


status_t
TimeKeeper::AddTask(TaskInfo* task)
{
	fTaskList->AddItem(task, 0);
	fTaskList->SortItems(CompareTasks);
	return B_OK;
}


int32
TimeKeeper::FindTask(const BHandler* client, uint32 code)
{
	int32 index = -1;
	for (int32 i = 0, n = fTaskList->CountItems(); i < n; ++i) {
		TaskInfo* task = (TaskInfo*) fTaskList->ItemAt(i);
		if (task->schedule.client == client
				&& task->schedule.message->what == code) {
			index = i;
			break;
		}
	}
	return index;
}



// vim: set ai ts=4 sw=4 fenc=utf-8 ff=unix :
