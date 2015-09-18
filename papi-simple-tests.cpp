// -*- C++ -*-
// Main0.cc
// cs181j hw1 example
// A simple file to illustrate how to use PAPI to measure things
// Jeff Amelang, 2015

// c junk
#include <cstdio>
#include <cstdlib>
#include <cmath>

// c++ junk
#include <array>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

// All the magic for measuring cache misses is in papi
#include "papi-simple.h"

// Reduce the amount of typing we have to do for timing things.
using std::chrono::high_resolution_clock;
using std::chrono::duration;
using std::chrono::duration_cast;

int main() {
  PAPI papi;

  // Create a c++11 random number generator
  std::mt19937 randomNumberEngine;
  std::uniform_real_distribution<double> randomNumberGenerator(0, 1);

  // Start timing
  const high_resolution_clock::time_point tic =
    high_resolution_clock::now();
  papi.startCounting( {PAPI_FDV_INS} );


  // We'll record how many floating point divides are used to generate a
  //  bunch of random numbers, because why not?
  const size_t numberOfRandomNumbers = 1e8;
  double randomNumberSum = 0;
  for (size_t i = 0; i < numberOfRandomNumbers; ++i) {
    const double randomNumberBetween0And1 =
      randomNumberGenerator(randomNumberEngine);
    randomNumberSum += randomNumberBetween0And1;
  }

  // Stop timing
  const high_resolution_clock::time_point toc =
    high_resolution_clock::now();
  const size_t numberOfDivisions = papi.getEvents()[0];
  const double elapsedTime =
    duration_cast<duration<double> >(toc - tic).count();

  printf("randomNumberSum was %11.4e, which is %%%5.1f of the number of random "
         "numbers (%8.2e)\n", randomNumberSum,
         100. * randomNumberSum / float(numberOfRandomNumbers),
         float(numberOfRandomNumbers));
  printf("in %5.2lf seconds, measured %zu (%8.2e) divisions used in the "
         "generation of the %zu (%8.2e) random numbers\n", elapsedTime,
         numberOfDivisions, float(numberOfDivisions),
         numberOfRandomNumbers, float(numberOfRandomNumbers));

  return 0;
}
