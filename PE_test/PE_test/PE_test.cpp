// PE_test.cpp: define el punto de entrada de la aplicación de consola.
//

//#include "stdafx.h"
#include<iostream>
#include<vector>
#include"PE_ScheduledFunction.h"
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
	t.setFunction(de,4,h);
	t.trigger();
	fun().trigger();
	w.trigger();

	std::priority_queue<PE_ScheduledTask*> vec;
	//std::mem_fn<>()
	vec.push(&w);
	vec.push(&t); 
	vec.push(&k);

	while (vec.size() > 0) {
		std::cout <<"fffffffffffffffffffff "<< vec.top()->getTriggerTime()<<std::endl;
		vec.pop();
	}

	std::cin.get();

	return 0;
}

