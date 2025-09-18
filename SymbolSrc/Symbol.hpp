
#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include <string>



struct Symbol {
  unsigned char letter_;
  std::string code_;
  int amount_;
  Symbol();
  Symbol(unsigned char letter, int amount);
  Symbol(unsigned char letter, std::string code, int amount);
  Symbol(const Symbol& symbol);
  int getAmount() const;
  unsigned char getLetter() const;
  std::string getCode() const;
};



std::ostream& operator<<(std::ostream& rulesFileThread,
                         const Symbol& curSymbol);

#endif
