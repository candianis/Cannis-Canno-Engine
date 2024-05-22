#pragma once

#include <cstdint>

using std::uint32_t;

struct IComponent {
	static uint32_t nextID;
};

template<typename T>
class Component : public IComponent {
public:
	static uint32_t GetID() {
		static uint32_t ID = nextID++;
		return ID;
	};
};