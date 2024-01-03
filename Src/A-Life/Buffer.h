#pragma once
#include "Color.h"
#include <vector>
#include <algorithm>

template <typename T>
class Buffer
{
public:
	Buffer() = default;
	Buffer(size_t size) { data.resize(size, T()); }

	void Resize(size_t size) { data.resize(size, T()); }

	const T& operator [] (int index) const { return data[index]; }
	T& operator [] (int index) { return data[index]; }

	const T& At(int index) const { return data[index]; }
	T& At(int index) { return data[index]; }

	void Fill(const T& v) { std::fill(data.begin(), data.end(), v); }

	std::vector<T>& GetData() { return data; }
	const std::vector<T>& GetData() const { return data; }

	size_t GetSize() const { return data.size(); }

protected:
	std::vector<T> data;
};

template <typename T>
class Buffer2D : public Buffer<T>
{
public:
	Buffer2D() = default;
	Buffer2D(int width, int height) : Buffer<T>(width* height), width{ width }, height{ height } { }

	void Resize(int width, int height) { Resize(width * height); }

	const T& At(int x, int y) const { return Buffer<T>::data[x + (y * width)]; }
	T& At(int x, int y) { return Buffer<T>::data[x + (y * width)]; }

	int GetWidth() const { return width; }
	int GetHeight() const { return height; }

protected:
	int width{ 0 };
	int height{ 0 };

};

inline bool Convert(Buffer<uint8_t>& source, Buffer<rgba_t>& destination)
{
	if (source.GetSize() != destination.GetSize()) return false;

	std::transform(source.GetData().begin(), source.GetData().end(), destination.GetData().begin(), [](uint8_t v)
		{
			{ return  v ? 0xffffffff : 0; }
		});

	return true;
}