#pragma once

#include "Component.h"

namespace Cannis {
	struct MeshComponent : IComponent {
		MeshComponent() = default;

		MeshComponent(uint8_t p_componentID) { 
			componentID = p_componentID; 
		}
	};
}