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

#if       !defined(__MANYGAMES__IMAGE_HPP__)
#define            __MANYGAMES__IMAGE_HPP__

// --------------------------------------
// Default include of parent class header
// --------------------------------------
#include <manygames/raster.hpp>
#include <manygames/rgbcolor.hpp>

namespace manygames
{ 

  // Sorry about these comments, as they are meant to be viewed in html form.
  /**
   * 
   * A generic class which combines the capabilities of raster and rgbcolor.
   * This class has almost no functionality of its own.
   *
   * Note the neat feature of this class: it can be reinterpreted as a pointer
   * to the base type given to it.
   *
   * For example:<br>
   * <font color="#008800">image</font>&lt;<font color="#000088">unsigned
   * char</font>&gt im(640, 480); 
   *
   * <font color="#880000">
   * // This next variable can be treated as a single array of size      <br>
   * // im.numpixels( ) in length, which would be 307200 in this case.   <br>
   * </font>
   * <font color="#000088">unsigned char</font>*
   * image_data</font> = 
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
   * @see rgbcolor
   * 
   */
  template <class T>
  class image : public raster<rgbcolor<T> >
  {

  private:

  protected:

  public:
    /** Default constructor */
    image();

    /** Size-specified constructor.  Creates a width by height sized image */
    image(unsigned width, unsigned height);

    /** Size-specified constructor.  Creates a width by height sized image */
    image(unsigned width, unsigned height, const rgbcolor<T>* pdata);    
    
    /** Destructor */
    virtual ~image();

    /** Copy constructor */
    image(const image& old);

    /** Assignment operator */
    image& operator= (const image& old);

  }; // class image

  //------------------------------------
  // Default constructor for class image
  //------------------------------------
  template <class T>
  image<T>::image(): raster<rgbcolor<T> >()
  {
  
  } // image()

  //--------------------------------------------
  // Size-specified  constructor for class image
  //--------------------------------------------
  template <class T>
  image<T>::image(unsigned width, unsigned height):
    raster<rgbcolor<T> >(width, height)
  {
  
  } // image(w,h)

  //--------------------------------------------------------
  // Size-specified, initialized constructor for class image
  //--------------------------------------------------------
  template <class T>
  image<T>::image(unsigned width, unsigned height, const rgbcolor<T>* pdata):
    raster<rgbcolor<T> >(width, height, pdata)
  {
  
  } // image(w,h,rgb*)  
    

  //---------------------------
  // Destructor for class image
  //---------------------------
  template <class T>
  image<T>::~image()
  {
  
  } // ~image()

  //---------------------------------
  // Copy constructor for class image
  //---------------------------------
  template <class T>
  image<T>::image(const image<T>& old):
    raster<rgbcolor<T> >(old)
  {

  } // image(image)

  //------------------------------------
  // Assignment operator for class image
  //------------------------------------
  template <class T>
  image<T>& image<T>::operator= (const image<T>& old)
  {
    // Generic check for self-assignment
    if( &old != this)
    {
      // The class currently has no members, but if they are added, they need
      // to be assigned here. 
      
      raster<rgbcolor<T> >::operator=(old);
    }
    return (*this);
  } // image::operator=(image)
  
} // namespace manygames


#endif /* !defined(__MANYGAMES__IMAGE_HPP__) */

