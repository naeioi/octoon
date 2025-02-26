#ifndef OCTOON_OFFLINE_SKINNED_MESH_RENDERER_COMPONENT_H_
#define OCTOON_OFFLINE_SKINNED_MESH_RENDERER_COMPONENT_H_

#include <octoon/offline_mesh_renderer_component.h>
#include <octoon/video/geometry.h>
#include <octoon/mesh_filter_component.h>
#include <octoon/skinned_component.h>

namespace octoon
{
	class OCTOON_EXPORT OfflineSkinnedMeshRendererComponent final : public OfflineMeshRendererComponent
	{
		OctoonDeclareSubClass(OfflineSkinnedMeshRendererComponent, RenderComponent)
	public:
		OfflineSkinnedMeshRendererComponent() noexcept;
		OfflineSkinnedMeshRendererComponent(model::Materials&& material, GameObjects&& transforms) noexcept;
		OfflineSkinnedMeshRendererComponent(model::MaterialPtr&& material, GameObjects&& transforms) noexcept;
		OfflineSkinnedMeshRendererComponent(const model::Materials& material, const GameObjects& transforms) noexcept;
		OfflineSkinnedMeshRendererComponent(const model::MaterialPtr& material, const GameObjects& transforms) noexcept;
		virtual ~OfflineSkinnedMeshRendererComponent() noexcept;

		void setTransforms(const GameObjects& transforms) noexcept;
		void setTransforms(GameObjects&& transforms) noexcept;
		const GameObjects& getTransforms() const noexcept;

		void setMorphBlendEnable(bool enable) noexcept;
		bool getMorphBlendEnable() const noexcept;

		void setTextureBlendEnable(bool enable) noexcept;
		bool getTextureBlendEnable() const noexcept;

		void uploadMeshData(const model::Mesh& mesh) noexcept;

		GameComponentPtr clone() const noexcept override;

	private:
		void onActivate() noexcept override;
		void onDeactivate() noexcept override;

		void onMeshReplace(const runtime::any& mesh) noexcept override;
		void onAnimationUpdate(const runtime::any& data) noexcept;

		void onAttachComponent(const GameComponentPtr& component) noexcept override;
		void onDetachComponent(const GameComponentPtr& component) noexcept override;

		void onPreRender() noexcept override;

	private:
		void updateJointData(const model::Mesh& mesh) noexcept;
		void updateBoneData(const model::Mesh& mesh) noexcept;
		void updateMorphBlendData() noexcept;
		void updateTextureBlendData() noexcept;

	private:
		OfflineSkinnedMeshRendererComponent(const OfflineSkinnedMeshRendererComponent&) = delete;
		OfflineSkinnedMeshRendererComponent& operator=(const OfflineSkinnedMeshRendererComponent&) = delete;

	private:
		bool needUpdate_;
		bool morphEnable_;
		bool textureEnable_;

		GameObjects transforms_;

		math::float4x4s joints_;

		model::MeshPtr mesh_;
		model::MeshPtr skinnedMesh_;

		std::vector<class SkinnedMorphComponent*> morphComponents_;
		std::vector<class SkinnedTextureComponent*> textureComponents_;
	};
}

#endif