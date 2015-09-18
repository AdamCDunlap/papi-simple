CXXFLAGS += -std=c++11 -Wall -Wextra -pedantic -O3
LD_FLAGS = -lpapi

TARGETS = papi-simple-tests

all: $(TARGETS)

papi-simple-tests: papi-simple-tests.o papi-simple.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LD_FLAGS) $^ -o $@

papi-simple-tests.o: papi-simple-tests.cpp papi-simple.h

papi-simple.o: papi-simple.cpp papi-simple.h

clean: 
	rm -f $(TARGETS) *.o
