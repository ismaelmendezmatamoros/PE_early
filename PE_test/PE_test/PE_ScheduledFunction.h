#pragma once
#include "PE_ScheduledTask.h"
class PE_ScheduledFunction :
	public PE_ScheduledTask
{
public:
	PE_ScheduledFunction(long id, int delay_, _MILISECONDS_TIPE time, int repetitions = 1);
	
	template <typename return_type, typename... types>
	void setFunction(return_type(f)(types...), types... Args);
	void trigger();
	
	~PE_ScheduledFunction();
};

