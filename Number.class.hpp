#ifndef NUMBER_CLASS_HPP
# define NUMBER_CLASS_HPP

# include "VM.class.hpp"
# include "Factory.class.hpp"
# include <sstream>

template <typename T>

class Number : public IOperand
{

  class Factory;
  
  // class IOperand;
  // friend IOperand;

  private:
    eOperandType  _type;
    T             _num;
    std::string   _value;

  public:
    Number() {}  
    Number(eOperandType type, T num, std::string val) : _type(type), _num(num), _value(val) {}
    Number(Number const &ref);
    ~Number() {}

    Number &operator=(Number const &ref) {

      this->_num = ref.getNum();
      this->_type = ref.getType();
      this->_value = ref.toString();
      return *this;
    }

    void setType(eOperandType type) {

      this->_type = type;
    }

    eOperandType getType(void) const {

      return (this->_type);
    }

    int getPrecision(void) const {


      return (0);
    }

    virtual std::string const &toString(void) const {

      return (this->_value);
    }

    IOperand const *operator+(IOperand const &rhs) const {
      
      if (this->_type < Float && rhs.getType() < Float)
      {
        Factory *lol = new Factory();

        eOperandType tp = this->_type > rhs.getType() ?  this->_type : rhs.getType();

        long l1 = std::stol(this->_value); 
        long l2 = std::stol(rhs.toString());
        
        long res = l1 + l2;

        const IOperand *nw = lol->createOperand(tp, std::to_string(res));
        return (nw);
      }
      else
      {
        Factory *lol = new Factory();
        
        eOperandType tp = this->_type > rhs.getType() ?  this->_type : rhs.getType();

        long double ld1 = std::stold(this->_value);
        long double ld2 = std::stold(rhs.toString());

        long double res = ld1 + ld2;

        const IOperand *nw = lol->createOperand(tp, std::to_string(res));
        return (nw);
      }
    }
    
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