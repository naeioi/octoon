#ifndef OCTOON_PHYSICS2D_FEATURE_H_
#define OCTOON_PHYSICS2D_FEATURE_H_

#include <memory>

#include <octoon/game_feature.h>

class b2World;


namespace octoon
{

    class OCTOON_EXPORT Physics2DFeature final : public GameFeature
	{
        OctoonDeclareSubClass(Physics2DFeature, GameFeature)
	public:
		Physics2DFeature() noexcept;
		virtual ~Physics2DFeature() noexcept;

	private:
		virtual void on_activate() except override;
		virtual void on_deactivate() noexcept override;

		virtual void on_input_event(const input::InputEvent& event) noexcept override;

		virtual void on_reset() noexcept override;

		virtual void on_frame_begin() noexcept override;
        virtual void on_frame() except;
		virtual void on_frame_end() noexcept override;

		virtual void on_open_scene(const GameScenePtr& scene) except;
		virtual void on_close_scene(const GameScenePtr& scene) noexcept;

	private:
		Physics2DFeature(const Physics2DFeature&) = delete;
		Physics2DFeature& operator=(const Physics2DFeature&) = delete;
    };
}

#endif // OCTOON_PHYSICS2D_FEATURE_H_