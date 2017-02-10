// PE_test.cpp: define el punto de entrada de la aplicación de consola.
//

//#include "stdafx.h"
#include<iostream>
#include<vector>
#include"PE_TaskScheduler.h"
#include<string>
#include<queue>

int de(int d, std::string k) {
	 
	return 5;
}

int fun(std::string f) 
	{
	std::string h("caca");
	//PE_ScheduledFunction t(0, 0, 500, 0), k(0, 0, 554, 0);
//	t.setFunction(de, 4, h);
	std::cout << "exec fun" << f <<std::endl;
	return 5;
	}

int main()
{
	std::string h("caca");
//	PE_ScheduledFunction t(0, 0, 500, 0), k(0,0,554,0),w(0,0,1000,0, de,666,h);
	PE_TaskScheduler::Init();
	PE_TaskScheduler::addTask(20000, 10, fun, "2000");
	PE_TaskScheduler::addTask(1000, 3, fun, "1000");
	PE_TaskScheduler::addTask(5000, -1, fun,"5000");
	PE_TaskScheduler::addTask(6000, 0, fun,"6000");
//	std::timed_mutex m;
	//m.try_lock();//_for(std::chrono::milliseconds(3000));
	 
//	m.try_lock_for(std::chrono::milliseconds(30000));
	//PE_TaskScheduler::stopExecution();
	std::cin.get();

	return 0;
}

