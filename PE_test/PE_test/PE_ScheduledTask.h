#pragma once
#include<functional>
#define _TASK_LAMBDA void()
#define _MILISECONDS_TIPE unsigned long


class PE_ScheduledTask
{
protected:
	_MILISECONDS_TIPE trigger_time;
	unsigned int delay;
	std::function<_TASK_LAMBDA> task;
	 unsigned long ID;
	int repetitions;

public:
	PE_ScheduledTask();
	PE_ScheduledTask(unsigned long id, unsigned int delay_, _MILISECONDS_TIPE time, int repetitions = 1);
	PE_ScheduledTask(const PE_ScheduledTask& other);
	PE_ScheduledTask(const PE_ScheduledTask&& other);
	virtual void trigger() = 0;
	_MILISECONDS_TIPE getTriggerTime() const;
	unsigned int getDelay() const;
	unsigned long getID() const;
	int getRepetitions() const;
	bool repeatForever() const;
	bool operator < (const PE_ScheduledTask& other);
	bool operator > (const PE_ScheduledTask& other);
	bool operator == (const PE_ScheduledTask& other);

	~PE_ScheduledTask();
};

