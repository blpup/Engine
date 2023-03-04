#pragma once
#include "Shape.h"
namespace GameEngine {
    class BoxComponent :
        public Shape
    {
    public:
        BoxComponent();
        BoxComponent(float size);
        BoxComponent(float width, float height);
    };
}


