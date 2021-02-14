#include <Spydr.h>
#include <imgui/imgui.h>

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Platform/OpenGL/OpenGLShader.h"

class ExampleLayer : public Spydr::Layer
{
public:
	ExampleLayer() : Layer("Example"), m_SquarePosition({ 0.0f, 0.0f, 0.0f })
	{
		float vertices[7 * 7]{
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.3f, 1.0f,
			 0.5f, -0.5f, 0.0f,	0.2f, 0.8f, 0.3f, 1.0f,
			 0.5f,  0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			-0.3f, -0.3f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			 0.3f, -0.3f, 0.0f, 0.2f, 0.2f, 0.2f, 1.0f,
			 0.0f,  0.3f, 0.0f, 0.8f, 0.8f, 0.8f, 1.0f
		};

		unsigned int indices[9]{ 0, 1, 2, 2, 3, 0, 4, 5, 6 };

		m_Camera = new Spydr::OrthographicCamera(-1.6f, 1.6f, -0.9f, 0.9f);
		m_VertexArray.reset(Spydr::VertexArray::Create());

		std::shared_ptr<Spydr::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Spydr::VertexBuffer::Create(vertices, sizeof(vertices)));

		Spydr::BufferLayout layout = {
			{ Spydr::ShaderDataType::Float3, "a_Position" },
			{ Spydr::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		std::shared_ptr<Spydr::IndexBuffer> indexBuffer;
		indexBuffer.reset(Spydr::IndexBuffer::Create(indices, ARRAY_SIZE(indices)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main() {
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			uniform vec3 u_Color;

			void main() {
				//color = vec4(v_Position * 0.5 + 0.5, 1.0);
				//color = v_Color * u_Color;
				color = vec4(u_Color, 1);
			}
		)";

		m_Shader.reset(Spydr::Shader::Create(vertexSrc, fragmentSrc));
	}

	void OnUpdate(Spydr::Timestep ts) override
	{
		Move(ts);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.2f));

		Spydr::RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
		Spydr::RenderCommand::Clear();

		Spydr::Renderer::BeginScene(*m_Camera);

		//Future material system:
		//Spydr::MaterialRef material = new Spydr::Material(m_Shader);
		//Spydr::MaterialInstanceRef mi = new Spydr::MaterialInstance(material);
		//material->Set("u_Color", redColor);

		std::dynamic_pointer_cast<Spydr::OpenGLShader>(m_Shader)->Bind();
		std::dynamic_pointer_cast<Spydr::OpenGLShader>(m_Shader)->UploadUniformFloat3("u_Color", m_SquareColor);

		glm::vec4 redColor(0.8f, 0.2f, 0.3f, 1.0f);
		glm::vec4 blueColor(0.2f, 0.3f, 0.8f, 1.0f);
		for (int i = 0; i < 5; i++) {
			glm::vec3 pos(i * 0.22f, 0.0f, 0.0f);
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
			Spydr::Renderer::SubmitVertexData(m_VertexArray, m_Shader, transform);
		}

		Spydr::Renderer::EndScene();
	}

	void Move(Spydr::Timestep ts)
	{
		m_Time = ts;
		glm::vec3 cameraPosition = m_Camera->GetPosition();
		if (Spydr::Input::IsKeyPressed(SP_KEY_W)) {
			cameraPosition.y += m_CameraSpeed * m_Time;
		}
		if (Spydr::Input::IsKeyPressed(SP_KEY_A)) {
			cameraPosition.x -= m_CameraSpeed * m_Time;
		}
		if (Spydr::Input::IsKeyPressed(SP_KEY_S)) {
			cameraPosition.y -= m_CameraSpeed * m_Time;
		}
		if (Spydr::Input::IsKeyPressed(SP_KEY_D)) {
			cameraPosition.x += m_CameraSpeed * m_Time;
		}
		m_Camera->SetPosition(cameraPosition);

		float cameraRotation = m_Camera->GetRotation();
		if (Spydr::Input::IsKeyPressed(SP_KEY_Y)) {
			cameraRotation += m_RotationSpeed * m_Time;
		}
		if (Spydr::Input::IsKeyPressed(SP_KEY_X)) {
			cameraRotation -= m_RotationSpeed * m_Time;
		}
		m_Camera->SetRotation(cameraRotation);
	}

	void OnEvent(Spydr::Event& event) override
	{
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
	std::shared_ptr<Spydr::Shader> m_Shader;
	std::shared_ptr<Spydr::VertexArray> m_VertexArray;
	Spydr::OrthographicCamera* m_Camera;

	float m_CameraSpeed = 2.5f;
	float m_RotationSpeed = 50.0f;
	float m_Time = 0.0f;

	bool m_ShowImGuiDemoWindow = true;

	glm::vec3 m_SquarePosition;
	glm::vec3 m_SquareColor = {0.2f, 0.3f, 0.8f};
};

class Sandbox : public Spydr::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Spydr::Application* Spydr::CreateApplication()
{
	return new Sandbox();
}