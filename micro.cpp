#include "napi.h"

#if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
    #define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
#else
    #define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
#endif

#if defined(_MSC_VER)
#include <windows.h>

int gettimeofday(struct timeval* tv, void* tz) {
    FILETIME ft;
    unsigned __int64 tmpres = 0;
    static int tzflag = 0;

    GetSystemTimeAsFileTime(&ft);

    tmpres |= ft.dwHighDateTime;
    tmpres <<= 32;
    tmpres |= ft.dwLowDateTime;

    tmpres /= 10;
    tmpres -= DELTA_EPOCH_IN_MICROSECS; 
    tv->tv_sec = (long)(tmpres / 1000000UL);
    tv->tv_usec = (long)(tmpres % 1000000UL);

    return 0;
}
#else
#include <sys/types.h>
#include <sys/time.h>
#endif

using namespace Napi;

/**
 *  Gettimeofday binding
 */
Value _gettimeofday(const CallbackInfo& info) {
    Env env = info.Env();
    timeval tv;

    int ret = gettimeofday(&tv, NULL);
    if (ret < 0) {
        Error::New(env, "Failed to get timeofday").ThrowAsJavaScriptException();
        return env.Null();
    }

    Object jsO = Object::New(env);
    jsO.Set("sec", Number::New(env, tv.tv_sec));
    jsO.Set("usec", Number::New(env, tv.tv_usec));

    return jsO;
}

/**
 *  Get Now as Microsecond
 */
Value now(const CallbackInfo& info) {
    Env env = info.Env();
    timeval tv;

    int ret = gettimeofday(&tv, NULL);
    if (ret < 0) {
        Error::New(env, "Failed to get timeofday").ThrowAsJavaScriptException();
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

// Export
NODE_API_MODULE(Micro, Init)
