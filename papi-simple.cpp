#include "papi-simple.h"
#include <papi.h>
#include <cstdlib>
#include <iostream>

void
PAPI::handle_papi_error(const int papi_return_val) {
    if (papi_return_val != PAPI_OK) {
        std::cerr << "PAPI error:" << std::endl << PAPI_strerror(papi_return_val);
        exit(1);
    }
}

PAPI::PAPI(std::vector<int> events) :
    event_set{PAPI_NULL},
    counts_buf(events.size()),
    dummy_buf(events.size())
{
    // Initialize the papi library
    PAPI_library_init(PAPI_VER_CURRENT);
    handle_papi_error(PAPI_create_eventset(&event_set));
    for (int e : events)
    {
        handle_papi_error(PAPI_add_event(event_set, e));
    }
    // Tell papi to start, after which we can do timing
    handle_papi_error(PAPI_start(event_set));
}

void
PAPI::start_counting() {
    std::fill(counts_buf.begin(), counts_buf.end(), 0);
    handle_papi_error(PAPI_accum(event_set, dummy_buf.data()));
}

std::vector<long long int>
PAPI::stop_counting() {
    handle_papi_error(PAPI_accum(event_set, counts_buf.data()));

    return counts_buf;
}


PAPI::~PAPI() {
    handle_papi_error(PAPI_stop(event_set, 0));
    handle_papi_error(PAPI_cleanup_eventset(event_set));
    handle_papi_error(PAPI_destroy_eventset(&event_set));
}
