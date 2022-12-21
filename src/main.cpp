#include <vector>
#include <thread>
#include <string.h>
#include <iostream>
#include "Controller.h"

using std::string;
int main()
{
	auto curr = Controller();
	curr.run();

	return EXIT_SUCCESS;
}