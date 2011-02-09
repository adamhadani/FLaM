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

#define flmwid_t uint32_t
#define flmcount_t uint32_t

// Compact ngram representation used by framework
struct flmngram_t {
  unsigned short n;
  flmwid_t  *id_array;
  flmcount_t count;
};

// Function parameters decorators, optionally used to clarify
#define IN
#define OUT
#define INOUT

#ifdef __WITH_GCC
# define _tname_
#else
# define _tname_ typename
#endif

#endif // TYPES_H_INCLUDED
