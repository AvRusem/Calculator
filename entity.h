/*
* Interface for variables and functions
*/

#pragma once

class IEntity {
public:
	virtual double Extract() const = 0;

	virtual ~IEntity() = default;

};
