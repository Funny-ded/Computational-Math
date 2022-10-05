#include "model.hpp"


namespace compmath
{
	namespace source
	{
		void Model::solve()
		{
			try
			{	
				std::cout << "Equation: " << std::endl;
				std::cout << m_equation << std::endl;

				std::cout << "Roots: " << std::endl;

				for (const auto& root : polynom::Solver()(m_equation))
				{
					std::cout << root << std::endl;

					m_wave_1.inside.P = root * m_wave_1.outside.P;
					m_wave_2.inside.P = m_wave_1.inside.P;

					m_wave_1.inside.U = U_inside_system(root);
					m_wave_2.inside.U = m_wave_1.inside.U;

					std::cout << "D_0 = " << Redefiner::discontunity_speed(m_wave_1) << "; D_3 = " << Redefiner::discontunity_speed(m_wave_2) << ";" << std::endl;
				}

			}
			catch (const std::exception& e)
			{
				throw model_exception("Model solve error: " + std::string(e.what()));
			}
			
		}

		Model::Type Model::convert_type(const std::string& type)
		{
			try
			{
				if (type == "double_shock")
				{
					return Type::Double_Shock;
				}
				if (type == "high_speed_double_shock")
				{
					return Type::High_Speed_Double_Shock;
				}
				if (type == "shock_discharge")
				{
					return Type::Shock_Discharge;
				}

				throw model_exception("Invalid type " + type);
			}
			catch (const std::exception& e)
			{
				throw model_exception("Model conver type error: " + std::string(e.what()));
			}

		}

		const double Model::U_inside_system(const double Y)
		{
			try
			{
				static const std::vector < std::pair < int, int > > signs =
				{
					std::make_pair(1, 1),
					std::make_pair(1, -1),
					std::make_pair(-1, 1),
					std::make_pair(-1, -1),
				};

				for (const auto [sign_1, sign_2] : signs)
				{
					auto U_1_1 = m_wave_1.outside.U
						+ sign_1 * (Redefiner::sound_speed(m_wave_1) * std::pow(2, 0.5)) / std::pow(m_wave_1.outside.gamma * (m_wave_1.outside.gamma - 1), 0.5)
						* (Y - 1) / std::pow(1 + Redefiner::alpha(m_wave_1) * Y, 0.5);

					auto U_1_2 = m_wave_2.outside.U
						+ sign_2 * (Redefiner::sound_speed(m_wave_2) * std::pow(2, 0.5)) / std::pow(m_wave_2.outside.gamma * (m_wave_2.outside.gamma - 1), 0.5)
						* (Y - Redefiner::pressure_ratio(m_wave_1, m_wave_2)) / std::pow(Redefiner::pressure_ratio(m_wave_1, m_wave_2) * (Redefiner::pressure_ratio(m_wave_1, m_wave_2) + Redefiner::alpha(m_wave_2) * Y), 0.5);

					if (std::abs(U_1_1 - U_1_2) <= 1.0)
					{
						return (U_1_1 + U_1_2) / 2;
					}
				}

				throw model_exception("No solution for root: " + std::to_string(Y));
			}
			catch (const std::exception& e)
			{
				throw model_exception("Model U inside system error: " + std::string(e.what()));
			}
		}

		void from_json(const nlohmann::json& obj, Model& model)
		{
			model.m_type = model.convert_type(obj["type"].get < std::string >());
			model.m_wave_1 = obj["waves"]["wave_1"].get < Model::wave_t >();
			model.m_wave_2 = obj["waves"]["wave_2"].get < Model::wave_t >();

			model.m_equation = Model::equation_t(model.coefficients());
		}

	} // namespace source

} // namespace compmath