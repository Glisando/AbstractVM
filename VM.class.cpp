#include "VM.class.hpp"

VM::VM() {

    vmap.emplace("push", &VM::push);
    vmap.emplace("assert", &VM::assert);

    //
}

VM::VM(VM const &ref){
    
    *this = ref;
}

VM &VM::operator=(VM const &ref) {

    (void)ref;
    return *this;
}

VM::~VM(){

}

void VM::start(std::string const &file) {
    
    std::string input;
    std::ifstream ifs(file);
    eOperandType type;

    if (ifs.good())
        std::cin.rdbuf(ifs.rdbuf());
    while (std::getline(std::cin, input))
    {
        if ((check_push_assert(input, type)))
            std::cout << "// check another commands ..." << std::endl;
        else {
            std::vector<const IOperand *>::iterator lol = this->stack.end();
            lol--;
            std::cout << (*lol)->toString() << std::endl;
        }
    }
}

int VM::check_push_assert(std::string const &input, eOperandType &type)
{
    std::cmatch result;
    std::regex  regular_decimal("^\\s*(\\bpush|assert\\b)\\s+(int[8,16,32]{1,2}\\b)\\(([-]?\\d+)\\)\\s*(;\\w+)?");
    std::regex  regulear_float("^\\s*(\\bpush|assert\\b)\\s+(float|double)\\(([-]?\\d+\\.\\d+)\\)\\s*(;\\w+)?");

    if (std::regex_match(input.c_str(), result, regular_decimal))
    {
        for (size_t i = 1; i < result.size(); i++)
        {
            std::cout << result[i] << std::endl;
        }
        if (result[2] == "int8")
            type = eOperandType::Int8;
        else if (result[2] == "int16")
            type = eOperandType::Int16;
        else if (result[2] == "int32")
            type = eOperandType::Int32;
        else {
            std::cout << "throw();" << std::endl;
            return (1);
        }
        if (this->vmap.find(result[1]) != this->vmap.end())
        {

            std::string value = result[3];
            (this->*vmap[result[1]])(value, type);
        }
        else
            std::cout << "throw();" << std::endl;        
    }
    else if (std::regex_match(input.c_str(), result, regulear_float))
    {
        for (size_t i = 1; i < result.size(); i++)
        {
            std::cout << result[i] << std::endl;
        }
        if (result[2] == "float")
            type = eOperandType::Float;
        else if (result[2] == "double")
            type = eOperandType::Double;
        if (this->vmap.find(result[1]) != this->vmap.end()) {

            std::string value = result[3];
            (this->*vmap[result[1]])(value, type);
        }
        else
            std::cout << "throw();" << std::endl;
    }
    else
        return (1);
    return(0);
}