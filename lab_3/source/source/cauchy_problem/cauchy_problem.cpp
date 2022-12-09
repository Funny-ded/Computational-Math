#include "cauchy_problem.hpp"

namespace compmath
{
	namespace source
	{
		std::vector < double > Cauchy_Problem::operator()(const double h, const double eps) const
		{
			try
			{
				auto result = solve(h);

				for (auto i = 1U;; ++i)
				{
					auto double_grid_result = solve(h / std::pow(2, i));
					if (error(result, double_grid_result) < eps)
					{
						return result;
					}

					result = double_grid_result;
				}
			}
			catch (const std::exception& e)
			{
				throw cauchy_problem_exception("Cauchy problem op() error: " + std::string(e.what()));
			}
		}

		std::vector < double > Cauchy_Problem::solve(const double h) const
		{
			try
			{
				return diff_equation::Euler_Solver().solve(m_equation.f(), m_initial_x, m_initial_y, m_equation.right_border(), h);
			}
			catch (const std::exception& e)
			{
				throw cauchy_problem_exception("Cauchy problem solve error: " + std::string(e.what()));
			}
		}

		double Cauchy_Problem::error(const std::vector < double >& single_grid, const std::vector < double >& double_grid) const
		{
			try
			{
				auto error = 0.0;

				for (auto i = 0U; i < std::size(single_grid); ++i)
				{
					error = std::max(std::abs(single_grid[i] - double_grid[2 * i]), error);
				}

				return error;
			}
			catch (const std::exception& e)
			{
				throw cauchy_problem_exception("Cauchy problem error error: " + std::string(e.what()));
			}
		}
	}
}