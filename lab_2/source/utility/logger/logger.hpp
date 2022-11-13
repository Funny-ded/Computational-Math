#pragma once

#include <chrono>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <string>


namespace utility
{
	class Logger
	{
	private:

		using path_t = std::filesystem::path;

	private:

		static void create_log_file();

	private:

		struct Message_Type
		{
			static inline constexpr auto system = "[SYSTEM]";
			static inline constexpr auto error	= "[ERROR]";
		};

	private:

		static auto message_time_info();

	public:

		static void write_system(const std::string& message)
		{
			write_system(message.c_str());
		}

		static void write_system(const char* const message)
		{
			write(std::format("{}: {}", Message_Type::system, message));
		}

		static void write_error(const std::string& message)
		{
			write_error(message.c_str());
		}

		static void write_error(const char* const message)
		{
			write(std::format("{}: {}", Message_Type::error, message));
		}


	private:
		static void write(const std::string& message)
		{
			write(message.c_str());
		}

		static void write(const char* const);

	private:

		static inline const path_t log_output = "log/output.log";

	};
}