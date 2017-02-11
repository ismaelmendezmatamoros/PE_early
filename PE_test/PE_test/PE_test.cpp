// PE_test.cpp: define el punto de entrada de la aplicación de consola.
//

//#include "stdafx.h"
#include<iostream>
#include<vector>
#include"PE_TaskScheduler.h"
#include<string>
#include<queue>



void fun()
{
	std::cout << "exec 5000" << std::endl;
}
void fan()
{
	std::cout << "exec 1000" << std::endl;
}

void fin()
{
	std::cout << "exec 20000" << std::endl;
}

int main()
{
	std::string h("caca");
//	PE_ScheduledFunction t(0, 0, 500, 0), k(0,0,554,0),w(0,0,1000,0, de,666,h);
	PE_TaskScheduler::Init();
	PE_TaskScheduler::addTask(1000, -1, fin);
	PE_TaskScheduler::addTask(2000, 3, fan);
	PE_TaskScheduler::addTask(5000, 10, fun);
	PE_TaskScheduler::addTask(6000, 0, fun);
//	std::timed_mutex m;
	//m.try_lock();//_for(std::chrono::milliseconds(3000));
	 
//	m.try_lock_for(std::chrono::milliseconds(30000));
	//PE_TaskScheduler::stopExecution();
	std::cin.get();

	return 0;
}

