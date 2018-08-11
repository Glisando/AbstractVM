#ifndef VM_CLASS_HPP
# define VM_CLASS_HPP

# include "IOperand.hpp"
# include "Number.class.hpp"
# include "Factory.class.hpp"

# include <map>
# include <vector>
# include <iostream>
# include <regex>
# include <fstream>

class VM
{

public:
  typedef void (VM::*Val)(std::string &, eOperandType &);
  typedef void (VM::*No_val)(void);

  std::string esc;
  
  std::map<std::string, Val> vmap;
  std::map<std::string, No_val> nmap;

  std::vector<const IOperand *> stack;

  VM();
  VM(VM const &ref);
  ~VM();

  VM &operator=(VM const &ref);

  void start(std::string const &file);
  int check_push_assert(std::string const &input, eOperandType &type);
  int check_other(std::string const &input, eOperandType &type);

  void push(std::string &value, eOperandType &type);
  void assert(std::string &value, eOperandType &type);

  void   pop(void);
  void   dump(void);
  void   add(void);
  void   sub(void);
  void   mul(void);
  void   div(void);
  void   mod(void);
  void   print(void);
  // void   exit(void);

};

#endif
