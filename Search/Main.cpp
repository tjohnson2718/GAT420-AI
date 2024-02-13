#include "Node.h"
#include <iostream>
#include <vector>
#include <stack>
#include <queue>

template<typename T>
using char_node_t = node<T>;

// Depth-First Search function
std::vector<char_node_t<char>*> getDFS(char_node_t<char>* root, char target) {
	// Check for valid root node
	if (root == nullptr) return std::vector<char_node_t<char>*>();

	// Create nodes stack and push root onto stack
	std::stack<char_node_t<char>*> node_stack;
	root->visited = true;
	node_stack.push(root);

	while (!node_stack.empty()) {
		// Get current node from the top of stack
		char_node_t<char>* current = node_stack.top();

		// Check if the current node data is the target value
		if (current->data == target) {
			std::cout << "found: " << current->data << std::endl;
			break;
		}
		else {
			std::cout << "visited: " << current->data << std::endl;
		}

		// If target not found then go down the tree (child of the current node)
		// Push unvisited child nodes onto the stack
		bool popNode = true; // Pop node if there are no unvisited children
		for (char_node_t<char>* child : current->children) {
			// If the child node is unvisited, mark it visited and push onto the stack
			if (!child->visited) {
				child->visited = true;
				node_stack.push(child);
				popNode = false;
				break;
			}
		}

		// If no unvisited children of the current node, then pop the stack to go back up the tree
		if (popNode) {
			node_stack.pop();
		}
	}

	// Convert stack nodes to a vector of nodes (path)
	// Stack nodes are in reverse order with the target at the top
	// Add stack nodes to the front of the path vector
	std::vector<char_node_t<char>*> path;
	while (!node_stack.empty()) {
		// Add top node and then pop the node off the stack
		path.insert(path.begin(), node_stack.top());
		node_stack.pop();
	}

	return path;
}

// Breadth-First Search function
std::vector<char_node_t<char>*> getBFS(char_node_t<char>* root, char target) {
	// Check for valid root node
	if (root == nullptr) return std::vector<char_node_t<char>*>();

	// Create nodes queue and queue root onto the stack
	std::queue<char_node_t<char>*> node_queue;
	root->visited = true;
	node_queue.push(root);

	while (!node_queue.empty()) {
		// Get current node from the front of the queue
		char_node_t<char>* current = node_queue.front();

		// Check if the current node data is the target value
		if (current->data == target) {
			std::cout << "found: " << current->data << std::endl;
			break;
		}
		else {
			std::cout << "visit: " << current->data << std::endl;
		}

		// If target not found, then enqueue all the children of the current node into the queue
		for (char_node_t<char>* child : current->children) {
			if (!child->visited) {
				child->visited = true;
				child->parent = current;
				node_queue.push(child);
			}
		}

		// Pop the front of the queue
		node_queue.pop();
	}

	// Convert nodes to a vector of nodes (path)
	// Nodes are in reverse order with the parent used to move through the nodes
	// Add nodes to the front of the path vector
	std::vector<char_node_t<char>*> path;
	char_node_t<char>* node = (node_queue.empty()) ? nullptr : node_queue.front();
	while (node) {
		// Add node and then set node to node parent
		path.insert(path.begin(), node);
		node = node->parent;
	}

	return path;
}

int main()
{
	//    A
	//   B C
	//  D E F
	// create nodes with char data

	char_node_t<char>* nodeA = new char_node_t<char>{ 'A' };
	char_node_t<char>* nodeB = new char_node_t<char>{ 'B' };
	char_node_t<char>* nodeC = new char_node_t<char>{ 'C' };
	char_node_t<char>* nodeD = new char_node_t<char>{ 'D' };
	char_node_t<char>* nodeE = new char_node_t<char>{ 'E' };
	char_node_t<char>* nodeF = new char_node_t<char>{ 'F' };

	// Create tree from nodes (children)
	nodeA->children.push_back(nodeB); // A->B
	nodeA->children.push_back(nodeC); // A->C
	nodeB->children.push_back(nodeD); // B->D
	nodeB->children.push_back(nodeE); // B->E
	nodeC->children.push_back(nodeF); // C->F

	// Get search path to 'F' from node 'A'
	auto path = getBFS(nodeA, 'F');

	// Display path result
	std::cout << "path: ";
	for (char_node_t<char>* node : path) {
		std::cout << "->" << node->data;
	}
	std::cout << std::endl;
}