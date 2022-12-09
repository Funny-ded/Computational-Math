#pragma once

#include <cmath>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include <nlohmann/json.hpp>

#include "../source/cauchy_problem/cauchy_problem.hpp"

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

		using value_t = double;
		using cauchy_problem_t = source::Cauchy_Problem;

	public:

		System() : m_problem(m_f, m_interval, m_initial)
		{
			//initialize();
		}

		~System() noexcept = default;

	private:

		void handle_user_inputs() const;

		void print_solution(const std::vector < double >&, const int) const;

	public:

		void run();

	private:

		static inline const auto m_f = [](const value_t x, const value_t y) { return 2 * y / (x * (2 * std::pow(x, 2) * y * std::log(y) + 1)); };
		
		static inline constexpr auto m_initial = std::make_pair(1.0, 1.0);
		static inline constexpr auto m_interval = std::make_pair(1.0, 1.2);
		
		static inline constexpr auto m_node_number	= 11;
		static inline constexpr auto m_eps			= 1e-4;

	private:

		cauchy_problem_t m_problem;
		
	}; // class System

} // namespace compmath