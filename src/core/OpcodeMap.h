#pragma once

#include "Instruction.h"
#include <array>

struct OpCodeMap {
	std::array <OpCode, static_cast<std::size_t>(OpCode::COUNT)> map;

	void Shuffle();
	OpCode Translate(std::size_t raw) const;
	std::size_t Encode(OpCode real) const;
};