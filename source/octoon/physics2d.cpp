#include <octoon/physics2d.h>

namespace octoon
{
	math::Vector2 Physics2D::gravity;

    void Physics2D::setGravity(const math::Vector2& g)
    {
        gravity=g;
    }

    math::Vector2 Physics2D::getGravity()
    {
        return gravity;
    }
}