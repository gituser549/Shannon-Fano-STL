
#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <string>



// The error when program can't open the file
extern const std::string ERROR_CANT_OPEN_FILE;

// The error when filename length is incorrect
extern const std::string ERROR_FILENAME_LENGTH;

// The error when length of file is incorrect
extern const std::string ERROR_FILE_LENGTH;

// The error when given file has incorrect extension
extern const std::string ERROR_FILE_EXT;

// The error when too much console parameters were given
extern const std::string ERROR_TOO_MUCH_CONS_PARAM;

// The error when too few console parameters were given
extern const std::string ERROR_TOO_FEW_CONS_PARAM;

// The error when programmer destroyed program logic
extern const std::string ERROR_INCORRECT_USAGE_CONS_PARAM_EXC;

// The error when user entered a wrong command
extern const std::string ERROR_INCORRECT_COMMAND;

// The error when it is too early to start coding - decoding process
extern const std::string ERROR_NOT_ENOUGH_PARAMETERS;

#endif
