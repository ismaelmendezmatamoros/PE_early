// PE_test.cpp: define el punto de entrada de la aplicación de consola.
//

//#include "stdafx.h"
#include<iostream>
#include<vector>
#include"PE_ScheduledFunction.h"
#include<string>


int main()
{
	std::string h("caca");
	PE_ScheduledFunction t(0, 0, 500, 0), k(0,0,554,0);
	std::cout << "asdfasdfafafa   " << (t < k) << std::endl;
	return 0;
}

