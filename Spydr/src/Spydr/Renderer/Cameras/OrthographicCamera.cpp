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
}