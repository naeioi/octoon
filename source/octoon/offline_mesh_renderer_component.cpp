#include <octoon/offline_mesh_renderer_component.h>
#include <octoon/offline_feature.h>
#include <octoon/mesh_filter_component.h>
#include <octoon/transform_component.h>
#include <octoon/video/render_system.h>
#include <octoon/game_prefabs.h>

#include <RadeonProRender.h>

namespace octoon
{
	OctoonImplementSubClass(OfflineMeshRendererComponent, OfflineRenderComponent, "OfflineMeshRenderer")

	OfflineMeshRendererComponent::OfflineMeshRendererComponent() noexcept
	{
	}

	OfflineMeshRendererComponent::OfflineMeshRendererComponent(model::Materials&& materials) noexcept
	{
		this->setMaterials(std::move(materials));
	}

	OfflineMeshRendererComponent::OfflineMeshRendererComponent(model::MaterialPtr&& material) noexcept
	{
		this->setMaterial(std::move(material));
	}

	OfflineMeshRendererComponent::OfflineMeshRendererComponent(const model::Materials& materials) noexcept
	{
		this->setMaterials(materials);
	}

	OfflineMeshRendererComponent::OfflineMeshRendererComponent(const model::MaterialPtr& material) noexcept
	{
		this->setMaterial(material);
	}

	OfflineMeshRendererComponent::~OfflineMeshRendererComponent() noexcept
	{
	}

	void*
	OfflineMeshRendererComponent::createImage(const std::string& path) noexcept
	{
		auto feature = this->tryGetFeature<OfflineFeature>();
		if (!feature)
			return nullptr;

		auto texture = GamePrefabs::instance()->createTexture(path);
		if (!texture)
			return nullptr;
		
		try
		{
			std::uint8_t* data;
			auto desc = texture->getTextureDesc();
			texture->map(0, 0, desc.getWidth(), desc.getHeight(), 0, (void**)& data);

			bool hasAlpha = false;
			std::uint8_t channel = 3;
			switch (desc.getTexFormat())
			{
			case hal::GraphicsFormat::B8G8R8A8UNorm:
				hasAlpha = true;
				channel = 4;
				break;
			case hal::GraphicsFormat::R8G8B8A8UNorm:
				hasAlpha = true;
				channel = 4;
				break;
			case hal::GraphicsFormat::B8G8R8A8SRGB:
				hasAlpha = true;
				channel = 4;
				break;
			case hal::GraphicsFormat::R8G8B8A8SRGB:
				hasAlpha = true;
				channel = 4;
				break;
			}

			rpr_image_format imageFormat = { channel, RPR_COMPONENT_TYPE_UINT8 };
			rpr_image_desc imageDesc;
			imageDesc.image_width = desc.getWidth();
			imageDesc.image_height = desc.getHeight();
			imageDesc.image_depth = 1;
			imageDesc.image_row_pitch = desc.getWidth() * imageFormat.num_components;
			imageDesc.image_slice_pitch = imageDesc.image_row_pitch * desc.getHeight();

			std::vector<std::uint8_t> array(desc.getWidth() * desc.getHeight() * imageFormat.num_components);
			for (std::size_t y = 0; y < desc.getHeight(); y++)
			{
				for (std::size_t x = 0; x < desc.getWidth(); x++)
				{
					auto dst = ((desc.getHeight() - 1 - y) * desc.getWidth() + x) * imageFormat.num_components;
					auto src = (y * desc.getWidth() + x) * imageFormat.num_components;

					for (std::uint8_t i = 0; i < imageFormat.num_components; i++)
						array[dst + i] = data[src + i];
				}
			}

			rpr_image image_;
			rprContextCreateImage(feature->getContext(), imageFormat, &imageDesc, array.data(), &image_);
			texture->unmap();

			return image_;
		}
		catch (...)
		{
			texture->unmap();
			return nullptr;
		}
	}

