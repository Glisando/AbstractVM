#include "VM.class.hpp"

void VM::push(std::string &value, eOperandType &type) {
    
    this->stack.push_back(Factory().createOperand(type, value));
}

void VM::assert(std::string &value, eOperandType &type)
{
    if (stack.size() < 1)
    {
        std::cout << "Error: operation: assert: less that one values in stack" << std::endl;
        return ;        
    }
    const IOperand *x = stack.back();;

    const IOperand *y = Factory().createOperand(type, value);

    if (x == NULL)
    {
        std::cout << "Error: operation: assert: unstack NULL operand pointer" << std::endl;
        return ;
    }

    if (*x == *y)
        std::cout << (*x).toString() << std::endl;
    else
        std::cout << "Error: operation: assert: An assert instruction is not true" << std::endl;

    delete y;
}

void VM::add(void)
{
    if (stack.size() < 2)
    {
        std::cout << "Error: operation: add: less that two values in stack" << std::endl;
        return ;        
    }

    const IOperand *p1 = this->stack.back();
    this->stack.pop_back();

    const IOperand *p2 = this->stack.back();
    this->stack.pop_back();

    if (p1 == NULL || p2 == NULL)
    {
        std::cout << "Error: operation: add: unstack NULL operand pointer" << std::endl;
        return ;
    }

    const IOperand *res = *p2 + *p1;
    this->stack.push_back(res);

    std::vector<const IOperand *>::iterator lol = this->stack.end();
    lol--;
    std::cout << (*lol)->toString() << std::endl;

    delete p1;
    delete p2;    
}

void VM::sub(void)
{
    if (stack.size() < 2)
    {
        std::cout << "Error: operation: sub: less that two values in stack" << std::endl;
        return ;
    }

    const IOperand *p1 = this->stack.back();
    this->stack.pop_back();

    const IOperand *p2 = this->stack.back();
    this->stack.pop_back();

    if (p1 == NULL || p2 == NULL)
    {
        std::cout << "Error: operation: sub: unstack NULL operand pointer" << std::endl;
        return ;
    }

    const IOperand *res = *p2 - *p1;
    this->stack.push_back(res);

    std::vector<const IOperand *>::iterator lol = this->stack.end();
    lol--;
    std::cout << (*lol)->toString() << std::endl;

    delete p1;
    delete p2;    
}

void VM::pop(void)
{
    if (stack.size() < 1)
    {
        std::cout << "Error: operation: pop: pop on an empty stack" << std::endl;
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
        std::cout << "Error: operation: dump: less that one values in stack" << std::endl;
        return ;
    }

    size_t i = stack.size() - 1;
    while (i != -1)
    {
        if (stack[i] == NULL)
        {
            std::cout << "Error: operation: dump: unstack NULL operand pointer" << std::endl;
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
        std::cout << "Error: operation: print: less that one values in stack" << std::endl;
        return ;
    }
    
    const IOperand *ptr = stack.back();


    if (ptr == NULL)
    {
        std::cout << "Error: operation: print: unstack NULL operand pointer" << std::endl;
        return ;
    }
    if (ptr->getType() != Int8)
    {
        std::cout << "Error: operation: print: bad number type" << std::endl;
        return ;
    }
    std::cout << static_cast<char>(std::stof(ptr->toString())) << std::endl;
}

void VM::mul(void)
{
    if (stack.size() < 2)
    {
        std::cout << "Error: operation: mul: less that two values in stack" << std::endl;
        return ;
    }

    const IOperand *p1 = this->stack.back();
    this->stack.pop_back();

    const IOperand *p2 = this->stack.back();
    this->stack.pop_back();

    if (p1 == NULL || p2 == NULL)
    {
        std::cout << "Error: operation: mul: unstack NULL operand pointer" << std::endl;
        return ;
    }
    const IOperand *res = *p2 * *p1;
    this->stack.push_back(res);

    std::vector<const IOperand *>::iterator lol = this->stack.end();
    lol--;
    std::cout << (*lol)->toString() << std::endl;

    delete p1;
    delete p2;  
}

void VM::div(void)
{
    if (stack.size() < 2)
    {
        std::cout << "Error: operation: div: less that two values in stack" << std::endl;
        return ;
    }

    const IOperand *p1 = this->stack.back();
    this->stack.pop_back();

    const IOperand *p2 = this->stack.back();
    this->stack.pop_back();

    if (p1 == NULL || p2 == NULL)
    {
        std::cout << "Error: operation: div: unstack NULL operand pointer" << std::endl;
        return ;
    }
    else if (p1->toString() == "0")
    {
        std::cout << "Error: operation: div: division by zero" << std::endl;
        return ;        
    }

    const IOperand *res = *p2 / *p1;
    this->stack.push_back(res);

    std::vector<const IOperand *>::iterator lol = this->stack.end();
    lol--;
    std::cout << (*lol)->toString() << std::endl;

    delete p1;
    delete p2;  
}

void VM::mod(void)
{
    if (stack.size() < 2)
    {
        std::cout << "Error: operation: mod: less that two values in stack" << std::endl;
        return ;
    }

    const IOperand *p1 = this->stack.back();
    this->stack.pop_back();

    const IOperand *p2 = this->stack.back();
    this->stack.pop_back();

    if (p1 == NULL || p2 == NULL)
    {
        std::cout << "Error: operation: mod: unstack NULL operand pointer" << std::endl;
        return ;
    }
    else if (p1->toString() == "0")
    {
        std::cout << "Error: operation: mod: modulo by zero" << std::endl;
        return ;
    }
    
    const IOperand *res = *p2 % *p1;
    this->stack.push_back(res);

    std::vector<const IOperand *>::iterator lol = this->stack.end();
    lol--;
    std::cout << (*lol)->toString() << std::endl;

    delete p1;
    delete p2;
}