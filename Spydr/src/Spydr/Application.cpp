#include "sppch.h"
#include "Application.h"

#include "Spydr/Events/ApplicationEvent.h"
#include "Spydr/Log.h"

#include "Spydr/Input/Input.h"

namespace Spydr
{

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application() : m_Camera(new OrthographicCamera(-1.6f, 1.6f, -0.9f, 0.9f))
	{
		SP_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
		PushLayer(m_Camera);

		float vertices[7 * 7] {
			-0.6f, -0.6f, 0.0f, 0.8f, 0.2f, 0.3f, 1.0f,
			 0.6f, -0.6f, 0.0f,	0.2f, 0.8f, 0.3f, 1.0f,
			 0.6f,  0.6f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			-0.6f,  0.6f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			-0.4f, -0.4f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			 0.4f, -0.4f, 0.0f, 0.2f, 0.2f, 0.2f, 1.0f,
			 0.0f,  0.4f, 0.0f, 0.8f, 0.8f, 0.8f, 1.0f
		};

		unsigned int indices[9]{ 0, 1, 2, 2, 3, 0, 4, 5, 6 };

		m_VertexArray.reset(VertexArray::Create());

		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, ARRAY_SIZE(indices)));
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

		m_Shader.reset(Shader::Create(vertexSrc, fragmentSrc));
	}

	Application::~Application()
	{

	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) {
			(*--it)->OnEvent(e);
			if (e.Handled) {
				break;
			}
		}
	}

	void Application::Run()
	{
		while (m_Running) {
			RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
			RenderCommand::Clear();

			Renderer::BeginScene(*m_Camera);
			Renderer::SubmitVertexData(m_VertexArray, m_Shader);
			Renderer::EndScene();

			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate();
			}
			m_VertexArray->Unbind();
			m_Shader->Unbind();

			m_ImGuiLayer->Begin();	
			for (Layer* layer : m_LayerStack) {
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;

		return true;
	}
}