#include "VM.class.hpp"

void VM::push(std::string &value, eOperandType &type) {
    
    this->stack.push_back(Factory().createOperand(type, value));
}

void VM::assert(std::string &value, eOperandType &type)
{
    if (stack.size() < 1)
    {
        Err("Error: operation: assert: less that one values in stack");
        return ;        
    }
    const IOperand *x = stack.back();;

    const IOperand *y = Factory().createOperand(type, value);

    if (x == NULL)
    {
        Err("Error: operation: assert: unstack NULL operand pointer");
        return ;
    }

    if (*x == *y)
        void(0);
    else
        Err("Error: operation: assert: An assert instruction is not true");

    delete y;
}

void VM::add(void)
{
    if (stack.size() < 2)
    {
        Err("Error: operation: add: less that two values in stack");
        return ;        
    }

    const IOperand *p1 = this->stack.back();
    this->stack.pop_back();

    const IOperand *p2 = this->stack.back();
    this->stack.pop_back();

    if (p1 == NULL || p2 == NULL)
    {
       Err("Error: operation: add: unstack NULL operand pointer");
        return ;
    }

    const IOperand *res = *p2 + *p1;
    this->stack.push_back(res);

    delete p1;
    delete p2;    
}

void VM::sub(void)
{
    if (stack.size() < 2)
    {
       Err("Error: operation: sub: less that two values in stack");
        return ;
    }

    const IOperand *p1 = this->stack.back();
    this->stack.pop_back();

    const IOperand *p2 = this->stack.back();
    this->stack.pop_back();

    if (p1 == NULL || p2 == NULL)
    {
       Err("Error: operation: sub: unstack NULL operand pointer");
        return ;
    }

    const IOperand *res = *p2 - *p1;
    this->stack.push_back(res);

    delete p1;
    delete p2;    
}

void VM::pop(void)
{
    if (stack.size() < 1)
    {
        Err("Error: operation: pop: pop on an empty stack");
        return ;
    }

    const IOperand *ptr = this->stack.back();
    this->stack.pop_back();
    
    if (ptr)
        delete ptr;
}

void   VM::dump(void)
{
    if (stack.size() < 1)
    {
        Err("Error: operation: dump: less that one values in stack");
        return ;
    }

    size_t i = stack.size() - 1;
    while (i != -1)
    {
        if (stack[i] == NULL)
        {
            Err("Error: operation: dump: unstack NULL operand pointer");
            return ;
        }
        std::cout << stack[i]->toString() << std::endl;
        i--;
    }
}

void   VM::print(void)
{
    if (stack.size() < 1)
    {
        Err("Error: operation: print: less that one values in stack");
        return ;
    }
    
    const IOperand *ptr = stack.back();


    if (ptr == NULL)
    {
        Err("Error: operation: print: unstack NULL operand pointer");
        return ;
    }
    if (ptr->getType() != Int8)
    {
        Err("Error: operation: print: bad number type");
        return ;
    }
    std::cout << static_cast<char>(std::stof(ptr->toString())) << std::endl;
}

void VM::mul(void)
{
    if (stack.size() < 2)
    {
        Err("Error: operation: mul: less that two values in stack");
        return ;
    }

    const IOperand *p1 = this->stack.back();
    this->stack.pop_back();

    const IOperand *p2 = this->stack.back();
    this->stack.pop_back();

    if (p1 == NULL || p2 == NULL)
    {
        Err("Error: operation: mul: unstack NULL operand pointer");
        return ;
    }
    const IOperand *res = *p2 * *p1;
    this->stack.push_back(res);

    delete p1;
    delete p2;  
}

void VM::div(void)
{
    if (stack.size() < 2)
    {
        Err("Error: operation: div: less that two values in stack");
        return ;
    }

    const IOperand *p1 = this->stack.back();
    this->stack.pop_back();

    const IOperand *p2 = this->stack.back();
    this->stack.pop_back();

    if (p1 == NULL || p2 == NULL)
    {
       Err("Error: operation: div: unstack NULL operand pointer");
        return ;
    }
    else if (p1->toString() == "0")
    {
       Err("Error: operation: div: division by zero");
        return ;        
    }

    const IOperand *res = *p2 / *p1;
    this->stack.push_back(res);

    delete p1;
    delete p2;  
}

void VM::mod(void)
{
    if (stack.size() < 2)
    {
        Err("Error: operation: mod: less that two values in stack");
        return ;
    }

    const IOperand *p1 = this->stack.back();
    this->stack.pop_back();

    const IOperand *p2 = this->stack.back();
    this->stack.pop_back();

    if (p1 == NULL || p2 == NULL)
    {
        Err("Error: operation: mod: unstack NULL operand pointer");
        return ;
    }
    else if (p1->toString() == "0")
    {
        Err("Error: operation: mod: modulo by zero");
        return ;
    }
    
    const IOperand *res = *p2 % *p1;
    this->stack.push_back(res);

    delete p1;
    delete p2;
}

void   VM::ex(std::string &input)
{
    clear_stack();
    exit(0);
}

void VM::clear_stack(void)
{
    for (size_t i = 0; i < stack.size(); i++)
    {
        delete stack[i];
    }
}