/*
 * $Id$
 *
 * Part of "Many Games" - A nearly infinitely expandable gaming framework
 * Copyright (C) 2003 Kevin Harris
 *
 * This program is free software; you can redistribute it and/or modify 
 * it under the terms of the GNU General Public License as published by 
 * the Free Software Foundation; either version 2 of the License, or    
 * (at your option) any later version.                                  
 *                                                                      
 * This program is distributed in the hope that it will be useful, but  
 * WITHOUT ANY WARRANTY; without even the implied warranty of           
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU    
 * General Public License for more details.                             
 *                                                                      
 * You should have received a copy of the GNU General Public License    
 * along with this program; if not, write to the Free Software          
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
 */

#if       !defined(__MANYGAMES__RGBACOLOR_HPP__)
#define            __MANYGAMES__RGBACOLOR_HPP__

namespace manygames
{ 

  /**
   * 
   * A generic class to represent RGBA colors (RGB with Alpha).  Note that only
   * built-in (or native) types (char, float, etc), are usable in this class.
   * The design of this class was chosen so that array accesses ([]) and direct
   * accesses (.N()) would be almost the same speed.  Also, this class *may* be
   * able to be used in an array and reinterpreted as an array of the base
   * type. 
   *
   * For example:
   *<pre>
   *@@ rgbacolor<unsigned char> foo[100];
   *@@ unsigned char* foo_reinterpreted = reinterpret_cast<char*>(foo);
   *@@ ...
   *</pre>
   *
   * The opposite should also be possible.  In either case, BE CAREFUL to make
   * sure that the correct type of destructor would be called (especially with
   * memory allocated by 'new').
   *
   * Whatver changes or additions are made in the future, NO virtual functions
   * should be added, as they would likely break the ability to reinterpret the
   * class as an array of three ints.
   *
   * @author Kevin Harris <kpharris@users.sourceforge.net>
   * @version $Revision$
   * 
   */
  template <class T, class T2=double>
  class rgbacolor
  {

  protected:
    /** A struct of three items directly accessible. */
    struct rgbacolor_direct
    {
      T r; ///< Red   component of RGBA color
      T g; ///< Green component of RGBA color
      T b; ///< Blue  component of RGBA color
    };
    /** A struct of three items array accessible. */    
    struct rgbacolor_array
    {
      T components[4]; ///< Components of RGBA in an 'array'
    };
    /**
     * A union to allow accesses to both indirectly through an array, and
     * directly athrough a name, without adding any extra processing time or
     * space requirements
     */        
    union rgbacolor_union
    {
      rgbacolor_union() { }
      /** A constructor, to simplify things. */
      rgbacolor_union(T r, T g, T b)
      {
	direct.r = r;
	direct.g = g;
	direct.b = b;
      }
      /** Operator for simplification of access. */
      T& operator[](unsigned index)       { return array.components[index]; }
      /** Operator for simplification of access. */
      T  operator[](unsigned index) const { return array.components[index]; }

      rgbacolor_direct direct; ///< The directly accessible part
      rgbacolor_array  array;  ///< The array accessible part
    };

    /** The actual RGB data */
    rgbacolor_union rgb;

    /** The alpha */
    T2 alpha;

  public:
    /** Default constructor (does nothing) */
    rgbacolor() { }
    
    /** Secondary constructor (initializes) */
    rgbacolor(T r, T g, T b, T2 a):rgb(r,g,b), alpha(a) { }

    /** Destructor -- NON VIRTUAL! (does nothing) */
    ~rgbacolor() { }

    /** Copy constructor */
    rgbacolor(const rgbacolor& old);

    /** Assignment operator */
    rgbacolor& operator= (const rgbacolor& old);

    inline void set_r(T r)  { rgba.direct.r = r; } ///< Set the red component
    inline void set_g(T g)  { rgba.direct.g = g; } ///< Set the green component
    inline void set_b(T b)  { rgba.direct.b = b; } ///< Set the blue component
    inline void set_a(T2 a) { alpha = a; }         ///< Set the alpha component
    inline T r() const { return rgba.direct.r; } ///< Get the red component
    inline T g() const { return rgba.direct.g; } ///< Get the green component
    inline T b() const { return rgba.direct.b; } ///< Get the blue component
    inline T a() const { return alpha; }         ///< Get the alpha component
    
    /** Get the element specified.  No bounds checking is performed */
    inline T& operator[](unsigned index)       { return rgba[index]; }    
    /** Get the element specified.  No bounds checking is performed */
    inline T  operator[](unsigned index) const { return rgba[index]; }

    /** Set the components to the given values */
    void set(T r, T g, T b, T2 a);

    rgbacolor& operator *=(T factor);          ///< Multiply by factor
    rgbacolor& operator /=(T factor);          ///< Divide by factor
    template <class U>
    rgbacolor& operator *=(U factor);          ///< Multiply by factor (general)
    template <class U>    
    rgbacolor& operator /=(U factor);          ///< Divide by factor (general)
    rgbacolor& operator +=(const rgbacolor& r); ///< Add the given to these
    rgbacolor& operator -=(const rgbacolor& r); ///< Sub the given from these
    
  }; // class rgbacolor

  /** Copy constructor */
  template <class T, class T2>
  rgbacolor<T,T2>::rgbacolor(const rgbacolor& old):
    rgb(old.r(), old.g(), old.b()),
    alpha(old.a())
  {
  } // rgbacolor::rgbacolor(rgbacolor)

