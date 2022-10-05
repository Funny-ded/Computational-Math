#include "wave.hpp"

namespace compmath
{
	namespace source
	{
		namespace model
		{
			void from_json(const nlohmann::json& obj, Wave::Half_Space& half_space)
			{
				half_space.gamma	= obj["gamma"]	.get < double >();
				half_space.rho		= obj["rho"]	.get < double >();
				half_space.U		= obj["U"]		.get < double >();
				half_space.P		= obj["P"]		.get < double >();
			}

			void from_json(const nlohmann::json& obj, Wave& wave)
			{
				if (obj.contains("outside"))
				{
					wave.outside = obj["outside"].get < Wave::Half_Space >();
				}

				if (obj.contains("inside"))
				{
					wave.inside = obj["inside"].get < Wave::Half_Space >();
				}

				if (obj.contains("D"))
				{
					wave.discontunity_speed = obj["D"].get < double >();
				}
			}

		} //namespace model

	} // namespace source

} // namespace compmath