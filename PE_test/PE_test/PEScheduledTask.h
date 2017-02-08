#pragma once
#include<functional>


class PEScheduledTask
{
	int delay;
	long trigger_time;
	int num_reps;
	int ID;

public:

	PEScheduledTask(int id_, int delay_, long time_, int reps_ = 1):delay(delay_), num_reps(reps_),ID(id_),trigger_time(time_)
	{
		
	}

	virtual void run() = 0 {}

	bool operator>(PEScheduledTask &other) 
	{
		return (trigger_time > other.trigger_time);
	}

	bool operator<(PEScheduledTask &other)
	{
		return (trigger_time < other.trigger_time);
	}

	~PEScheduledTask()
	{
	}
};

