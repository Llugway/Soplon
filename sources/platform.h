#pragma once

#ifdef _WIN32
    #include <windows.h>     // Sleep, GetCurrentProcessId, etc.
    #include <io.h>           // _access, _close, etc.
    #include <direct.h>       // _getcwd, _chdir
    #include <process.h>      // _getpid (mais voir ci-dessous)
    #include <stdlib.h>       // rand/srand

    #define sleep(seconds)     Sleep((seconds) * 1000)   
    #define usleep(microseconds) Sleep((microseconds) / 1000)

    #define getpid()           GetCurrentProcessId()
    #define getcwd(buf, size)  _getcwd(buf, size)
    #define chdir(path)        _chdir(path)
    #define access(path, mode) _access(path, mode)

    #define srandom(seed)      srand(seed)
    #define random()           rand()

#else
    #include <unistd.h>
#endif