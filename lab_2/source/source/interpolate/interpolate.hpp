#pragma once

#include <algorithm>
#include <exception>
#include <string>

#include "../polynom/polynom.hpp"

namespace compmath
{
	namespace source
	{
		class interpolate_exception : public std::exception
		{
		public:

			explicit interpolate_exception(const std::string& message) noexcept: 
				std::exception(message.c_str()) {}

			explicit interpolate_exception(const char * const message) noexcept:
				std::exception(message) {}

			~interpolate_exception() noexcept = default;
		};

		class Interpolation
		{
		protected:

			using value_t	= double;
			using polynom_t = Polynom < value_t >;

		public:

			virtual polynom_t interpolate(const std::vector < value_t >&, const std::vector < value_t >&) const = 0;
		};

		class Lagrange : public Interpolation
		{
		private: 

			polynom_t part(const std::vector < value_t >&, const value_t, const std::size_t) const;

		public:

			polynom_t interpolate(const std::vector < value_t >&, const std::vector < value_t >&) const override;
		};

		class Newton : public Interpolation
		{
		private:

			std::vector < std::vector < value_t > > coefs(const std::vector < value_t >&, const std::vector < value_t >&) const;

			polynom_t part(const std::vector < value_t >&, const value_t, const std::size_t) const;

		public:

			polynom_t interpolate(const std::vector < value_t >&, const std::vector < value_t >&) const override;
		};
	}
}