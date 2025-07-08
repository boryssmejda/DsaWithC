#include "dsa/common/error_codes.h"

const char* dsa_strerror(const dsa_error_code_t code)
{
    switch (code)
    {
        case DSA_SUCCESS:
            return "Success";
        case DSA_INVALID_INPUT:
            return "Invalid input";
        case DSA_ALLOC_FAILURE:
            return "Allocation failure";
        case DSA_EMPTY_LIST:
            return "Empty List";
        default:
            return "Unknown error";
    }
}
