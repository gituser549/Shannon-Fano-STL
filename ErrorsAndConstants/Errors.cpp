
#include "Errors.hpp"



// The error when program can't open the file
const std::string ERROR_CANT_OPEN_FILE = "ERROR: can't open : ";

// The error when filename length is incorrect
const std::string ERROR_FILENAME_LENGTH =
    "ERROR: inccorect filename because of its length given : ";

// The error when length of file is incorrect
const std::string ERROR_FILE_LENGTH = "ERROR: you've given an empty file : ";

// The error when given file has incorrect extension
const std::string ERROR_FILE_EXT = "ERROR: error with extension : ";

// The error when too much console parameters were given
const std::string ERROR_TOO_MUCH_CONS_PARAM =
    "ERROR: you've given too much console params, their amount must be 4";

// The error when too few console parameters were given
const std::string ERROR_TOO_FEW_CONS_PARAM =
    "ERROR: you've given too few console params, their amount must be 4";

// The error when programmer destroyed program logic
const std::string ERROR_INCORRECT_USAGE_CONS_PARAM_EXC =
    "ERROR: you've destroyed program logic";

// The error when user entered a wrong command
const std::string ERROR_INCORRECT_COMMAND =
    "ERROR: you've enteread an incorrect command";

// The error when it is too early to start coding - decoding process
const std::string ERROR_NOT_ENOUGH_PARAMETERS =
    "ERROR: you haven't entered enough parameters to start coding - decoding "
    "process";
