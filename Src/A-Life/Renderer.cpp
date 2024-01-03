#include "Renderer.h"
#include "Texture.h"
#include <iostream>

bool Renderer::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}

void Renderer::Shutdown()
{
	if (window) SDL_DestroyWindow(window);
	if (renderer) SDL_DestroyRenderer(renderer);

	SDL_Quit();
}

bool Renderer::CreateWindow(const std::string& title, int width, int height)
{
	this->width = width;
	this->height = height;

	window = SDL_CreateWindow(title.c_str(), 100, 100, width, height, SDL_WINDOW_SHOWN);
	if (!window)
	{
		std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer)
	{
		std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}

void Renderer::Present()
{
	SDL_RenderPresent(renderer);
}

void Renderer::RenderCopy(std::shared_ptr<Texture> texture)
{
	if (SDL_RenderCopy(renderer, texture->texture, nullptr, nullptr) != 0)
	{
		std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
	}
}

