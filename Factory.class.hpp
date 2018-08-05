#ifndef FACTORY_CLASS_HPP
# define FACTORY_CLASS_HPP

# include "VM.class.hpp"

class Factory {

    public:
        Factory();
        Factory(Factory const &ref);
        ~Factory();

        Factory &operator=(Factory const &ref);

        IOperand const *createOperand(eOperandType type, std::string const &value) const;

      private:
        IOperand const *createInt8(std::string const &value) const;
        IOperand const *createInt16(std::string const &value) const;
        IOperand const *createInt32(std::string const &value) const;
        IOperand const *createFloat(std::string const &value) const;
        IOperand const *createDouble(std::string const &value) const;
};

#endif