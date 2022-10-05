#pragma once

#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include "wave/wave.hpp"

#include "../polynom/polynom.hpp"
#include "../polynom/solver/solver.hpp"

namespace compmath
{
	namespace source
	{
		class model_exception : public std::exception 
		{
		public:

			explicit model_exception(const std::string& message) : 
				std::exception(message.c_str()) {}

			explicit model_exception(const char * const message) :
				std::exception(message) {}

			~model_exception() noexcept = default;
		};

		class Model
		{
		private:

			using wave_t = model::Wave;

			using equation_t = Polynom < double >;

		public:

			Model() = default;

			~Model() noexcept = default;

		public:

			void solve();

		private:

			enum class Type
			{
				Double_Shock,
				High_Speed_Double_Shock,
				Shock_Discharge,

			};

			static Type convert_type(const std::string&);

		private:

			const double U_inside_system(const double);

		private:

			inline const std::vector < double > coefficients() const
			{
				return Redefiner::coefficients(m_wave_1, m_wave_2);
			}

		private:

			class Redefiner
			{

			public:

				inline static std:: vector < double > coefficients(const wave_t& wave_1, const wave_t& wave_2)
				{
					return std::vector (
						{
							a_0(wave_1, wave_2),
							a_1(wave_1, wave_2),
							a_2(wave_1, wave_2),
							a_3(wave_1, wave_2),
							a_4(wave_1, wave_2),
							a_5(wave_1, wave_2),
							a_6(wave_1, wave_2),
						}
					);
				}

			public:

				inline static double alpha(const wave_t& wave)
				{
					return alpha(wave.outside.gamma);
				}

				inline static double e(const wave_t& wave_1, const wave_t& wave_2)
				{
					return e(wave_1.outside.gamma, sound_speed(wave_1), wave_2.outside.U - wave_1.outside.U);
				}

				inline static double sound_speed(const wave_t& wave)
				{
					return sound_speed(wave.outside.P, wave.outside.rho, wave.outside.gamma);
				}

				inline static double pressure_ratio(const wave_t& wave_1, const wave_t& wave_2)
				{
					return pressure_ratio(wave_2.outside.P, wave_1.outside.P);
				}

				inline static double discontunity_speed(const wave_t& wave)
				{
					return (density_ratio(wave.outside.gamma, wave.outside.P, wave.inside.P) * wave.outside.U - wave.inside.U) /
						(density_ratio(wave.outside.gamma, wave.outside.P, wave.inside.P) - 1.0);
				}

			private:

				inline static const double alpha(const double gamma)
				{
					return (gamma + 1) / (gamma - 1);
				}

				inline static const double e(const double gamma, const double sound_speed, const double diff)
				{
					return 2 * std::pow(sound_speed, 2) / (gamma * (gamma - 1) * std::pow(diff, 2));
				}

				inline static const double sound_speed(const double P, const double rho, const double gamma)
				{
					return std::pow(gamma * P / rho, 0.5);
				}

				inline static const double pressure_ratio(const double P_1, const double P_2)
				{
					return P_1 / P_2;
				}

				inline static const double density_ratio(const double gamma, const double P_0, const double P_1)
				{
					return (gamma + 1.0 + (gamma - 1.0) * P_1 / P_0) / (gamma - 1.0 + (gamma + 1.0) * P_1 / P_0);
				}

			private:

				inline static double a_0(const wave_t& wave_1, const wave_t& wave_2)
				{
					return std::pow(alpha(wave_1) * e(wave_2, wave_1) - alpha(wave_2) * pressure_ratio(wave_2.outside.P, wave_1.outside.P) * e(wave_1, wave_2), 2);
				}

