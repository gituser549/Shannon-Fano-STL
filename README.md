# Shannon-Fano-STL

This repository contains my realization of Shannon-Fano coding algorithms. 
Project was made with the using of STL, lambda functions, functors and special data-structures.

This is project is a console application which make full-cycle (coding and decoding) text files. Works with .txt and .bin formats. 

**You can build this project using this command:** `make CXXFLAGS="-std=c++14 -O3 -march=native -flto -DNDEBUG"`

# Basic commands to interact with the programs are:

To start program use just `./program_file` when you are in the same directory as program file.

**SET_INPUT_FILE [input.txt]** - command to set the file to encode. The extension of file must be .txt;

**SET_BINARY_FILE [binary.bin]** - command to set the file to put coded text. The extension of file must be .bin;

**SET_DECODE_FILE [output.txt]** - command to set the file to put the result of decoding .bin file with coded text. The extension of file must be .txt;

**SET_RULES_FILE [rules.txt]** - command to set the file to store decoding rules file. The extension of file must be .txt;

**RUN_ARCHIVE** - command to start archivating.

You will see such results as **efficiency of coding** and **result of equality input and output files check** after execution of the program.



