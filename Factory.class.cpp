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
    try
    {
        int val = std::stoi(value);
        if (val > CHAR_MAX)
        {
            Err("Error: int8: overflow");
        }
        else if (val < CHAR_MIN)
        {
            Err("Error: int8: underflow");
        }
    }
    catch (std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
        exit(0);
    } 
    return (new Number<char>(Int8, value));
}

IOperand const *Factory::createInt16(std::string const &value) const
{   
    try
    {
        int val = std::stoi(value);

        if (val > INT16_MAX)
        {
            Err("Error: int16: overflow");
        }
        if (val < INT16_MIN)
        {
            Err("Error: int16: underflow");
        }
    }
    catch (std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
        exit(0);
    } 
    return (new Number<short>(Int16, value));
}

IOperand const *Factory::createInt32(std::string const &value) const
{
    try
    {
        int val = std::stoi(value);

        std::string check = std::to_string(val);
    }
    catch (std::exception &e)
    {
        std::cout << "Line #" << line << ": " << "Error: int32: overflow or underflow" << std::endl;
        exit(0);
    }
    return (new Number<int>(Int32, value));
}

IOperand const *Factory::createFloat(std::string const &value) const
{
    std::stringstream deb(std::stringstream::out);
    std::string str;

    try
    {
        long double f = std::stold(value);
        if (f > FLT_MAX)
        {
            Err("Error: float: overflow");
        }
        else if (f < -FLT_MAX)
        {
            Err("Error: float: underflow");      
        }
    }
    catch (std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
        exit(0);
    }  
    deb << std::setprecision(7) << std::stof(value);
    str = deb.str();
    return (new Number<float>(Float, str));
}

IOperand const *Factory::createDouble(std::string const &value) const
{
    std::stringstream deb(std::stringstream::out);
    std::string str;

    try
    {
        long double ld = std::stold(value);
        if (ld >= 9223372036854775807)
        {
            Err("Error: double: overflow");
        }
        else if (ld < -9223372036854775807)
        {
            Err("Error: double: underflow");
        }
    }
    catch (std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
        exit(0);
    }
    deb << std::setprecision(14) << std::stod(value);
    str = deb.str();
    return (new Number<double>(Double, str));
}
