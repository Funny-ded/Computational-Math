#pragma once

#include <exception>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "localizer/localizer.hpp"
#include "../polynom.hpp"

namespace compmath
{
	namespace source
	{
		namespace polynom
		{
			class solver_exception : public std::exception
			{
			public:

				explicit solver_exception(const std::string& message) :
					std::exception(message.c_str()) {}

				explicit solver_exception(const char * const message) :
					std::exception(message) {}

				~solver_exception() noexcept = default;

			};

			class Solver
			{
			private:

				using polynom_t = Polynom < double >;

			public:

				Solver() = default;

				~Solver() noexcept = default;

			public:

				std::vector < double > operator()(const polynom_t&);

			private:

				std::vector < double > find_roots(const polynom_t&, const solver::Localizer::Ring&, const int);

				double newton_root(const polynom_t&, const solver::Localizer::Ring&);

			}; // class Solver

		} // namespace polynom

	} // class source

} // compmath