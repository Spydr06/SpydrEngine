#pragma once

#include "Spydr.h"

class Sandbox2D : public Spydr::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(Spydr::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Spydr::Event& e) override;
private:
	Spydr::OrthographicCameraController m_CameraController;

	//Temp
	Spydr::Ref<Spydr::VertexArray> m_SquareVA;
	Spydr::Ref<Spydr::Shader> m_FlatColorShader;

	Spydr::Ref<Spydr::Texture2D> m_Texture;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};