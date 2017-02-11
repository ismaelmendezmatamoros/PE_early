#pragma once
#include<functional>
#include<atomic>
#include<time.h>
#include<chrono>
#include "defines.h"



class PE_ScheduledTask
{
protected:
	MILISECONDS_TIPE trigger_time;
	unsigned int delay;
	std::function<TASK_LAMBDA> task;
	 ID_TYPE ID;
	int repetitions;

public:
	PE_ScheduledTask();
	PE_ScheduledTask(ID_TYPE id, unsigned int delay_, MILISECONDS_TIPE time, int repetitions = 1);
	PE_ScheduledTask(const PE_ScheduledTask& other);
	PE_ScheduledTask(const PE_ScheduledTask&& other);
	virtual void trigger() = 0;
	MILISECONDS_TIPE getTriggerTime() const;
	unsigned int getDelay() const;
	unsigned long getID() const;
	int getRepetitions() const;
	bool repeatForever() const;
	void setRepetitions(int n);
	void setTriggerTime(MILISECONDS_TIPE time);
	bool operator < (const PE_ScheduledTask& other);
	bool operator > (const PE_ScheduledTask& other);
	bool operator == (const PE_ScheduledTask& other);
	bool operator()(const PE_ScheduledTask& a, const PE_ScheduledTask& b) const;

	~PE_ScheduledTask();
};

