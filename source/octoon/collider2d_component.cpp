#include <octoon/collider2d_component.h>
#include <Box2D/Box2D.h>


namespace octoon
{
    OctoonImplementSubClass(Collider2D, GameComponent, "Collider2D")

    Collider2D::Collider2D() noexcept
        :collider(nullptr)
    {

    }

    Collider2D::~Collider2D()
    {

    }

    GameComponentPtr Collider2D::clone() const noexcept
    {
        return std::make_shared<CircleCollider2D>();
    }

    void Collider2D::set_bounciness(float b) noexcept
    {
        bounciness = b;
        if(collider)
        {
            collider->SetRestitution(bounciness);
        }
    }

    float Collider2D::get_bounciness() const noexcept
    {
        return bounciness;
    }

    void Collider2D::set_density(float d) noexcept
    {
        density = d;
        if(collider)
        {
            collider->SetDensity(density);
        }
    }

    float Collider2D::get_density() const noexcept
    {
        return density;
    }

    void Collider2D::set_friction(float f) noexcept
    {
        friction = f;
        if(collider)
        {
            collider->SetFriction(friction);
        }
    }

    float Collider2D::get_friction() const noexcept
    {
        return friction;
    }
}