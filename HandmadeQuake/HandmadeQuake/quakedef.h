#pragma once

#include <iostream>
#include <cstdint>

typedef uint8_t uint8;
typedef uint32_t uint32;
typedef int32_t int32;

#define SAFE_DELETE(a) if( (a) != nullptr ) delete (a); (a) = nullptr;

#define SAFE_DELETE_ARRAY(a) if( (a) != nullptr ) delete[] (a); (a) = nullptr;