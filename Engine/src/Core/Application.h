#pragma once

#include "Core.h"

namespace Cannis {
	class CANNIS_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	Application* CreateApplication();
}