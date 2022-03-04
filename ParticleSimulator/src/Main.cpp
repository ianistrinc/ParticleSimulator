#include "Screen.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "Swarm.h"
#include "Particle.h"

int main()
{
	srand(time(NULL));

	Window::Screen screen;

	if (!screen.Init())
		printf("Error initialising SDL\n");

	Window::Swarm swarm;

	while (true)
	{
		int elapsed = SDL_GetTicks();

		swarm.Update(elapsed);

		unsigned char green = (unsigned char)((1 + sin(elapsed * 0.001)) * 128);
		unsigned char red = (unsigned char)((1 + sin(elapsed * 0.002)) * 128);
		unsigned char blue = (unsigned char)((1 + sin(elapsed * 0.003)) * 128);

		const Window::Particle* const pParticles = swarm.GetParticles();

		for (int i = 0; i < Window::Swarm::PARTICLES; i++)
		{
			Window::Particle particle = pParticles[i];

			int x = (particle.X + 1) * Window::Screen::SCREEN_WIDTH / 2;
			int y = particle.Y * Window::Screen::SCREEN_WIDTH / 2 + Window::Screen::SCREEN_HEIGHT / 2;

			screen.SetPixel(x, y, red, green, blue);
		}

		screen.Blur();
		screen.Update();

		if (!screen.ProcessEvents())
			break;
	}

	screen.Close();
}