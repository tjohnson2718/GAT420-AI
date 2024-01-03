#include "Cells.h"
#include "Texture.h"

bool Cells::Initialize()
{
	buffer.resize(size.x * size.y);

	return true;
}

void Cells::Step()
{
	// "draw" onto buffer
	if (mouse_button[1])
	{
		Write<uint8_t>(buffer, mouse_position.x, mouse_position.y, 255);
	}

	// convert buffer data format to color buffer
	std::transform(buffer.begin(), buffer.end(), color_buffer.begin(), [](uint8_t v)
		{
			uint8_t color = v;
			return v ? (color << 24 | color << 16 | color << 8 | 0xff) : 0;
		});

	// copy color buffer to texture
	texture->Copy(color_buffer);
}

