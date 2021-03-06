#if       !defined(KH_USEFUL_FUNCTIONS_H)
#define            KH_USEFUL_FUNCTIONS_H
// ----------------------------------------------------------------------------
// useful_functions.h -- Kevin Harris (kpharris@users.sourceforge.net)
// Some functions which I have not been able to locate in the C++ standard
// library, and would find very useful to have.
//
// NOTE: These are declared as static, but are very small, so they won't make
// much difference to your code.
//
// Another note: The use of this header file will likely result in the compiler
// emitting warnings about one or both of these functions not being used.  This
// should be expected, and isn't much to worry about.  The only way that
// including this could have much effect on you, is if it is included in quite
// a few separately gcompiled modules (100 or more), where your executable size
// will have grown by a bit (these are REALLY small functions).
// ----------------------------------------------------------------------------
// This file is really small, and I'm not really writing much, so I'm not going
// to bother with a license.
// ----------------------------------------------------------------------------
// Revision History:
// 29Nov1999 Created this file.
// 30Nov1999 Wrote these comments
// ----------------------------------------------------------------------------

#include <string>
#include <stdio.h>

// The following is used to eliminate the unused static function warning
// generated by gcc.
#if       defined(__GNUC__) || defined(__GNUG__)
#define KH_UNUSED_WARNING_ELIMINATOR __attribute__ ((unused))
#else
#define KH_UNUSED_WARNING_ELIMINATOR
#endif // defined(__GNUC__) || defined(__GNUG__)


/**
 * Convert the given integer to a string.  This is done very simply using
 * sprintf. 
 * @param i The integer to convert to a string representation.
 * @author Kevin Harris
 */
static std::string KH_UNUSED_WARNING_ELIMINATOR int_to_str(int i)
{
  char buffer[64];
  sprintf(buffer, "%d", i);
  return(std::string(buffer));
}
/**
 * Convert the given float to a string.  This is done very simply using
 * sprintf.
 * @param d The double to convert to a string representation.
 * @author Kevin Harris
 */
static std::string KH_UNUSED_WARNING_ELIMINATOR float_to_str(double d)
{
  char buffer[64];
  sprintf(buffer, "%f", d);
  return(std::string(buffer));  
}

#undef KH_UNUSED_WARNING_ELIMINATOR

#endif // !defined(KH_USEFUL_FUNCTIONS_H)
