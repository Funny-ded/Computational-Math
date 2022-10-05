#pragma once
#pragma once

#include <algorithm>
#include <iostream>
#include <exception>
#include <string>
#include <vector>

#include "../../polynom.hpp"

namespace compmath
{
	namespace source
	{
		namespace polynom
		{
			namespace solver
			{
				class localizer_exception : public std::exception
				{
				public:

					explicit localizer_exception(const std::string& message) :
						std::exception(message.c_str()) {}

					explicit localizer_exception(const char* const message) :
						std::exception(message) {}

					~localizer_exception() noexcept = default;

				};

				class Localizer
				{
				private:

					using polynom_t = Polynom < double >;

				public:

					Localizer() = default;

					~Localizer() noexcept = default;

				public:

					struct Ring
					{
						Ring(const double l, const double r) : left(l), right(r) {}

						double left;
						double right;

					}; // struct Ring

				private:

					inline static double A(const polynom_t& polynom)
					{
						return *std::max_element(std::next(std::cbegin(polynom.coefficients())), std::cend(polynom.coefficients()),
							[](const auto a, const auto b) { return std::abs(a) < std::abs(b); });
					}

					inline static double B(const polynom_t& polynom)
					{
						return *std::max_element(std::cbegin(polynom.coefficients()), std::prev(std::cend(polynom.coefficients())),
							[](const auto a, const auto b) { return std::abs(a) < std::abs(b); });
					}

				public:

					Ring localize(const polynom_t&) const;

					int num_roots(const polynom_t&, const Ring&);

				}; // class Localizer

			} // namespace solver

		} // namespace polynom

	} // namespace source

} // namespace compmath