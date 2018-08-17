#include "../inc/VM.class.hpp"

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
    this->nmap["max"] = &VM::max;
    this->nmap["min"] = &VM::min;
    this->nmap["rev"] = &VM::rev;
    this->nmap["more"] = &VM::more;
    this->nmap["less"] = &VM::less;
    this->nmap["exit"] = &VM::ex;
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
    line = 0;
    while (!std::cin.eof())
    {
        std::getline(std::cin, input);
        line++;
        try {

            if (esc == ";;" && input == ";;")
                ex();
            else if (!(check_push_assert(input, type)))
                continue ;
            else if (!(check_other(input)))
                continue ;
            else
                Err("invalid string");
        }
        catch (std::runtime_error &e)
        {
            std::cout << e.what() << std::endl;
        }
    }
    try
    {
        Err("Error: no exit command");
    }
    catch (std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
        ex();
    }
}

int VM::check_push_assert(std::string const &input, eOperandType &type)
{
    std::cmatch result;
    std::regex  regular_decimal("^\\s*(\\bpush|assert\\b)\\s+(int[8,16,32]{1,2}\\b)\\(([-]?\\d+)\\)\\s*(;.*)?");
    std::regex  regular_float("^\\s*(\\bpush|assert\\b)\\s+(float|double)\\(([-]?\\d+\\.\\d+)\\)\\s*(;.*)?");

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
            (this->*vmap[result[1]])(value, type);
        }
    }
    else
        return (1);
    return(0);
}

int VM::check_other(std::string const &input)
{
    std::cmatch result;
    std::regex  regular("^\\s*(\\bpop|dump|sub|add|mul|div|mod|print|exit|max|min|rev|more|less|exit\\b)\\s*(;.*)?");
    std::regex  regular_comment("^\\s*(;.*)?");
    std::regex  regular_exit("^\\s*exit\\s*(;.*)?");

    if (std::regex_match(input.c_str(), result, regular))
    {
        if (this->nmap.find(result[1]) != this->nmap.end())
            (this->*nmap[result[1]])();
    }
    else if (std::regex_match(input.c_str(), result, regular_comment))
        void(0);
    // else if (std::regex_match(input.c_str(), result, regular_exit))
    //     ex();
    else
         Err("Error: invalid string");
    return (0);
}