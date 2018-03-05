#include <octoon/distance_joint2d_component.h>
#include <octoon/rigidbody2d_component.h>
#include <Box2D/Box2D.h>


namespace octoon
{
    OctoonImplementSubClass(DistanceJoint2D, AnchoredJoint2D, "DistanceJoint2D")

    DistanceJoint2D::DistanceJoint2D() noexcept
    {
    }

    DistanceJoint2D::~DistanceJoint2D()
    {

    }
}