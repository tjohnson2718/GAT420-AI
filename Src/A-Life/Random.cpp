#include "Random.h"

std::random_device g_random_device;
std::mt19937 g_random_generator(g_random_device());
