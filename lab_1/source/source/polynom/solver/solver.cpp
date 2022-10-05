#include "solver.hpp"

namespace compmath
{
	namespace source
	{
		namespace polynom
		{
			std::vector < double > Solver::operator()(const polynom_t& polynom)
			{
				try
				{
					solver::Localizer localizer;

					auto ring = localizer.localize(polynom);

					return find_roots(polynom, ring, localizer.num_roots(polynom, ring));
				}
				catch (const std::exception& e)
				{
					throw solver_exception("Solver call error: " + std::string(e.what()));
				}
			}

			std::vector < double > Solver::find_roots(const polynom_t& polynom, const solver::Localizer::Ring& ring, const int num_roots)
			{
				try
				{	
					if (num_roots == 1 && polynom(ring.left) * polynom(ring.right) < 0)
					{
						return std::vector({ newton_root(polynom, ring) });
					}
					if (num_roots == 0)
					{
						return std::vector < double >();
					}

					std::vector < double > result;
					result.reserve(num_roots);

					auto diff = (ring.right - ring.left) / num_roots;

					for (auto i = 0U; i < num_roots; ++i)
					{
						auto new_ring = solver::Localizer::Ring(ring.left + i * diff, ring.right - (num_roots - 1 - i) * diff);

						for (const auto root : find_roots(polynom, new_ring, solver::Localizer().num_roots(polynom, new_ring)))
						{
							result.push_back(root);
						}
					}

					return result;
				}
				catch (const std::exception& e)
				{
					throw solver_exception("Solver find roots error: " + std::string(e.what()));
				}
			}
			double Solver::newton_root(const polynom_t& polynom, const solver::Localizer::Ring& ring)
			{
				try
				{
					auto x = (ring.right + ring.left) / 2;

					for (auto last_x = x;std::abs(polynom(x)) >= 1.0e-11; last_x = x)
					{
						x = x - polynom(x) / polynom.derivative()(x);

						if (x < ring.left)
						{
							x = ring.left;
						}
						if (x > ring.right)
						{
							x = ring.right;
						}

						if (std::abs(x - last_x) < 1.0e-11)
						{
							return x;
						}
					}

					return x;
				}
				catch (const std::exception& e)
				{
					throw solver_exception("Solver newton root error: " + std::string(e.what()));
				}

			}

		} // namespace polynom

	} // namespace source

} // namespace compmath