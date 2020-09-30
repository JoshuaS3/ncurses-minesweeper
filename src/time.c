#include <stdint.h>
#include <stdlib.h>

#if defined(__unix__) || defined(unix) || defined(__unix) || defined(__CYGWIN__)
#    include <sys/time.h>
uint64_t time_us(void) {
    uint64_t us;
    struct timeval lnm_current_time;
    gettimeofday(&lnm_current_time, NULL);
    us = (lnm_current_time.tv_sec * 1000000ULL + lnm_current_time.tv_usec);
    return us;
}
#elif defined(_WIN32) || defined(__WINDOWS__)
#    include <sysinfoapi.h>
#    include <windows.h>
uint64_t time_us(void) {
    uint64_t us;
    // get system time in ticks
    FILETIME lnm_win32_filetime;
    GetSystemTimeAsFileTime(&lnm_win32_filetime);
    // load time from two 32-bit words into one 64-bit integer
    us = lnm_win32_filetime.dwHighDateTime;
    us = us << 32;
    us |= lnm_win32_filetime.dwLowDateTime;
    // convert to microseconds
    us /= 10ULL; // is there a better way to do this?
    // convert from time since Windows NT epoch to time since Unix epoch
    us -= 11644473600000000ULL;
    return us;
}
#endif
