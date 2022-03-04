#include "Screen.h"

namespace Window {

	const char* Screen::m_WindowName = "Particle Simulator";

	Screen::Screen()
		: m_Window(NULL), m_Renderer(NULL),m_Texture(NULL), m_Buffer(NULL), m_BlurBuffer(NULL)
	{

	}
	bool Screen::Init()
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			return false;
		}

		m_Window = SDL_CreateWindow(m_WindowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (m_Window == NULL)
		{
			SDL_Quit();
			return false;
		}

		m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_PRESENTVSYNC);
		m_Texture = SDL_CreateTexture(m_Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC,
			SCREEN_WIDTH, SCREEN_HEIGHT);

		if (m_Renderer == NULL)
		{
			SDL_DestroyWindow(m_Window);
			SDL_Quit();
			return false;
		}

		if (m_Texture == NULL)
		{
			SDL_DestroyRenderer(m_Renderer);
			SDL_DestroyWindow(m_Window);
			SDL_Quit();
			return false;
		}

		m_Buffer = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
		m_BlurBuffer = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
		SDL_memset(m_Buffer, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
		SDL_memset(m_BlurBuffer, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));

		return true;
	}

	void Screen::Update()
	{
		SDL_UpdateTexture(m_Texture, NULL, m_Buffer, SCREEN_WIDTH * sizeof(Uint32));
		SDL_RenderClear(m_Renderer);
		SDL_RenderCopy(m_Renderer, m_Texture, NULL, NULL);
		SDL_RenderPresent(m_Renderer);
	}

	void Screen::SetPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue)
	{
		if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
			return;

		Uint32 color = 0;

		color += red;
		color <<= 8;
		color += green;
		color <<= 8;
		color += blue;
		color <<= 8;
		color += 0xff; // alpha

		m_Buffer[(y * SCREEN_WIDTH) + x] = color;
	}

	bool Screen::ProcessEvents()
	{
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				return false;
		}
		return true;
	}


	void Screen::Close()
	{
		delete[] m_Buffer;
		delete[] m_BlurBuffer;
		SDL_DestroyRenderer(m_Renderer);
		SDL_DestroyTexture(m_Texture);
		SDL_DestroyWindow(m_Window);
		SDL_Quit();
	}

	void Screen::Blur()
	{
		Uint32* temp = m_Buffer;
		m_Buffer = m_BlurBuffer;
		m_BlurBuffer = temp;

		for(int y = 0; y < SCREEN_HEIGHT; y++)
			for (int x = 0; x < SCREEN_WIDTH; x++)
			{
				int redT = 0;
				int greenT = 0;
				int blueT = 0;


				for(short int row = -1; row <= 1; row++)
					for (short int col = -1; col <= 1; col++)
					{
						int currentX = x + col;
						int currentY = y + row;

						if (currentX >= 0 && currentX < SCREEN_WIDTH && currentY >= 0 && currentY < SCREEN_HEIGHT)
						{
							Uint32 color = m_BlurBuffer[currentY * SCREEN_WIDTH + currentX];

							Uint8 red = color >> 24;
							Uint8 green = color >> 16;
							Uint8 blue = color >> 8;

							redT += red;
							greenT += green;
							blueT += blue;
						}
							 
					}

				Uint8 red = redT/9;
				Uint8 green = greenT/9;
				Uint8 blue = blueT/9;

				SetPixel(x, y, red, green, blue);
			}
	}
}