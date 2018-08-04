#pragma once
#include "deltaFi.h"

class Particle
{
public:
	unsigned long long int mass;
	float charge;
	int radius;
	float elasticity;
	sf::Color color;

	Particle();
	~Particle();
};

