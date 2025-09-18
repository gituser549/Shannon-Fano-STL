
#include <algorithm>
#include <fstream>
#include <functional>
#include <numeric>

#include "Coder.hpp"
#include "CodingProcessException.hpp"
#include "Constants.hpp"
#include "Errors.hpp"



using namespace std::placeholders;

Coder::Coder(const std::string& inFileName, const std::string& binFileName,
             const std::string& rulesFileName)
  : inputFileName_(inFileName),
    binFileName_(binFileName),
    rulesFileName_(rulesFileName),
    prefix_(ALPHABET_SIZE),
    letsByAmounts_(ALPHABET_SIZE),
    letToCode_(ALPHABET_SIZE),
    symbCounter_(0) {
  TextFileNameValidator(std::move(inputFileName_));
  BinFileNameValidator(std::move(binFileName_));
  TextFileNameValidator(std::move(rulesFileName_));
}


int Coder::getLetsAndSort() {
  std::ifstream inputFileThread(inputFileName_);

  if (!inputFileThread.is_open()) {
    throw FileOpenningException(inputFileName_);
  }

  int numEls = 0;

  int i = 0;
  std::for_each(letsByAmounts_.begin(), letsByAmounts_.end(),
                [&i](Symbol& curSymbol) {
                  curSymbol = Symbol(i, 0);
                  i++;
                });

  std::for_each(std::istreambuf_iterator<char>(inputFileThread),
                std::istreambuf_iterator<char>(),
                [this, &numEls](char curSymb) {
                  unsigned char curSymbUC = static_cast<unsigned char>(curSymb);
                  if (letsByAmounts_[curSymbUC].amount_ == 0) {
                    numEls++;
                  }
                  letsByAmounts_[curSymbUC].amount_++;
                });

  inputFileThread.close();

  std::stable_sort(letsByAmounts_.begin(), letsByAmounts_.end(),
                   std::bind(std::greater<int>(),
                             std::bind(&Symbol::getAmount, _1),
                             std::bind(&Symbol::getAmount, _2)));

  return numEls;
}



void Coder::getPrefixes(const int& begin, const int& end) {

  std::fill(prefix_.begin() + begin, prefix_.begin() + end + 1, 0);


  prefix_[begin] = letsByAmounts_[begin].amount_;

  std::transform(
      prefix_.begin() + begin, prefix_.begin() + end,
      letsByAmounts_.cbegin() + begin + 1, prefix_.begin() + begin + 1,
      std::bind(std::plus<int>(), _1, std::bind(&Symbol::getAmount, _2)));
}



void Coder::getCodes(const int& begin, const int& end,
                     const std::string& code) {
  if (end > begin) {
    getPrefixes(begin, end);
    int endOfPrefix = prefix_[end];
    auto iteratorMin = std::min_element(
        prefix_.begin() + begin, prefix_.begin() + end,
        [&endOfPrefix](const int firstPrefix, const int secondPrefix) {
          return std::abs(endOfPrefix - 2 * firstPrefix) <
              std::abs(endOfPrefix - 2 * secondPrefix);
        });

    int bestPos = static_cast<int>(std::distance(prefix_.begin(), iteratorMin));

    getCodes(begin, bestPos, code + "0");
    getCodes(bestPos + 1, end, code + "1");
  } else if (begin == end) {
    letsByAmounts_[begin].code_ = (code.length()) ? code : "1";
  }
}



void Coder::codeText() {
  int size = getLetsAndSort();

  if (size == 0) {
    throw FileLengthException(inputFileName_);
  }

  getCodes(0, size - 1);

  std::for_each(letToCode_.begin(), letToCode_.end(),
                [](std::string& curCode) { curCode = ""; });

  symbCounter_ = 0;
  std::for_each(letsByAmounts_.cbegin(), letsByAmounts_.cbegin() + size,
                [this](const Symbol& curSymb) {
                  letToCode_[curSymb.letter_] = curSymb.code_;
                  symbCounter_ += curSymb.amount_;
                });

  std::ifstream inputFileThread(inputFileName_);
  if (!inputFileThread.is_open()) {
    throw FileOpenningException(inputFileName_);
  }

  std::ofstream binFileThread(
      binFileName_, std::ios::out | std::ios::binary | std::ios::trunc);
  if (!binFileThread.is_open()) {
    throw FileOpenningException(binFileName_);
  }

  unsigned char byte = 0;
  int bitCount = 0;

  std::for_each(
      std::istreambuf_iterator<char>(inputFileThread),
      std::istreambuf_iterator<char>(),
      [this, &binFileThread, &byte, &bitCount](const char symb) {
        const std::string& code = letToCode_[static_cast<unsigned char>(symb)];
        std::for_each(code.cbegin(), code.cend(),
                      [&binFileThread, &byte, &bitCount](const char bitChar) {
                        // We move current byte left by one bit
                        byte <<= 1;
                        if (bitChar == '1') {
                          // We compare the lowest (nearly appeared after previous action) with 1 (00000001) and get next bit in code
                          byte |= 1;
                        }
                        bitCount++;
                        // If full byte was collected, write it to binary file
                        if (bitCount == BITS_PER_BYTE) {
                          binFileThread.write(
                              reinterpret_cast<const char*>(&byte), 1);
                          // Refresh byte and bit counter variables to get the next byte
                          byte = 0;
                          bitCount = 0;
                        }
                      });
      });

  // If we have non-written bits, we need to write them to file in correct form
  if (bitCount > 0) {
    // We move current byte (with bitCount real bits) left by some bits to get correct byte
    byte <<= (BITS_PER_BYTE - bitCount);
    binFileThread.write(reinterpret_cast<const char*>(&byte), 1);
  }

  inputFileThread.close();
  binFileThread.close();
}



void Coder::exportRules() {
  std::ofstream rulesFileThread(rulesFileName_,
                                std::ios::out | std::ios::trunc);
  if (!rulesFileThread.is_open()) {
    throw FileOpenningException(rulesFileName_);
  }

  rulesFileThread << symbCounter_ << "\n";

  std::copy_if(
      letsByAmounts_.begin(), letsByAmounts_.end(),
      std::ostream_iterator<Symbol>(rulesFileThread),
      std::bind(std::greater<int>(), std::bind(&Symbol::getAmount, _1), 0));
}



void Coder::operator()() {
  codeText();
  exportRules();
}



long long getFileSize(const std::string& fileName) {
  if (fileName.length() <= LENGTH_OF_EXT_IN_FILENAME) {
    throw FileNameLengthException(fileName);
  }

  std::ifstream fileThreadToCheck(fileName, std::ios::binary | std::ios::ate);

  if (!fileThreadToCheck.is_open()) {
    throw FileOpenningException(fileName);
  }

  long long result = static_cast<long long>(fileThreadToCheck.tellg());
  fileThreadToCheck.close();
  return result;
}
