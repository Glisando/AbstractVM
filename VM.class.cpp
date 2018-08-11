#include "VM.class.hpp"

VM::VM(void) {

    this->vmap["push"] = &VM::push;
    this->vmap["assert"] = &VM::assert;

    this->nmap["add"] = &VM::add;
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
        if (!(check_push_assert(input, type)))
            std::cout << "// check push assert commands ..." << std::endl;
        else if (!(check_other(input, type)))
            std::cout << "// check other commands ..." << std::endl;        
        // else {
        //     std::vector<const IOperand *>::iterator lol = this->stack.end();
        //     lol--;
        //     std::cout << (*lol)->toString() << std::endl;
        // }
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
            type = Int8;
        else if (result[2] == "int16")
            type = Int16;
        else if (result[2] == "int32")
            type = Int32;
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
            type = Float;
        else if (result[2] == "double")
            type = Double;
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

int VM::check_other(std::string const &input, eOperandType &type)
{
    std::cmatch result;
    std::regex  regular_decimal("^\\s*(\\bpop|dump|sub|add|mul|div|mod|print|exit\\b)\\s*(;\\w+)?");
    std::regex  regulear_float("^\\s*(\\bpop|dump|sub|add|mul|div|mod|print|exit\\b)\\s*(;\\w+)?");

    if (std::regex_match(input.c_str(), result, regular_decimal))
    {
        for (size_t i = 1; i < result.size(); i++)
        {
            std::cout << result[i] << std::endl;
        }
        if (this->nmap.find(result[1]) != this->nmap.end())
        {

            std::string value = result[3];
            (this->*nmap[result[1]])();
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
        if (this->nmap.find(result[1]) != this->nmap.end()) {

            std::string value = result[3];
            (this->*nmap[result[1]])();
        }
        else
            std::cout << "throw();" << std::endl;
    }
    else
        return (1);
    return (0);
}