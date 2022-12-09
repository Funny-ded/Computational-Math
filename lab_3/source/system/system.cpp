#include "system.hpp"

namespace compmath
{
	void System::handle_user_inputs() const
	{
		try
		{
			std::string input;

			std::cout << "\nInput params to count values using spline (print 'exit' to exit): \n>> ";
			for (std::cin >> input; input != "exit"; std::cout << ">> ", std::cin >> input)
			{
				auto h = (m_problem.equation().right_border() - m_problem.equation().left_border()) / (std::stoi(input) - 1);

				print_solution(m_problem(h, m_eps), std::stoi(input));
			}
		}
		catch (const std::exception& e)
		{
			throw system_exception("System handle user inputs exception: " + std::string(e.what()));
		}
	}

	void System::print_solution(const std::vector < double >& solution, const int node_number) const
	{
		try
		{
			auto h = (m_problem.equation().right_border() - m_problem.equation().left_border()) / (node_number - 1);

			auto k = std::size(solution) / node_number;

			for (auto i = 0U; i < node_number; ++i)
			{
				std::cout << i + 1 << ": y(" << m_problem.equation().left_border() + h * i << ") = " << solution[i * k] << std::endl;
			}
		}
		catch (const std::exception& e)
		{
			throw system_exception("System handle user inputs exception: " + std::string(e.what()));
		}
	}

	void System::run()
	{
		try
		{
			auto h = (m_problem.equation().right_border() - m_problem.equation().left_border()) / (m_node_number - 1);

			print_solution(m_problem(h, m_eps), m_node_number);

			handle_user_inputs();
		}
		catch (const std::exception& e)
		{
			throw system_exception("System run error: " + std::string(e.what()));
		}
	}

} // namespace compmath