#pragma once

#include <xhash>

namespace GameEngine {
	class UUID
	{
	public:
		UUID();
		UUID(uint64_t uuid);
		operator uint64_t() const { return m_UUID; };
		void setID(const UUID id) { m_UUID = id; };
	private:
		uint64_t m_UUID;
	};
}


