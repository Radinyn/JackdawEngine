#include "include/Jackdaw.h"

int main()
{
    const int WIDTH = 400, HEIGHT = 400;
    jdw::Application::init(WIDTH, HEIGHT, L"Hello world!", false);

    jdw::Polygon polygon = {
        {
            {3, 0}, {9, 0}, {12, 3}, {12, 9},
            {9, 12}, {3, 12}, {0, 9}, {0, 3}
        },

        {0.0f, 1.0f, 0.0f, 1.0f}
    };

    polygon.setScale({4, 4});

    jdw::setFillColor({ 0.9f, 0.9f, 0.9f, 1.0f });

    double deltaTime;

    while (jdw::Application::run())
    {
        deltaTime = jdw::getDeltaTime();

        polygon.setPosition(jdw::getMousePosition());
 
        if (jdw::isHeld(jdw::KEY::LMB))
            polygon.setRotation( polygon.getRotation() + 1.0f * (float)deltaTime );

        jdw::draw(polygon);
    }

    jdw::Application::terminate();
    return 0;
}