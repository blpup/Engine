#pragma once
#include <vector>
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
	class ISubject;
	class IObserver;
	class PhysicsSubject;

	class ISubject {
	public:
		virtual ~ISubject() {};
		virtual void Attach(IObserver* observer) = 0;
		virtual void Detach(IObserver* observer) = 0;
		virtual void Notify(const GameObjectDef& entity) = 0;
	};

	class IObserver {
		
	public:
		virtual ~IObserver() {};
		IObserver();
		virtual void Update(const GameObjectDef& entity) = 0;
		PhysicsSubject* m_sub;
	};



	class OnCollideObserver : public IObserver
	{
		using stdfunc_type = std::function<void(const GameObjectDef*)>;
	public:
		OnCollideObserver(stdfunc_type callback, uint64_t id);
		~OnCollideObserver() {};
		void Update(const GameObjectDef& entity) override;
		uint64_t GetID() const { return m_id;  };
	private:
		PhysicsSubject* m_subject;
		stdfunc_type m_function;
		uint64_t m_id;
	};


	class PhysicsSubject {
	public:
		void Attach(OnCollideObserver observer);
		void Detach(IObserver* observer);
		void Notify(const GameObjectDef& entity);
		static PhysicsSubject& GetInstance();
		PhysicsSubject() {};
		void operator=(const PhysicsSubject&) = delete;
		PhysicsSubject(PhysicsSubject& other) = delete;
	private:
		std::vector<OnCollideObserver> m_observers;
	};
}



