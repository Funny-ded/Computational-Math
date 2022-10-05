#include "logger.hpp"

namespace sentiment
{

	void Logger::create_log_file()
	{
		std::filesystem::create_directories(log_output.parent_path());
		std::ofstream(log_output).close();

		if (!std::ifstream(log_output))
		{
			std::cerr << "Error: " << log_output.string() << " file didn't create. Try to do it manually" << std::endl;
			std::abort();
		}

		std::cout << "Created successfully" << std::endl;

		write_system("Log file created");
	}

	auto Logger::message_time_info()
	{
		auto curr_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

		tm timeinfo;
		gmtime_s(&timeinfo, &curr_time);

		return std::put_time(&timeinfo, "%F %T");
	}

	void Logger::write(const char* const message)
	{
		std::fstream ilog(log_output, std::ios::app);

		if (!ilog)
		{
			std::cout << "Log file stream issue. Trying to create log file." << std::endl;
			create_log_file();
		}

		auto curr_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

		tm timeinfo;
		gmtime_s(&timeinfo, &curr_time);

		ilog << message_time_info() << ' ' << message << std::endl;
	}
}
