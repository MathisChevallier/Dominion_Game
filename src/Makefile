CXX=g++
CXXFLAGS=-std=c++11 -Wall -Wextra -Werror

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -c -o $@

PartieClass: PartieClass.o main.o
	$(CXX) $^ -o $@

.PHONY: run clean

run: PartieClass
	./$<

clean:
	rm -f *.o *~ *.core 