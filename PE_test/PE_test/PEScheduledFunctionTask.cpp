#include "PEScheduledFunctionTask.h"






PEScheduledFunctionTask::PEScheduledFunctionTask(int id_, int delay_, long time_, int reps_):PEScheduledTask(id_, delay_, time_, reps_)
{
}

void PEScheduledFunctionTask::run()
{
}

template<typename return_type, typename ...types>
void PEScheduledFunctionTask::setFunction(return_type(func)(types...))
{
}


PEScheduledFunctionTask::~PEScheduledFunctionTask()
{
}
