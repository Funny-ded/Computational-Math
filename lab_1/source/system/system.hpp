#pragma once

#include <exception>
#include <filesystem>
#include <fstream>
#include <string>

#include <nlohmann/json.hpp>

#include "../source/model/model.hpp"

namespace compmath
{
	class system_exception : public std::exception 
	{
	public:
		explicit system_exception(const std::string& message) :
			std::exception(message.c_str()) {}

		explicit system_exception(const char * const message) :
			std::exception(message) {}

		~system_exception() noexcept = default;
	};

	class System
	{
	private:

		using model_t = source::Model;

	public:

		System()
		{
			initialize();
		}

		~System() noexcept = default;

	private:

		void initialize();

	private:

		void load_model();

	private:

		class Data
		{
		private:

			using path_t = std::filesystem::path;
			using json_t = nlohmann::json;

		private:

			struct File
			{
				static inline const path_t config_json = "config.json";
			};

			struct Directory
			{
				static inline const path_t config		= "system/config";
				static inline const path_t config_model = "system/config/model";
			};

		public:

			static void load_model(source::Model&);

		private:

			static void load(const path_t&, json_t&);
		};

	public:

		void run();

	private:

		model_t m_model;
	}; // class System

} // namespace compmath