#include "OrthographicCamera.h"
#include <iostream>
#include <cmath>
#include <glm/glm/gtc/matrix_transform.hpp>
#include "GameObject.h"
#include "Vector2.h"

namespace GameEngine {
	OrthographicCamera::OrthographicCamera(float top, float bottom, float left, float right) :
		m_projectionMatrix(glm::ortho(left,right, bottom, top)), m_viewMatrix(1.0f)
	{
		m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
	}

	void OrthographicCamera::LockToObject(const GameObject& gameObject)
	{
		Vector2 objectPosition = gameObject.GetCoords();
		SetPosition(glm::vec3(0-objectPosition.x, 0-objectPosition.y, 0));
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_position) *
			glm::rotate(glm::mat4(1.0f), m_rotation, glm::vec3(0, 0, 1));
		m_viewMatrix = glm::inverse(transform);
		m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;

	}
}

