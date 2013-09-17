// main.cpp : Defines the entry point for the console application.
//



#include "test_node_parser.h"


#include <iostream>


int wmain(int, wchar_t* [])
{
    if(test_json_node_parser()
        && test_xml_node_parser())
    {
        std::cout << "All Test Passed" << std::endl;
    }

    std::cout << "press Enter to exit." << std::endl;
    std::cin.get();
	return 0;
}

