#pragma once

#ifdef _WIN32

#include "windows/winWindow.h"
typedef winWindow Window;

#else
#error JackdawEngine currently supports only Windows!
#endif