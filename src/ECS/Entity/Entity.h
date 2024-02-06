#pragma once

class Entity
{
private:
	unsigned long ID;

public:
	Entity(int ID) : ID(ID) {};
	Entity(const Entity& entity) = default;
	int GetID() const;
};