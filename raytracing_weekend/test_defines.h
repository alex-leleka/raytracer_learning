#pragma once

//#define TEST_RUN

#ifndef TEST_RUN
#define CONSTEXPR static constexpr

#define INITIALIZATION(A) A
#else
#define CONSTEXPR extern
#define INITIALIZATION(A)
#endif

