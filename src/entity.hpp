/*
* Base class for variables and functions
*/

#pragma once

#include <list>

class Entity {
private:
	double value_;
	std::list<Entity*> dependent_;
	bool is_actual_;

protected:
	void SetValue(double new_value) noexcept;
	const std::list<Entity*>& GetDependent() const noexcept;
	virtual void MakeActual() noexcept;

public:
	Entity(double value);

	virtual double Extract();
	void AddDependent(Entity* entity);
	virtual bool IsActual() const noexcept;
	virtual void MakeNonActual();

	virtual ~Entity() = default;

};
