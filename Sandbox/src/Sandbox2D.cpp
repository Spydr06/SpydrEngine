#include "Sandbox2D.h"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

#include <chrono>

//#define SP_ENABLE_PROFILING

template<typename Fn>
class Timer
{
public:
	Timer(const char* name, Fn&& func) 
		: m_Name(name), m_Func(func), m_Stopped(false)
	{
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		if (!m_Stopped) {
			Stop();
		}
	}

	void Stop() 
	{
		auto endTimepoint = std::chrono::high_resolution_clock::now();

		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

		m_Stopped = true;

		float duration = (end - start) * 0.001f;
		m_Func({ m_Name, duration });
	}
private:
	const char* m_Name;
	std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
	bool m_Stopped;
	Fn& m_Func;
};

#ifdef SP_ENABLE_PROFILING
#define PROFILE_SCOPE(name) Timer timer##__LINE__(name, [&](ProfileResult profileResult) { m_ProfileResults.push_back(profileResult); })
#else
#define PROFILE_SCOPE(name)
#endif

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(16.0f / 9.0f)
{
}

void Sandbox2D::OnAttach()
{
	m_Texture = Spydr::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Spydr::Timestep ts)
{
	PROFILE_SCOPE("Sandbox2D::OnUpdate");
	//Update
	{
		PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(ts);
	}

	//Render
	{
		PROFILE_SCOPE("Renderer Prep");
		Spydr::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Spydr::RenderCommand::Clear();
	}

	{
		PROFILE_SCOPE("Renderer Draw");
		Spydr::Renderer2D::BeginScene(m_CameraController.GetCamera());

		Spydr::Renderer2D::DrawQuad({ 0.0f, 0.0f }, 0.0f, { 10.0f, 10.0f }, m_Texture);
		Spydr::Renderer2D::DrawQuad({ 0.5f, -0.5f, 0.1f }, 0.0f, { 1.5f, 0.5f }, { 0.8f, 0.2f, 0.3f, 0.8f });
	}
	Spydr::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();

#ifdef SP_ENABLE_PROFILING
	ImGui::Begin("Profiler");
	for (auto& result : m_ProfileResults) 
	{
		char label[64];
		strcpy(label, "%.3fms	");
		strcat(label, result.Name);
		ImGui::Text(label, result.Time);
	}

	ImGui::End();
	m_ProfileResults.clear();
#endif
}

void Sandbox2D::OnEvent(Spydr::Event& e)
{
	m_CameraController.OnEvent(e);
}