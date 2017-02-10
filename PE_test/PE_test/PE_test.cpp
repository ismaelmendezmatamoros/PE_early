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

PE_ScheduledFunction fun() 
	{
	std::string h("caca");
	PE_ScheduledFunction t(0, 0, 500, 0), k(0, 0, 554, 0);
	t.setFunction(de, 4, h);
	return t;
	}

int main()
{
	std::string h("caca");
	PE_ScheduledFunction t(0, 0, 500, 0), k(0,0,554,0),w(0,0,1000,0, de,666,h);
	PE_TaskScheduler::Init();
	PE_TaskScheduler::addTask(5000, 5000, fun);
	std::cin.get();

	return 0;
}

