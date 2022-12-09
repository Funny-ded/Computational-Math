#pragma once

#include <exception>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

#include "butcher_table/butcher_table.hpp"

namespace compmath
{
	namespace source
	{
		namespace diff_equation
		{
			class solver_exception : public std::exception
			{
			public:

				explicit solver_exception(const char * const message) noexcept :
					std::exception(message) {}

				explicit solver_exception(const std::string& message) noexcept :
					std::exception(message.c_str()) {}

				~solver_exception() noexcept = default;
				
			};


			class Solver
			{
			private:
				using butcher_table_t = solver::Butcher_Table;

			public:

				Solver(const butcher_table_t& table, const int s) : m_table(table), m_s(s) {}

			public:

				std::vector < double > solve(const std::function < double(const double, const double) >& f,
					const double initial_x,
					const double initial_y,
					const double final_x,
					const double h) const;

				std::vector < double > function_values(const std::function < double(const double, const double) >& f, 
					const double x_n, const double y_n, const double h) const;

			protected:

				butcher_table_t m_table;
				int m_s;

			}; // class Solver


			class Euler_Solver : public Solver
			{
			public:
				Euler_Solver() : 
					Solver(solver::euler_table, 2) {}

			}; // class Euler_Solver

		} // namespace diff_equation

	} // namespace source

} // namespace compmath