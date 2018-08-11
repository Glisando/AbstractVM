# include "Number.class.hpp"

template <typename T> Number<T>::Number() {}
template <typename T> Number<T>::Number(eOperandType type, T num, std::string val) : _type(type), _num(num), _value(val) {}
template <typename T> Number<T>::Number(Number const &ref) { *this = ref; }
template <typename T> Number<T>::~Number() {}

template <typename T> Number<T> &Number<T>::operator=(Number const &ref) {

    this->_type = ref.getType();
    this->_value = ref.toString();
    return *this;
}

template <typename T> void Number<T>::setType(eOperandType type) {

    this->_type = type;
}

template <typename T> eOperandType Number<T>::getType(void) const {

    return (this->_type);
}

template <typename T> int Number<T>::getPrecision(void) const {


    return (0);
}

template <typename T> std::string const &Number<T>::toString(void) const {

    return (this->_value);
}

template <typename T> IOperand const *Number<T>::operator+(IOperand const &rhs) const {
    
    if (this->_type < Float && rhs.getType() < Float)
    {
        eOperandType tp = this->_type > rhs.getType() ?  this->_type : rhs.getType();
        
        long res = std::stol(this->_value) + std::stol(rhs.toString());
        const IOperand *nw = Factory().createOperand(tp, std::to_string(res));
        return (nw);
    }
    else
    {
        eOperandType tp = this->_type > rhs.getType() ?  this->_type : rhs.getType();

        long double res = std::stold(this->_value) + std::stold(rhs.toString());
        const IOperand *nw = Factory().createOperand(tp, std::to_string(res));
        return (nw);
    }
}

template <typename T> bool Number<T>::operator==(IOperand const &rhs) const {

    if (rhs.toString() == this->_value && rhs.getType() == this->_type)
    {
        std::cout << "truuuuuuue" << std::endl;           
        return (true);
    }
    else
    {
        std::cout << "faaaalse" << std::endl;   
        return (false);
    }
    return (false);
}

template class Number<char>;
template class Number<short>;
template class Number<int>;
template class Number<float>;
template class Number<double>;