#include <octoon/guizmo_component.h>
#include <octoon/camera_component.h>
#include <octoon/transform_component.h>
#include <octoon/input/input.h>

namespace octoon
{
	OctoonImplementSubClass(GuizmoComponent, GameComponent, "Guizmo")

	GuizmoComponent::GuizmoComponent() noexcept
		: op_(imgui::guizmo::Translate)
	{
	}

	GuizmoComponent::GuizmoComponent(const GameObjectPtr& camera) noexcept
		: camera_(camera)
		, op_(imgui::guizmo::Translate)
	{
	}

	void
	GuizmoComponent::setCamera(const GameObjectPtr& camera) noexcept
	{
		camera_ = camera;
	}

	const GameObjectPtr&
	GuizmoComponent::getCamera() const noexcept
	{
		return camera_;
	}

	void
	GuizmoComponent::onActivate() noexcept
	{
		this->addComponentDispatch(GameDispatchType::Gui);
	}

	void
	GuizmoComponent::onDeactivate() noexcept
	{
		this->removeComponentDispatch(GameDispatchType::Gui);
	}

	void
	GuizmoComponent::onGui() noexcept
	{
		if (camera_)
		{
			auto transform = this->getComponent<TransformComponent>();

			auto& view = camera_->getComponent<CameraComponent>()->getView();
			auto& project = camera_->getComponent<CameraComponent>()->getProjection();
			auto model = transform->getTransform();

			if (imgui::isKeyPressed(input::InputKey::Code::Key1))
				op_ = imgui::guizmo::Translate;
			if (imgui::isKeyPressed(input::InputKey::Code::Key2))
				op_ = imgui::guizmo::Rotation;
			if (imgui::isKeyPressed(input::InputKey::Code::Key3))
				op_ = imgui::guizmo::Scale;

			imgui::guizmo::BeginFrame();
			imgui::guizmo::SetRect(0, 0, imgui::getDisplaySize().x, imgui::getDisplaySize().y);
			imgui::guizmo::Manipulate(view.ptr(), project.ptr(), op_, imgui::guizmo::Mode::Local, model.ptr());

			transform->setTransform(model);
		}
	}

	GameComponentPtr
	GuizmoComponent::clone() const noexcept
	{
		auto instance = std::make_shared<GuizmoComponent>();
		instance->setName(this->getName());
		return instance;
	}
}