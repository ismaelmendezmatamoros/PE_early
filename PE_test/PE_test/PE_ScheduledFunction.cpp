#include "PE_ScheduledFunction.h"



PE_ScheduledFunction::PE_ScheduledFunction(long id, int delay_, _MILISECONDS_TIPE time, int repetitions): PE_ScheduledTask(id,delay_,time,repetitions)
{
}

template <typename return_type, typename... types>
void PE_ScheduledFunction::setFunction(return_type(f)(types...), types... Args) {}
void PE_ScheduledFunction::trigger() {}

PE_ScheduledFunction::~PE_ScheduledFunction()
{
}
