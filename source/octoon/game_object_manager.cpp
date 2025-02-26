#include <octoon/game_object_manager.h>
#include <octoon/mesh_filter_component.h>
#include <octoon/transform_component.h>

namespace octoon
{
	OctoonImplementSingleton(GameObjectManager)

	GameObjectManager::GameObjectManager() noexcept
	{
	}

	GameObjectManager::~GameObjectManager() noexcept
	{
	}

	void
	GameObjectManager::_instanceObject(GameObject* entity, std::size_t& instanceID) noexcept
	{
		assert(entity);

		std::lock_guard<std::mutex> guard_lock(lock_);
		if (emptyLists_.empty())
		{
			instanceLists_.push_back(entity);
			instanceID = instanceLists_.size();
		}
		else
		{
			std::size_t instance_id_ = emptyLists_.top();
			emptyLists_.pop();
			instanceLists_[instance_id_ - 1] = entity;
			instanceID = instance_id_;
		}
	}

	void
	GameObjectManager::_unsetObject(GameObject* entity) noexcept
	{
		assert(entity);
		std::lock_guard<std::mutex> guard_lock(lock_);
		auto instanceID = entity->id();
		instanceLists_[instanceID - 1] = nullptr;
		emptyLists_.push(instanceID);
		this->_activeObject(entity, false);
	}

	void
	GameObjectManager::_activeObject(GameObject* entity, bool active) noexcept
	{
		if (active)
		{
			assert(std::find(activeActors_.begin(), activeActors_.end(), entity) == activeActors_.end());
			activeActors_.push_back(entity);
		}
		else
		{
			auto it = std::find(activeActors_.begin(), activeActors_.end(), entity);
			if (it != activeActors_.end())
			{
				*it = nullptr;
				hasEmptyActors_ = true;
			}
		}
	}

	GameObjectPtr
	GameObjectManager::find(const char* name) noexcept
	{
		std::lock_guard<std::mutex> guard_lock(lock_);

		for (auto& it : instanceLists_)
		{
			if (it)
			{
				if (it->getName() == name)
					return it->downcast_pointer<GameObject>();
			}
		}

		return nullptr;
	}

	GameObjectPtr
	GameObjectManager::find(const std::string& name) noexcept
	{
		return this->find(name.c_str());
	}

	const GameObjectRaws&
	GameObjectManager::instances() const noexcept
	{
		return instanceLists_;
	}

	void
	GameObjectManager::sendMessage(const std::string& event, const runtime::any& data) noexcept
	{
		dispatchEvents_[event].call_all_slots(data);
	}

	void
	GameObjectManager::addMessageListener(const std::string& event, std::function<void(const runtime::any&)> listener) noexcept
	{
		dispatchEvents_[event].connect(listener);
	}

	void
	GameObjectManager::removeMessageListener(const std::string& event, std::function<void(const runtime::any&)> listener) noexcept
	{
		dispatchEvents_[event].disconnect(listener);
	}

	std::size_t
	GameObjectManager::raycastHit(const math::Raycast& ray, RaycastHit& hit, float distance, std::uint32_t layerMask) noexcept
	{
		std::size_t result = 0;

		for (auto& object : instanceLists_)
		{
			if (!object)
				continue;

			if ((1 << object->getLayer()) & layerMask)
				continue;

			auto meshFilter = object->getComponent<MeshFilterComponent>();
			if (meshFilter)
			{
				auto mesh = meshFilter->getMesh();
				if (!mesh)
					continue;

				auto transform = object->getComponent<TransformComponent>();
				auto boundingBox = math::transform(mesh->getBoundingBoxAll(), transform->getTransform());

				if (!math::intersects(boundingBox, ray))
					continue;

				for (std::size_t i = 0; i < mesh->getNumSubsets(); i++)
				{
					auto boundingBox = math::transform(mesh->getBoundingBox(i), transform->getTransform());
					if (!math::intersects(boundingBox, ray))
						continue;

					float dist = math::sqrDistance(boundingBox.center(), ray.origin);
					if (dist < distance)
					{
						hit.object = object;
						hit.mesh = i;
						hit.distance = distance;

						result++;
					}
				}
			}
		}

		return result;
	}

	std::size_t
	GameObjectManager::raycastHit(const math::float3& orgin, const math::float3& end, RaycastHit& hit, float distance, std::uint32_t layerMask) noexcept
	{
		return this->raycastHit(math::Raycast(orgin, end), hit, distance, layerMask);
	}

	void
	GameObjectManager::onFixedUpdate() noexcept
	{
		for (std::size_t i = 0; i < activeActors_.size(); i++)
		{
			if (activeActors_[i])
				activeActors_[i]->onFixedUpdate();
		}
	}

	void
	GameObjectManager::onUpdate() noexcept
	{
		for (std::size_t i = 0; i < activeActors_.size(); i++)
		{
			if (activeActors_[i])
				activeActors_[i]->onUpdate();
		}
	}

	void
	GameObjectManager::onLateUpdate() noexcept
	{
		for (std::size_t i = 0; i < activeActors_.size(); i++)
		{
			if (activeActors_[i])
				activeActors_[i]->onLateUpdate();
		}

		if (hasEmptyActors_)
		{
			for (auto it = activeActors_.begin(); it != activeActors_.end();)
			{
				if (!(*it))
					it = activeActors_.erase(it);
				else
					++it;
			}

			hasEmptyActors_ = false;
		}
	}

	void
	GameObjectManager::onGui() noexcept
	{
		for (std::size_t i = 0; i < activeActors_.size(); i++)
		{
			if (activeActors_[i])
				activeActors_[i]->onGui();
		}
	}
}