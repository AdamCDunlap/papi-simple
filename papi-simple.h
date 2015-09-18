#include <papiStdEventDefs.h>
#include <vector>
#include <cstddef>

class PAPI
{

    size_t num_events;
    int eventSet;

    void
    handlePapiError(const int papiReturnVal);

public:

    PAPI();

    void startCounting(std::vector<int> events);

    std::vector<long long int> getEvents();
};
