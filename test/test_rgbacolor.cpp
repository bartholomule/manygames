#include <manygames/rgbacolor.hpp>
#include <iostream>
#include <cmath>
using namespace std;
#include "testinclude.hpp"

#define ERROR_TEXT(text) ((++error_count),text)
#define EPSILON 1e-9

template <class T, class T2>
ostream& operator<<(ostream& o, const manygames::rgbacolor<T,T2>& c)
{
  o << "<" << c.r() << ", " << c.g() << ", " << c.b() << ", " << c.a() << ">";
  return o;
}

bool fequals(double a, double b)
{
  if( fabs(a - b) < EPSILON )
  {
    return true;
  }
  return false;
}

int main(int,char**)
{
  int error_count = 0;
  const char* passed = "Passed";
  const char* failed = "FAILED!";

  typedef manygames::rgbacolor<int> color;

  color blah01;

  cout << "-------------------------------------" << endl;
  cout << "Testing rgbacolor member functions/ops" << endl;
  cout << "-------------------------------------" << endl;

  TEST_RESULT_NAMED("to see if get/set functions work",
                    ((blah01.set_r(1),(blah01.r() == 1)) && // single r
                     (blah01.set_g(2),(blah01.g() == 2)) && // single g
                     (blah01.set_b(3),(blah01.b() == 3)) && // single b
                     (blah01.set_a(0.5),(fequals(blah01.a(),0.5))) && // single a
                     (blah01.set(3,2,1,0.75),((blah01.r() == 3) && // multiple
                                              (blah01.g() == 2) &&
                                              (blah01.b() == 1) &&
                                              (fequals(blah01.a(),0.75))))
                    ),
                    passed,
                    ERROR_TEXT(failed));

  // Check both const/non-const [] operators
  TEST_RESULT_NAMED("to see if operator[] works",
                    (((blah01[0] = 1),(((const color)blah01)[0] == 1)) &&
                     ((blah01[1] = 2),(((const color)blah01)[1] == 2)) &&
                     ((blah01[2] = 3),(((const color)blah01)[2] == 3))
                    ),
                    passed,
                    ERROR_TEXT(failed));

  color blah02(blah01);
  TEST_RESULT_NAMED("to see if the copy constructor works",
                    ((blah02[0] == 1) && (blah02[1] == 2) && (blah02[2] == 3) && (fequals(blah02.a(),0.75))),
                    passed,
                    ERROR_TEXT(failed));

  color blah03; blah03 = blah01;
  TEST_RESULT_NAMED("to see if the assignment operator works",
                    ((blah03[0] == 1) && (blah03[1] == 2) && (blah03[2] == 3) && (fequals(blah03.a(),0.75))),
                    passed,
                    ERROR_TEXT(failed));

  //
  // NOTE: These tests rely on integer truncation (always rounding down).
  //
  color blah04 = blah01; blah04 *= 2;
  TEST_RESULT_NAMED("to see if operator *= (specific) works",
                    ((blah04[0] == 2) && (blah04[1] == 4) && (blah04[2] == 6) && fequals(blah04.a(),0.5)),
                    passed,
                    ERROR_TEXT(failed));

  color blah05 = blah01; blah05 *= 2.5;
  TEST_RESULT_NAMED("to see if operator *= (general) works",
                    ((blah05[0] == 2) && (blah05[1] == 5) && (blah05[2] == 7) && fequals(blah05.a(),0.375)),
                    passed,
                    ERROR_TEXT(failed));

  color blah06 = blah04; blah06 /= 2;
  TEST_RESULT_NAMED("to see if operator /= (specific) works",
                    ((blah06[0] == 1) && (blah06[1] == 2) && (blah06[2] == 3) && fequals(blah06.a(),0.75)),
                    passed,
                    ERROR_TEXT(failed));

  color blah07 = blah05; blah07 /= 2.5;
  TEST_RESULT_NAMED("to see if operator /= (general) works",
                    ((blah07[0] == 0) && (blah07[1] == 2) && (blah07[2] == 2) && fequals(blah07.a(), 0.75)),
                    passed,
                    ERROR_TEXT(failed));

  color blah08 = blah05; blah08 += blah04;
  TEST_RESULT_NAMED("to see if operator += works",
                    ((blah08[0] == 4) && (blah08[1] == 9) && (blah08[2] == 13) && fequals(blah08.a(), blah05.a() * blah04.a())),
                    passed,
                    ERROR_TEXT(failed));

  color blah09 = blah05; blah09 -= blah04;
  TEST_RESULT_NAMED("to see if operator -= works",
                    ((blah09[0] == 0) && (blah09[1] == 1) && (blah09[2] == 1) && fequals(blah09.a(),blah05.a() / blah04.a())),
                    passed,
                    ERROR_TEXT(failed));

  cout << "-------------------------------------" << endl;
  cout << "Testing rgbacolor global functions/ops" << endl;
  cout << "-------------------------------------" << endl;

  color blah10 = 2 * blah01;
  TEST_RESULT_NAMED("to see if global binary operator * (specific) works",
                    ((blah10[0] == 2) && (blah10[1] == 4) && (blah10[2] == 6) && fequals(blah10.a(), 1 - (1 - blah01.a()) * 2)),
                    passed,
                    ERROR_TEXT(failed));

  color blah11 = 2.5 * blah01;
  TEST_RESULT_NAMED("to see if global binary operator * (general) works",
                    ((blah11[0] == 2) && (blah11[1] == 5) && (blah11[2] == 7) && fequals(blah11.a(), 1 - (1 - blah01.a()) * 2.5)),
                    passed,
                    ERROR_TEXT(failed));

  color blah12 = blah10 + blah11;
  TEST_RESULT_NAMED("to see if global binary operator + works",
                    ((blah12[0] == 4) && (blah12[1] == 9) && (blah12[2] == 13) && fequals(blah12.a(),blah10.a()*blah11.a())),
                    passed,
                    ERROR_TEXT(failed));

  color blah13 = blah10 - blah11;
  TEST_RESULT_NAMED("to see if global binary operator - works",
                    ((blah13[0] == 0) && (blah13[1] == -1) && (blah13[2] == -1) && fequals(blah13.a(), std::max(std::min(blah10.a() / blah11.a(), 1.0), 0.0))),
                    passed,
                    ERROR_TEXT(failed));

  color blah14 = -blah12;
  TEST_RESULT_NAMED("to see if global unary operator - works",
                    ((blah14[0] == -4) && (blah14[1] == -9) && (blah14[2] == -13) && fequals(blah14.a(), 1 - blah12.a())),
                    passed,
                    ERROR_TEXT(failed));

  if( !error_count )
  {

    cout << "----------------------------------" << endl;
    cout << "*** All rgbacolor tests passed. ***" << endl;
    cout << "----------------------------------" << endl;
    return 0;
  }
  else
  {
    cout << "---------------------------------" << endl;
    cout << "ERROR: Failed " << error_count << " rgbacolor tests." << endl;
    cout << "---------------------------------" << endl;
    return(2);
  }

}

//(templated) class rgbacolor
