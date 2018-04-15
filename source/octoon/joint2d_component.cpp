#include <octoon/joint2dComponent.h>
#include <octoon/rigidbody2dComponent.h>
#include <Box2D/Box2D.h>


namespace octoon
{
    OctoonImplementSubClass(Joint2D, GameComponent, "Joint2D")

    Joint2D::Joint2D() noexcept
    {
    }

    Joint2D::~Joint2D()
    {

    }
}