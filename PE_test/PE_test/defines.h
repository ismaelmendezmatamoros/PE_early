#pragma once



#define MILISECONDS_TIPE clock_t

#define ID_COUNTER_TYPE std::atomic<ID_TYPE>
#define ID_TYPE unsigned long

#define TASK_LAMBDA void()
#define TASKS_QUEUED_TYPE PE_ScheduledTask*