				inline static double a_1(const wave_t& wave_1, const wave_t& wave_2)
				{
					return 2 * (
						(
							alpha(wave_1) * e(wave_2, wave_1) 
							- alpha(wave_2) * pressure_ratio(wave_2.outside.P, wave_1.outside.P) * e(wave_1, wave_2)
						) * 
						(
							e(wave_2, wave_1) * 
							(
								1 
								- 2 * alpha(wave_1) * pressure_ratio(wave_2.outside.P, wave_1.outside.P)
							)
							- e(wave_1, wave_2) * pressure_ratio(wave_2.outside.P, wave_1.outside.P) * 
							(
								pressure_ratio(wave_2.outside.P, wave_1.outside.P) 
								- 2 * alpha(wave_2)
							)
						)
						- alpha(wave_1) * alpha(wave_2) * pressure_ratio(wave_2.outside.P, wave_1.outside.P) * 
						(
							alpha(wave_1) * e(wave_2, wave_1) 
							+ alpha(wave_2) * pressure_ratio(wave_2.outside.P, wave_1.outside.P) * e(wave_1, wave_2)
						)
					);
				}

				inline static double a_2(const wave_t& wave_1, const wave_t& wave_2)
				{
					return std::pow(e(wave_2, wave_1), 2) * 
						(
							6 * std::pow(alpha(wave_1) * pressure_ratio(wave_2.outside.P, wave_1.outside.P), 2)
							- 8 * alpha(wave_1) * pressure_ratio(wave_2.outside.P, wave_1.outside.P) 
							+ 1
						)
						- 2 * e(wave_1, wave_2) * e(wave_2, wave_1) * pressure_ratio(wave_2.outside.P, wave_1.outside.P) * 
						(
							alpha(wave_1) * alpha(wave_2) *
							(
								std::pow(pressure_ratio(wave_2.outside.P, wave_1.outside.P), 2) 
								+ 4 * pressure_ratio(wave_2.outside.P, wave_1.outside.P) 
								+ 1
							)
							- 2 * 
							(
								pressure_ratio(wave_2.outside.P, wave_1.outside.P) 
								+ 1
							) * 
							(
								alpha(wave_2) + 
								alpha(wave_1) * pressure_ratio(wave_2.outside.P, wave_1.outside.P)
							)
							+ pressure_ratio(wave_2.outside.P, wave_1.outside.P)
						)
						+ std::pow(e(wave_1, wave_2) * pressure_ratio(wave_2.outside.P, wave_1.outside.P), 2) * 
						(
							6 * std::pow(alpha(wave_2), 2) 
							- 8 * alpha(wave_2) * pressure_ratio(wave_2.outside.P, wave_1.outside.P) 
							+ std::pow(pressure_ratio(wave_2.outside.P, wave_1.outside.P), 2)
						)
						+ std::pow(alpha(wave_1) * alpha(wave_2) * pressure_ratio(wave_2.outside.P, wave_1.outside.P), 2)
						- 2 * alpha(wave_1) * pressure_ratio(wave_2.outside.P, wave_1.outside.P) * e(wave_2, wave_1) * 
						(
							alpha(wave_1) * pressure_ratio(wave_2.outside.P, wave_1.outside.P) 
							- 2 * alpha(wave_1) * alpha(wave_2) * pressure_ratio(wave_2.outside.P, wave_1.outside.P) 
							+ 2 * alpha(wave_2)
						)
						- 2 * alpha(wave_2) * std::pow(pressure_ratio(wave_2.outside.P, wave_1.outside.P), 2) * e(wave_1, wave_2) * 
						(
							alpha(wave_2) 
							+ 2 * alpha(wave_1) * pressure_ratio(wave_2.outside.P, wave_1.outside.P) 
							- 2 * alpha(wave_1) * alpha(wave_2)
						);
				}

