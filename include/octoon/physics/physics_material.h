#ifndef OCTOON_PHYSICS_MATERIAL_H_
#define OCTOON_PHYSICS_MATERIAL_H_

#include <octoon/runtime/platform.h>
#include <octoon/runtime/rtti_macros.h>
#include <octoon/runtime/rtti_interface.h>
#include <octoon/math/math.h>

namespace octoon
{
    namespace physics
    {
        class OCTOON_EXPORT PhysicsMaterial : public runtime::RttiInterface
        {
            OctoonDeclareSubInterface(PhysicsMaterial, runtime::RttiInterface)
        public:
            PhysicsMaterial() noexcept;
            virtual ~PhysicsMaterial() noexcept;
        };
    }
}

#endif //OCTOON_PHYSICS_MATERIAL_H_