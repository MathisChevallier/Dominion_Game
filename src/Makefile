CXX=g++
CXXFLAGS=-std=c++11 -Wall -Wextra -Werror

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -c -o $@

MakeCompilation: PartieClass.o main.o
	$(CXX) $^ -o $@

.PHONY: run clean

run: MakeCompilation
	./$<

clean:
	rm -f *.o *~ *.core 