#pragma once

#include <exception>
#include <functional>
#include <string>
#include <type_traits>
#include <vector>

namespace compmath
{
	namespace source
	{
		class diff_equation_exception : public std::exception
		{
		public:

			explicit diff_equation_exception(const char* const message) noexcept :
				std::exception(message) {}

			explicit diff_equation_exception(const std::string& message) noexcept :
				std::exception(message.c_str()) {}

			~diff_equation_exception() noexcept = default;

		};


		class Diff_Equation
		{
		public:
			Diff_Equation(const std::function < double(const double, const double) >& func,
				const std::pair < double, double >& def_area) :
				m_f(func), 
				m_left_border(def_area.first), 
				m_right_border(def_area.second) 
			{}

		public:

			constexpr auto& f() const
			{
				return m_f;
			}

			constexpr auto& right_border() const
			{
				return m_right_border;
			}

			constexpr auto& left_border() const
			{
				return m_left_border;
			}

		private:

			std::function < double(const double, const double) > m_f;
			double m_right_border;
			double m_left_border;

		};
	}
}