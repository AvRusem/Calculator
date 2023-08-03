#include "entity.hpp"

Entity::Entity(double value) : value_(value), is_actual_(true) {}

double Entity::Extract() {
	return value_;
}

void Entity::SetValue(double new_value) noexcept {
	value_ = new_value;
}

void Entity::AddDependent(Entity* entity) {
	dependent_.push_back(entity);
}

void Entity::MakeActual() noexcept {
	is_actual_ = true;
}

const std::list<Entity*>& Entity::GetDependent() const noexcept {
	return dependent_;
}

bool Entity::IsActual() const noexcept {
	return is_actual_;
}

void Entity::MakeNonActual() {
	is_actual_ = false;

	for (auto el : GetDependent()) {
		if (el->IsActual()) {
			el->MakeNonActual();
		}
	}
}
