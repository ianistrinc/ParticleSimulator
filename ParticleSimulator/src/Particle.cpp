#include "Particle.h"
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.1415926535897932384626433
#endif
namespace Window {
	Particle::Particle()
		: X(0), Y(0)
	{
		Init();
	}
	Particle::~Particle(){}

	void Particle::Update(int& interval)
	{	
		m_Direction += interval * 0.0003;
		double xSpeed = m_Speed * cos(m_Direction);
		double ySpeed = m_Speed * sin(m_Direction);

		X += xSpeed * interval;
		Y += ySpeed * interval;

		if (X < -1 || X > 1 || Y < -1 || Y > 1)
			Init();
		if (rand() < RAND_MAX / 100)
			Init();
	}

	void Particle::Init()
	{
		X = 0;
		Y = 0;
		m_Direction = (2 * M_PI * rand()) / RAND_MAX;
		m_Speed = (0.02 * rand()) / RAND_MAX;
		m_Speed *= m_Speed;

	}
}