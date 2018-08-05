#include "VM.class.hpp"

void VM::push(std::string &value, eOperandType &type) {

    Factory *fac = new Factory();
    
    this->stack.push_back(fac->createOperand(type, value));
    delete fac;
}

void VM::assert(std::string &value, eOperandType &type)
{

    Factory *fac = new Factory();
    this->stack.push_back(fac->createOperand(type, value));
    delete fac;
}

void VM::add(void)
{
    std::vector<const IOperand *>::iterator it = this->stack.end();
    --it;
    const IOperand *p1 = *it;
    this->stack.pop_back();
    it = this->stack.end();
    --it;
    const IOperand *p2 = *it;
    this->stack.pop_back();

    const IOperand *res = p1 + p2;
    this->stack.push_back(res);
}
