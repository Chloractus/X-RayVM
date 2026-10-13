#pragma once

enum class OpCode {
	PUSH,
	POP,
	ADD,
	SUB,
	MUL,
	DIV,
	JMP,
	JZ,
	HALT,
	COUNT
};

struct Instruction {
	OpCode opcode;
	int operand;
};