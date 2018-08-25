#include "../inc/VM.class.hpp"

void VM::push(std::string &value, eOperandType &type) {
    
    const IOperand *ptr = Factory().createOperand(type, value);
    if (ptr == NULL)
        return ;
    this->stack.push_back(ptr);
}

void VM::assert(std::string &value, eOperandType &type)
{
    if (stack.size() < 1)
    {
        Err("Error: operation: assert: less than one value in stack");
        return ;        
    }
    const IOperand *x = stack.back();

    const IOperand *y = Factory().createOperand(type, value);

    if (y == NULL)
        return ;
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
        Err("Error: operation: add: less than two values in stack");
        return ;        
    }

    const IOperand *p1 = stack[stack.size() - 1];
    const IOperand *p2 = stack[stack.size() - 2];

    if (p1 == NULL || p2 == NULL)
    {
        Err("Error: operation: add: unstack NULL operand pointer");
        return ;
    }
    this->stack.pop_back();
    this->stack.pop_back();

    const IOperand *res = *p2 + *p1;
    if (res == NULL)
        return ;
    this->stack.push_back(res);

    delete p1;
    delete p2;    
}

void VM::sub(void)
{
    if (stack.size() < 2)
    {
        Err("Error: operation: sub: less than two values in stack");
        return ;
    }

    const IOperand *p1 = stack[stack.size() - 1];
    const IOperand *p2 = stack[stack.size() - 2];

    if (p1 == NULL || p2 == NULL)
    {
        Err("Error: operation: sub: unstack NULL operand pointer");
        return ;
    }
    this->stack.pop_back();
    this->stack.pop_back();

    const IOperand *res = *p2 - *p1;
    if (res == NULL)
        return ;
    this->stack.push_back(res);

    delete p1;
    delete p2;    
}

void VM::pop(void)
{
    if (stack.size() < 1)
    {
        Err("Error: operation: pop: pop on an empty stack");
        ex();
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
        Err("Error: operation: dump: less than one value in stack");
        return ;
    }
    
    int i = stack.size() - 1;

    while (i != -1)
    {
        if (stack[i] == NULL)
        {
            Err("Error: operation: dump: unstack NULL operand pointer");
            return ;
        }
        std::cout << "\033[32m" << stack[i]->toString() << "\33[0m" << std::endl;
        i--;
    }
}

void   VM::print(void)
{
    if (stack.size() < 1)
    {
        Err("Error: operation: print: less than one value in stack");
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
        Err("Error: operation: mul: less than two values in stack");
        return ;
    }

    const IOperand *p1 = stack[stack.size() - 1];
    const IOperand *p2 = stack[stack.size() - 2];

    if (p1 == NULL || p2 == NULL)
    {
        Err("Error: operation: mul: unstack NULL operand pointer");
        return ;
    }
    this->stack.pop_back();
    this->stack.pop_back();
    
    const IOperand *res = *p2 * *p1;
    if (res == NULL)
        return ;
    this->stack.push_back(res);

    delete p1;
    delete p2;  
}

void VM::div(void)
{
    if (stack.size() < 2)
    {
        Err("Error: operation: div: less than two values in stack");
        return ;
    }

    const IOperand *p1 = stack[stack.size() - 1];
    const IOperand *p2 = stack[stack.size() - 2];

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
    this->stack.pop_back();
    this->stack.pop_back();

    const IOperand *res = *p2 / *p1;
    if (res == NULL)
        return ;
    this->stack.push_back(res);

    delete p1;
    delete p2;  
}

void VM::mod(void)
{
    if (stack.size() < 2)
    {
        Err("Error: operation: mod: less than two values in stack");
        return ;
    }

    const IOperand *p1 = stack[stack.size() - 1];
    const IOperand *p2 = stack[stack.size() - 2];

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
    this->stack.pop_back();
    this->stack.pop_back();
    
    const IOperand *res = *p2 % *p1;
    if (res == NULL)
        return ;
    this->stack.push_back(res);

    delete p1;
    delete p2;
}

void   VM::ex()
{
    clear_stack();
    exit(0);
}

void VM::clear_stack(void)
{

    for (size_t i = 0; i < stack.size(); i++)
        delete stack[i];
}

void VM::max(void)
{
    if (stack.size() < 1)
    {
        Err("Error: operation: max: less than one value in stack");
        return ;        
    }

    long double max = DBL_MIN;
    long double tmp;
    size_t ind = 0;

    for (size_t i = 0; i < stack.size(); i++)
    {
        tmp = std::stold((stack[i])->toString());
        if (tmp > max)
        {
            max = tmp;
            ind = i;
        }
    }
    std::cout << "\033[32m" << (stack[ind])->toString() << "\33[0m" << std::endl;
}

void VM::min(void)
{
    if (stack.size() < 1)
    {
        Err("Error: operation: min: less than one value in stack");
        return ;        
    }

    long double max = DBL_MAX;
    long double tmp;
    size_t ind = 0;

    for (size_t i = 0; i < stack.size(); i++)
    {
        tmp = std::stold((stack[i])->toString());
        if (tmp < max)
        {
            max = tmp;
            ind = i;
        }
    }
    std::cout << "\033[32m" << (stack[ind])->toString() << "\33[0m" << std::endl;
}

void VM::rev(void)
{
    if (stack.size() < 1)
    {
        Err("Error: operation: rev: less than one value in stack");
        return ;        
    }

    std::vector<const IOperand *> ptr;
    size_t i = stack.size() - 1;
    while (i > 0)
    {
        ptr.push_back(stack[i]);
        i--;
    }
    ptr.push_back(stack[i]);
    stack = ptr;
}

void VM::more()
{
    if (stack.size() < 2)
    {
        Err("Error: operation: more: less than two values in stack");
        return ;        
    }
    size_t x = stack.size() - 1;
    size_t y = stack.size() - 2;
    if (stack[x] == NULL || stack[y] == NULL)
    {
        Err("Error: operation: more: unstack NULL operand pointer");
        return ;
    }

    if (*(stack[y]) >= *(stack[x]))
        void(0);
    else
        Err("Error: operation: more: instruction is not true");
}

void VM::swap()
{
    if (stack.size() < 2)
    {
        Err("Error: operation: swap: less than two values in stack");
        return ;        
    }
    size_t x = stack.size() - 1;
    size_t y = stack.size() - 2;
    if (stack[x] == NULL || stack[y] == NULL)
    {
        Err("Error: operation: swap: unstack NULL operand pointer");
        return ;
    }
    const IOperand *p1 = stack[stack.size() - 1];
    const IOperand *p2 = stack[stack.size() - 2];
    stack.pop_back();
    stack.pop_back();
    this->stack.push_back(p1);
    this->stack.push_back(p2);
}