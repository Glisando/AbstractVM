#include "VM.class.hpp"

void VM::push(std::string &value, eOperandType &type) {

    Factory *fac = new Factory();
    
    this->stack.push_back(fac->createOperand(type, value));
}

void VM::assert(std::string &value, eOperandType &type)
{

    Factory *fac = new Factory();
    this->stack.push_back(fac->createOperand(type, value));
}
