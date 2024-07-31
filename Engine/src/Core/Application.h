#pragma once

#include "Core.h"

namespace CannisCanno {
	class CANNIS_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	Application* CreateApplication();
}