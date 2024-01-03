#include "Environment.h"
#include "Texture.h"
#include "Random.h"

void Environment::KeyDown(SDL_Keycode keycode)
{
}

void Environment::MouseButtonDown(int mouse)
{
	mouse_button[mouse] = 1;
}

void Environment::MouseButtonUp(int mouse)
{
	mouse_button[mouse] = 0;
}

void Environment::MousePositionNormalized(const glm::vec2& position)
{
	mouse_position_prev = mouse_position;

	// convert normalized mouse position to environment size position
	mouse_position = glm::floor(clamp(position, glm::vec2{ 0 }, glm::vec2{ 1 }) * (glm::vec2)size);
	mouse_relative = mouse_position - mouse_position_prev;
}
