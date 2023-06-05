/*
* Base class for variables and functions
*/

#pragma once

#include <list>

class Entity {
private:
	double value_;
	std::list<Entity*> dependent_;

protected:
	void SetValue(double new_value) noexcept;
	const std::list<Entity*>& GetDependent() const noexcept;


public:
	Entity(double value);

	virtual double Extract() noexcept;
	void AddDependent(Entity* entity) noexcept;

	virtual ~Entity() = default;

};
