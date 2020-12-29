#include "sppch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Spydr/Input/Input.h"
#include "Spydr/Events/Event.h"
#include "Spydr/Events/KeyEvent.h"
#include "Spydr/Input/KeyCodes.h"

namespace Spydr
{
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float near_, float far_)
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, near_, far_)), m_ViewMatrix(1.0f), m_Position({0.0f, 0.0f, 0.0f})
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));
		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::OnUpdate()
	{
		glm::vec3 movement = glm::vec3(0.0f, 0.0f, 0.0f);
		if (Input::IsKeyPressed(SP_KEY_W)) {
			movement.y += 0.075f;
		}
		else if (Input::IsKeyPressed(SP_KEY_S)) {
			movement.y -= 0.075f;
		}
		
		if (Input::IsKeyPressed(SP_KEY_D)) {
			movement.x += 0.075f;
		}
		else if (Input::IsKeyPressed(SP_KEY_A)) {
			movement.x -= 0.075f;
		}

		if (movement != glm::vec3(0.0f, 0.0f, 0.0f)) {
			m_Position += movement;
			RecalculateViewMatrix();
		}
	}

	void OrthographicCamera::OnEvent(Event& event)
	{
		if (event.GetEventType() == EventType::KeyPressed) {
			KeyPressedEvent& e = (KeyPressedEvent&)event;
			if (e.GetKeyCode() == SP_KEY_F1) {
				m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
				RecalculateViewMatrix();
			}
		}
	}
}