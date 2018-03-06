#include <octoon/joint2d_component.h>
#include <octoon/rigidbody2d_component.h>
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