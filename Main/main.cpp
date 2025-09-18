
#include <iostream>
#include <string>

#include "Commands.hpp"
#include "Constants.hpp"



int main() {

  std::cout << "Use " << COMMAND_SET_INPUT_FILE << " [input.txt] command to set input file"
            << "\n";
  std::cout << "Use " << COMMAND_SET_BINARY_FILE
            << " [binary.bin] command to set binary file" << "\n";
  std::cout << "Use " << COMMAND_SET_DECODE_FILE
            << " [output.txt] command to set file to decode binary file" << "\n";
  std::cout << "Use " << COMMAND_SET_RULES_FILE
            << " [rules.txt] command to set decoding rules file" << "\n";
  std::cout << "Use " << COMMAND_RUN_ARCHIVE
            << " command to start archivating" << "\n";
  std::cout << "Good luck!" << "\n\n";

  ParametersSet newParamSet;
  std::for_each(std::istream_iterator<std::string>(std::cin),
                std::istream_iterator<std::string>(),
                [&newParamSet](const std::string& curCommand) {
                  processCommand(std::cin, curCommand, newParamSet);
                });

  return EXIT_SUCCESS;
}
