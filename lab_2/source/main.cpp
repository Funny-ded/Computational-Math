#include <iostream>
#include <exception>

#include "system/system.hpp"
#include "utility/logger/logger.hpp"

#include "source/polynom/polynom.hpp"


int main(int argc, char** argv)
{
	try
	{
		utility::Logger::write_system("Start System");

		compmath::System().run();

		system("pause");

		return EXIT_SUCCESS;
	}
	catch (const std::exception& e)
	{
		utility::Logger::write_error(e.what());

		std::cerr << e.what() << std::endl;

		system("pause");

		return EXIT_FAILURE;
	}
	catch (...)
	{
		utility::Logger::write_error("unknown exception");

		std::cerr << "unknown exception" << std::endl;

		system("pause");

		return EXIT_FAILURE;
	}
}