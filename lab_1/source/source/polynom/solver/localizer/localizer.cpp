#include "localizer.hpp"

namespace compmath
{
	namespace source
	{
		namespace polynom
		{
			namespace solver
			{
				Localizer::Ring Localizer::localize(const polynom_t& equation) const
				{
					try
					{
						return Ring(std::abs(equation.coefficients().back()) / (std::abs(equation.coefficients().back()) + B(equation)),
							1 + A(equation) / std::abs(equation.coefficients().front()));
					}
					catch (const std::exception& e)
					{
						throw localizer_exception("Localizer localize error: " + std::string(e.what()));
					}
				}

				int Localizer::num_roots(const polynom_t& polynom, const Ring& ring)
				{
					try
					{
						auto k_left = 0;
						auto k_right = 0;

						auto left_sign = polynom(ring.left) > 0 ? +1 : -1;
						auto right_sign = polynom(ring.right) > 0 ? +1 : -1;

						for (auto derivative = polynom.derivative(); !derivative.is_zero(); derivative = derivative.derivative())
						{
							auto curr_value = derivative(ring.left);
							k_left += left_sign * curr_value < 0 ? 1 : 0;
							left_sign = curr_value == 0 ? left_sign : curr_value > 0 ? +1 : -1;

							curr_value = derivative(ring.right);
							k_right += right_sign * curr_value < 0 ? 1 : 0;
							right_sign = curr_value == 0 ? right_sign : curr_value > 0 ? +1 : -1;
						}

						return std::abs(k_left - k_right);
					}
					catch (const std::exception& e)
					{
						throw localizer_exception("Localizer num roots error: " + std::string(e.what()));
					}
				}

			} // namespace solver

		} // namespace polynom

	} // namespace source

} // namespace compmath