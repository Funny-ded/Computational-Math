#pragma once

#include <exception>
#include <string>
#include <vector>

namespace compmath
{
	namespace source
	{
		namespace diff_equation
		{
			namespace solver
			{

				class butcher_table_exception : public std::exception
				{
				public:

					explicit butcher_table_exception(const char* const message) noexcept :
						std::exception(message) {}

					explicit butcher_table_exception(const std::string& message) noexcept :
						std::exception(message.c_str()) {}

					~butcher_table_exception() noexcept = default;

				};

				struct Butcher_Table
				{
					Butcher_Table() noexcept = default;

					Butcher_Table(const std::vector < std::vector < double > >& a_coefs,
						const std::vector < double > b_coefs,
						const std::vector < double > c_coefs) : a(a_coefs), b(b_coefs), c(c_coefs) {}

					std::vector < std::vector < double > > a;
					std::vector < double > b;
					std::vector < double > c;

				}; // struct Butcher_Table

				static const Butcher_Table euler_table{
					std::vector < std::vector < double > >({
						std::vector < double >({ 0.0 }),
						std::vector < double >({ 1.0, 0.0 })
					}),
					std::vector < double >({ 0.5 , 0.5 }),
					std::vector < double >({ 0, 1.0 })
				};
			}
		}
	}
}