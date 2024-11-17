#pragma once

#include "Component.h"

namespace Cannis {
	struct ModelComponent : IComponent {
		ModelComponent() = default;

		ModelComponent(uint8_t p_componentID) { 
			componentID = p_componentID; 
		}
	};
}