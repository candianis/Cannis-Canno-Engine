#pragma once

#include "Component.h"

namespace Cannis {
	struct GUIComponent : IComponent {
		GUIComponent() : isSelected(false) {}

		bool isSelected;
	};
}