#pragma once

#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include <nlohmann/json.hpp>

#include "../source/interpolate/interpolate.hpp"
#include "../source/spline/spline.hpp"

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

		using value_t		= double;
		using polynom_t		= source::Polynom < value_t >;
		using lagrange_t	= source::Lagrange;
		using newton_t		= source::Newton;
		using spline_t		= source::Cubic;

	public:

		System()
		{
			initialize();
		}

		~System() noexcept = default;

	private:

		void initialize();

	private:

		void load_values();

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
				static inline const path_t values_json = "values.json";
			};

			struct Directory
			{
				static inline const path_t config = "system/config";
			};

		public:

			static void load_values(std::vector < value_t >&, std::vector < value_t >&);

		private:

			static void load(const path_t&, json_t&);
		};

	private:

		void handle_user_inputs(const std::vector< polynom_t >&) const;

	public:

		void run();

	private:

		std::string m_interpolation_type;

		std::unordered_map < std::string, source::Interpolation* > m_interpolation;

		std::vector < value_t > m_params;
		std::vector < value_t > m_values;

		spline_t	m_spline;
		
	}; // class System

} // namespace compmath