				inline static double a_3(const wave_t& wave_1, const wave_t& wave_2)
				{
					return -2 * pressure_ratio(wave_2.outside.P, wave_1.outside.P) * (
						2 * std::pow(e(wave_2, wave_1), 2) * 
						(
							std::pow(alpha(wave_1) * pressure_ratio(wave_2.outside.P, wave_1.outside.P), 2) 
							- 3 * alpha(wave_1) * pressure_ratio(wave_2.outside.P, wave_1.outside.P) 
							+ 1
						)
						+ e(wave_1, wave_2) * e(wave_2, wave_1) * 
						(
							(
								alpha(wave_2) 
								+ alpha(wave_1) * pressure_ratio(wave_2.outside.P, wave_1.outside.P)
							) * 
							(
								std::pow(pressure_ratio(wave_2.outside.P, wave_1.outside.P), 2) 
								+ 4 * pressure_ratio(wave_2.outside.P, wave_1.outside.P) 
								+ 1
							)
							- 2 * alpha(wave_1) * alpha(wave_2) * pressure_ratio(wave_2.outside.P, wave_1.outside.P) * 
							(
								pressure_ratio(wave_2.outside.P, wave_1.outside.P) 
								+ 1
							)
							- 2 * pressure_ratio(wave_2.outside.P, wave_1.outside.P) * 
							(
								pressure_ratio(wave_2.outside.P, wave_1.outside.P) 
								+ 1
							)
						)
						+ 2 * std::pow(e(wave_1, wave_2), 2) * pressure_ratio(wave_2.outside.P, wave_1.outside.P) * 
						(
							std::pow(pressure_ratio(wave_2.outside.P, wave_1.outside.P), 2) 
							- 3 * alpha(wave_2) * pressure_ratio(wave_2.outside.P, wave_1.outside.P) 
							+ std::pow(alpha(wave_2), 2)
						)
						- alpha(wave_1) * alpha(wave_2) * pressure_ratio(wave_2.outside.P, wave_1.outside.P) * 
						(
							alpha(wave_1) * pressure_ratio(wave_2.outside.P, wave_1.outside.P) 
							+ alpha(wave_2)
						)
						+ e(wave_2, wave_1) * 
						(
							std::pow(alpha(wave_1) * pressure_ratio(wave_2.outside.P, wave_1.outside.P), 2) * alpha(wave_2)
							- 2 * pressure_ratio(wave_2.outside.P, wave_1.outside.P) * 
							(
								2 * alpha(wave_1) * alpha(wave_2) 
								+ std::pow(alpha(wave_1), 2) * pressure_ratio(wave_2.outside.P, wave_1.outside.P)
							)
							+ 2 * alpha(wave_1) * pressure_ratio(wave_2.outside.P, wave_1.outside.P) 
							+ alpha(wave_2)
						)
						+ e(wave_1, wave_2) * pressure_ratio(wave_2.outside.P, wave_1.outside.P) * 
						(
							alpha(wave_1) * std::pow(alpha(wave_2), 2)
							- 2 * alpha(wave_2) * 
							(
								alpha(wave_2) 
								+ 2 * alpha(wave_1) * pressure_ratio(wave_2.outside.P, wave_1.outside.P)
							)
							+ 2 * alpha(wave_2) * pressure_ratio(wave_2.outside.P, wave_1.outside.P)
							+ alpha(wave_1) * std::pow(pressure_ratio(wave_2.outside.P, wave_1.outside.P), 2)
						)
					);
				}

