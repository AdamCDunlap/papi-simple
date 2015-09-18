#include <papiStdEventDefs.h>
#include <vector>
#include <cstddef>

class PAPI
{

    int event_set;
    std::vector<long long int> counts_buf;
    std::vector<long long int> dummy_buf;

    void handle_papi_error(const int papiReturnVal);

public:

    PAPI(std::vector<int> events);
    ~PAPI();

    void start_counting();

    std::vector<long long int> stop_counting();
};
