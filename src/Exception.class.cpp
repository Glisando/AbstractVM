#include "../inc/Exception.class.hpp"
#include <exception>

Exception::Exception() : std::runtime_error("no error") {}

Exception::~Exception() throw() {}

Exception::Exception(Exception const &ref) : std::runtime_error("no error")
{
    *this = ref;
}

Exception::Exception(const std::string &err) : std::runtime_error(err)
{
    _err = "\033[31mLine #" + std::to_string(line) + ": " + err + "\033[0m";
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