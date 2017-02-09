#include "PE_TaskScheduler.h"


/*
PE_TaskScheduler::PE_TaskScheduler()
{
}

PE_TaskScheduler::~PE_TaskScheduler()
{
}
*/

unsigned long PE_TaskScheduler::ID_counter;
std::priority_queue<PE_ScheduledTask*>  PE_TaskScheduler::scheduled_tasks;

void PE_TaskScheduler::Init() {
	ID_counter = 0;
}

const PE_ScheduledTask& PE_TaskScheduler::nextTask() { return *scheduled_tasks.top(); }
std::priority_queue<PE_ScheduledTask*>& PE_TaskScheduler::queuedTasks() { return scheduled_tasks; }
const PE_ScheduledTask* PE_TaskScheduler::getTaskbyOrder(int numtask) { return scheduled_tasks.top(); }
const PE_ScheduledTask* PE_TaskScheduler::getTaskbyID(unsigned long id) { return scheduled_tasks.top(); }
const PE_ScheduledTask& PE_TaskScheduler::lastTask() { return *scheduled_tasks.top(); }
bool PE_TaskScheduler::cancelTaskbyID(unsigned long ID) { return false; }
bool PE_TaskScheduler::cancelTaskbyNumber(unsigned long position) { return false; }
void PE_TaskScheduler::cancelAll() {}