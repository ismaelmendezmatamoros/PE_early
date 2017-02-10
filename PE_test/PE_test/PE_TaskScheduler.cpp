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
std::mutex PE_TaskScheduler::queue_mutex;
std::timed_mutex PE_TaskScheduler::trigger_mutex;
std::thread* PE_TaskScheduler::loop_thread;
std::atomic<bool>  PE_TaskScheduler::false_awakening;
std::lock_guard<std::timed_mutex> PE_TaskScheduler::time_expired(trigger_mutex);
//const  MILISECONDS_TIPE PE_TaskScheduler::tics_per_milisecond = (CLOCKS_PER_SEC / 1000);

bool PE_TaskScheduler::exit;

void PE_TaskScheduler::Init() {
	ID_counter = 0;
	exit = false;
	false_awakening = false;
	std::atexit([]() {PE_TaskScheduler::stopExecution(); });
	loop_thread = new std::thread(loopCycle);
}

void PE_TaskScheduler::loopCycle() {
	 
	bool empty = false;
	while (!exit) { 
		cycle();		
		{
			std::lock_guard<std::mutex> lock(queue_mutex);
			empty = scheduled_tasks.empty();
		}
		if (empty)
			trigger_mutex.lock();
		else
			trigger_mutex.try_lock_for(std::chrono::milliseconds(scheduled_tasks.top()->getDelay()));
	}	
}

void PE_TaskScheduler::triggerNextTask(PE_ScheduledTask* task) {
		auto callable = std::mem_fn(&PE_ScheduledTask::trigger);
		callable(task);
		task->setRepetitions(task->getRepetitions() - (1 * (task->getRepetitions() > 0)) );
		if (task->getRepetitions() == 0)
			delete task;
		else {
			task->setTriggerTime(makeTriggerTime(std::chrono::milliseconds(clock()), task->getDelay()));
			addTask(task);
		}
}

void PE_TaskScheduler::cycle() { 
	std::lock_guard<std::mutex> lock(queue_mutex); 
	if (scheduled_tasks.empty()) 
		return;	
	if (false_awakening) {
		false_awakening = false;
		return;
	}
	else {
		std::thread(triggerNextTask, scheduled_tasks.top()).detach();
		scheduled_tasks.pop();
	}
}

void PE_TaskScheduler::stopExecution() {
	 
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
/*
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
}*/