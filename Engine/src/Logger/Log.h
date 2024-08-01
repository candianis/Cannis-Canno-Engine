#pragma once

#include "../Core/Core.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <memory>

namespace Cannis {
	class CANNIS_API Log {
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger;  }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define CC_CORE_CRITICAL(...) ::Cannis::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define CC_CORE_ERROR(...) ::Cannis::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CC_CORE_WARN(...)  ::Cannis::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CC_CORE_INFO(...)  ::Cannis::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CC_CORE_TRACE(...) ::Cannis::Log::GetCoreLogger()->trace(__VA_ARGS__)

//Client log macros
#define CC_CLIENT_CRITICAL(...) ::Cannis::Log::GetClientLogger()->critical(__VA_ARGS__)
#define CC_CLIENT_ERROR(...) ::Cannis::Log::GetClientLogger()->error(__VA_ARGS__)
#define CC_CLIENT_WARN(...)  ::Cannis::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CC_CLIENT_INFO(...)  ::Cannis::Log::GetClientLogger()->info(__VA_ARGS__)
#define CC_CLIENT_TRACE(...) ::Cannis::Log::GetClientLogger()->trace(__VA_ARGS__)
