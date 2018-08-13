#include "VM.class.hpp"

VM::VM(void) {

    this->vmap["push"] = &VM::push;
    this->vmap["assert"] = &VM::assert;

    this->nmap["add"] = &VM::add;
    this->nmap["sub"] = &VM::sub;
    this->nmap["pop"] = &VM::pop;
    this->nmap["dump"] = &VM::dump;
    this->nmap["print"] = &VM::print;
    this->nmap["mul"] = &VM::mul;
    this->nmap["div"] = &VM::div;
    this->nmap["mod"] = &VM::mod;
    
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
    {
        esc = "exit";
        std::cin.rdbuf(ifs.rdbuf());
    }
    else
        esc = ";;";

    while (!std::cin.eof())
    {
        std::getline(std::cin, input);
        try {
            if (input == esc)
                ex(input);
            else if (!(check_push_assert(input, type)))
                continue ;
            else if (!(check_other(input, type)))
                continue ;
            else
                Err("invalid string");
        }
        catch (std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }
    }
}

int VM::check_push_assert(std::string const &input, eOperandType &type)
{
    std::cmatch result;
    std::regex  regular_decimal("^\\s*(\\bpush|assert\\b)\\s+(int[8,16,32]{1,2}\\b)\\(([-]?\\d+)\\)\\s*(;\\w+)?");
    std::regex  regular_float("^\\s*(\\bpush|assert\\b)\\s+(float|double)\\(([-]?\\d+\\.\\d+)\\)\\s*(;\\w+)?");

    if (std::regex_match(input.c_str(), result, regular_decimal))
    {
        if (result[2] == "int8")
            type = Int8;
        else if (result[2] == "int16")
            type = Int16;
        else if (result[2] == "int32")
            type = Int32;
        if (this->vmap.find(result[1]) != this->vmap.end())
        {
            std::string value = result[3];
            // std::cout << "// " << result[1] << std::endl;         
            (this->*vmap[result[1]])(value, type);
        }      
    }
    else if (std::regex_match(input.c_str(), result, regular_float))
    {
        if (result[2] == "float")
            type = Float;
        else if (result[2] == "double")
            type = Double;
        if (this->vmap.find(result[1]) != this->vmap.end())
        {
            std::string value = result[3];
            // std::cout << "// " << result[1] << std::endl;
            (this->*vmap[result[1]])(value, type);
        }
    }
    else
        return (1);
    return(0);
}

int VM::check_other(std::string const &input, eOperandType &type)
{
    std::cmatch result;
    std::regex  regular("^\\s*(\\bpop|dump|sub|add|mul|div|mod|print|exit\\b)\\s*(;\\w+)?");

    if (std::regex_match(input.c_str(), result, regular))
    {
        if (this->nmap.find(result[1]) != this->nmap.end())
        {
            // std::cout << "// " << result[1] << std::endl;
            (this->*nmap[result[1]])();
        }
    }
    else
         Err("Error: invalid string");
    return (0);
}