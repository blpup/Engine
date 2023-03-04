#pragma once
#include "Shape.h"
namespace GameEngine {
    class CircleComponent : public Shape
    {
    public:
        CircleComponent(float radius, Vector2 vector);
    private:
        float m_radius;
    };
}


