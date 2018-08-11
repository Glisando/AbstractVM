#include "VM.class.hpp"

void VM::push(std::string &value, eOperandType &type) {
    
    this->stack.push_back(Factory().createOperand(type, value));
}

void VM::assert(std::string &value, eOperandType &type)
{
    const IOperand *x = stack.back();;

    const IOperand *y = Factory().createOperand(type, value);

    if (*x == *y)
        std::cout << (*x).toString() << "uraa" << std::endl;
    else
        std::cout << "throw(assert);" << std::endl;
        
}

void VM::add(void)
{
    const IOperand *p1 = this->stack.back();
    this->stack.pop_back();

    const IOperand *p2 = this->stack.back();
    this->stack.pop_back();

    const IOperand *res = *p2 + *p1;
    this->stack.push_back(res);

    std::vector<const IOperand *>::iterator lol = this->stack.end();
    lol--;
    std::cout << (*lol)->toString() << std::endl;

    delete p1;
    delete p2;    
}
