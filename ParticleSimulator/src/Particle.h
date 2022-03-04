#pragma once

namespace Window {

	class Particle
	{
	public:
		double X;
		double Y;
	private:
		double m_Speed;
		double m_Direction;
	public:
		Particle();
		~Particle();
		void Update(int& interval);
	private:
		void Init();
	};
}