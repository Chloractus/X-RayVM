#include "VM.h"

VM::VM(std::vector<Instruction> prog) {
	program = prog;
};

void VM::Reset() {
	context.Reset();
	halted = false;
};

bool VM::IsHalted() const {
	return halted;
};

const VMContext& VM::GetContext() const {
	return context;
};

const Instruction& VM::CurrentInstruction() const {
	return program.at(context.counter);
};

void VM::Step() {
	if (IsHalted() || context.counter >= program.size()) {
		halted = true;
		return;
	};

	const Instruction& instruct = VM::CurrentInstruction();

	int b = 0;
	int a = 0;

	switch (instruct.opcode) {
	case OpCode::PUSH:
		context.OpStack.push_back(instruct.operand);
		context.counter++;
		break;

	case OpCode::POP:
		context.OpStack.pop_back();
		context.counter++;
		break;

	case OpCode::ADD:
		b = context.OpStack.back(); context.OpStack.pop_back();
		a = context.OpStack.back(); context.OpStack.pop_back();
		context.OpStack.push_back(a + b);
		context.counter++;
		break;

	case OpCode::SUB:
		b = context.OpStack.back(); context.OpStack.pop_back();
		a = context.OpStack.back(); context.OpStack.pop_back();
		context.OpStack.push_back(a - b);
		context.counter++;
		break;

	case OpCode::MUL:
		b = context.OpStack.back(); context.OpStack.pop_back();
		a = context.OpStack.back(); context.OpStack.pop_back();
		context.OpStack.push_back(a * b);
		context.counter++;
		break;

	case OpCode::DIV:
		b = context.OpStack.back(); context.OpStack.pop_back();
		a = context.OpStack.back(); context.OpStack.pop_back();
		if (b == 0) {
			halted = true;
			context.OpStack.push_back(0);
			break;
		}
		else {
			context.OpStack.push_back(a / b);
			context.counter++;
			break;
		}

	case OpCode::HALT:
		halted = true;
		break;

	case OpCode::JMP:
		context.counter = instruct.operand;
		break;

	case OpCode::JZ:
		b = context.OpStack.back(); context.OpStack.pop_back();

		if (b == 0) {
			context.counter = instruct.operand;
		}
		else {
			context.counter++;
		};
		break;
	};
};

void VM::VMEnter() {
	while (!VM::IsHalted()) {
		Step();
	};
};