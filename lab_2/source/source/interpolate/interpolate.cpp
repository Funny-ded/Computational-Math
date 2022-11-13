#include "interpolate.hpp"

namespace compmath
{
	namespace source
	{
		Lagrange::polynom_t Lagrange::interpolate(const std::vector < value_t >& params, const std::vector < value_t >& values) const
		{
			try
			{
				polynom_t interpolation({ value_t(0) });

				for (auto i = 0U; i < std::size(values); ++i)
				{
					interpolation += part(params, values[i], i);
				}

				return interpolation;
			}
			catch (const std::exception& e)
			{
				throw interpolate_exception("Lagrange interpolate exception: " + std::string(e.what()));
			}
		}

		Lagrange::polynom_t Lagrange::part(const std::vector < value_t >& params, const value_t value, const std::size_t n) const
		{
			try
			{
				polynom_t part({ value });

				for (auto j = 0U; j < std::size(params); ++j)
				{
					if (n != j)
					{
						part *= polynom_t({ -params[j], 1 }) / (params[n] - params[j]);
					}
				}

				return part;
			}
			catch (const std::exception& e)
			{
				throw interpolate_exception("Lagrange part exception: " + std::string(e.what()));
			}
		}

		std::vector < std::vector < Newton::value_t > > Newton::coefs(const std::vector < value_t >& params, const std::vector < value_t >& values) const
		{
			try
			{
				std::vector < std::vector < value_t > > coefs;
				coefs.reserve(std::size(params));

				coefs.push_back(values);
				for (; std::size(coefs) < std::size(params);)
				{
					std::vector < value_t > delta;
					delta.reserve(std::size(coefs.back()) - 1);

					for (auto i = 0U; i < std::size(coefs.back()) - 1; ++i)
					{
						delta.push_back((coefs.back()[i + 1] - coefs.back()[i]) / (params[std::size(coefs) + i] - params[i]));
					}

					coefs.push_back(delta);
				}

				return coefs;
			}
			catch (const std::exception& e)
			{
				throw interpolate_exception("Newton coefs exception: " + std::string(e.what()));
			}
		}

		Newton::polynom_t Newton::part(const std::vector < value_t >& params, const value_t value, const std::size_t n) const
		{
			try
			{
				polynom_t part({ value });

				for (auto j = 0U; j < n; ++j)
				{
					part *= polynom_t({ -params[j], 1 });
				}

				return part;
			}
			catch (const std::exception& e)
			{
				throw interpolate_exception("Lagrange part exception: " + std::string(e.what()));
			}
		}

		Newton::polynom_t Newton::interpolate(const std::vector < value_t >& params, const std::vector < value_t >& values) const
		{
			try
			{
				polynom_t interpolation({ value_t(0) });

				auto delta = coefs(params, values);

				for (auto n = 0U; n < std::size(delta); ++n)
				{
					interpolation += part(params, delta[n][0], n);
				}

				return interpolation;
			}
			catch (const std::exception& e)
			{
				throw interpolate_exception("Newton interpolate exception: " + std::string(e.what()));
			}
		}
	}
}