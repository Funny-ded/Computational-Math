#pragma once

#include <algorithm>
#include <exception>
#include <functional>
#include <string>
#include <unordered_map>

#include "diff_equation/diff_equation.hpp"
#include "solver/solver.hpp"


namespace compmath
{
	namespace source
	{
		class cauchy_problem_exception : public std::exception
		{
		public:

			explicit cauchy_problem_exception(const char * const message) noexcept :
				std::exception(message) {}

			explicit cauchy_problem_exception(const std::string& message) noexcept :
				std::exception(message.c_str()) {}

			~cauchy_problem_exception() noexcept = default;

		};


		class Cauchy_Problem
		{
		public:

			Cauchy_Problem(const std::function < double(const double, const double) >& func,
				const std::pair < double, double >& interval,
				const std::pair < double, double >& initial) :
				m_equation(func, interval),
				m_initial_x(initial.first),
				m_initial_y(initial.second)
			{}

		public:

			std::vector < double > operator()(const double h, const double eps) const;

		private:
			std::vector < double > solve(const double h) const;

			double error(const std::vector < double >& single_grid, const std::vector < double >& double_grid) const;

		public:

			constexpr auto& equation() const
			{
				return m_equation;
			}

		private:

			Diff_Equation m_equation;
			double m_initial_x;
			double m_initial_y;

		};
	}
}