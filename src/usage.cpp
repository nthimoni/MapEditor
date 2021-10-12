#include <iostream>

bool usage(int argc)
{
	if (argc != 6)
	{
		std::cout << "Usage :" << std::endl;
		return false;
	}
	return true;
}
