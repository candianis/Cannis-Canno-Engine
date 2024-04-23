#pragma once

#include <bitset>
#include <cstdint>

using std::uint32_t;
using std::uint8_t;

class Entity
{
private:
	uint32_t ID;

public:
	Entity(int ID) : ID(ID) {};
	Entity(const Entity& entity) = default;
	int GetID() const;
};