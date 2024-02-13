#pragma once
#include <string>
#include <iostream>
using namespace std;

struct node_t
{
	node_t(const string& info) : info{info} {}

	virtual node_t* execute() = 0;

	string info;
	node_t* trueNode{ nullptr };
	node_t* falseNode{ nullptr };
};

enum ePredicate
{
	Less,
	Greater,
	Equal,
	Not_Equal
};

inline string getString(ePredicate predicate)
{
	switch (predicate)
	{
	case ePredicate::Less:
		return "<";
	case ePredicate::Greater:
		return ">";
	case ePredicate::Equal:
		return "=";
	case ePredicate::Not_Equal:
		return "!=";
	}

	return "";
}

template <typename T>
struct decision_t : public node_t
{
	decision_t(const string& info, T& parameter, ePredicate predicate, const T& value) :
		node_t{ info },
		parameter{ parameter },
		predicate{ predicate },
		value{ value }
	{}

	node_t* execute()
	{
		bool result = false;
		switch (predicate)
		{
		case ePredicate::Less:
			result = (parameter < value);
			break;
		case ePredicate::Greater:
			result = (parameter > value);
			break;
		case ePredicate::Equal:
			result = (parameter == value);
			break;
		case ePredicate::Not_Equal:
			result = (parameter != result);
			break;
		}

		cout << "decision: " << info << " : " << parameter << " " << getString(predicate) << " " << value << " (" << (result ? "true" : "fasle") << ")\n";
		return result ? trueNode : falseNode;
	}

	T& parameter; // reference to the parameter used for comparison
	T value; // value for comparison
	ePredicate predicate; // predicate used for comparison
};

struct action_t : public node_t
{
	action_t(const string& info) : node_t{ info } {}
	
	virtual node_t* execute() override
	{
		cout << "action: " << info << endl;
		return nullptr;
	}
};