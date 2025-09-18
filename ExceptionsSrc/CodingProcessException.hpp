

#ifndef CODING_PROCESS_EXCEPTION_HPP
#define CODING_PROCESS_EXCEPTION_HPP

#include <string>



class CodingProcessException {
protected:
  std::string fileName_;

public:
  CodingProcessException(const std::string& fileName);
  virtual const std::string what() const = 0;
  virtual ~CodingProcessException() = default;
};



class FileNameLengthException : public CodingProcessException {
public:
  using CodingProcessException::CodingProcessException;
  const std::string what() const;
};



class FileLengthException : public CodingProcessException {
public:
  using CodingProcessException::CodingProcessException;
  const std::string what() const;
};



class FileExtensionException : public CodingProcessException {
public:
  using CodingProcessException::CodingProcessException;
  const std::string what() const;
};



class FileOpenningException : public CodingProcessException {
public:
  using CodingProcessException::CodingProcessException;
  const std::string what() const;
};



class ConsoleParametersException {
private:
  int amountConsoleParameters_;

public:
  ConsoleParametersException(int numConsoleParam);
  const std::string what() const;
};



class TextFileNameValidator {
private:
  std::string textFileName_;

public:
  TextFileNameValidator(const std::string& textFileName);
  void operator()() const;
};



class BinFileNameValidator {
private:
  std::string binFileName_;

public:
  BinFileNameValidator(const std::string& binFileName);
  void operator()() const;
};

#endif
