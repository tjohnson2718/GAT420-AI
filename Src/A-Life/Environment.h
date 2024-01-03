#pragma once
#include "Color.h"
#include "MathUtils.h"
#include <SDL.h>
#include <glm/glm.hpp>
#include <memory>
#include <vector>

class Environment
{
public:
	Environment(int width, int height, std::shared_ptr<class Texture> texture) : 
		size{ width, height },
		texture{ texture } 
	{
		color_buffer.resize(width * height);
	}

	virtual bool Initialize() = 0;
	virtual void Step() = 0;

	// buffers
	template<typename T>
	T Read(const std::vector<T>& buffer, int x, int y, bool envWrap = true);
	template<typename T>
	void Write(std::vector<T>& buffer, int x, int y, const T& value, bool envWrap = true);

	const std::vector<rgba_t>& GetColorBuffer() const { return color_buffer; }

	// input
	virtual void KeyDown(SDL_Keycode keycode);
	virtual void MouseButtonDown(int mouse);
	virtual void MouseButtonUp(int mouse);
	virtual void MousePositionNormalized(const glm::vec2& position);

protected:
	glm::ivec2 size{ 0, 0 };

	// input
	glm::ivec2 mouse_position{ 0, 0 };
	glm::ivec2 mouse_position_prev{ 0, 0 };
	glm::ivec2 mouse_relative{ 0, 0 };
	uint8_t mouse_button[3] = { 0, 0, 0 };

	// color buffer -> texture
	std::vector<rgba_t> color_buffer;
	std::shared_ptr<class Texture> texture;
};

template<typename T>
inline T Environment::Read(const std::vector<T>& buffer, int x, int y, bool wrapValue)
{
	if (wrapValue)
	{
		x = wrap(x, 0, size.x);
		y = wrap(y, 0, size.y);
	}
	else if (x < 0 || x >= size.x || y < 0 || y >= size.y) return 0;

	return buffer[x + (y * size.x)];
}

template<typename T>
inline void Environment::Write(std::vector<T>& buffer, int x, int y, const T& value, bool wrapValue)
{
	if (wrapValue)
	{
		x = wrap(x, 0, size.x);
		y = wrap(y, 0, size.y);
	}
	else if (x < 0 || x >= size.x || y < 0 || y >= size.y) return;

	buffer[x + (y * size.x)] = value;
}
