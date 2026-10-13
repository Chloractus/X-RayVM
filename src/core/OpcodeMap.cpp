#include "OpcodeMap.h"
#include <algorithm>
#include <random>
#include <stdexcept>

void OpCodeMap::Shuffle() {
	for (std::size_t i = 0; i < map.size(); i++) {
		map[i] = static_cast<OpCode>(i);
	}

	std::random_device rd;
	std::mt19937 gen(rd());
	std::shuffle(map.begin(), map.end(), gen);
}

OpCode OpCodeMap::Translate(std::size_t raw) const {
	return map.at(raw);
}

std::size_t OpCodeMap::Encode(OpCode real) const {
	for (std::size_t i = 0; i < map.size(); i++) {
		if (map[i] == real) {
			return i;
		}
	}
	throw std::out_of_range("OpCodeMap::Encode: opcode not found in map");
}