#pragma once
#include"PE_ScheduledFunction.h"
#include<queue>
#include<time.h>

#define _CLOCK_TYPE clock_t

class PE_TaskScheduler
{
	static unsigned long ID_counter;
	static std::priority_queue<PE_ScheduledTask*> scheduled_tasks;
public:
	//PE_TaskScheduler();
	static void Init();

	template<typename functype, typename... Args>
		static void addTask(int delay_, int repetitions, functype func, Args... args);
	
	static const PE_ScheduledTask& nextTask();
	static std::priority_queue<PE_ScheduledTask*>& queuedTasks();
	static const PE_ScheduledTask* getTaskbyOrder(int numtask);
	static const PE_ScheduledTask* getTaskbyID(unsigned long id);
	static const PE_ScheduledTask& lastTask();
	static bool cancelTaskbyID(unsigned long ID);
	static bool cancelTaskbyNumber(unsigned long position);
	static void cancelAll();
	//static bool	
	//~PE_TaskScheduler();

	template<typename functype, typename... Args>
	static void PE_TaskScheduler::addTask(int delay_, int repetitions, functype func, Args... args) {

	}

};

