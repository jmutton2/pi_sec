#include "Password.h"

int CHECK_PASS(std::string st)
{
    static std::string pass = st; // first time you call this function, set pass

    if (pass.compare(st) == 0)
    {
        return 1;
    }
    else
        return 0;
    // Compare mem->useless_information with mem2->uselessInformation
    // If equal >> RESET_ALARM(mem)
}