/*
*  Copyright (C) 2001 Kevin Harris
*
*  This program is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2 of the License, or
*  (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful, but
*  WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*  General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program; if not, write to the Free Software
*  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/
#if       !defined(KH_MY_DEFINES_H)
#define            KH_MY_DEFINES_H

// my_defines.h -- Some defines and classes which I have found useful in the
// past. This was taken from my own graphics project, and had non-relevant
// (less useful) items stripped out. 

#include <cstring>
#include <string>

/**
 * Traits for use in a case independent string...  When using in place
 * of a normal C++ string, you may need to convert it to a c_string
 * first (some things work automatically, some do not).  It was mostly
 * taken from the char traits of GCC-2.95.something, and modified to
 * work the way I needed.
 */
struct unicase_string_char_traits {
  typedef char char_type;
  
  static void assign (char_type& c1, const char_type& c2)
    { c1 = c2; }
  static bool eq (const char_type & c1, const char_type& c2)
    { return(strncasecmp(&c1,&c2,1) == 0); }
  static bool ne (const char_type& c1, const char_type& c2)
    { return(strncasecmp(&c1,&c2,1) != 0); }    
  static bool lt (const char_type& c1, const char_type& c2)
    { return(strncasecmp(&c1,&c2,1) < 0); }        
  static char_type eos () { return 0; }
  static bool is_del(char_type a) { return isspace(a); }

  static int compare (const char_type* s1, const char_type* s2, size_t n)
    { return strncasecmp(s1, s2, n); }
  static size_t length (const char_type* s)
    { return strlen (s); }
  static char_type* copy (char_type* s1, const char_type* s2, size_t n)
    { return (char_type*) memcpy (s1, s2, n); }
  static char_type* move (char_type* s1, const char_type* s2, size_t n)
    { return (char_type*) memmove (s1, s2, n); }
  static char_type* set (char_type* s1, const char_type& c, size_t n)
    { return (char_type*) memset (s1, c, n); }
};

/** Typedef for ease of 'unicase_string' use */
typedef std::basic_string<char,unicase_string_char_traits> unicase_string;
/** Typedef for ease of 'unicase_string' use (as ustring) */
typedef std::basic_string<char,unicase_string_char_traits> ustring;

#endif /* !defined(KH_MY_DEFINES_H) */
