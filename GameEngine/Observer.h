#pragma once
#include <vector>
#include <functional>
#include "GameObject.h"

namespace GameEngine {
	class IObserver;
	class PhysicsSubject;


	class IObserver {
		
	public:
		virtual ~IObserver() {};
		IObserver() : m_sub(nullptr) {};
		virtual void Update(const GameObjectDefinition& entity) = 0;
		PhysicsSubject* m_sub;
	};



	class OnCollideObserver : public IObserver
	{
		using func = std::function<void(const GameObjectDefinition*)>;
	public:
		OnCollideObserver(func callback, uint64_t id);
		~OnCollideObserver() {};
		void Update(const GameObjectDefinition& entity) override;
		uint64_t GetID() const { return m_id;  };
	private:
		PhysicsSubject* m_subject;
		func m_function;
		uint64_t m_id;
	};


	class PhysicsSubject {
	public:
		void Attach(OnCollideObserver observer);
		void Detach(IObserver* observer);
		void Notify(const GameObjectDefinition& otherEntity, const GameObjectDefinition& currentEntity);
		static PhysicsSubject& GetInstance();
		PhysicsSubject() {};
		void operator=(const PhysicsSubject&) = delete;
		PhysicsSubject(PhysicsSubject& other) = delete;
	private:
		std::vector<OnCollideObserver> m_observers;
	};
}



