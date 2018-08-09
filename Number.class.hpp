#ifndef NUMBER_CLASS_HPP
# define NUMBER_CLASS_HPP

# include "VM.class.hpp"
# include "Factory.class.hpp"

template <typename T>

class Number : public IOperand
{

  class Factory;

  private:
    eOperandType  _type;
    T             _num;
    std::string   _value;

  public:
    Number();
    Number(eOperandType type, T num, std::string val);
    Number(Number const &ref);
    ~Number();

    Number &operator=(Number const &ref);

    void setType(eOperandType type);

    eOperandType getType(void) const;

    int getPrecision(void) const;

    virtual std::string const &toString(void) const;

    IOperand const *operator+(IOperand const &rhs) const;
    
    // IOperand const *operator-(IOperand const &rhs) const {
    //   return (Number(this->_num - rhs._num));
    // }
    
    // IOperand const *operator*(IOperand const &rhs) const {
    //   return (Number(this->_num * rhs._num));
    // }
    
    // IOperand const *operator/(IOperand const &rhs) const {
    //   return (Number(this->_num / rhs._num));
    // }
    
    // IOperand const *operator%(IOperand const &rhs) const {
    //   return (Number(this->_num % rhs._num));
    // }
};

#endif