  /** Assignment operator */
  template <class T, class T2>
  rgbacolor<T,T2>& rgbacolor<T,T2>::operator=(const rgbacolor& old)
  {
    // The generic check for self-assignment has been removed, as it has
    // already been specified that the type given MUST be a native type.  Thus,
    // it should be really fast to do the assignment, and the branch could be
    // very slow.
    rgba.direct.r = old.rgba.direct.r;
    rgba.direct.g = old.rgba.direct.g;
    rgba.direct.b = old.rgba.direct.b;
    alpha = old.alpha;    
    return (*this);    
  } // rgbacolor::operator=(rgbacolor)

  /** Sets the data... */
  template <class T, class T2>
  void rgbacolor<T,T2>::set(T r, T g, T b, T2 a)
  {
    rgba.direct.r = r;
    rgba.direct.g = g;
    rgba.direct.b = b;
    alpha = a;    
  } // rgbacolor::set(r,g,b,a)

  /** Multiplication by a factor/assign (specific) */
  template <class T, class T2>
  rgbacolor<T,T2>& rgbacolor<T,T2>::operator *=(T factor)
  {
    rgba.direct.r *= factor;
    rgba.direct.g *= factor;
    rgba.direct.b *= factor;
    alpha *= factor;    
    return *this;
  } // rgbacolor::operator*=(T)

  /** Division by a factor/assign (specific) */
  template <class T, class T2>
  rgbacolor<T,T2>& rgbacolor<T,T2>::operator /=(T factor)
  {
    rgba.direct.r /= factor;
    rgba.direct.g /= factor;
    rgba.direct.b /= factor;
    alpha /= factor;    
    return *this;
  } // rgbacolor::operator/=(T)
  
  /** Multiplication by a factor/assign (general) */
  template <class T, class T2>
  template <class U>
  rgbacolor<T,T2>& rgbacolor<T,T2>::operator *=(U factor)
  {
    rgba.direct.r = T(rgba.direct.r * factor);
    rgba.direct.g = T(rgba.direct.g * factor);
    rgba.direct.b = T(rgba.direct.b * factor);
    alpha = T2(alpha * factor);    
    return *this;
  } // rgbacolor::operator*=(U)

  /** Division by a factor/assign (general) */  
  template <class T, class T2>
  template <class U>
  rgbacolor<T,T2>& rgbacolor<T,T2>::operator /=(U factor)
  {
    rgba.direct.r = T(rgba.direct.r / factor);
    rgba.direct.g = T(rgba.direct.g / factor);
    rgba.direct.b = T(rgba.direct.b / factor);
    alpha = T2(alpha / factor);    
    return *this;    
  } // rgbacolor::operator/=(U)

  /** addition/assign */
  template <class T, class T2>
  rgbacolor<T,T2>& rgbacolor<T,T2>::operator +=(const rgbacolor<T,T2>& r)
  {
    rgba.direct.r += r.rgba.direct.r;
    rgba.direct.g += r.rgba.direct.g;
    rgba.direct.b += r.rgba.direct.b;
    alpha += r.alpha;    
    return *this;
  } // rgbacolor::operator+=(rgbacolor)

  /** subtraction/assign */
  template <class T, class T2>
  rgbacolor<T,T2>& rgbacolor<T,T2>::operator -=(const rgbacolor<T,T2>& r)
  {
    rgba.direct.r -= r.rgba.direct.r;
    rgba.direct.g -= r.rgba.direct.g;
    rgba.direct.b -= r.rgba.direct.b;
    alpha -= r.alpha;
    return *this;
  } // rgbacolor::operator-=(rgbacolor)


  /** Multiplication of an rgba color by a factor (non-member) */
  template <class T, class T2>
  rgbacolor<T,T2> operator*(T factor, const rgbacolor<T,T2>& r)
  {
    rgbacolor<T,T2> retval(r);
    retval *= factor;
    return retval;
  } // operator*(T,rgbacolor)
  
  /** Multiplication of an rgba color by a factor (non-member, general) */
  template <class T, class U>
  rgbacolor<T,T2> operator*(U factor, const rgbacolor<T,T2>& r)
  {
    rgbacolor<T,T2> retval(r);
    retval *= factor;
    return retval;
  } // operator*(U,rgbacolor)

  /** Addition of two rgba colors. */
  template <class T, class T2>
  rgbacolor<T,T2> operator+(const rgbacolor<T,T2>& c1, const rgbacolor<T,T2>& c2)
  {
    rgbacolor<T,T2> retval(c1);
    retval += c2;
    return retval;
  } // operator+(rgbacolor,rgbacolor)
  
  /** Subtraction of two rgba colors. */
  template <class T, class T2>
  rgbacolor<T,T2> operator-(const rgbacolor<T,T2>& c1, const rgbacolor<T,T2>& c2)
  {
    rgbacolor<T,T2> retval(c1);
    retval -= c2;
    return retval;
  } // operator-(rgbacolor,rgbacolor)

  /** Unary negation of an rgba color. */
  template <class T, class T2>
  rgbacolor<T,T2> operator-(const rgbacolor<T,T2>& c)
  {
    // [FIXME] Question... What effect does this have on the alpha?
    return rgbacolor<T,T2>(-c.r(),-c.g(),-c.b(),-c.a());
  } // operator-(rgbacolor,rgbacolor)  
  
  
} // namespace manygames


#endif /* !defined(__MANYGAMES__RGBACOLOR_HPP__) */
