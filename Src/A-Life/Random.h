#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtc/noise.hpp>

#include <random>

extern std::random_device g_random_device;
extern std::mt19937 g_random_generator;

inline void seedRandom(unsigned int seed)
{
	g_random_generator.seed(seed);
}

inline int random()
{
	return std::uniform_int_distribution<int>(0, std::numeric_limits<int>::max())(g_random_generator);
}

inline int random(int max)
{
	return std::uniform_int_distribution<int>(0, max - 1)(g_random_generator);
}

inline int random(int min, int max) 
{
	return std::uniform_int_distribution<int>(min, max)(g_random_generator);
}

template<typename T>
inline T random01()
{
	return std::uniform_real_distribution<T>((T)0, (T)1)(g_random_generator);
}

template<typename T>
inline T random(T min, T max)
{
	if (min > max) std::swap(min, max);
	return min + (max - min) * random01<T>();
}

inline glm::vec3 random(const glm::vec3& min, const glm::vec3& max)
{
	return glm::vec3{ random(min.x, max.x), random(min.y, max.y), random(min.z, max.z) };
}

inline glm::vec3 randomInUnitSphere()
{
	glm::vec3 v;
	// generate random vectors between -1 <-> +1, return vector if length is less than 1
	do
	{
		v = random(glm::vec3{ -1 }, glm::vec3{ 1 });
	} while (glm::length2(v) >= 1.0f);

	return v;
}
