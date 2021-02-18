#include "Sandbox2D.h"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

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
	//Update
	m_CameraController.OnUpdate(ts);

	//Render
	Spydr::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	Spydr::RenderCommand::Clear();

	Spydr::Renderer2D::BeginScene(m_CameraController.GetCamera());

	Spydr::Renderer2D::DrawQuad({ 0.0f, 0.0f }, 0.0f, { 10.0f, 10.0f }, m_Texture);
	Spydr::Renderer2D::DrawQuad({ 0.5f, -0.5f, 0.1f }, 0.0f, { 1.5f, 0.5f }, {0.8f, 0.2f, 0.3f, 0.8f});

	Spydr::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Spydr::Event& e)
{
	m_CameraController.OnEvent(e);
}