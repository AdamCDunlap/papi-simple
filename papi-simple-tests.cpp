#include "papi-simple.h"

// c junk
#include <cmath>
#include <vector>
#include <random>
#include <iostream>

#include <cassert>

// Reduce the amount of typing we have to do for timing things.
using std::size_t;
using std::cout;
using std::endl;

int main() {

    for (size_t i=0; i<10; ++i) {
        PAPI papi({PAPI_FDV_INS});
  
        // Create a c++11 random number generator
        std::mt19937 randomNumberEngine;
        std::uniform_real_distribution<double> randomNumberGenerator(0, 1);
  
  
        // We'll record how many floating point divides are used to generate a
        //  bunch of random numbers, because why not?
        const size_t numberOfRandomNumbers = 100000000;
        double randomNumberSum = 0;

        papi.start_counting();
        for (size_t i = 0; i < numberOfRandomNumbers; ++i) {
            const double randomNumberBetween0And1 =
                randomNumberGenerator(randomNumberEngine);
            randomNumberSum += randomNumberBetween0And1;
        }
        const size_t numberOfDivisions = papi.stop_counting()[0];
  
        //volatile size_t sumcopy = randomNumberSum;
  
        cout << "sum: " << randomNumberSum
             << ", divisions: "<< numberOfDivisions << endl;
        assert(numberOfDivisions > 99000000 && numberOfDivisions < 110000000);
    }
  
    return 0;
}
