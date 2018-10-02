#include "napi.h"
#include <limits>

#if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
    #define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
#else
    #define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
#endif

#if defined(_MSC_VER)
#include <windows.h>

/**
 * gettimeofday implementation for WINDOWS !
 * 
 * @doc: https://docs.microsoft.com/en-us/windows/desktop/SysInfo/converting-a-time-t-value-to-a-file-time
 * @doc: http://mathieuturcotte.ca/textes/windows-gettimeofday/
 */
int gettimeofday(struct timeval* tv, void* tz) {
    ULARGE_INTEGER ul; // As specified on MSDN.
    FILETIME ft;

    // Returns a 64-bit value representing the number of
    // 100-nanosecond intervals since January 1, 1601 (UTC).
    GetSystemTimeAsFileTime(&ft);

    // Fill ULARGE_INTEGER low and high parts.
    ul.LowPart  = ft.dwLowDateTime;
    ul.HighPart = ft.dwHighDateTime;

    // Convert to microseconds.
    ul.QuadPart /= 10ULL;

    // Remove Windows to UNIX Epoch delta.
    ul.QuadPart -= DELTA_EPOCH_IN_MICROSECS;

    // Modulo to retrieve the microseconds.
    tv->tv_usec = (long) (ul.QuadPart % 1000000LL);

    // Divide to retrieve the seconds.
    tv->tv_sec = (long) (ul.QuadPart / 1000000LL);

    return 0;
}
#else
#include <sys/types.h>
#include <sys/time.h>
#endif

using namespace Napi;
using namespace std;

/**
 * gettimeofday binding (prefixed with underscore here to avoid overloading)
 * 
 * @doc: http://man7.org/linux/man-pages/man2/gettimeofday.2.html
 */
Value _gettimeofday(const CallbackInfo& info) {
    Env env = info.Env();
    timeval tv;

    if (gettimeofday(&tv, NULL) < 0) {
        Error::New(env, "gettimeofday returned -1").ThrowAsJavaScriptException();
        return env.Null();
    }

    // Return timeval struct as a JavaScript Object!
    Object ret = Object::New(env);
    ret.Set("sec", Number::New(env, tv.tv_sec));
    ret.Set("usec", Number::New(env, tv.tv_usec));

    return ret;
}

/**
 *  Convert gettimeofday to microsecond timestamp
 */
Value now(const CallbackInfo& info) {
    Env env = info.Env();
    timeval tv;

    if (gettimeofday(&tv, NULL) < 0) {
        Error::New(env, "gettimeofday returned -1").ThrowAsJavaScriptException();
        return env.Null();
    }

    return Number::New(env, (tv.tv_sec * 1000000.0) + tv.tv_usec);
}

/*
 * Initialize Node.JS Binding exports
 * 
 * @header: napi.h
 */
Object Init(Env env, Object exports) {
    exports.Set("gettimeofday", Function::New(env, _gettimeofday));
    exports.Set("now", Function::New(env, now));

    return exports;
}

// Export Micro module
NODE_API_MODULE(Micro, Init)
