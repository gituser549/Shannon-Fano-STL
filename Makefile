CXX = g++
CXXFLAGS = -std=c++14 -O2 \
           -ICoderSrc -ICommandsSrc -IDeCoderSrc \
           -IErrorsAndConstants -IExceptionsSrc -ISymbolSrc -IMain

SRCS = $(wildcard */*.cpp)
OBJS = $(SRCS:.cpp=.o)

program: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(OBJS) program

.PHONY: clean
