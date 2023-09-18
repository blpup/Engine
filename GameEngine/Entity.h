#pragma once
#include <vector>
#include <unordered_map>
#include <iostream>
#include <utility>
namespace GameEngine {
	namespace Entity {
		enum class ComponentId {
			Physics = 10,
			Player = 20,
			Render = 30,
			Movement = 40,
			Rotation = 50,
			Ground = 60
		};

		using Type = std::vector<ComponentId>;
		using EntityId = uint64_t;
		using EntityMap = std::unordered_map<EntityId, Type>;

		inline EntityMap& GetEntityMapInstance() {
			static EntityMap entityMap;
			return entityMap;
		}

		//One of inline features is to help make sure that there is only one instance.
		inline bool hasComponent(EntityId entityId, ComponentId component) {
			if (GetEntityMapInstance().find(entityId) == GetEntityMapInstance().end()) return false;

			Type& type = GetEntityMapInstance()[entityId];
			for (auto c : type) {
				if (c == component) return true;
			}

			return false;
		}

		inline void registerComponents(EntityId entityId, Type components) {
			GetEntityMapInstance().insert(std::make_pair(entityId, components));
		}

		inline void registerComponent(const EntityId entityId, ComponentId component) {
			if (GetEntityMapInstance().find(entityId) == GetEntityMapInstance().end()) {
				GetEntityMapInstance().insert({ entityId, Type {component} });
				return;
			};

			if (hasComponent(entityId, component) == 1) return;

			auto value = GetEntityMapInstance().find(entityId);
			value->second.push_back(component);
		}

		inline std::vector<ComponentId> getComponents(EntityId entityId) {
			if (GetEntityMapInstance().find(entityId) == GetEntityMapInstance().end()) return {};

			return GetEntityMapInstance()[entityId];
		}
	}
}
