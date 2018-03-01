#include <octoon/collider2d_component.h>
#include <octoon/circle_collider2d_component.h>
#include <Box2D/Box2D.h>


namespace octoon
{
    OctoonImplementSubClass(Collider2D, GameComponent, "Collider2D")

    Collider2D::Collider2D() noexcept
    {

    }

    Collider2D::~Collider2D()
    {

    }

    GameComponentPtr Collider2D::clone() const noexcept
    {
        return std::make_shared<CircleCollider2D>();
    }
}