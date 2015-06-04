//==============================================================================
//
//	main.cpp:
//	
//
//		
//		
//
//==============================================================================


//	System dependencies ...
#include <iostream>

//	Boost dependencies ...

//	Project dependencies ...
#include "Bot.hpp"


int main(int args, const char * argv[], const char * arge[])
{
	// Unused things
	(void*)args;
	(void*)argv;
	(void*)arge;

	try 
	{
		// Start Smartass Bot with the variables set in the file "config.txt"
		smartass::Bot bot("config.txt");

		// Main execution
		bot.waitForEvents();
	}
	catch (const std::exception& e) 
	{
		std::cout << e.what() << std::endl;
		std::string keypress;
		std::cin >> keypress;
	}

	return 0;
}
