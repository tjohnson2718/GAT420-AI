#pragma once
#include "Buffer.h"
#include <SDL.h>

class Texture
{
public:
	Texture() = default;
	Texture(int width, int height, const class Renderer& renderer);
	~Texture();

	bool Copy(const std::vector<rgba_t>& buffer);

	glm::ivec2 GetSize() const { return size; }

	friend class Renderer;

private:
	glm::ivec2 size{ 0, 0 };
	SDL_Texture* texture{ nullptr };
};