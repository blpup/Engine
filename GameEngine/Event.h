#pragma once
#include "UUID.h"
#include <functional>
#include "GameObject.h"

namespace GameEngine {
	enum class EventType {
		EVENT_TYPE_LEVEL_STARTED,
		EVENT_TYPE_PLAYER_SPAWNED,
		EVENT_TYPE_ENEMY_SPOTTED,
		EVENT_TYPE_EXPLOSION,
		EVENT_TYPE_COLLISION
	};
	struct EventDefinition {
		UUID id;
		EventType type;
	};
	struct OnCollideDefinition :EventDefinition {
		std::function<void(GameObjectDef)> funCall;
	};
	class Event {
	public:
		Event(EventDefinition e) : m_type(e.type) {};
		void virtual getEventFunction() const = 0;
		EventType GetEventType() const { return m_type; };
		void Register();
	private:
		EventType m_type;
	};

	class OnCollideEvent : Event {

	public:
		OnCollideEvent(OnCollideDefinition e) : Event(e) {
			m_funCall = e.funCall;
		};
	private:
		std::function<void(GameObjectDef)> m_funCall;
	};

	class EventHandler {

	public:
		EventHandler();
		bool Dispatch(EventType eventType) {
			for (size_t i = 0; i < m_registeredEvents.size(); i++)
			{
				Event* e = &m_registeredEvents[i];
				if (eventType == e->GetEventType()) {

				}
			}
		}
		void Add(Event e);
	private:
		Event& m_currentEvent;
		std::vector<Event> m_registeredEvents;
	};
}


