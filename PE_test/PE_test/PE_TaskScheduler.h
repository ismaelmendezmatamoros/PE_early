#pragma once
#include"PE_ScheduledFunction.h"
#include<queue>
#include<time.h>
#include<mutex>
#include<thread>
#include<iostream>
#include<chrono>
#include "defines.h"




class PE_TaskScheduler
{
	//const static MILISECONDS_TIPE tics_per_milisecond;
	static ID_COUNTER_TYPE ID_counter;
	static std::priority_queue<TASKS_QUEUED_TYPE> scheduled_tasks;
	static std::mutex read_queue_mutex;
	static std::mutex queue_mutex;
	static std::timed_mutex trigger_mutex;
	static std::thread* loop_thread;
	static std::atomic<bool> false_awakening;
	static bool exit;

public:
	//PE_TaskScheduler();
	static void Init();

	//template<typename functype, typename... Args>
		//static void addTask(int delay_, int repetitions, functype func, Args... args);
	
	static const MILISECONDS_TIPE makeTriggerTime(MILISECONDS_TIPE x, unsigned int delay = 0);
	static const PE_ScheduledTask& nextTask();
	static std::priority_queue<TASKS_QUEUED_TYPE>& queuedTasks();
	static const PE_ScheduledTask* getTaskbyOrder(int numtask);
	static const PE_ScheduledTask* getTaskbyID(ID_TYPE id);
	static const PE_ScheduledTask& lastTask();
	static bool cancelTaskbyID(ID_TYPE id);
	static bool cancelTaskbyNumber(unsigned long position);
	static void cancelAll();
	static void loopCycle();
	static void cycle();
	static void stopExecution();
	//static bool	
	//~PE_TaskScheduler();
	template<typename functype, typename... Args>
	//ID_TYPE id, int delay_, MILISECONDS_TIPE time, int repetitions, functype func, Args... args): PE_ScheduledTask(id, delay_, time, repetitions
	static void addTask(unsigned int delay_, int repetitions, functype func, Args... args) {
		 
		std::lock_guard<std::mutex> lock(queue_mutex);
		std::cout << "inserting" << std::endl;
			unsigned long id = ID_counter++;
			
			PE_ScheduledFunction* task_pointer = new PE_ScheduledFunction(id, delay_, makeTriggerTime(std::chrono::milliseconds	(clock()), delay_), repetitions, func, args...);
			if ( (scheduled_tasks.size() == 0) || ( task_pointer->getTriggerTime() < scheduled_tasks.top()->getTriggerTime() )  ){						//if its the firs element on the que or if it's the next one to be triggered needs to wake up the loopCycle and make it update the next wake up time
				false_awakening = true;
				scheduled_tasks.emplace(task_pointer);
				//trigger_mutex.unlock();																													//awakens the loopCycle thread and makes it process the new element through a false awakening
			}else
				scheduled_tasks.push(task_pointer);
			std::cout << "exit inserting" << std::endl;
	}

private:
	static void emplaceQueue(TASKS_QUEUED_TYPE task_);
	static void pushQueue(TASKS_QUEUED_TYPE task_);
};


