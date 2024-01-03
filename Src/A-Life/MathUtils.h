#pragma once
#include <glm/glm.hpp>

template <typename T>
inline T clamp(const T& v, const T& min, const T& max)
{
	return (v <= min) ? min : (v >= max) ? max : v;
}

inline float clamp(float v)
{
	return (v <= 0) ? 0 : (v >= 1) ? 1 : v;
}

inline int wrap(int v, int min, int max)
{
	if (min > max) std::swap(min, max);
	return (v - min + (max - min)) % (max - min) + min;
}

inline float wrap(float v, float min, float max)
{
	if (min > max) std::swap(min, max);
	return std::fmod((v - min + (max - min)), (max - min)) + min;
}

template <typename T>
inline T lerp(const T& a, const T& b, float t)
{
	return (a * (1.0f - t)) + (b * t);
}

template <typename T1, typename T2>
inline T2 map(const T1& t, const T1& min1, const T1& max1, const T2& min2, const T2& max2)
{
	return min2 + (t - min1) * (max2 - min2) / (max1 - min1);
}

inline float smoothstep(float edge0, float edge1, float t) 
{
	t = clamp((t - edge0) / (edge1 - edge0));
	return t * t * (3.0f - 2.0f * t);
	//return t * t * t * (t * (6.0f * t - 15.0f) + 10.0f);
}

inline float dot(const glm::vec3& v1, const glm::vec3& v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

inline glm::vec3 cross(const glm::vec3& v1, const glm::vec3& v2)
{
	return glm::vec3
	{
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x,
	};
}

inline bool approximately(float value1, float value2)
{
	// check if the difference between the values is less than epsilon
	return (fabs(value1 - value2) < FLT_EPSILON);
}

inline glm::vec3 reflect(const glm::vec3& v, const glm::vec3& n)
{
	return v - ((2 * dot(n, v)) * n);
}

inline bool refract(const glm::vec3& v, const glm::vec3& n, float index, glm::vec3& refracted)
{
	// normalize the incoming vector (v)
	glm::vec3 nv = glm::normalize(v);

	float dt = dot(nv, n);
	float discriminant = 1 - (index * index) * (1 - dt * dt);
	if (discriminant > 0)
	{
		refracted = index * (nv - (n * dt)) - (n * std::sqrt(discriminant));
		return true;
	}

	return false;
}

inline float schlick(float cosine, float index)
{
	// calculate specular reflection coefficient, or probability of reflection
	float r0 = (1.0f - index) / (1 + index);
	r0 = r0 * r0;
	return r0 + (1.0f - r0) * (float)std::pow((1.0f - cosine), 5);
}