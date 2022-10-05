#include <iostream>
#include <exception>

#include "system/system.hpp"
#include "utility/logger/logger.hpp"


int main(int argc, char** argv)
{
	try
	{
		compmath::System().run();

		system("pause");

		return EXIT_SUCCESS;
	}
	catch (const std::exception& e)
	{
		sentiment::Logger::write_error(e.what());

		std::cerr << e.what() << std::endl;

		system("pause");

		return EXIT_FAILURE;
	}
	catch (...)
	{
		sentiment::Logger::write_error("unknown exception");

		std::cerr << "unknown exception" << std::endl;

		system("pause");

		return EXIT_FAILURE;
	}
}