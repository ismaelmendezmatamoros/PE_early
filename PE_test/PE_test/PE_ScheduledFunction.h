#pragma once
#include "PE_ScheduledTask.h"
#include "defines.h"


class PE_ScheduledFunction :
	public PE_ScheduledTask
{

public:
	
	PE_ScheduledFunction(ID_TYPE id, unsigned int delay_, MILISECONDS_TIPE time, int repetitions);
	PE_ScheduledFunction(const PE_ScheduledTask& other);
	PE_ScheduledFunction(const PE_ScheduledTask&& other);
	
	void trigger();
	~PE_ScheduledFunction();



	//*****************************************************************************************************//
	
	template<typename functype, typename... Args>
	void setFunction(functype f, Args... args) {
		auto call = std::bind(f, args...);
		task = [=]() {call(); };
	}

	template<typename functype, typename... Args>
	PE_ScheduledFunction(ID_TYPE id, unsigned int delay_, MILISECONDS_TIPE time, int repetitions, functype func, Args... args): PE_ScheduledTask(id, delay_, time, repetitions) {
		setFunction(func, args...);
	}

};

