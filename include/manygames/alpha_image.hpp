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

#if       !defined(__MANYGAMES__ALPHA_IMAGE_HPP__)
#define            __MANYGAMES__ALPHA_IMAGE_HPP__

// --------------------------------------
// Default include of parent class header
// --------------------------------------
#include <manygames/raster.hpp>
#include <manygames/rgbacolor.hpp>

namespace manygames
{ 

  // Sorry about these comments, as they are meant to be viewed in html form.
  /**
   * 
   * A generic class which combines the capabilities of raster and rgbacolor.
   * This class has almost no functionality of its own.
   *
   * Note the neat feature of this class: it can be reinterpreted as a pointer
   * to the base type given to it.
   *
   * For example:<br>
   * <font color="#008800">alpha_image</font>&lt;<font color="#000088">unsigned
   * char</font>&gt im(640, 480); 
   *
   * <font color="#880000">
   * // This next variable can be treated as a single array of size      <br>
   * // im.numpixels( ) in length, which would be 307200 in this case.   <br>
   * </font>
   * <font color="#000088">unsigned char</font>*
   * alpha_image_data</font> = 
   * im.<font color="#008800">reinterpret</font>
   * &lt;<font color="#000088">unsigned char</font>*&gt; ( );<br>
   * ...<br>
   * <font color="#880000">
   * // Act on the data, being careful not to go beyond bounds on either <br>
   * // end, or (whether intentional or not) deallocate the pointer.     <br>
   * </font>
   * 
   * @author Kevin Harris <kpharris@users.sourceforge.net>
   * @version $Revision$
   * @see raster
   * @see rgbacolor
   * 
   */
  template <class T>
  class alpha_image : public raster<rgbacolor<T> >
  {

  private:

  protected:

  public:
    /** Default constructor */
    alpha_image();

    /** Size-specified constructor.  Creates a width by height sized alpha_image */
    alpha_image(unsigned width, unsigned height);
    
    /** Destructor */
    virtual ~alpha_image();

    /** Copy constructor */
    alpha_image(const alpha_image& old);

    /** Assignment operator */
    alpha_image& operator= (const alpha_image& old);

  }; // class alpha_image

  //------------------------------------
  // Default constructor for class alpha_image
  //------------------------------------
  template <class T>
  alpha_image<T>::alpha_image(): raster<rgbacolor<T> >()
  {
  
  } // alpha_image()

  //--------------------------------------------
  // Size-specified  constructor for class alpha_image
  //--------------------------------------------
  template <class T>
  alpha_image<T>::alpha_image(unsigned width, unsigned height):
    raster<rgbacolor<T> >(width, height)
  {
  
  } // alpha_image(w,h)  

  //---------------------------
  // Destructor for class alpha_image
  //---------------------------
  template <class T>
  alpha_image<T>::~alpha_image()
  {
  
  } // ~alpha_image()

  //---------------------------------
  // Copy constructor for class alpha_image
  //---------------------------------
  template <class T>
  alpha_image<T>::alpha_image(const alpha_image<T>& old):
    raster<rgbacolor<T> >(old)
  {

  } // alpha_image(alpha_image)

  //------------------------------------
  // Assignment operator for class alpha_image
  //------------------------------------
  template <class T>
  alpha_image<T>& alpha_image<T>::operator= (const alpha_image<T>& old)
  {
    // Generic check for self-assignment
    if( &old != this)
    {
      // The class currently has no members, but if they are added, they need
      // to be assigned here. 
      
      raster<rgbacolor<T> >::operator=(old);
    }
    return (*this);
  } // alpha_image::operator=(alpha_image)
  
} // namespace manygames


#endif /* !defined(__MANYGAMES__ALPHA_IMAGE_HPP__) */

