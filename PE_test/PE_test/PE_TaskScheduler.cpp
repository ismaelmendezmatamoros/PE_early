#include "PE_TaskScheduler.h"


/*
PE_TaskScheduler::PE_TaskScheduler()
{
}

PE_TaskScheduler::~PE_TaskScheduler()
{
}
*/

ID_COUNTER_TYPE PE_TaskScheduler::ID_counter;
std::priority_queue<TASKS_QUEUED_TYPE>  PE_TaskScheduler::scheduled_tasks;
std::mutex PE_TaskScheduler::read_queue_mutex;
std::mutex PE_TaskScheduler::write_queue_mutex;
std::timed_mutex PE_TaskScheduler::trigger_mutex;
std::thread* PE_TaskScheduler::loop_thread;
std::atomic<bool>  PE_TaskScheduler::false_awakening;
//const  MILISECONDS_TIPE PE_TaskScheduler::tics_per_milisecond = (CLOCKS_PER_SEC / 1000);

bool PE_TaskScheduler::exit;

void PE_TaskScheduler::Init() {
	ID_counter = 0;
	exit = false;
	false_awakening = false;
	std::atexit([]() {PE_TaskScheduler::stopExecution(); });
	loop_thread = new std::thread(loopCycle);
//	ID_counter++;//std::cout << "inited  " << std::endl;
}

void PE_TaskScheduler::loopCycle() {
	std::cout << "launched  " << std::endl;
	bool empty;
	while (!exit) {	
		if(scheduled_tasks.size()>0)
			std::cout << "delay " << (int)scheduled_tasks.top()->getDelay() << std::endl;
																							//checks if the loop should terminate
		write_queue_mutex.lock();																		//losck to get emptiness safely
			empty = scheduled_tasks.size() == 0;
		write_queue_mutex.unlock();
		trigger_mutex.lock();//?
		if (!empty) {																						//if no empty locks until next event otherwise locks until something is inserted and hooked using a false awakening. See addFunction function 
			trigger_mutex.try_lock_for(std::chrono::milliseconds(scheduled_tasks.top()->getDelay()));
			std::cout << "duration " << (int)scheduled_tasks.top()->getDelay() << std::endl;
		}
		else
			trigger_mutex.lock();	
		
		write_queue_mutex.lock();
			if (scheduled_tasks.size() > 0) {
				//std::cout << "delay " << scheduled_tasks.top()->getDelay() << std::endl;
				if (false_awakening) {																	//false awakening: something new has been pushed int the queue and it's on the next triggered event. the lock time must be rewriten.
					false_awakening = false;
					std::cout << "awakened" << std::endl;
					trigger_mutex.unlock();
					write_queue_mutex.unlock();////********									
					continue;
				}
				auto callable = std::mem_fn(&PE_ScheduledTask::trigger);
				std::cout << "executi" << std::endl;
				std::thread(callable, scheduled_tasks.top()).detach();
				scheduled_tasks.pop();	
			}
		write_queue_mutex.unlock();		
	}
	
}

void PE_TaskScheduler::stopExecution() {
	std::cout << "exit  " << std::endl;
	exit = true;
	loop_thread->join();
}

const MILISECONDS_TIPE PE_TaskScheduler::makeTriggerTime(MILISECONDS_TIPE time, unsigned int delay) { return time  + std::chrono::milliseconds(delay) ; }
const PE_ScheduledTask& PE_TaskScheduler::nextTask() { return *scheduled_tasks.top(); }
std::priority_queue<PE_ScheduledTask*>& PE_TaskScheduler::queuedTasks() { return scheduled_tasks; }
const PE_ScheduledTask* PE_TaskScheduler::getTaskbyOrder(int numtask) { return scheduled_tasks.top(); }
const PE_ScheduledTask* PE_TaskScheduler::getTaskbyID(ID_TYPE id) { return scheduled_tasks.top(); }
const PE_ScheduledTask& PE_TaskScheduler::lastTask() { return *scheduled_tasks.top(); }
bool PE_TaskScheduler::cancelTaskbyID(ID_TYPE id) { return false; }
bool PE_TaskScheduler::cancelTaskbyNumber(unsigned long position) { return false; }
void PE_TaskScheduler::cancelAll() {}
void PE_TaskScheduler::emplaceQueue(TASKS_QUEUED_TYPE task) {
	write_queue_mutex.lock();
	read_queue_mutex.lock();
	scheduled_tasks.emplace(task);
	read_queue_mutex.unlock();
	write_queue_mutex.unlock();
}

void PE_TaskScheduler::pushQueue(TASKS_QUEUED_TYPE task) {
	write_queue_mutex.lock();
	read_queue_mutex.lock();
	scheduled_tasks.push(task);
	read_queue_mutex.unlock();
	write_queue_mutex.unlock();
}