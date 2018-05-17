#ifndef OCTOON_CONTACT_POINT_H_
#define OCTOON_CONTACT_POINT_H_

#include <octoon/math/math.h>
#include <octoon/collider_component.h>

namespace octoon
{
    class Collider;
    class ContactPoint
    {
    public:
        math::float3 normal; //Normal of the contact point.
        std::weak_ptr<Collider> otherCollider; //The other collider in contact at the point.
        math::float3 point; // The point of contact.
        float separation; // The distance between the colliders at the contact point.
        std::weak_ptr<Collider> thisCollider; // The first collider in contact at the point.
    };
}

#endif // OCTOON_CONTACT_POINT_H_