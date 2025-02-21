#ifndef OCTOON_OFFLINE_FEATURE_H_
#define OCTOON_OFFLINE_FEATURE_H_

#include <octoon/game_feature.h>
#include <octoon/offline_listener.h>
#include <octoon/hal/graphics_framebuffer.h>

namespace octoon
{
	class OCTOON_EXPORT OfflineFeature final : public GameFeature
	{
		OctoonDeclareSubClass(OfflineFeature, GameFeature)
	public:
		OfflineFeature() noexcept;
		OfflineFeature(std::uint32_t framebuffer_w, std::uint32_t framebuffer_h) noexcept;
		~OfflineFeature() noexcept;

		void addOfflineListener(OfflineListener* listener) noexcept;
		void removeOfflineListener(OfflineListener* listener) noexcept;

		void setFramebufferScale(std::uint32_t w, std::uint32_t h) noexcept;
		void getFramebufferScale(std::uint32_t& w, std::uint32_t& h) noexcept;

		void setFramebufferDirty(bool dirty) noexcept;
		bool getFramebufferDirty() const noexcept;

		void* getScene() const noexcept;
		void* getContext() const noexcept;
		void* getMaterialSystem() const noexcept;

		hal::GraphicsFramebufferPtr getColorFramebuffer() const noexcept;

		void readColorFramebuffer(void* dst) noexcept;
		void readNormalFramebuffer(void* dst) noexcept;
		void readAlbedoFramebuffer(void* dst) noexcept;

	private:
		void onActivate() except override;
		void onDeactivate() noexcept override;

		void onInputEvent(const runtime::any& data) noexcept;

		void onFrame() noexcept override;

		void onFramebufferChange(std::uint32_t w, std::uint32_t h) except;

	private:
		void cleanupFramebuffers() noexcept;

	private:
		bool dirty_;

		void* rprScene_;
		void* rprContext_;
		void* rprMaterialSystem_;

		void* colorFramebuffer_;
		void* normalFramebuffer_;
		void* albedoFramebuffer_;

		hal::GraphicsTexturePtr colorTexture_;
		hal::GraphicsTexturePtr normalTexture_;
		hal::GraphicsTexturePtr albedoTexture_;

		hal::GraphicsFramebufferPtr framebuffer_;

		std::uint32_t framebuffer_w_;
		std::uint32_t framebuffer_h_;

		std::vector<OfflineListener*> listener_;
	};
}

#endif