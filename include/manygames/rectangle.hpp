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

#if       !defined(__MANYGAMES__RECTANGLE_HPP__)
#define            __MANYGAMES__RECTANGLE_HPP__

namespace manygames
{ 

  /**
   * 
   * A simple rectangle class.  This assumes it is bottom-heavy, meaning that
   * the bottom coordinate is larger in size than the top. 
   * 
   * @author Kevin Harris <kpharris@users.sourceforge.net>
   * @version $Revision$
   * 
   */
  template<class base>
  struct rectangle
  {

    base left;
    base right;
    base top;
    base bottom;
    
    /** Default constructor */
    rectangle(base l, base r, base t, base b);

    /** Destructor */
    virtual ~rectangle();

    /** Copy constructor */
    rectangle(const rectangle& old);

    /** Assignment operator */
    rectangle& operator= (const rectangle& old);

    base width() const { return right - left; }
    base height() const { return bottom - top; }    
    
  }; // class rectangle



  //----------------------------------------
  // Default constructor for class rectangle
  //----------------------------------------
  template<class base>
  rectangle<base>::rectangle(base l, base r, base t, base b):
    left(l), right(r),
    top(t), bottom(b)
  {
    
  } // rectangle()

  //-------------------------------
  // Destructor for class rectangle
  //-------------------------------
  template<class base>
  rectangle<base>::~rectangle()
  {
    
  } // ~rectangle()

  //-------------------------------------
  // Copy constructor for class rectangle
  //-------------------------------------
  template<class base>
  rectangle<base>::rectangle(const rectangle<base>& old):
    left(old.left), right(old.right),
    top(old.top), bottom(old.bottom)
  {

  } // rectangle(rectangle)

  //----------------------------------------
  // Assignment operator for class rectangle
  //----------------------------------------
  template<class base>
  rectangle<base>& rectangle<base>::operator= (const rectangle<base>& old)
  {
    // Generic check for self-assignment
    if( &old != this)
    {
      left = old.left;
      right = old.right;
      top = old.top;
      bottom = old.bottom;
    }
    return (*this);
  } // rectangle::operator=(rectangle)

} // namespace manygames


#endif /* !defined(__MANYGAMES__RECTANGLE_HPP__) */

