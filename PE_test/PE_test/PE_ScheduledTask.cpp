#include "PE_ScheduledTask.h"



PE_ScheduledTask::PE_ScheduledTask()
{
}

PE_ScheduledTask::PE_ScheduledTask(unsigned long id, unsigned int delay_, _MILISECONDS_TIPE time, int repetitions_):ID(id),
																					delay(delay),
																					trigger_time(time),
																					repetitions(repetitions)
																					{}
PE_ScheduledTask::PE_ScheduledTask(const PE_ScheduledTask& other) {
	delay = other.delay;
	ID = other.ID;
	trigger_time = other.trigger_time;
	repetitions = other.repetitions;
	task = other.task;
}

PE_ScheduledTask::PE_ScheduledTask(const PE_ScheduledTask&& other) {
	delay = other.delay;
	ID = other.ID;
	trigger_time = other.trigger_time;
	repetitions = other.repetitions;
	task = other.task;
}
_MILISECONDS_TIPE PE_ScheduledTask::getTriggerTime() const {return trigger_time; }
unsigned int PE_ScheduledTask::getDelay() const { return delay; }
unsigned long PE_ScheduledTask::getID() const { return ID; }
int PE_ScheduledTask::getRepetitions() const { return repetitions; }
bool PE_ScheduledTask::operator < (const PE_ScheduledTask& other) { return trigger_time < other.trigger_time; }
bool PE_ScheduledTask::operator > (const PE_ScheduledTask& other) { return trigger_time > other.trigger_time; }
bool PE_ScheduledTask::operator == (const PE_ScheduledTask& other) { return (ID < other.ID) && (trigger_time == other.trigger_time) && (delay == other.delay); }
bool PE_ScheduledTask::repeatForever() const { return repetitions > 0; }

PE_ScheduledTask::~PE_ScheduledTask()
{
}
