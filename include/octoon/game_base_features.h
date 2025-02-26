#ifndef OCTOON_GAME_BASE_FEATURES_H_
#define OCTOON_GAME_BASE_FEATURES_H_

#include <octoon/game_feature.h>

namespace octoon
{
	class OCTOON_EXPORT GameBaseFeature final : public GameFeature
	{
		OctoonDeclareSubClass(GameBaseFeature, GameFeature)
	public:
		GameBaseFeature() noexcept;
		~GameBaseFeature() noexcept;

		GameObjectManager* getGameObjectManager() const noexcept;

	private:
		void onActivate() noexcept override;

		void onFrameBegin() noexcept override;
		void onFrame() noexcept override;
		void onFrameEnd() noexcept override;

		void onInputEvent(const runtime::any& data) noexcept;
		void onFixedUpdate(const runtime::any& data) noexcept;
	};
}

#endif