#pragma once

#include "Spydr.h"
#include <imgui/imgui.h>
#include "Level.h"

class GameLayer : public Spydr::Layer
{
public: 
	GameLayer();

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Spydr::Timestep ts);
	virtual void OnImGuiRender() override;
	void OnEvent(Spydr::Event& e) override;
	bool OnMouseButtonPressed(Spydr::MouseButtonPressedEvent& e);
	bool OnWindowResize(Spydr::WindowResizeEvent& e);
private:
	void CreateCamera(uint32_t width, uint32_t height);

	Spydr::Scope<Spydr::OrthographicCamera> m_Camera;
	Level m_Level;
	ImFont* m_Font;
	float m_Time = 0.0f;
	bool m_Blink = false;

	enum class GameState
	{
		Play = 0, Menu = 1, GameOver = 2
	};

	GameState m_State = GameState::Menu;
};