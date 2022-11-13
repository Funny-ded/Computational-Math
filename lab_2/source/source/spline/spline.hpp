#pragma once

#include <algorithm>
#include <exception>
#include <string>

#include "../polynom/polynom.hpp"

namespace compmath
{
	namespace source
	{
		class spline_exception : public std::exception
		{
		public:

			explicit spline_exception(const std::string& message) noexcept :
				std::exception(message.c_str()) {}

			explicit spline_exception(const char* const message) noexcept  :
				std::exception(message) {}

			~spline_exception() noexcept = default;
		};

		class Spline
		{
		protected:

			using value_t = double;
			using polynom_t = Polynom < value_t >;

		public:

			virtual std::vector < polynom_t > spline(const std::vector < value_t >&, const std::vector < value_t >&, const std::vector < value_t >&) const = 0;

		};

		class Cubic : public Spline
		{
		private:

			polynom_t spline_part(const std::pair < value_t, value_t >&, const std::pair < value_t, value_t >&, const std::pair < value_t, value_t >&) const;

		public:

			std::vector < polynom_t > spline(const std::vector < value_t >& params, const std::vector < value_t >& values, const std::vector < value_t >& derivatives) const override;
		};
	}
}