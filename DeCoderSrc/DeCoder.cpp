
#include <bitset>
#include <fstream>

#include "CodingProcessException.hpp"
#include "Constants.hpp"
#include "DeCoder.hpp"
#include "Errors.hpp"



std::istream& operator>>(std::istream& rulesFileThread, RulesPair& rulesPair) {
  int symb = rulesFileThread.get();
  if (symb != EOF) {
    // Return last symbol to thread because it is correct
    rulesFileThread.putback(symb);
    // Get code from thread
    rulesFileThread >> rulesPair.code_;
    // Ignore space - separator
    rulesFileThread.ignore();
    // Get coded symbol (byte)
    rulesPair.symb_ = rulesFileThread.get();
    // Ignore space ('\n' symbol)
    rulesFileThread.ignore();
  }
  return rulesFileThread;
}



DeCoder::DeCoder(const std::string& rulesFileName,
                 const std::string& binFileName,
                 const std::string& decodeFileName)
  : rulesFileName_(rulesFileName),
    binFileName_(binFileName),
    decodeFileName_(decodeFileName),
    symbCounter_(0) {
  TextFileNameValidator(std::move(rulesFileName_));
  BinFileNameValidator(std::move(binFileName_));
  TextFileNameValidator(std::move(decodeFileName_));
}



void DeCoder::getRules() {
  std::ifstream rulesFileThread(rulesFileName_);
  if (!rulesFileThread.is_open()) {
    throw FileOpenningException(rulesFileName_);
  }

  codeToLet_.clear();

  rulesFileThread >> symbCounter_;
  rulesFileThread.ignore();

  std::string code;

  std::vector<RulesPair> rulesPairs;
  std::copy(std::istream_iterator<RulesPair>(rulesFileThread),
            std::istream_iterator<RulesPair>(), std::back_inserter(rulesPairs));

  std::for_each(rulesPairs.cbegin(), rulesPairs.cend(),
                [this](const RulesPair& rulesPair) {
                  codeToLet_[rulesPair.code_] = rulesPair.symb_;
                });

  rulesFileThread.close();
}



void DeCoder::decodeText() {
  std::ifstream binFileThread(binFileName_, std::ios::in | std::ios::binary);
  if (!binFileThread.is_open()) {
    throw FileOpenningException(binFileName_);
  }
  std::ofstream decodeFileThread(decodeFileName_,
                                 std::ios::out | std::ios::trunc);
  if (!decodeFileThread.is_open()) {
    throw FileOpenningException(decodeFileName_);
  }

  std::string code = "";

  std::for_each(
      std::istreambuf_iterator<char>(binFileThread),
      std::istreambuf_iterator<char>(),
      [this, &decodeFileThread, &code](char signedByte) {
        unsigned char unsignedByte = static_cast<unsigned char>(signedByte);
        std::string strByte =
            std::bitset<BITS_PER_BYTE>(unsignedByte).to_string();
        std::for_each(strByte.cbegin(), strByte.cend(),
                      [&code, &decodeFileThread, this](const char& bit) {
                        code += bit;
                        if (codeToLet_.find(code) != codeToLet_.end() &&
                            symbCounter_ > 0) {
                          decodeFileThread.put(codeToLet_[code]);
                          // To refresh the current code chain assign empty string to code variable
                          code = "";
                          symbCounter_--;
                        }
                      });
      });
  binFileThread.close();
  decodeFileThread.close();
}



void DeCoder::operator()() {
  getRules();
  decodeText();
}



bool checkIdentity(const std::string& firFileName,
                   const std::string& secFileName) {
  TextFileNameValidator(std::move(firFileName));
  TextFileNameValidator(std::move(secFileName));

  std::ifstream firFileThread(firFileName, std::ios::in | std::ios::binary);
  std::ifstream secFileThread(secFileName, std::ios::in | std::ios::binary);

  if (!firFileThread.is_open() || !secFileThread.is_open()) {
    throw FileOpenningException(!firFileThread.is_open() ? firFileName
                                                         : secFileName);
  }

  return std::equal(std::istreambuf_iterator<char>(firFileThread),
                    std::istreambuf_iterator<char>(),
                    std::istreambuf_iterator<char>(secFileThread),
                    std::istreambuf_iterator<char>());
}
