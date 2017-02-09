#include "PE_ScheduledFunction.h"



PE_ScheduledFunction::PE_ScheduledFunction(long id, int delay_, _MILISECONDS_TIPE time, int repetitions): PE_ScheduledTask(id,delay_,time,repetitions)
{
}

PE_ScheduledFunction::PE_ScheduledFunction(const PE_ScheduledTask& other) : PE_ScheduledTask(other){

}

PE_ScheduledFunction::PE_ScheduledFunction(const PE_ScheduledTask&& other) : PE_ScheduledTask(other){

}

void PE_ScheduledFunction::trigger() {
	task();
}

PE_ScheduledFunction::~PE_ScheduledFunction()
{
}
