# include "Factory.class.hpp"

Factory::Factory() {

    create.push_back(&Factory::createInt8);
    create.push_back(&Factory::createInt16);
    create.push_back(&Factory::createInt32);
    create.push_back(&Factory::createFloat);
    create.push_back(&Factory::createDouble); 
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
    return ((*this.*create.at(type))(value));
}

IOperand const *Factory::createInt8(std::string const &value) const
{
    // put next string in block try!
    char val = static_cast<char>(std::stoi(value));
    std::string check = std::to_string(val);
    if (value != check)
        std::cout << "Type int8 - fucked up" << std::endl;
    return (new Number<char>(Int8, val, value));
}

IOperand const *Factory::createInt16(std::string const &value) const
{
    // put next string in block try!
    short val = static_cast<short>(std::stoi(value));
    std::string check = std::to_string(val);
    if (value != check)
        std::cout << "Type int16 - fucked up" << std::endl;
    return (new Number<short>(Int16, val, value));
}

IOperand const *Factory::createInt32(std::string const &value) const
{
    // put next string in block try!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    int val = std::stoi(value);
    std::string check = std::to_string(val);
    if (value != check)
        std::cout << "Type int32 - fucked up" << std::endl;
    return (new Number<int>(Int32, val, value));
}

IOperand const *Factory::createFloat(std::string const &value) const
{
    // put next string in block try!
    std::stringstream deb(std::stringstream::out);

    deb << std::setprecision(7) << std::stof(value);

    float f = std::stof(deb.str());
    std::string str = deb.str();
    return (new Number<float>(Float, f, str));
}

IOperand const *Factory::createDouble(std::string const &value) const
{
    // put next string in block try!
    std::stringstream deb(std::stringstream::out);

    deb << std::setprecision(14) << std::stod(value);

    double ld = std::stod(deb.str());
    std::string str = deb.str();    
    return (new Number<double>(Double, ld, str));
}