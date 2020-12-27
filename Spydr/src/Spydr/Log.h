#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Spydr
{
	class SPYDR_API Log
	{
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() {return s_CoreLogger;}
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

#undef SP_ERROR //undef SP_ERROR because its used by an external lib

//Core log macros
#define SP_CORE_FATAL(...) ::Spydr::Log::GetCoreLogger()->fatal(__VA_ARGS__)
#define SP_CORE_ERROR(...) ::Spydr::Log::GetCoreLogger()->error(__VA_ARGS__)
#define SP_CORE_WARN(...)  ::Spydr::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define SP_CORE_INFO(...)  ::Spydr::Log::GetCoreLogger()->info(__VA_ARGS__)
#define SP_CORE_TRACE(...) ::Spydr::Log::GetCoreLogger()->trace(__VA_ARGS__)

//Client log macros
#define SP_FATAL(...) ::Spydr::Log::GetClientLogger()->fatal(__VA_ARGS__)
#define SP_ERROR(...) ::Spydr::Log::GetClientLogger()->error(__VA_ARGS__)
#define SP_WARN(...)  ::Spydr::Log::GetClientLogger()->warn(__VA_ARGS__)
#define SP_INFO(...)  ::Spydr::Log::GetClientLogger()->info(__VA_ARGS__)
#define SP_TRACE(...) ::Spydr::Log::GetClientLogger()->trace(__VA_ARGS__)