				inline static double a_4(const wave_t& wave_1, const wave_t& wave_2)
				{
					return std::pow(pressure_ratio(wave_2.outside.P, wave_1.outside.P), 2) * (
						std::pow(e(wave_2, wave_1), 2) * 
						(
							std::pow(alpha(wave_1) * pressure_ratio(wave_2.outside.P, wave_1.outside.P), 2) 
							- 8 * alpha(wave_1) * pressure_ratio(wave_2.outside.P, wave_1.outside.P) 
							+ 6
						)
						- 2 * e(wave_1, wave_2) * e(wave_2, wave_1) * 
						(
							alpha(wave_1) * alpha(wave_2) * pressure_ratio(wave_2.outside.P, wave_1.outside.P) 
							- 2 * 
							(
								pressure_ratio(wave_2.outside.P, wave_1.outside.P) 
								+ 1
							) * 
							(
								alpha(wave_2) 
								+ alpha(wave_1) * pressure_ratio(wave_2.outside.P, wave_1.outside.P)
							) 
							+ std::pow(pressure_ratio(wave_2.outside.P, wave_1.outside.P), 2) 
							+ 4 * pressure_ratio(wave_2.outside.P, wave_1.outside.P) 
							+ 1
						)
						+ std::pow(e(wave_1, wave_2), 2) * 
						(
							std::pow(alpha(wave_2), 2) 
							- 8 * alpha(wave_2) * pressure_ratio(wave_2.outside.P, wave_1.outside.P) 
							+ 6 * std::pow(pressure_ratio(wave_2.outside.P, wave_1.outside.P), 2)
						)
						+ std::pow(alpha(wave_2), 2) 
						+ 4 * alpha(wave_1) * alpha(wave_2) * pressure_ratio(wave_2.outside.P, wave_1.outside.P) 
						+ std::pow(alpha(wave_1) * pressure_ratio(wave_2.outside.P, wave_1.outside.P), 2)
						- 2 * e(wave_2, wave_1) * 
						(
							pressure_ratio(wave_2.outside.P, wave_1.outside.P) * 
							(
								std::pow(alpha(wave_1), 2) * pressure_ratio(wave_2.outside.P, wave_1.outside.P)
								+ 2 * alpha(wave_1) * alpha(wave_2)
							) 
							- 2 * 
							(
								2 * alpha(wave_1) * pressure_ratio(wave_2.outside.P, wave_1.outside.P) 
								+ alpha(wave_2)
							) 
							+ 1
						)
						- 2 * e(wave_1, wave_2) * 
						(
							alpha(wave_2) * 
							(
								2 * alpha(wave_1) * pressure_ratio(wave_2.outside.P, wave_1.outside.P) 
								+ alpha(wave_2)
							) 
							- 2 * pressure_ratio(wave_2.outside.P, wave_1.outside.P) * 
							(
								2 * alpha(wave_2) 
								+ alpha(wave_1) * pressure_ratio(wave_2.outside.P, wave_1.outside.P)
							) 
							+ std::pow(pressure_ratio(wave_2.outside.P, wave_1.outside.P), 2)
						)
					);
				}

				inline static double a_5(const wave_t& wave_1, const wave_t& wave_2)
				{
					return 2 * std::pow(pressure_ratio(wave_2.outside.P, wave_1.outside.P), 3) * (
						std::pow(e(wave_2, wave_1), 2) * 
						(
							alpha(wave_1) * pressure_ratio(wave_2.outside.P, wave_1.outside.P) 
							- 2
						)
						- e(wave_1, wave_2) * e(wave_2, wave_1) * 
						(
							alpha(wave_1) * pressure_ratio(wave_2.outside.P, wave_1.outside.P) 
							- 2 
							+ alpha(wave_2) 
							- 2 * pressure_ratio(wave_2.outside.P, wave_1.outside.P)
						)
						+ std::pow(e(wave_1, wave_2), 2) * 
						(
							alpha(wave_2) 
							- 2 * pressure_ratio(wave_2.outside.P, wave_1.outside.P)
						)
						+ alpha(wave_2) 
						+ alpha(wave_1) * pressure_ratio(wave_2.outside.P, wave_1.outside.P)
						- e(wave_2, wave_1) * 
						(
							2 * alpha(wave_1) * pressure_ratio(wave_2.outside.P, wave_1.outside.P) 
							+ alpha(wave_2) 
							- 2
						)
						- e(wave_1, wave_2) * 
						(
							2 * alpha(wave_2) 
							+ alpha(wave_1) * pressure_ratio(wave_2.outside.P, wave_1.outside.P) 
							- 2 * pressure_ratio(wave_2.outside.P, wave_1.outside.P)
						)
					);
				}

				inline static double a_6(const wave_t& wave_1, const wave_t& wave_2)
				{
					return std::pow(pressure_ratio(wave_2.outside.P, wave_1.outside.P), 4) * (
						std::pow(
							e(wave_2, wave_1) 
							- e(wave_1, wave_2), 
						2) 
						+ 1 
						- 2 * (e(wave_2, wave_1) + e(wave_1, wave_2))
					);
				}
			};

		private:

			friend void from_json(const nlohmann::json&, Model&);

		private:

			wave_t m_wave_1;
			wave_t m_wave_2;

			Type m_type;

			equation_t m_equation;

		}; // class Model

	} // namespace source

} // namespace compmath