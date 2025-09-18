
#ifndef DECODER_HPP
#define DECODER_HPP

#include <string>
#include <unordered_map>

#include "Constants.hpp"



struct RulesPair {
  std::string code_;
  char symb_;
};



class DeCoder {
private:
  std::string rulesFileName_;
  std::string binFileName_;
  std::string decodeFileName_;
  std::unordered_map<std::string, char> codeToLet_;
  int symbCounter_;

  void getRules();
  void decodeText();

public:
  DeCoder(const std::string& rulesFileName, const std::string& binFileName,
          const std::string& decodeFileName);
  DeCoder(const DeCoder&) = delete;
  DeCoder& operator=(const DeCoder&) = delete;
  DeCoder(DeCoder&&) = delete;
  DeCoder& operator=(DeCoder&&) = delete;
  void operator()();
};



bool checkIdentity(const std::string& firFileName,
                   const std::string& secFileName);

#endif
