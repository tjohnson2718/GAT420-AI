#include "Texture.h"
#include "Renderer.h"
#include <cassert>

Texture::Texture(int width, int height, const class Renderer& renderer) 
{
	size = { width, height };
	texture = SDL_CreateTexture(renderer.renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
		width, height);
}

Texture::~Texture()
{
	if (texture) SDL_DestroyTexture(texture);
}

bool Texture::Copy(const std::vector<rgba_t>& buffer)
{
	assert(buffer.size() == (size.x * size.y));

	SDL_UpdateTexture(texture, nullptr, buffer.data(), size.x * sizeof(rgba_t));
	return true;
}
