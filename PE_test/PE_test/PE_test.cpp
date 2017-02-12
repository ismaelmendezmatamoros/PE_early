// PE_test.cpp: define el punto de entrada de la aplicación de consola.
//

//#include "stdafx.h"
#include<iostream>
#include<vector>
#include"PE_TaskScheduler.h"
#include<string>
#include<queue>
#include<vld.h>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


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

void fen()
{
	std::cout << "exec 33" << std::endl;
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	std::string h("caca");
	PE_TaskScheduler::Init();
	PE_TaskScheduler::addTask(8, -1, fin);
	PE_TaskScheduler::addTask(2000, 3, fan);
	PE_TaskScheduler::addTask(250, 50, fun);
	PE_TaskScheduler::addTask(18, -1, fun);
	PE_TaskScheduler::addTask(33, -1, fen);
	std::cin.get();

	return 0;
}

