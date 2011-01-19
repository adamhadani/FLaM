#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <string>

using std::string;

// Function parameters decorators
#define IN
#define OUT
#define INOUT

typedef char flmchar_t;
typedef std::string flmstring_t;


#define flmstrlen strlen
#define flmstrcpy strcpy

#endif // TYPES_H_INCLUDED
