#include <Spydr.h>
#include <imgui/imgui.h>

class ExampleLayer : public Spydr::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{
		float vertices[7 * 7]{
			-0.6f, -0.6f, 0.0f, 0.8f, 0.2f, 0.3f, 1.0f,
			 0.6f, -0.6f, 0.0f,	0.2f, 0.8f, 0.3f, 1.0f,
			 0.6f,  0.6f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			-0.6f,  0.6f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			-0.4f, -0.4f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			 0.4f, -0.4f, 0.0f, 0.2f, 0.2f, 0.2f, 1.0f,
			 0.0f,  0.4f, 0.0f, 0.8f, 0.8f, 0.8f, 1.0f
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

			out vec3 v_Position;
			out vec4 v_Color;

			void main() {
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main() {
				//color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(Spydr::Shader::Create(vertexSrc, fragmentSrc));
	}

	void OnUpdate() override
	{
		glm::vec3 cameraPosition = m_Camera->GetPosition();
		if (Spydr::Input::IsKeyPressed(SP_KEY_W)) {
			cameraPosition.y += 0.1f;
		}
		if (Spydr::Input::IsKeyPressed(SP_KEY_A)) {
			cameraPosition.x -= 0.1f;
		}
		if (Spydr::Input::IsKeyPressed(SP_KEY_S)) {
			cameraPosition.y -= 0.1f;
		}
		if (Spydr::Input::IsKeyPressed(SP_KEY_D)) {
			cameraPosition.x += 0.1;
		}
		m_Camera->SetPosition(cameraPosition);

		Spydr::RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
		Spydr::RenderCommand::Clear();

		Spydr::Renderer::BeginScene(*m_Camera);
		Spydr::Renderer::SubmitVertexData(m_VertexArray, m_Shader);
		Spydr::Renderer::EndScene();
	}

	void OnEvent(Spydr::Event& event) override
	{
	}

	void OnImGuiRender()
	{
	}
private:
	std::shared_ptr<Spydr::Shader> m_Shader;
	std::shared_ptr<Spydr::VertexArray> m_VertexArray;
	Spydr::OrthographicCamera* m_Camera;
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