
#include <fstream>

#include "Symbol.hpp"



Symbol::Symbol() : letter_('\0'), code_(""), amount_(0) {};



Symbol::Symbol(unsigned char letter, int amount)
  : letter_(letter), code_(""), amount_(amount) {};



Symbol::Symbol(unsigned char letter, std::string code, int amount)
  : letter_(letter), code_(code), amount_(amount) {};



Symbol::Symbol(const Symbol& symbol)
  : letter_(symbol.letter_), code_(symbol.code_), amount_(symbol.amount_) {};



std::ostream& operator<<(std::ostream& rulesFileThread,
                         const Symbol& curSymbol) {
  rulesFileThread << curSymbol.code_ << " " << curSymbol.letter_ << "\n";
  return rulesFileThread;
}



int Symbol::getAmount() const {
  return amount_;
}



unsigned char Symbol::getLetter() const {
  return letter_;
}



std::string Symbol::getCode() const {
  return code_;
}
