#include "system.hpp"

namespace compmath
{
	void System::initialize()
	{
		try
		{
			load_model();
		}
		catch (const std::exception& e)
		{
			throw system_exception("System initialize error: " + std::string(e.what()));
		}
	}

	void System::load_model()
	{
		try
		{
			Data::load_model(m_model);
		}
		catch (const std::exception& e)
		{
			throw system_exception("System load model error: " + std::string(e.what()));
		}
	}

	void System::Data::load_model(source::Model& model)
	{
		try
		{
			json_t raw_model;

			load(Directory::config_model / File::config_json, raw_model);

			model = raw_model.get < source::Model >();
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
			m_model.solve();
		}
		catch (const std::exception& e)
		{
			throw system_exception("System run error: " + std::string(e.what()));
		}
	}

} // namespace compmath