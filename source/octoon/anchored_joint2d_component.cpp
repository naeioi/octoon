#include <octoon/anchored_joint2d_component.h>
#include <octoon/rigidbody2d_component.h>
#include <Box2D/Box2D.h>


namespace octoon
{
    OctoonImplementSubClass(AnchoredJoint2D, Joint2D, "AnchoredJoint2D")

    AnchoredJoint2D::AnchoredJoint2D() noexcept
    {
    }

    AnchoredJoint2D::~AnchoredJoint2D()
    {

    }

    void AnchoredJoint2D::set_anchor(const math::Vector2& a) noexcept
    {
        anchor = a;
    }

    math::Vector2 AnchoredJoint2D::get_anchor() const noexcept
    {
        return anchor;
    }

    void AnchoredJoint2D::set_auto_configure_connected_anchor(bool is_auto_configure) noexcept
    {
        auto_configure_connected_anchor = is_auto_configure;
    }

    bool AnchoredJoint2D::get_auto_configure_connected_anchor() const noexcept
    {
        return auto_configure_connected_anchor;
    }

    void AnchoredJoint2D::set_connected_anchor(const math::Vector2& a) noexcept
    {
        connected_anchor = a;
    }

    math::Vector2 AnchoredJoint2D::get_connected_anchor() const noexcept
    {
        return connected_anchor;
    }
}