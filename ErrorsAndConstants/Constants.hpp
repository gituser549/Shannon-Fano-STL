
#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <regex>
#include <string>



// The size of alphabet
static const int ALPHABET_SIZE = 256;

// The amount of bits in one byte
static const int BITS_PER_BYTE = 8;

// The fullness factor of HashTable
extern const double HASH_TABLE_FULLNESS_FACTOR;

// The number of console arguments needed
extern const int AMOUNT_EXPECTED_ARGS;

// The length of extension in file name
extern const int LENGTH_OF_EXT_IN_FILENAME;

// The standard decoder table size
extern const int DECODER_TABLE_SIZE;

// The default size of HashTable
extern const int DEFAULT_TABLE_SIZE;

// The default amount of fnv offset basis for hash function FNV-1a
extern const unsigned long long FNV_OFFSET_BASIS;

// The default amount of fnv prime number for hash function FNV-1a
extern const unsigned long long FNV_PRIME;

// The text file extension
extern const std::string TEXT_FILE_EXTENSION;

// The binary file extension
extern const std::string BIN_FILE_EXTENSION;

// The command for setting input file
extern const std::string COMMAND_SET_INPUT_FILE;

// The command for setting binary file
extern const std::string COMMAND_SET_BINARY_FILE;

// The command for setting decode file
extern const std::string COMMAND_SET_DECODE_FILE;

// The command for setting rules file
extern const std::string COMMAND_SET_RULES_FILE;

// The general parsing pattern for any set command
extern const std::regex COMMAND_ANY_SET_FILE;

// The run archvation command
extern const std::string COMMAND_RUN_ARCHIVE;



#endif
