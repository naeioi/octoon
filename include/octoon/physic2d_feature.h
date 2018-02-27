#ifndef OCTOON_PHYSIC2D_FEATURE_H_
#define OCTOON_PHYSIC2D_FEATURE_H_

#include <octoon/game_feature.h>

namespace octoon
{
    class OCTOON_EXPORT Physic2DFeature final : public GameFeature
	{
        OctoonDeclareSubClass(Physic2DFeature, GameFeature)
	public:
		Physic2DFeature() noexcept;
		virtual ~Physic2DFeature() noexcept;

	private:
		virtual void on_activate() except override;
		virtual void on_deactivate() noexcept override;

		virtual void on_input_event(const input::InputEvent& event) noexcept override;

		virtual void on_reset() noexcept override;

		virtual void on_frame_begin() noexcept override;
		virtual void on_frame_end() noexcept override;

	private:
		Physic2DFeature(const Physic2DFeature&) = delete;
		Physic2DFeature& operator=(const Physic2DFeature&) = delete;

	private:
    }
}

#endif // OCTOON_PHYSIC2D_FEATURE_H_