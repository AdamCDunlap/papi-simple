#include "papi-simple.h"
#include <papi.h>
#include <cstdlib>
#include <iostream>

void
PAPI::handlePapiError(const int papiReturnVal) {
    if (papiReturnVal != PAPI_OK) {
        std::cerr << "PAPI error:" << std::endl << PAPI_strerror(papiReturnVal);
        exit(1);
    }
}

PAPI::PAPI() :
    eventSet(PAPI_NULL)
{
    // Initialize the papi library
    PAPI_library_init(PAPI_VER_CURRENT);
}

void
PAPI::startCounting(std::vector<int> events) {
    handlePapiError(PAPI_create_eventset(&eventSet));
    for (int e : events)
    {
        handlePapiError(PAPI_add_event(eventSet, e));
    }
    // Tell papi to start, after which we can do timing
    handlePapiError(PAPI_start(eventSet));
}

std::vector<long long int>
PAPI::getEvents() {
    std::vector<long long int> ret(num_events);

    handlePapiError(PAPI_accum(eventSet, ret.data()));

    handlePapiError(PAPI_stop(eventSet, 0));
    handlePapiError(PAPI_cleanup_eventset(eventSet));
    handlePapiError(PAPI_destroy_eventset(&eventSet));

    return ret;
}
