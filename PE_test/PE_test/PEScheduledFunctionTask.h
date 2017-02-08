#pragma once
#include "PEScheduledTask.h"
class PEScheduledFunctionTask :
	public PEScheduledTask
{

public:
	PEScheduledFunctionTask(int id_, int delay_, long time_, int reps_ = 1);
	template<typename return_type, typename... types>
	void setFunction(return_type(func)(types...));
	void run();
	~PEScheduledFunctionTask();


};


