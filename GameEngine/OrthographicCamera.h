#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm/glm.hpp>
#include "Matrix.h"
#include "GameObject.h"

namespace GameEngine {
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float top, float bottom, float left, float right);

		const glm::vec3& GetPosition() const { return m_position; };
		void SetPosition(const glm::vec3& position) { m_position = position; RecalculateViewMatrix(); };
		void LockToObject(const struct GameObject& gameObject);
		float GetRotation() const { return m_rotation; };
		void SetRotation(float rotation) { m_rotation = rotation; RecalculateViewMatrix(); };
		const glm::mat4& GetProjectionMatrix() const { return m_projectionMatrix; };
		const glm::mat4& GetViewMatrix() const { return m_viewMatrix; };
		const glm::mat4& GetViewProjectionMatrix() const { return m_viewProjectionMatrix; };
	private:
		void RecalculateViewMatrix();
	public:
		glm::mat4 m_viewMatrix;
		glm::mat4 m_projectionMatrix;
		glm::mat4 m_viewProjectionMatrix;

		glm::vec3 m_position{0,0,0};
		float m_rotation = 0.0f;
	};
}


