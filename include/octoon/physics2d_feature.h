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
		virtual void onActivate() except override;
		virtual void onDeactivate() noexcept override;

		virtual void onInputEvent(const input::InputEvent& event) noexcept override;

		virtual void onReset() noexcept override;

		virtual void onFrameBegin() noexcept override;
        virtual void onFrame() except;
		virtual void onFrameEnd() noexcept override;

		virtual void onOpenScene(const GameScenePtr& scene) except;
		virtual void onCloseScene(const GameScenePtr& scene) noexcept;

	private:
		Physics2DFeature(const Physics2DFeature&) = delete;
		Physics2DFeature& operator=(const Physics2DFeature&) = delete;
    };
}

#endif // OCTOON_PHYSICS2D_FEATURE_H_