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

#include <manygames/rgbcolor.hpp>
#include <manygames/template_functions.hpp>

namespace manygames
{ 

  /**
   * 
   * A generic class to represent RGBA colors (RGB with Alpha).  Note that only
   * built-in (or native) types (char, float, etc), are usable in this class.
   * Note that this differs from the rgbcolor class in that reinterpretation
   * probably is NOT going to work.
   *
   *
   * Since I had not previously defined any ground work here, as to what an
   * RGBA color is, I'm going to do it now (30Oct2003).
   *
   * The alpha component is of type T2, which is assumed to be a floating point
   * value, although it could be of some other type, such as fixed point, or
   * other.  In any case, it will now be assumed that an alpha value can range
   * from 0 (completely opaque), to 1 (completely transparent).
   *
   * I am going to define things such that alpha values, when added,
   * subtracted, multiplied, or otherwise, will always remain positive, and
   * between 0 and 1.  If an alpha color is added to another, then the
   * transparency is multiplied.  If they are subtracted, then the transparency
   * is divided (to undo an addition).  If an alpha color is multiplied by a
   * constant, then its OPACITY is multiplied, not its transparency.
   * Conversly, if it is divided by a constant, it's opacity is divided.
   *
   * Make sure to note that the opacity is 1 - alpha.
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
    struct rgbcolor_direct
    {
      T r; ///< Red   component of RGBA color
      T g; ///< Green component of RGBA color
      T b; ///< Blue  component of RGBA color
    };
    /** A struct of three items array accessible. */    
    struct rgbcolor_array
    {
      T components[3]; ///< Components of RGB in an 'array'
    };
    /**
     * A union to allow accesses to both indirectly through an array, and
     * directly athrough a name, without adding any extra processing time or
     * space requirements
     */        
    union rgbcolor_union
    {
      rgbcolor_union() { }
      /** A constructor, to simplify things. */
      rgbcolor_union(T r, T g, T b)
      {
        direct.r = r;
        direct.g = g;
        direct.b = b;
      }
      /** Operator for simplification of access. */
      T& operator[](unsigned index)       { return array.components[index]; }
      /** Operator for simplification of access. */
      T  operator[](unsigned index) const { return array.components[index]; }

      rgbcolor_direct direct; ///< The directly accessible part
      rgbcolor_array  array;  ///< The array accessible part
    };

    /** The actual RGB data */
    rgbcolor_union rgb;

    /** The alpha.  Note that this is NOT included in the above union, as
        the alpha may need to be a different type, and it would mess up the
        ability to use the [] operators. */
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

    inline void set_r(T r)  { rgb.direct.r = r; } ///< Set the red component
    inline void set_g(T g)  { rgb.direct.g = g; } ///< Set the green component
    inline void set_b(T b)  { rgb.direct.b = b; } ///< Set the blue component
    inline void set_a(T2 a) { alpha = a; }        ///< Set the alpha component
    inline T r() const { return rgb.direct.r; }   ///< Get the red component
    inline T g() const { return rgb.direct.g; }   ///< Get the green component
    inline T b() const { return rgb.direct.b; }   ///< Get the blue component
    inline T2 a() const { return alpha; }         ///< Get the alpha component
    
