#include "entity.hpp"

Entity::Entity(double value) : value_(value) {}

double Entity::Extract() {
	return value_;
}

void Entity::SetValue(double new_value) noexcept {
	value_ = new_value;
}

void Entity::AddDependent(Entity* entity) {
	dependent_.push_back(entity);
}

const std::list<Entity*>& Entity::GetDependent() const noexcept {
	return dependent_;
}
