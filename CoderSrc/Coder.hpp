
#ifndef CODER_HPP
#define CODER_HPP

#include <string>
#include <vector>

#include "Constants.hpp"
#include "Symbol.hpp"



class Coder {
private:
  std::string inputFileName_;
  std::string binFileName_;
  std::string rulesFileName_;
  std::vector<int> prefix_;
  std::vector<Symbol> letsByAmounts_;
  std::vector<std::string> letToCode_;
  int symbCounter_;

  int getLetsAndSort();
  void getPrefixes(const int& begin, const int& end);
  void getCodes(const int& begin, const int& end, const std::string& code = "");
  void codeText();
  void exportRules();

public:
  Coder(const std::string& inFileName, const std::string& binFileName,
        const std::string& rulesFileName);
  Coder(const Coder&) = delete;
  Coder& operator=(const Coder&) = delete;
  Coder(Coder&&) = delete;
  Coder& operator=(Coder&&) = delete;
  void operator()();
};



long long getFileSize(const std::string& fileName);

#endif