    /** Get the element specified.  No bounds checking is performed */
    inline T& operator[](unsigned index)       { return rgb[index]; }    
    /** Get the element specified.  No bounds checking is performed */
    inline T  operator[](unsigned index) const { return rgb[index]; }

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
    rgb.direct.r = old.rgb.direct.r;
    rgb.direct.g = old.rgb.direct.g;
    rgb.direct.b = old.rgb.direct.b;
    alpha = old.alpha;    
    return (*this);    
  } // rgbacolor::operator=(rgbacolor)

  /** Sets the data... */
  template <class T, class T2>
  void rgbacolor<T,T2>::set(T r, T g, T b, T2 a)
  {
    rgb.direct.r = r;
    rgb.direct.g = g;
    rgb.direct.b = b;
    alpha = a;    
  } // rgbacolor::set(r,g,b,a)

  /** Multiplication by a factor/assign (specific) */
  template <class T, class T2>
  rgbacolor<T,T2>& rgbacolor<T,T2>::operator *=(T factor)
  {
    rgb.direct.r *= factor;
    rgb.direct.g *= factor;
    rgb.direct.b *= factor;
    // multiply the OPACITY by the factor, not the transparency.
    alpha = T2(1) - T2((1 - alpha) * factor);
    ::clamp(alpha, T2(0), T2(1));
    
    return *this;
  } // rgbacolor::operator*=(T)

  /** Division by a factor/assign (specific) */
  template <class T, class T2>
  rgbacolor<T,T2>& rgbacolor<T,T2>::operator /=(T factor)
  {
    rgb.direct.r /= factor;
    rgb.direct.g /= factor;
    rgb.direct.b /= factor;
    // divide the OPACITY by the factor, not the transparency.
    alpha = T2(1) - T2((1 - alpha) / factor);
    ::clamp(alpha, T2(0), T2(1));    
    return *this;
  } // rgbacolor::operator/=(T)
  
  /** Multiplication by a factor/assign (general) */
  template <class T, class T2>
  template <class U>
  rgbacolor<T,T2>& rgbacolor<T,T2>::operator *=(U factor)
  {
    rgb.direct.r = T(rgb.direct.r * factor);
    rgb.direct.g = T(rgb.direct.g * factor);
    rgb.direct.b = T(rgb.direct.b * factor);
    
    // multiply the OPACITY by the factor, not the transparency.
    alpha = T2(1) - T2((1 - alpha) * factor);
    ::clamp(alpha, T2(0), T2(1));
    
    return *this;
  } // rgbacolor::operator*=(U)

  /** Division by a factor/assign (general) */  
  template <class T, class T2>
  template <class U>
  rgbacolor<T,T2>& rgbacolor<T,T2>::operator /=(U factor)
  {
    rgb.direct.r = T(rgb.direct.r / factor);
    rgb.direct.g = T(rgb.direct.g / factor);
    rgb.direct.b = T(rgb.direct.b / factor);

    // divide the OPACITY by the factor, not the transparency.
    alpha = T2(1) - T2(((1 - alpha) / factor));
    ::clamp(alpha, T2(0), T2(1));
    
    return *this;    
  } // rgbacolor::operator/=(U)

  /** addition/assign */
  template <class T, class T2>
  rgbacolor<T,T2>& rgbacolor<T,T2>::operator +=(const rgbacolor<T,T2>& r)
  {
    rgb.direct.r += r.rgb.direct.r;
    rgb.direct.g += r.rgb.direct.g;
    rgb.direct.b += r.rgb.direct.b;

    alpha *= r.alpha;
    ::clamp(alpha, T2(0), T2(1));

    return *this;
  } // rgbacolor::operator+=(rgbacolor)

  /** subtraction/assign */
  template <class T, class T2>
  rgbacolor<T,T2>& rgbacolor<T,T2>::operator -=(const rgbacolor<T,T2>& r)
  {
    rgb.direct.r -= r.rgb.direct.r;
    rgb.direct.g -= r.rgb.direct.g;
    rgb.direct.b -= r.rgb.direct.b;
    
    alpha = alpha / r.alpha;
    ::clamp(alpha, T2(0), T2(1));

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
  template <class T, class T2, class U>
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
    T2 alpha = T2(1) - c.a();
    ::clamp(alpha, T2(0), T2(1));
    return rgbacolor<T,T2>(-c.r(),-c.g(),-c.b(),alpha);
  } // operator-(rgbacolor,rgbacolor)  


  /** Now a group of rgb/rgba color manipulations -- They all revert to being
      plain old RGB colors, after integrating their alphas into their
      components. */

  template <class T, class T2>
  rgbcolor<T> operator+(const rgbcolor<T>& c1, const rgbacolor<T,T2>& c2)
  {
    T2 opacity = T2(1) - c2.a();
    return rgbcolor<T>( c1.r() + c2.r() * opacity,
                        c1.g() + c2.g() * opacity,
                        c1.b() + c2.b() * opacity );                    
  } // operator+(rgbcolor,rgbacolor)

  template <class T, class T2>
  rgbcolor<T> operator+(const rgbacolor<T,T2>& c1, const rgbcolor<T>& c2)
  {
    T2 opacity = T2(1) - c1.a();
    return rgbcolor<T>( c1.r() * opacity + c2.r(),
                        c1.g() * opacity + c2.g(),
                        c1.b() * opacity + c2.b() );                    
  } // operator+(rgbacolor,rgbcolor)

  
  template <class T, class T2>
  rgbcolor<T> operator-(const rgbcolor<T>& c1, const rgbacolor<T,T2>& c2)
  {
    T2 opacity = T2(1) - c2.a();
    return rgbcolor<T>( c1.r() - c2.r() * opacity,
                        c1.g() - c2.g() * opacity,
                        c1.b() - c2.b() * opacity );                    
  } // operator-(rgbcolor,rgbacolor)

  template <class T, class T2>
  rgbcolor<T> operator-(const rgbacolor<T,T2>& c1, const rgbcolor<T>& c2)
  {
    T2 opacity = T2(1) - c1.a();
    return rgbcolor<T>( c1.r() * opacity - c2.r(),
                        c1.g() * opacity - c2.g(),
                        c1.b() * opacity - c2.b() );                    
  } // operator-(rgbacolor,rgbcolor)    

  template <class T, class T2>
  rgbcolor<T> scaled_convert_color(const rgbacolor<T,T2>& c)
  {
    T2 factor = T2(1) - c.a();
    return rgbcolor<T>(c.r() * factor,
                       c.g() * factor,
                       c.b() * factor);
  }

  template <class T, class T2>
  rgbcolor<T> convert_color(const rgbacolor<T,T2>& c)
  {
    return rgbcolor<T>(c.r(),c.g(),c.b());
  }
} // namespace manygames


#endif /* !defined(__MANYGAMES__RGBACOLOR_HPP__) */
