#ifndef CREATE_CLASS_HPP
# define CREATE_CLASS_HPP

# include "VM.class.hpp"
# include <sstream>

template <typename T>

class Number : public IOperand
{
  class IOperand;
  friend IOperand;

  private:
    eOperandType  _type;
    T             _num;

  public:
    Number(eOperandType type, T num) : _type(type), _num(num)
    {
    }
    Number(Number const &ref);
    ~Number() {

    }

    Number &operator=(Number const &ref) {

      this->_num = ref.getNum();
      this->_type = ref.getType();
      return *this;
    }

    void setType(eOperandType type) {

      this->_type = type;
    }

    eOperandType getType(void) const {

      return (this->_type);
    }

    int getPrecision(void) const {

      return (this->_type);
    }

    virtual std::string const &toString(void) const {

      std::stringstream deb;

      deb << this->_num; // for debugging;
      std::string const *str = new std::string(std::to_string(_num));
      std::string const &strRef = *str;
      return (strRef);
    }

    // IOperand const *operator+(IOperand const &rhs) const {
    //   return (Number(this->_num + rhs._num));
    // }
    
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