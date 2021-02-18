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
	m_SquareVA = Spydr::VertexArray::Create();

	float vertices[5 * 4]{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
	};
	Spydr::Ref<Spydr::VertexBuffer> squareVB = Spydr::VertexBuffer::Create(vertices, sizeof(vertices));

	Spydr::BufferLayout layout = {
		{ Spydr::ShaderDataType::Float3, "a_Position" },
		{ Spydr::ShaderDataType::Float2, "a_TexCoord" },
	};
	squareVB->SetLayout(layout);
	m_SquareVA->AddVertexBuffer(squareVB);

	unsigned int indices[6]{ 0, 1, 2, 2, 3, 0 };
	Spydr::Ref<Spydr::IndexBuffer> squareIB = Spydr::IndexBuffer::Create(indices, (uint32_t)ARRAY_SIZE(indices));
	m_SquareVA->SetIndexBuffer(squareIB);

	m_FlatColorShader = Spydr::Shader::Create("assets/shaders/FlatColor.glsl");
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

	Spydr::Renderer::BeginScene(m_CameraController.GetCamera());

	std::dynamic_pointer_cast<Spydr::OpenGLShader>(m_FlatColorShader)->Bind();
	std::dynamic_pointer_cast<Spydr::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

	for (int y = 0; y < 20; y++) {
		for (int x = 0; x < 20; x++) {
			glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
			Spydr::Renderer::SubmitVertexData(m_SquareVA, m_FlatColorShader, transform);
		}
	}

	Spydr::Renderer::EndScene();
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
