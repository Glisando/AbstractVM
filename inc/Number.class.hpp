#ifndef NUMBER_CLASS_HPP
# define NUMBER_CLASS_HPP

# include "IOperand.hpp"
# include "Factory.class.hpp"

# include <vector>
# include <iostream>
# include <cmath>

template <typename T>

class Number : public IOperand
{

  private:
    eOperandType  _type;
    std::string   _value;

  public:
    Number();
    Number(eOperandType type, std::string val);
    Number(Number const &ref);
    ~Number();

    Number &operator=(Number const &ref);

    void setType(eOperandType type);
    eOperandType getType(void) const;
    int getPrecision(void) const;
    virtual std::string const &toString(void) const;

    bool operator==(IOperand const &rhs) const;
    bool operator>=(IOperand const &rhs) const;
    bool operator<=(IOperand const &rhs) const;
    IOperand const *operator+(IOperand const &rhs) const;    
    IOperand const *operator-(IOperand const &rhs) const;    
    IOperand const *operator*(IOperand const &rhs) const;
    IOperand const *operator/(IOperand const &rhs) const;
    IOperand const *operator%(IOperand const &rhs) const;
};

#endif