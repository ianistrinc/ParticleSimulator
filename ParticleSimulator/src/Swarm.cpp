#include "Swarm.h"

namespace Window {
	Swarm::Swarm()
		:lastTime(0)
	{
		m_pParticles = new Particle[PARTICLES];
	}

	Swarm::~Swarm()
	{
		delete[] m_pParticles;
	}

	const Particle* const Swarm::GetParticles()
	{
		return m_pParticles;
	}

	void Swarm::Update(int& elapsed)
	{
		int interval = elapsed - lastTime;

		for (unsigned int i = 0; i < PARTICLES; i++)
			m_pParticles[i].Update(interval);

		lastTime = elapsed;
	}
}
