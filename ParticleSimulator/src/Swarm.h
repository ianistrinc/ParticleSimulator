#pragma once
#include "Particle.h"

namespace Window {

	class Swarm
	{
	public:
		const static int PARTICLES = 8000;
	private:
		Particle* m_pParticles;
		int lastTime;
	public:
		Swarm();
		~Swarm();
		void Update(int& elapsed);
		const Particle* const GetParticles();
	};
}