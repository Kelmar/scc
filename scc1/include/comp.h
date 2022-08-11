#pragma once

#include <stddef.h>

#ifdef _MSC_VER
# define RET_NOTNULL _Ret_notnull_
# define DECL_NORET __declspec(noreturn) extern
# define DEPRECATED __declspec(deprecated)
#else
# define RET_NOTNULL
# define DECL_NORET
# define DEPRECATED
#endif