	void
	OfflineMeshRendererComponent::uploadMaterialData(const model::Materials& materials) noexcept
	{
		auto feature = this->tryGetFeature<OfflineFeature>();
		if (!feature)
			return;

		for (auto& it : this->materials_)
			rprObjectDelete(it);

		this->materials_.clear();

		for (auto& mat : materials)
		{
			std::string name;
			std::string path;
			std::string normalName;
			std::string textureName;

			math::float3 base = math::float3(1.0f, 0.0f, 1.0f);
			math::float3 specular = math::float3::One;
			math::float3 ambient;
			math::float4 metalness = math::float4::Zero;
			
			float opacity = 1.0f;
			float shininess = 10.0f;
			
			mat->get(MATKEY_NAME, name);
			mat->get(MATKEY_PATH, path);
			mat->get(MATKEY_TEXTURE_SPECULAR, normalName);
			mat->get(MATKEY_TEXTURE_DIFFUSE, textureName);
			mat->get(MATKEY_COLOR_DIFFUSE, base);
			mat->get(MATKEY_COLOR_AMBIENT, ambient);			
			mat->get(MATKEY_COLOR_SPECULAR, specular);
			mat->get(MATKEY_COLOR_EDGE, metalness);
			mat->get(MATKEY_OPACITY, opacity);
			mat->get(MATKEY_SHININESS, shininess);

			rpr_material_node rprMaterial;
			rprMaterialSystemCreateNode(feature->getMaterialSystem(), RPR_MATERIAL_NODE_UBERV2, &rprMaterial);

			std::uint32_t layers = 0;
			if (ambient != math::float3::Zero && base == math::float3::Zero)
				layers |= RPR_UBER_MATERIAL_LAYER_EMISSION;
			else
			{
				layers |= RPR_UBER_MATERIAL_LAYER_REFLECTION;

				if (opacity < 1.0f)
					layers |= RPR_UBER_MATERIAL_LAYER_TRANSPARENCY;
				if (!normalName.empty())
					layers |= RPR_UBER_MATERIAL_LAYER_SHADING_NORMAL;
				if (metalness.x == 0.0f)
					layers |= RPR_UBER_MATERIAL_LAYER_DIFFUSE;
			}

			rprMaterialNodeSetInputU(rprMaterial, "uberv2.layers", layers);

			if (layers & RPR_UBER_MATERIAL_LAYER_TRANSPARENCY)
				rprMaterialNodeSetInputF(rprMaterial, "uberv2.transparency", 1.0f - opacity, 1.0f, 1.0f, 1.0f);

			if (layers & RPR_UBER_MATERIAL_LAYER_EMISSION)
			{
				rprMaterialNodeSetInputU_ext(rprMaterial, RPR_UBER_MATERIAL_LAYERS, RPR_UBER_MATERIAL_LAYER_EMISSION);
				rprMaterialNodeSetInputF_ext(rprMaterial, RPR_UBER_MATERIAL_EMISSION_COLOR, ambient.x, ambient.y, ambient.z, 0.0f);
			}

			if (layers & RPR_UBER_MATERIAL_LAYER_DIFFUSE)
			{
				if (!textureName.empty())
				{
					rpr_material_node textureNode;
					rprMaterialSystemCreateNode(feature->getMaterialSystem(), RPR_MATERIAL_NODE_IMAGE_TEXTURE, &textureNode);
					rprMaterialNodeSetInputImageData(textureNode, "data", this->createImage(path + textureName));
					rprMaterialNodeSetInputN(rprMaterial, "uberv2.diffuse.color", textureNode);
				}
				else
				{
					rprMaterialNodeSetInputF(rprMaterial, "uberv2.diffuse.color", base[0], base[1], base[2], 1.0f);
				}
			}

			if (layers & RPR_UBER_MATERIAL_LAYER_REFLECTION)
			{
				float roughness = 1.0f - math::saturate(shininess / 1000.0f);

				rprMaterialNodeSetInputF(rprMaterial, "uberv2.reflection.ior", 1.5f, 1.5f, 1.5f, 1.5f);				
				rprMaterialNodeSetInputF(rprMaterial, "uberv2.reflection.roughness", roughness, roughness, roughness, roughness);

				if (metalness.x > 0.0f)
				{
					rpr_material_node textureNode;
					rprMaterialSystemCreateNode(feature->getMaterialSystem(), RPR_MATERIAL_NODE_IMAGE_TEXTURE, &textureNode);
					rprMaterialNodeSetInputImageData(textureNode, "data", this->createImage(path + textureName));
					rprMaterialNodeSetInputN(rprMaterial, "uberv2.reflection.color", textureNode);
					rprMaterialNodeSetInputF(rprMaterial, "uberv2.reflection.metalness", metalness.x, 0.0f, 0.0f, 0.0f);
				}
				else
				{
					rprMaterialNodeSetInputF(rprMaterial, "uberv2.reflection.color", specular.x, specular.y, specular.z, 1.0f);
				}
			}

			if (layers & RPR_UBER_MATERIAL_LAYER_REFRACTION)
			{
				if (!textureName.empty())
				{
					rpr_material_node textureNode;
					rprMaterialSystemCreateNode(feature->getMaterialSystem(), RPR_MATERIAL_NODE_IMAGE_TEXTURE, &textureNode);
					rprMaterialNodeSetInputImageData(textureNode, "data", this->createImage(path + textureName));

					rprMaterialNodeSetInputF(rprMaterial, "uberv2.refraction.ior", 1.5f, 1.5f, 1.5f, 1.5f);
					rprMaterialNodeSetInputF(rprMaterial, "uberv2.refraction.roughness", 1.0f, 1.0f, 1.0f, 1.0f);
					rprMaterialNodeSetInputN(rprMaterial, "uberv2.refraction.color", textureNode);
				}
				else
				{
					rprMaterialNodeSetInputF(rprMaterial, "uberv2.refraction.ior", 1.5f, 1.5f, 1.5f, 1.5f);
					rprMaterialNodeSetInputF(rprMaterial, "uberv2.refraction.roughness", 1.0f, 1.0f, 1.0f, 1.0f);
					rprMaterialNodeSetInputF(rprMaterial, "uberv2.refraction.color", 1.0f, 1.0f, 1.0f, 1.0f);
				}
			}

			if (layers & RPR_UBER_MATERIAL_LAYER_SHADING_NORMAL)
			{
				rpr_material_node textureNode;
				rprMaterialSystemCreateNode(feature->getMaterialSystem(), RPR_MATERIAL_NODE_NORMAL_MAP, &textureNode);
				rprMaterialNodeSetInputImageData(textureNode, "data", this->createImage(path + normalName));
				rprMaterialNodeSetInputN(rprMaterial, "uberv2.normal", textureNode);
			}

			materials_.push_back(rprMaterial);
		}

		for (std::size_t i = 0; i < shapes_.size(); i++)
		{
			if (i < materials_.size())
				rprShapeSetMaterial(shapes_[i], materials_[i]);
			else
				rprShapeSetMaterial(shapes_[i], materials_.front());
		}
	}

