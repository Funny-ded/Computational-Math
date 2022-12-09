#include "solver.hpp"

namespace compmath
{
	namespace source
	{
		namespace diff_equation
		{
			std::vector < double > Solver::solve(const std::function < double(const double, const double) >& f,
				const double initial_x,
				const double initial_y,
				const double final_x,
				const double h) const
			{
				try
				{
					std::vector result = { initial_y };
					result.reserve((final_x - initial_x) / h + 1);

					for (auto k = 0U; k < (final_x - initial_x) / h; ++k)
					{
						auto f_values = function_values(f, initial_x + k * h, result.back(), h);

						auto factor = 0.0;
						for (auto i = 0U; i < std::size(f_values); ++i)
						{
							factor += m_table.b[i] * f_values[i];
						}

						result.push_back(result.back() + h * factor);
					}

					return result;
				}
				catch (const std::exception& e)
				{
					throw solver_exception("Solver solve exception: " + std::string(e.what()));
				}
			}

			std::vector < double > Solver::function_values(const std::function < double(const double, const double) >& f, 
				const double x_n, const double y_n, const double h) const
			{
				try
				{
					std::vector < double > f_values = { f(x_n, y_n) };

					f_values.reserve(m_s);

					for (auto i = 1U; i < m_s; ++i)
					{
						auto y_arg = y_n;
						for (auto j = 0U; j < std::size(f_values); ++j)
						{
							y_arg += h * m_table.a[i][j] * f_values[j];
						}

						f_values.push_back(f(x_n + h * m_table.c[i], y_arg));
					}

					return f_values;
				}
				catch (const std::exception& e)
				{
					throw solver_exception("Solver function_values exception: " + std::string(e.what()));
				}
			}
		}
	}
}