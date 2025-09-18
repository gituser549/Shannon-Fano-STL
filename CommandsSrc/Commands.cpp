
#include <regex>

#include "Coder.hpp"
#include "CodingProcessException.hpp"
#include "Commands.hpp"
#include "Constants.hpp"
#include "DeCoder.hpp"
#include "Errors.hpp"



ParametersSet::ParametersSet()
  : srcFileName_(""),
    binFileName_(""),
    decodeFileName_(""),
    rulesFileName_("") {};



ParametersSet::ParametersSet(const std::string& srcFileName,
                             const std::string& binFileName,
                             const std::string& decodeFileName,
                             const std::string& rulesFileName)
  : srcFileName_(srcFileName),
    binFileName_(binFileName),
    decodeFileName_(decodeFileName),
    rulesFileName_(rulesFileName) {};



bool ParametersSet::checkIfReady() const {
  return !(srcFileName_.empty() || binFileName_.empty() ||
           decodeFileName_.empty() || rulesFileName_.empty());
}



void processCommand(std::istream& inputThread, const std::string& curCommand,
                    ParametersSet& parametersSet) {
  std::string curParams;
  try {
    if (std::regex_match(curCommand, COMMAND_ANY_SET_FILE)) {
      inputThread >> curParams;
      if (curCommand == COMMAND_SET_INPUT_FILE) {
        parametersSet.srcFileName_ = curParams;
      } else if (curCommand == COMMAND_SET_BINARY_FILE) {
        parametersSet.binFileName_ = curParams;
      } else if (curCommand == COMMAND_SET_DECODE_FILE) {
        parametersSet.decodeFileName_ = curParams;
      } else if (curCommand == COMMAND_SET_RULES_FILE) {
        parametersSet.rulesFileName_ = curParams;
      }
    } else if (curCommand == COMMAND_RUN_ARCHIVE) {
      if (parametersSet.checkIfReady()) {

        std::string srcFileName = parametersSet.srcFileName_;
        std::string binFileName = parametersSet.binFileName_;
        std::string decodeFileName = parametersSet.decodeFileName_;
        std::string rulesFileName = parametersSet.rulesFileName_;

        Coder testCoder(srcFileName, binFileName, rulesFileName);
        testCoder();

        DeCoder testDeCoder(rulesFileName, binFileName, decodeFileName);
        testDeCoder();

        long long srcFileSize = getFileSize(srcFileName);
        long long binFileSize = getFileSize(binFileName);
        long long rulesFileSize = getFileSize(rulesFileName);

        std::cout << "Efficiency without rules file: "
                  << 1 - static_cast<double>(binFileSize) / srcFileSize << "\n";
        std::cout << "Efficiency with rules file: "
                  << 1 -
                static_cast<double>(binFileSize + rulesFileSize) / srcFileSize
                  << "\n";
        std::cout << "Influence of rules file: "
                  << static_cast<double>(rulesFileSize) / srcFileSize << "\n";
        std::cout << "Are source and decoded files equal: " << std::boolalpha
                  << checkIdentity(srcFileName, decodeFileName) << "\n";
      } else {
        throw std::logic_error(ERROR_NOT_ENOUGH_PARAMETERS);
      }
    } else {
      std::getline(inputThread, curParams);
      throw std::runtime_error(ERROR_INCORRECT_COMMAND);
    }
  } catch (const ConsoleParametersException& error) {
    std::cout << error.what() << "\n";
  } catch (const CodingProcessException& error) {
    std::cout << error.what() << "\n";
  } catch (const std::exception& error) {
    std::cout << error.what() << "\n";
  }
}
