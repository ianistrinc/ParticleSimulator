#pragma once
#include <SDL.h>
#undef main

namespace Window {
	class Screen
	{
	private:
		SDL_Window* m_Window;
		SDL_Renderer* m_Renderer;
		SDL_Texture* m_Texture;
		Uint32* m_Buffer;
		Uint32* m_BlurBuffer;
		const static char* m_WindowName;

	public:
		const static int SCREEN_WIDTH = 800;
		const static int SCREEN_HEIGHT = 600;
	
	public:
		Screen();
		bool Init();
		void Update();
		void SetPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
		bool ProcessEvents();
		void Close();
		void Blur();
	};
}