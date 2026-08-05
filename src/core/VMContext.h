#pragma once

#include <vector>
#include <cstddef>


struct VMContext {

	std::vector<int> OpStack;
	size_t counter = 0;

	void Reset() {
		OpStack.clear();
		counter = 0;
	}
};