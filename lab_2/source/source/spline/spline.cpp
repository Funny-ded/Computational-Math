#include "spline.hpp"

namespace compmath
{
	namespace source
	{
		Cubic::polynom_t Cubic::spline_part(const std::pair < value_t, value_t >& params, const std::pair < value_t, value_t >& values, const std::pair < value_t, value_t >& derivatives) const
		{
			try
			{
				return polynom_t({
					-derivatives.second * std::pow(params.first, 2) * params.second * (params.second - params.first) + values.second * std::pow(params.first, 2) * (3 * params.second - params.first) + values.first * std::pow(params.second, 2) * (params.second - 3 * params.first) - derivatives.first * params.first * std::pow(params.second, 2) * (params.second - params.first),
					derivatives.second * params.first* (2 * params.second + params.first) * (params.second - params.first) - 6 * (values.second - values.first) * params.first * params.second + derivatives.first * params.second * (params.second + 2 * params.first) * (params.second - params.first),
					-derivatives.second * (params.second - params.first) * (params.second + 2 * params.first) + 3 * (values.second - values.first) * (params.second + params.first) - derivatives.first * (params.second - params.first) * (params.first + 2 * params.second),
					derivatives.second * (params.second - params.first) - 2 * (values.second - values.first) + derivatives.first * (params.second - params.first)
					}) / std::pow(params.second - params.first, 3);
			}
			catch (const std::exception& e)
			{
				throw spline_exception("Cubic spline exception: " + std::string(e.what()));
			}
		}

		std::vector < Cubic::polynom_t >  Cubic::spline(const std::vector < value_t >& params, const std::vector < value_t >& values, const std::vector < value_t >& derivatives) const
		{
			try
			{
				std::vector < polynom_t > splines;
				splines.reserve(std::size(params) - 1);

				for (auto i = 0U; i < std::size(params) - 1; ++i)
				{
					splines.push_back(spline_part(std::make_pair(params[i], params[i + 1]), std::make_pair(values[i], values[i + 1]), std::make_pair(derivatives[i], derivatives[i + 1])));
				}

				return splines;
			}
			catch (const std::exception& e)
			{
				throw spline_exception("Cubic spline exception: " + std::string(e.what()));
			}
		}
	}
}