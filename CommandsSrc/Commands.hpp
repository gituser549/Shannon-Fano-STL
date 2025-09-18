
#ifndef COMMANDS_H
#define COMMANDS_H

#include <iostream>
#include <string>



struct ParametersSet {
  std::string srcFileName_;
  std::string binFileName_;
  std::string decodeFileName_;
  std::string rulesFileName_;
  ParametersSet();
  ParametersSet(const std::string& srcFileName, const std::string& binFileName,
                const std::string& decodeFileName,
                const std::string& rulesFileName);
  bool checkIfReady() const;
};



void processCommand(std::istream& inputThread, const std::string& curCommand,
                    ParametersSet& parametersSet);

#endif
