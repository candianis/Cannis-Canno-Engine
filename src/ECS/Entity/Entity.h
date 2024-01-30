#pragma once

class Entity
{
private:
	int ID;

public:
	Entity(int ID) : ID(ID) {};
	Entity(const Entity& entity) = default;
	int GetID() const;
};

