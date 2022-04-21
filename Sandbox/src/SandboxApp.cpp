#include <Spydr.h>
#include <Spydr/Core/EntryPoint.h>
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Platform/OpenGL/OpenGLShader.h"

#include "Sandbox2D.h"

/*class ExampleLayer : public Spydr::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(16.0f / 9.0f)
	{
		float vertices[5 * 4] {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		unsigned int indices[6]{ 0, 1, 2, 2, 3, 0 };

		m_VertexArray = Spydr::VertexArray::Create();

		Spydr::Ref<Spydr::VertexBuffer> squareVB;
		squareVB = Spydr::VertexBuffer::Create(vertices, sizeof(vertices));

		Spydr::BufferLayout layout = {
			{ Spydr::ShaderDataType::Float3, "a_Position" }
		};
		squareVB->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(squareVB);

		Spydr::Ref<Spydr::IndexBuffer> indexBuffer;
		indexBuffer = Spydr::IndexBuffer::Create(indices, (uint32_t) ARRAY_SIZE(indices));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_ShaderLibrary.Load("assets/shaders/FlatColor.glsl");
		m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = Spydr::Texture2D::Create("assets/textures/Checkerboard.png");
		m_LogoTexture = Spydr::Texture2D::Create("assets/textures/SpydrLogo.png");

		m_ShaderLibrary.Get("Texture")->Bind();
		std::dynamic_pointer_cast<Spydr::OpenGLShader>(m_ShaderLibrary.Get("Texture"))->UploadUniformInt("u_Texture", 0);
	} 

	void OnUpdate(Spydr::Timestep ts) override
	{
		//Update
		m_CameraController.OnUpdate(ts);
		m_Time = ts;

		//Render
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.2f));

		Spydr::RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
		Spydr::RenderCommand::Clear();

		Spydr::Renderer::BeginScene(m_CameraController.GetCamera());

		auto flatColorShader = m_ShaderLibrary.Get("FlatColor");
		auto textureShader = m_ShaderLibrary.Get("Texture");

		flatColorShader->Bind();
		std::dynamic_pointer_cast<Spydr::OpenGLShader>(flatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				glm::vec3 pos(i * 0.22f, j * 0.22f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Spydr::Renderer::SubmitVertexData(m_VertexArray, flatColorShader, transform);
			}
		}

		m_Texture->Bind();
		Spydr::Renderer::SubmitVertexData(m_VertexArray, textureShader, glm::scale(glm::mat4(1.0f), glm::vec3(0.5f)));
		m_LogoTexture->Bind();
		Spydr::Renderer::SubmitVertexData(m_VertexArray, textureShader, glm::scale(glm::mat4(1.0f), glm::vec3(0.5f)));

		Spydr::Renderer::EndScene();
	}

	void OnEvent(Spydr::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}

	void OnImGuiRender()
	{
		ImGui::Begin("Sandbox");
		ImGui::Text("Frame Rate: ");
		ImGui::Text("%i",(int) (1 / m_Time));

		ImGui::Checkbox("Show Demo Window", &m_ShowImGuiDemoWindow);
		if (m_ShowImGuiDemoWindow) {
			bool show = true;
			ImGui::ShowDemoWindow(&show);
		}

		ImGui::End();

		ImGui::Begin("Settings");
		ImGui::Text("Square Color:");
		ImGui::ColorPicker3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}
private:
	Spydr::ShaderLibrary m_ShaderLibrary;
	Spydr::Ref<Spydr::VertexArray> m_VertexArray;
	Spydr::Ref<Spydr::Texture2D> m_Texture, m_LogoTexture;

	Spydr::OrthographicCameraController m_CameraController;

	float m_Time = 0.0f;
	bool m_ShowImGuiDemoWindow = true;

	glm::vec3 m_SquareColor = {0.2f, 0.3f, 0.8f};
};*/

class Sandbox : public Spydr::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{

	}
};

Spydr::Application* Spydr::CreateApplication()
{
	return new Sandbox();
}