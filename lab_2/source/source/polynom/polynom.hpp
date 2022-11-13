#pragma once

#include <exception>
#include <functional>
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

			explicit Polynom(const std::vector < T >& a) : m_a(a) {}
			explicit Polynom(const T* const a) : m_a(a) {}

			~Polynom() noexcept = default;

		public:

			friend std::ostream& operator<< (std::ostream& stream, const Polynom < T, Enable >& polynom)
			{
				for (auto i = 0U; i < std::size(polynom.m_a); ++i)
				{
					if (polynom.m_a[i] != 0 || std::size(polynom.m_a) == 1)
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

						if (i > 0)
						{
							stream << " * X";

							if (i > 1)
							{
								stream << "^" << i;
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

			void swap(Polynom < T >& other)
			{
				std::swap(m_a, other.m_a);
			}

		public:


			Polynom < T >& operator+=(const Polynom < T >&);
			Polynom < T >& operator+=(const T);


			Polynom < T >& operator-=(const Polynom < T >&);
			Polynom < T >& operator-=(const T);

			Polynom < T >& operator*=(const Polynom < T >&);
			Polynom < T >& operator*=(const T);

			Polynom < T >& operator/=(const T);

		public:

			friend Polynom operator+(const Polynom < T, Enable >& lhs, const Polynom < T, Enable >& rhs)
			{
				return Polynom(lhs) += rhs;
			}

			friend Polynom operator+(const Polynom < T, Enable >& lhs, const T rhs)
			{
				return Polynom(lhs) += rhs;
			}

			friend Polynom operator-(const Polynom < T, Enable >& lhs, const Polynom < T, Enable >& rhs)
			{
				return Polynom(lhs) -= rhs;
			}

			friend Polynom operator-(const Polynom < T, Enable >& lhs, const T rhs)
			{
				return Polynom(lhs) -= rhs;
			}

			friend Polynom operator*(const Polynom < T, Enable >& lhs, const Polynom < T, Enable >& rhs)
			{
				return Polynom(lhs) *= rhs;
			}

			friend Polynom operator*(const Polynom < T, Enable >& lhs, const T rhs)
			{
				return Polynom(lhs) *= rhs;
			}

			friend Polynom operator/(const Polynom < T, Enable >& lhs, const T rhs)
			{
				return Polynom(lhs) /= rhs;
			}

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

			std::vector < T > m_a; // polynomial coefficients; a[0] is the coefficient for x^0 

		}; //class Polynom

		template < typename T, typename Enable >
		T Polynom< T, Enable >::operator()(T value) const
		{
			try
			{
				T result(0);

				for (auto i = 0U; i < std::size(m_a); ++i)
				{
					result += m_a[i] * std::pow(value, i);
				}

				return result;
			}
			catch (const std::exception& e)
			{
				throw polynom_exception("Polynom call error: " + std::string(e.what()));
			}
		}

		template<typename T, typename Enable>
		Polynom<T> Polynom<T, Enable>::derivative() const
		{
			try
			{
				std::vector < T > new_coef;
				new_coef.reserve(std::size(m_a) - 1);

				for (auto i = 0U; i < std::size(m_a); ++i)
				{
					if (i != 0 || std::size(m_a) == 1)
					{
						new_coef.push_back(m_a[i] * i);
					}
				}

				return Polynom < T >(new_coef);
			}
			catch (const std::exception& e)
			{
				throw polynom_exception("Polynom derivative exception: " + std::string(e.what()));
			}
		}

		template < typename T, typename Enable >
		Polynom < T >& Polynom < T , Enable>::operator+=(const Polynom < T >& other)
		{
			try
			{
				m_a.reserve(std::max(std::size(m_a), std::size(other.m_a)));

				for (auto i = 0U; i < std::min(std::size(m_a), std::size(other.m_a)); ++i)
				{
					m_a[i] += other.m_a[i];
				}

				if (std::size(m_a) < std::size(other.m_a))
				{
					for (auto i = std::size(m_a); i < std::size(other.m_a); ++i)
					{
						m_a.push_back(other.m_a[i]);
					}
				}

				for (; m_a.back() == T(0);)
				{
					m_a.erase(std::prev(std::end(m_a)));
				}

				m_a.shrink_to_fit();

				return *this;
			}
			catch (const std::exception& e)
			{
				throw polynom_exception("Polynom op+= exception: " + std::string(e.what()));
			}
		}

		template < typename T, typename Enable >
		Polynom < T >& Polynom < T, Enable>::operator+=(const T a)
		{
			try
			{
				return *this += Polynom({ a });
			}
			catch (const std::exception& e)
			{
				throw polynom_exception("Polynom op+= exception: " + std::string(e.what()));
			}
		}

		template < typename T, typename Enable >
		Polynom < T >& Polynom < T, Enable >::operator-=(const Polynom < T >& other)
		{
			try
			{
				std::vector < T > opposite;

				opposite.reserve(std::size(other.m_a));

				std::transform(std::begin(other.m_a), std::end(other.m_a), std::back_inserter(opposite), std::negate<>{});

				return *this += Polynom < T > (opposite);
			}
			catch (const std::exception& e)
			{
				throw polynom_exception("Polynom op+= exception: " + std::string(e.what()));
			}
		}

		template < typename T, typename Enable >
		Polynom < T >& Polynom < T, Enable>::operator-=(const T a)
		{
			try
			{
				return *this -= Polynom({ a });
			}
			catch (const std::exception& e)
			{
				throw polynom_exception("Polynom op+= exception: " + std::string(e.what()));
			}
		}

		template < typename T, typename Enable >
		Polynom < T >& Polynom < T, Enable >::operator*=(const Polynom < T >& other)
		{
			try
			{
				auto old_coefs = m_a;
				m_a = std::vector < T > (std::size(m_a) + std::size(other.m_a) - 1, T(0));

				for (auto i = 0U; i < std::size(m_a); ++i)
				{
					for (auto j = 0U; j < i + 1 && j < std::size(old_coefs); ++j)
					{
						if (i - j < std::size(other.m_a) && old_coefs[j] != T(0) && other.m_a[i - j] != T(0))
						{
							m_a[i] += old_coefs[j] * other.m_a[i - j];
						}
					}
				}

				return *this;
			}
			catch (const std::exception& e)
			{
				throw polynom_exception("Polynom op*= exception: " + std::string(e.what()));
			}
		}

		template < typename T, typename Enable >
		Polynom < T >& Polynom < T, Enable>::operator*=(const T a)
		{
			try
			{
				return *this *= Polynom({ a });
			}
			catch (const std::exception& e)
			{
				throw polynom_exception("Polynom op+= exception: " + std::string(e.what()));
			}
		}

		template < typename T, typename Enable >
		Polynom < T >& Polynom < T, Enable>::operator/=(const T a)
		{
			try
			{
				return *this *= 1 / a;
			}
			catch (const std::exception& e)
			{
				throw polynom_exception("Polynom op+= exception: " + std::string(e.what()));
			}
		}

	} // namespace source

} // namespace compmath

