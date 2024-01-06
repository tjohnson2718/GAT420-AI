#pragma once
#include "Environment.h"
class CA : public Environment
{
public:
	CA(int width, int height, std::shared_ptr<class Texture> texture) :
		Environment{ width, height, texture } {}

	bool Initialize() override;
	void Step() override;

protected:
	std::vector<uint8_t> buffer;
};