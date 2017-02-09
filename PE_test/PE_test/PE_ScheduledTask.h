#pragma once
#include<functional>
#define _TASK_LAMBDA void()
#define _MILISECONDS_TIPE long


class PE_ScheduledTask
{
	_MILISECONDS_TIPE trigger_time;
	int delay;
	std::function<_TASK_LAMBDA> task;
	long ID;
	int repetitions;

public:
	PE_ScheduledTask();
	PE_ScheduledTask(long id, int delay_, _MILISECONDS_TIPE time, int repetitions = 1);
	virtual void trigger() = 0;
	_MILISECONDS_TIPE getTriggerTime() const;
	int getDelay() const;
	long getID() const;
	int getRepetitions() const;
	bool repeatForever() const;
	bool operator < (const PE_ScheduledTask& other);
	bool operator > (const PE_ScheduledTask& other);
	bool operator == (const PE_ScheduledTask& other);

	~PE_ScheduledTask();
};

