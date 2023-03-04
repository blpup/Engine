#pragma once
namespace GameEngine{
	class GameMovement
	{
	public:
		GameMovement(GameMovement& other) = delete;
		void operator=(const GameMovement&) = delete;
		static GameMovement& GetInstance();
		void Add();
		void Remove();
		void Update();
	private:
		GameMovement(void){}
	};
}


