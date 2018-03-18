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

    void DistanceJoint2D::set_auto_configure_distance(bool b) noexcept
    {
        auto_configure_distance = b;
    }

    bool DistanceJoint2D::get_auto_configure_distance() const noexcept
    {
        return auto_configure_distance;
    }

    void DistanceJoint2D::set_distance(float d) noexcept
    {
        distance = d;
        b2DistanceJointDef jointDef;
        jointDef.Initialize(myBodyA, myBodyB, worldAnchorOnBodyA, worldAnchorOnBodyB);
        jointDef.collideConnected = true;
    }

    float DistanceJoint2D::get_distance() const noexcept
    {
        return distance;
    }

    void DistanceJoint2D::set_max_distance_only(bool b) noexcept
    {
        max_distance_only = b;
    }
    bool DistanceJoint2D::get_max_distance_only() const noexcept
    {
        return max_distance_only;
    }

    void DistanceJoint2D::on_joint_change()
    {

    }

    void DistanceJoint2D::on_joint_enter()
    {

    }

    void DistanceJoint2D::on_joint_exit()
    {

    }
}