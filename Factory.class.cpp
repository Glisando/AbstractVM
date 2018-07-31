# include "Factory.class.hpp"

Factory::Factory() {

}

Factory::Factory(Factory const &ref) {
    
    *this = ref;
}

Factory::~Factory(){

}

Factory &Factory::operator=(Factory const &ref) {

    (void)ref;
    return *this;
}

IOperand const *Factory::createOperand(eOperandType type, std::string const &value) const
{
    typedef IOperand const *(Factory::*Create)(std::string const &) const;
    Create crt[4] = {&Factory::createInt8, &Factory::createInt16, &Factory::createInt32, &Factory::createFloat};
    return ((this->*crt[type])(value));
}

IOperand const *Factory::createInt8(std::string const &value) const
{
    // put next string in block try!
    char val = static_cast<char>(std::stoi(value));
    std::string check = std::to_string(val);
    if (value != check)
        std::cout << "Type int8 - fucked up" << std::endl;
    return (new Number<char>(Int8, val));
}

IOperand const *Factory::createInt16(std::string const &value) const
{
    // put next string in block try!
    short val = static_cast<short>(std::stoi(value));
    std::string check = std::to_string(val);
    if (value != check)
        std::cout << "Type int16 - fucked up" << std::endl;
    return (new Number<short>(Int8, val));
}

IOperand const *Factory::createInt32(std::string const &value) const
{
    // put next string in block try!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    int val = std::stoi(value);
    return (new Number<int>(Int8, val));
}

IOperand const *Factory::createFloat(std::string const &value) const
{
    // put next string in block try!
    std::strstream deb;

    deb << std::setprecision(7) << std::stold(value);

    long double ld = std::stold(deb.str());
    return (new Number<float>(Float, ld));
}