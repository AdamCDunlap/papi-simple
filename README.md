# papi-simple

This is a simplified C++ interface to PAPI. How to use:

    #inclue "papi-simple.h"
    PAPI papi( {PAPI_FDV_INS, /*Other events*/} ); // Create the PAPI object
    papi.start_counting();
    // Do stuff involving floating point instructions...
    std::vector<long long int> results = papi.stop_counting();
    long long int num_divides = results[0];
    // You can also just do num_divides = papi.stop_counting()[0];
    // You can call start and stop again as much as you want
