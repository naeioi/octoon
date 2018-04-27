#include <octoon/collider2d_component.h>
#include <Box2D/Box2D.h>


namespace octoon
{
	OctoonImplementSubInterface(Collider2D, GameComponent, "Collider2D")

    Collider2D::Collider2D() noexcept
        :collider(nullptr)
    {

    }

    Collider2D::~Collider2D()
    {

    }

    void Collider2D::setBounciness(float b) noexcept
    {
        bounciness = b;
        if(collider)
        {
            collider->SetRestitution(bounciness);
        }
    }

    float Collider2D::getBounciness() const noexcept
    {
        return bounciness;
    }

    void Collider2D::setDensity(float d) noexcept
    {
        density = d;
        if(collider)
        {
            collider->SetDensity(density);
        }
    }

    float Collider2D::getDensity() const noexcept
    {
        return density;
    }

    void Collider2D::setFriction(float f) noexcept
    {
        friction = f;
        if(collider)
        {
            collider->SetFriction(friction);
        }
    }

    float Collider2D::getFriction() const noexcept
    {
        return friction;
    }
}