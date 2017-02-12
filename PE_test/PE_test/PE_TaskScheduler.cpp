#include "PE_TaskScheduler.h"

ID_COUNTER_TYPE PE_TaskScheduler::ID_counter;
std::priority_queue<TASKS_QUEUED_TYPE, std::vector<TASKS_QUEUED_TYPE>, cmpQueuedPointers<TASKS_QUEUED_TYPE>>  PE_TaskScheduler::scheduled_tasks;
std::mutex PE_TaskScheduler::active_tasks_mutex;
std::mutex PE_TaskScheduler::queue_mutex;
std::timed_mutex PE_TaskScheduler::trigger_mutex;
std::mutex PE_TaskScheduler::inactive_tasks_mutex;
std::thread* PE_TaskScheduler::loop_thread;
std::atomic<bool>  PE_TaskScheduler::false_awakening;
std::lock_guard<std::timed_mutex> PE_TaskScheduler::time_expired(trigger_mutex);
std::map<std::thread::id, ACTIVE_TASK_MAPPED_ELEMENT> PE_TaskScheduler::active_tasks;
std::vector<std::thread*> PE_TaskScheduler::inactive_tasks;
bool PE_TaskScheduler::exit;


void PE_TaskScheduler::Init() {
	ID_counter = 0;
	exit = false;
	false_awakening = false;
	loop_thread = new std::thread(loopCycle);
	std::atexit([]() {PE_TaskScheduler::stopExecution(); });
	
}

void PE_TaskScheduler::removeIdleThreads() {  /////////////////////////////////////////////
	if (inactive_tasks.empty())
		return;
	for (auto thread = 0; thread < inactive_tasks.size(); thread++ ) {
		auto b = inactive_tasks[thread]->get_id();
		inactive_tasks[thread]->join();
		doSafely([&]() {active_tasks.erase(b); }, active_tasks_mutex);
		delete inactive_tasks[thread];
	}
	doSafely([&]() { inactive_tasks.clear(); }, inactive_tasks_mutex);
}

void PE_TaskScheduler::loopCycle() {	 
	bool empty = false;
	while (!exit) { 		
		removeIdleThreads();
		cycle();		
		{
			std::lock_guard<std::mutex> lock(queue_mutex);
			empty = scheduled_tasks.empty();
		}
		if (empty) 
			trigger_mutex.lock();
		else
			trigger_mutex.try_lock_until(scheduled_tasks.top()->getTriggerTime() );
	}	
}

void PE_TaskScheduler::triggerNextTask(PE_ScheduledTask* task ) {
	auto callable = std::mem_fn(&PE_ScheduledTask::trigger);
	callable(task);
	task->setRepetitions(task->getRepetitions() - (1 * (task->getRepetitions() > 0)));
	if (task->getRepetitions() == 0)
		delete task;
	else {
		task->setTriggerTime(makeTriggerTime(std::chrono::system_clock::now(), task->getDelay()));
		addTask(task);
	}
	auto j = std::this_thread::get_id();
	doSafely([&]() { inactive_tasks.push_back(active_tasks[j].thread); }, inactive_tasks_mutex);
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
		std::thread* task;
		auto top = scheduled_tasks.top();
		scheduled_tasks.pop();
		task = new  std::thread(triggerNextTask, top);
		ACTIVE_TASK_MAPPED_ELEMENT active_task(top, task);
		doSafely([&]() { active_tasks[task->get_id()] = active_task; }, active_tasks_mutex);
		
	}
}

void PE_TaskScheduler::stopExecution() {
	exit = true;
	trigger_mutex.unlock();
	loop_thread->join();
	removeIdleThreads();
	for (; !scheduled_tasks.empty(); scheduled_tasks.pop())
		delete scheduled_tasks.top();
	for (auto element = active_tasks.begin(); element != active_tasks.end(); (element++)) {
		if( (element)->second.thread->joinable() )
			(element)->second.thread->join();
		delete (element)->second.thread;
	}
	delete loop_thread;
}

template<typename T, typename... Args>
static void PE_TaskScheduler::doSafely(T func, std::mutex& mut, Args... args) {
	std::lock_guard<std::mutex> lock(mut);
	func(args...);
}

const MILISECONDS_TIPE PE_TaskScheduler::makeTriggerTime(MILISECONDS_TIPE time, unsigned int delay) { return time  + std::chrono::milliseconds(delay) ; }
const PE_ScheduledTask& PE_TaskScheduler::nextTask() { return *scheduled_tasks.top(); }
std::priority_queue<TASKS_QUEUED_TYPE, std::vector<TASKS_QUEUED_TYPE>, cmpQueuedPointers<TASKS_QUEUED_TYPE>>& PE_TaskScheduler::queuedTasks() { return scheduled_tasks; }
const PE_ScheduledTask* PE_TaskScheduler::getTaskbyOrder(int numtask) { return scheduled_tasks.top(); }
const PE_ScheduledTask* PE_TaskScheduler::getTaskbyID(ID_TYPE id) { return scheduled_tasks.top(); }
const PE_ScheduledTask& PE_TaskScheduler::lastTask() { return *scheduled_tasks.top(); }
bool PE_TaskScheduler::cancelTaskbyID(ID_TYPE id) { return false; }
bool PE_TaskScheduler::cancelTaskbyNumber(unsigned long position) { return false; }
void PE_TaskScheduler::cancelAll() {}
