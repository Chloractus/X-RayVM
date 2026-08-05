#pragma once

enum class OpCode {
	PUSH,
	POP,
	ADD,
	SUB,
	MUL,
	JMP,
	JZ,
	HALT
};

struct Instruction {
	OpCode opcode;
	int operand;
};