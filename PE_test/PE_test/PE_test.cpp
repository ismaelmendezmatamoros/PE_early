// PE_test.cpp: define el punto de entrada de la aplicación de consola.
//

//#include "stdafx.h"
#include<iostream>
#include<vector>
#include"PEScheduledFunctionTask.h"
#include<string>

int de(int h) {
	std::cout << "cac" << std::endl;
	return  8;
}

int main()
{
	std::string h("caca");
	PEScheduledFunctionTask p(0, 0, 0);
	p.setFunction<int, int>(de);

    return 0;
}

