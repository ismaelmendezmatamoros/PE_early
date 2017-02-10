// PE_test.cpp: define el punto de entrada de la aplicación de consola.
//

//#include "stdafx.h"
#include<iostream>
#include<vector>
#include"PE_TaskScheduler.h"
#include<string>
#include<queue>

int de(int d, std::string k) {
	std::cout << "sdfsdf    "<<d<<k <<std::endl;
	return 5;
}

int fun() 
	{
	std::string h("caca");
	//PE_ScheduledFunction t(0, 0, 500, 0), k(0, 0, 554, 0);
//	t.setFunction(de, 4, h);
	return 5;
	}

int main()
{
	std::string h("caca");
//	PE_ScheduledFunction t(0, 0, 500, 0), k(0,0,554,0),w(0,0,1000,0, de,666,h);
	PE_TaskScheduler::Init();
	PE_TaskScheduler::addTask(20000, 5000, fun);
	PE_TaskScheduler::addTask(12000, 5000, fun);
	PE_TaskScheduler::addTask(5000, 5000, fun);
	PE_TaskScheduler::addTask(6000, 5000, fun);
//	std::timed_mutex m;
	//m.try_lock();//_for(std::chrono::milliseconds(3000));
	std::cout << "sem,1" << std::endl;
//	m.try_lock_for(std::chrono::milliseconds(30000));
	std::cout << "sem,21" << std::endl;
	std::cin.get();

	return 0;
}

