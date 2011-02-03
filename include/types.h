/*
 *
 * Types and definitions used through-out the framework
 *
 * @author Adam Ever-Hadani <adamhadani@videosurf.com>
 *
 */
#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <string>

using std::string;
using std::wstring;

#ifndef _UNICODE
 typedef char flmchar_t;
 typedef std::string flmstring_t;

 #define flmstrlen strlen
 #define flmstrcpy strcpy
 #define flmstrcmp strcmp
#else
 typedef wchar flmchar_t;
 typedef std::wstring flmstring_t;

 #define flmstrlen w_strlen
 #define flmstrcpy w_strcpy
 #define flmstrcmp w_strcmp
#endif

// Function parameters decorators, optionally used to clarify
#define IN
#define OUT
#define INOUT

#endif // TYPES_H_INCLUDED
