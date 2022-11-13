#include "system.hpp"

namespace compmath
{
	void System::initialize()
	{
		try
		{
			m_interpolation.insert(std::make_pair("lagrange", new lagrange_t()));
			m_interpolation.insert(std::make_pair("newton", new newton_t()));

			std::cout << "Choose your interpolation type: \n\t1. lagrange\n\t2. newton\n" << std::endl;
			std::cout << "Answer: ";

			std::cin >> m_interpolation_type;

			if (m_interpolation_type != "lagrange" && m_interpolation_type != "newton")
			{
				throw system_exception("Wrong interpolation type");
			}

			load_values();
		}
		catch (const std::exception& e)
		{
			throw system_exception("System initialize error: " + std::string(e.what()));
		}
	}

	void System::load_values()
	{
		try
		{
			Data::load_values(m_params, m_values);
		}
		catch (const std::exception& e)
		{
			throw system_exception("System load values error: " + std::string(e.what()));
		}
	}

	void System::Data::load_values(std::vector < value_t >& params, std::vector < value_t >& values)
	{
		try
		{
			json_t raw_data;

			load(Directory::config / File::values_json, raw_data);

			params = raw_data["params"].get < std::vector < value_t > >();
			values = raw_data["values"].get < std::vector < value_t > >();
		}
		catch (const std::exception& e)
		{
			throw system_exception("System data load model error: " + std::string(e.what()));
		}
	}

	void System::Data::load(const path_t& path, json_t& object)
	{
		try
		{
			std::fstream fin(path, std::ios::in);

			if (!fin)
			{
				throw system_exception("Cannot open file " + path.string());
			}

			fin >> object;
		}
		catch (const std::exception& e)
		{
			throw system_exception("System data load error: " + std::string(e.what()));
		}
	}

	void System::run()
	{
		try
		{
			auto interpolation = m_interpolation[m_interpolation_type]->interpolate(m_params, m_values);

			auto interpolation_der = interpolation.derivative();

			std::cout << "\nInterpolation: " << interpolation << std::endl;
			std::cout << "Interpolation derivative: " << interpolation_der << std::endl;

			std::vector < double > derivatives;
			derivatives.reserve(std::size(m_params));

			std::transform(std::begin(m_params), std::end(m_params), std::back_inserter(derivatives),
				[&interpolation_der](const auto val) { return interpolation_der(val); });

			auto splines = m_spline.spline(m_params, m_values, derivatives);

			std::cout << "\nSplines: " << std::endl;
			for (const auto& spline : splines)
			{
				std::cout << spline << std::endl;
			}

			std::string input;

			std::cout << "\nInput params to count values using spline (print 'exit' to exit): \n>> ";
			for (std::cin >> input; input != "exit"; std::cout << ">> ", std::cin >> input)
			{
				auto param = std::stod(input);
				if (param < m_params[0] || param > m_params.back())
				{
					std::cout << "Wrong param. Please, input values between " << m_params[0] << " and " << m_params.back() << std::endl;
					continue;
				}

				auto n = std::size(m_params) / 2;
				for (; !(param <= m_params[n] && param >= m_params[n - 1]);)
				{
					if (param < m_params[n - 1])
					{
						n -= (std::size(m_params) - n) / 2;
					}
					else if(param > m_params[n])
					{
						n += (std::size(m_params) - n) / 2;
					}
				}

				std::cout << splines[n - 1](param) << std::endl;
			}
		}
		catch (const std::exception& e)
		{
			throw system_exception("System run error: " + std::string(e.what()));
		}
	}

} // namespace compmath