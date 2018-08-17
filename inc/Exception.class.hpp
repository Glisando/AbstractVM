#ifndef EXCEPTION_CLASS_HPP
# define EXCEPTION_CLASS_HPP

#include "VM.class.hpp"

# include <exception>
# include <string>
# include <iostream>

# define Err(err) throw Exception(err);

extern int line;

class Exception : public std::runtime_error
{
    private:
        std::string _err;

    public:
        Exception();
        Exception(const std::string &err);
        Exception(Exception const &ref);
        ~Exception() throw();

        Exception &operator=(Exception const &ref);
        const char  *what() const throw();
};

#endif