#pragma once
#include <vector>

template<typename T>
struct node
{
	node(const T& data) : data{ data } {}

	T data = T();

	bool visited{ false };
	node* parent{ nullptr };
	std::vector<node*> children;
};