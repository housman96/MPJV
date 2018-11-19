#pragma once

enum class Type { Particle, Rigibody };

class GameObject
{
public:
	Type t;
	virtual void update(float) = 0;        /* Integre la position et la vitesse */
};

