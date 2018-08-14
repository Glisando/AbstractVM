#include "Exception.class.hpp"
# include <exception>

Exception::Exception() : std::runtime_error("no error") {}

Exception::~Exception() throw() {}

Exception::Exception(Exception const &ref) : std::runtime_error("no error")
{
    *this = ref;
}

Exception::Exception(const std::string &err) : std::runtime_error(err)
{
    _err = "Line #" + std::to_string(line) + ": " + err;
}

Exception &Exception::operator=(Exception const &ref)
{
    _err = ref._err;
    return *this;

}

const char *Exception::what() const throw()
{
    return _err.c_str();
}