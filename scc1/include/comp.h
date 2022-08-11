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

// Use inline to avoid double processing of increment/decrement should that be used.

inline int MIN_i(int X, int N) { return X < N ? X : N; }
inline int MAX_i(int X, int N) { return X > N ? X : N; }

inline size_t MIN_z(size_t X, size_t N) { return X < N ? X : N; }
inline size_t MAX_z(size_t X, size_t N) { return X > N ? X : N; }

#define MIN(X_, N_) _Generic((X_), int: MIN_i, size_t: MIN_z)(X_, N_)
#define MAX(X_, N_) _Generic((X_), int: MAX_i, size_t: MAX_z)(X_, N_)

