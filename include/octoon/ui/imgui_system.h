#ifndef OCTOON_IMGUI_SYSTEM_H_
#define OCTOON_IMGUI_SYSTEM_H_

#include <octoon/ui/imgui.h>
#include <octoon/input/input.h>
#include <octoon/runtime/singleton.h>
#include <octoon/hal/graphics.h>

struct ImGuiContext;

namespace octoon
{
	namespace imgui
	{
		class OCTOON_EXPORT System final : public runtime::Singleton<System>
		{
		public:
			System() noexcept;
			System(const hal::GraphicsDevicePtr& device) noexcept;
			~System() noexcept;

			void open(const hal::GraphicsDevicePtr& device) except;
			void close() noexcept;

			bool injectMouseMove(float absx, float absy) noexcept;
			bool injectMousePress(float absx, float absy, input::InputButton::Code id) noexcept;
			bool injectMouseRelease(float absx, float absy, input::InputButton::Code id) noexcept;
			bool injectMouseWheel(float wheel) noexcept;

			bool injectKeyPress(input::InputKey::Code key, wchar_t char_) noexcept;
			bool injectKeyRelease(input::InputKey::Code key) noexcept;

			bool injectWindowFocus(bool focus) noexcept;

			void setImeWindowHandle(input::WindHandle window) noexcept;
			input::WindHandle getImeWindowHandle() const noexcept;

			void setViewport(std::uint32_t w, std::uint32_t h) noexcept;
			void getViewport(std::uint32_t& w, std::uint32_t& h) noexcept;

			void setFramebufferScale(std::uint32_t w, std::uint32_t h) noexcept;
			void getFramebufferScale(std::uint32_t& w, std::uint32_t& h) noexcept;

			bool loadFont(const char* path, float font_size = 15) noexcept;

			void newFrame() noexcept;
			void endFrame() noexcept;

			void render(hal::GraphicsContext& context) noexcept;

		private:
			System(const System&) noexcept = delete;
			System& operator=(const System&) noexcept = delete;

		private:
			std::string imguiPath_;
			std::string imguiDockPath_;

			ImGuiContext* imguiContext_;

			hal::GraphicsDataPtr vbo_;
			hal::GraphicsDataPtr ibo_;
			hal::GraphicsTexturePtr texture_;
			hal::GraphicsDescriptorSetPtr descriptor_set_;

			hal::GraphicsUniformSetPtr proj_;
			hal::GraphicsUniformSetPtr decal_;

			hal::GraphicsDevicePtr device_;
			hal::GraphicsPipelinePtr pipeline_;
		};
	}
}

#endif