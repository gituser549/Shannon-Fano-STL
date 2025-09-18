
#include "Constants.hpp"



// The text file extension
const std::string TEXT_FILE_EXTENSION = ".txt";

// The binary file extension
const std::string BIN_FILE_EXTENSION = ".bin";

// The fullness factor of HashTable
const double HASH_TABLE_FULLNESS_FACTOR = 0.7;

// The number of console arguments needed
const int AMOUNT_EXPECTED_ARGS = 5;

// The length of extension in file name
const int LENGTH_OF_EXT_IN_FILENAME = 4;

// The command for setting input file
const std::string COMMAND_SET_INPUT_FILE = "SET_INPUT_FILE";

// The command for setting binary file
const std::string COMMAND_SET_BINARY_FILE = "SET_BINARY_FILE";

// The command for setting decode file
const std::string COMMAND_SET_DECODE_FILE = "SET_DECODE_FILE";

// The command for setting rules file
const std::string COMMAND_SET_RULES_FILE = "SET_RULES_FILE";

// The general parsing pattern for any set command
const std::regex COMMAND_ANY_SET_FILE = std::regex(
    "(" + COMMAND_SET_INPUT_FILE + ")|(" + COMMAND_SET_BINARY_FILE + ")|(" +
    COMMAND_SET_DECODE_FILE + ")|(" + COMMAND_SET_RULES_FILE + ")");

// The run archvation command
const std::string COMMAND_RUN_ARCHIVE = "RUN_ARCHIVE";
