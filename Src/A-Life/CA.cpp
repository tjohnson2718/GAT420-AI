#include "CA.h"
#include "Texture.h"

bool CA::Initialize()
{
	buffer.resize(size.x * size.y);

	return true;
}

void CA::Step()
{
	// "draw" onto buffer
	Write<uint8_t>(buffer, size.x / 2, 0, 1);

	// rule 30
	//uint8_t rule[] = { 0, 0, 0, 1, 0, 1, 1, 0 };
	static uint8_t rule = 149;
	//rule++;

	for (int y = 0; y < size.y - 1; y++)
	{
		for (int x = 0; x < size.x; x++)
		{
			uint8_t i = 0;
			i |= Read<uint8_t>(buffer, x - 1, y) << 2;
			i |= Read<uint8_t>(buffer, x, y) << 1;
			i |= Read<uint8_t>(buffer, x + 1, y) << 0;

			uint8_t state = (rule & 1 << i) ? 1 : 0;
			Write<uint8_t>(buffer, x, y + 1, state);
		}
	}

	// convert buffer data format to color buffer
	std::transform(buffer.begin(), buffer.end(), color_buffer.begin(), [](uint8_t v)
		{
			uint8_t color = v ? 255 : 0;
			return v ? (color << 24 | color << 16 | color << 8 | 0xff) : 0;
		});

	// copy color buffer to texture
	texture->Copy(color_buffer);
}