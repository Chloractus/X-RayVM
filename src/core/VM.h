#pragma once

#include "Instruction.h"
#include "VMContext.h"
#include <vector>

class VM {
public:

	VM(std::vector<Instruction> prog);

	void Step();
	void VMEnter();
	void Reset();
	bool IsHalted() const;
	const VMContext& GetContext() const;
	const Instruction& CurrentInstruction() const;

private:
	VMContext context;
	bool halted = false;
	std::vector<Instruction> program;
};