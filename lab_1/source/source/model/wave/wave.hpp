#pragma once

#include <nlohmann/json.hpp>

namespace compmath
{
	namespace source
	{
		namespace model
		{
			struct Wave
			{
				struct Half_Space
				{
					double gamma;
					double rho;
					double U;
					double P;
				};

				enum class Type
				{
					Shock,
					Discharge
				};

				Half_Space inside; // outside - inside
				Half_Space outside;

				double discontunity_speed;

			}; // struct Wave

			void from_json(const nlohmann::json&, Wave::Half_Space&);

			void from_json(const nlohmann::json&, Wave&);

		} // namespace model

	} // namespace source

} // namespace compmath