#pragma once

#include <stddef.h>

#ifdef _MSC_VER
# define RET_NOTNULL _Ret_notnull_
# define DECL_NORET __declspec(noreturn) extern
#else
# define RET_NOTNULL
# define DECL_NORET
#endif

