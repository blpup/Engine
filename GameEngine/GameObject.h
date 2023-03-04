#pragma once
#include <vector>
#include "GamePhysics.h"
#include "Vector2.h"
#include "UUID.h"
#include <GLFW/glfw3.h>

namespace GameEngine {
	class GameObject
	{

	public:
		GameObject();
		~GameObject();
		virtual void Update();
		virtual void Destroy();
		Vector2 GetCoords() const;
		void SetCoords(float x, float y);
		int GetID() const;
		void SetSpeed(float speed);
		float GetSpeed();
		virtual void OnCollide(GameObject* OtherObject, int direction);
	private:
		UUID m_ID;
		Vector2 m_coords;
		float m_speed;
	};
}


