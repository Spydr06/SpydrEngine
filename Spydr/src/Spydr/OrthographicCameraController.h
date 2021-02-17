#pragma once
#include "Spydr/Renderer/Cameras/OrthographicCamera.h"
#include "Spydr/Core/Timestep.h"

#include "Spydr/Events/ApplicationEvent.h"
#include "Spydr/Events/MouseEvent.h"

namespace Spydr
{
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		void SetZoomLevel(float level) { m_ZoomLevel = level; }
		float GetZoomLevel(float level) { return m_ZoomLevel; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		bool m_Rotation;

		OrthographicCamera m_Camera;

		float m_CameraRotation = 0.0f;
		float m_CameraTranslationSpeed = 3.0f;
		float m_CameraRotationSpeed = 180.0f;
		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
	};
}