	void
	OfflineMeshRendererComponent::uploadMeshData(const model::Mesh& mesh) noexcept
	{
		auto feature = this->tryGetFeature<OfflineFeature>();
		if (feature)
		{
			for (auto& it : shapes_)
			{
				rprSceneDetachShape(feature->getScene(), it);
				rprObjectDelete(it);
			}

			shapes_.clear();

			for (std::size_t i = 0; i < mesh.getNumSubsets(); i++)
			{
				math::uint1s faceArray(mesh.getIndicesArray(i).size() / 3, 3);

				rpr_shape rprShape;
				rprContextCreateMesh(feature->getContext(),
					mesh.getVertexArray().data()->ptr(), mesh.getVertexArray().size() / 3, sizeof(math::float3),
					mesh.getNormalArray().data()->ptr(), mesh.getNormalArray().size() / 3, sizeof(math::float3),
					mesh.getTexcoordArray().data()->ptr(), mesh.getTexcoordArray().size() / 2, sizeof(math::float2),
					(rpr_int*)mesh.getIndicesArray(i).data(), sizeof(rpr_int),
					(rpr_int*)mesh.getIndicesArray(i).data(), sizeof(rpr_int),
					(rpr_int*)mesh.getIndicesArray(i).data(), sizeof(rpr_int),
					(rpr_int*)faceArray.data(), faceArray.size(),
					&rprShape);

				rprShapeSetShadow(rprShape, true);
				rprShapeSetShadowCatcher(rprShape, true);
				rprShapeSetVisibility(rprShape, true);
				rprShapeSetLayerMask(rprShape, this->getGameObject()->getLayer());
				rprShapeSetObjectGroupID(rprShape, (rpr_uint)this->getGameObject()->id());
				rprShapeSetTransform(rprShape, false, this->getComponent<TransformComponent>()->getTransform().ptr());
				rprSceneAttachShape(feature->getScene(), rprShape);

				shapes_.push_back(rprShape);
			}

			for (std::size_t i = 0; i < materials_.size(); i++)
			{
				if (i < shapes_.size())
					rprShapeSetMaterial(shapes_[i], materials_[i]);
				else
					rprShapeSetMaterial(shapes_[i], materials_.front());
			}
		}
	}

