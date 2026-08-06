#include <iostream>
#include <vector>
#include "Instruction.h"
#include "VM.h"

int main() {
    std::vector<Instruction> program = {
        { OpCode::PUSH, 3 },
        { OpCode::PUSH, 4 },
        { OpCode::ADD,  0 },
        { OpCode::PUSH, 2 },
        { OpCode::MUL,  0 },
        { OpCode::HALT, 0 }
    };

    VM vm(program);
    vm.VMEnter();

    std::cout << "Result: " << vm.GetContext().OpStack.back() << std::endl;
    return 0;
}