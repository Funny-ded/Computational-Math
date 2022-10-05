#pragma once

#include <exception>
#include <ostream>
#include <string>
#include <type_traits>
#include <vector>

namespace compmath
{
	namespace source
	{
		class polynom_exception : public std::exception
		{
		public:

			explicit polynom_exception(const std::string& message) :
				std::exception(message.c_str()) {}

			explicit polynom_exception(const char* const message) :
				std::exception(message) {}

			~polynom_exception() noexcept = default;
		};

		// Polynom template class.
		// Coefficient represents a polynom coefficients' class
		// Variable represents a polynom variables' class
		template < typename T, typename Enable = std::enable_if_t < std::is_arithmetic_v < T > > >
		class Polynom
		{
		public:

			Polynom() = default;

			Polynom(const std::vector < T >& a) : m_a(a) {}
			Polynom(const T* const a) : m_a(a) {}

			~Polynom() noexcept = default;

		public:

			friend std::ostream& operator<< (std::ostream& stream, const Polynom < T, Enable >& polynom)
			{
				for (auto i = 0U; i < std::size(polynom.m_a); ++i)
				{
					if (polynom.m_a[i] != 0)
					{
						if (polynom.m_a[i] > 0 && i != 0)
						{
							stream << " + ";
						}
						else if (polynom.m_a[i] < 0)
						{
							stream << " - ";
						}

						stream << std::abs(polynom.m_a[i]);

						if (std::size(polynom.m_a) - 1 - i > 0)
						{
							stream << " * X";

							if (std::size(polynom.m_a) - 1 - i > 1)
							{
								stream << "^" << std::size(polynom.m_a) - 1 - i;
							}

						}

					}
				}

				return stream;
			}

		public:

			T operator()(T value) const;

		public:

			Polynom < T > derivative() const;

		public:

			inline bool is_zero() const
			{
				return std::size(m_a) == 1 && m_a[0] == 0;
			}

		public:

			inline const auto& coefficients() const
			{
				return m_a;
			}

		private:

			std::vector < T > m_a; // polynomial coefficients

		}; //class Polynom

		template < typename T, typename Enable >
		inline T Polynom< T, Enable >::operator()(T value) const
		{
			try
			{
				T result(0);

				for (auto i = 0U; i < std::size(m_a); ++i)
				{
					result += m_a[i] * std::pow(value, std::size(m_a) - 1 - i);
				}

				return result;
			}
			catch (const std::exception& e)
			{
				throw polynom_exception("Polynom call error: " + std::string(e.what()));
			}
		}

		template<typename T, typename Enable>
		inline Polynom<T> Polynom<T, Enable>::derivative() const
		{
			try
			{
				std::vector < T > new_coef;
				new_coef.reserve(std::size(m_a) - 1);

				for (auto i = 0U; i < std::size(m_a); ++i)
				{
					if (std::size(m_a) - 1 - i != 0 || std::size(m_a) == 1)
					{
						new_coef.push_back(m_a[i] * (std::size(m_a) - 1 - i));
					}
				}

				return Polynom < T >(new_coef);
			}
			catch (const std::exception& e)
			{
				throw polynom_exception("Polynom derivative exception: " + std::string(e.what()));
			}
		}

	} // namespace source

} // namespace compmath

