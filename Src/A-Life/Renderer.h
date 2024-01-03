#pragma once
#include <SDL.h>
#include <glm/glm.hpp>
#include <memory>
#include <string>

class Renderer
{
public:
	Renderer() = default;

	bool Initialize();
	void Shutdown();
	bool CreateWindow(const std::string& title, int width, int height);
	void Present();

	void RenderCopy(std::shared_ptr<class Texture> texture);

	int GetWidth() const { return width; }
	int GetHeight() const { return height; }

	friend class Texture;

private:
	int width{ 0 };
	int height{ 0 };

	SDL_Window* window{ nullptr };
	SDL_Renderer* renderer{ nullptr };
};