	GameComponentPtr
	OfflineMeshRendererComponent::clone() const noexcept
	{
		auto instance = std::make_shared<OfflineMeshRendererComponent>();
		instance->setName(this->getName());
		instance->setMaterial(this->getMaterial() ? (this->isSharedMaterial() ? this->getMaterial() : this->getMaterial()->clone()) : nullptr, this->isSharedMaterial());

		return instance;
	}

	void
	OfflineMeshRendererComponent::onActivate() noexcept
	{
		this->addComponentDispatch(GameDispatchType::MoveAfter);
		this->addMessageListener("octoon:mesh:update", std::bind(&OfflineMeshRendererComponent::onMeshReplace, this, std::placeholders::_1));
		this->sendMessage("octoon:mesh:get", nullptr);

		auto feature = this->getFeature<OfflineFeature>();
		if (feature)
			feature->addOfflineListener(this);

		this->onMaterialReplace(this->getMaterials());
	}

	void
	OfflineMeshRendererComponent::onDeactivate() noexcept
	{
		this->removeComponentDispatch(GameDispatchType::MoveAfter);
		this->removeMessageListener("octoon:mesh:update", std::bind(&OfflineMeshRendererComponent::onMeshReplace, this, std::placeholders::_1));

		auto feature = this->getFeature<OfflineFeature>();
		if (feature)
		{
			feature->removeOfflineListener(this);
			for (auto& shape : shapes_)
				rprSceneDetachShape(feature->getScene(), shape);
		}

		for (auto& shape : shapes_)
			rprObjectDelete(shape);
		shapes_.clear();

		for (auto& material : materials_)
			rprObjectDelete(material);
		materials_.clear();
	}

	void
	OfflineMeshRendererComponent::onMoveAfter() noexcept
	{
		for (auto& shape : shapes_)
		{
			auto transform = this->getComponent<TransformComponent>();
			rprShapeSetTransform(shape, false, transform->getTransform().ptr());

			auto feature = this->getFeature<OfflineFeature>();
			if (feature)
				feature->setFramebufferDirty(true);
		}
	}

	void
	OfflineMeshRendererComponent::onLayerChangeAfter() noexcept
	{
		for (auto& shape : shapes_)
			rprShapeSetLayerMask(shape, this->getGameObject()->getLayer());
	}

	void
	OfflineMeshRendererComponent::onMeshReplace(const runtime::any& mesh_) noexcept
	{
		auto mesh = runtime::any_cast<model::MeshPtr>(mesh_);
		if (mesh && this->getMaterial())
			this->uploadMeshData(*mesh);
	}

	void
	OfflineMeshRendererComponent::onMaterialReplace(const model::Materials& material) noexcept
	{
		if (this->getGameScene())
		{
			this->uploadMaterialData(material);
			this->trySendMessage("octoon:mesh:get");
		}
	}
}