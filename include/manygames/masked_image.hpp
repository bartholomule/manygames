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

#if       !defined(__MANYGAMES__MASKED_IMAGE_HPP__)
#define            __MANYGAMES__MASKED_IMAGE_HPP__

// --------------------------------------
// Default include of parent class header
// --------------------------------------
#include <manygames/image.hpp>
#include <manygames/raster.hpp>

namespace manygames
{

  /**
   *
   * An image which has a mask for use in determining weather or not the color
   * value should be used.
   *
   * @author Kevin Harris <kpharris@users.sourceforge.net>
   * @version $Revision$
   *
   */
  template <class T, class mask_base = bool>
  class masked_image : public image<T>
  {

  private:

  protected:
    raster<mask_base> my_mask;

  public:
    /** Default constructor */
    masked_image();

    /** Secondary constructor; initialized */
    masked_image(const image<T>& img, const raster<mask_base>& msk);

    /** Sized constructor */
    masked_image(unsigned width, unsigned height);

    masked_image(unsigned width, unsigned height,
                 const rgbcolor<T>* pdata, const mask_base* mdata);

    /** Destructor */
    virtual ~masked_image();

    /** Copy constructor */
    masked_image(const masked_image& old);

    /** Assignment operator */
    masked_image& operator= (const masked_image& old);

    /**
     * Get the mask element at the given (x,y)
     * @param x The column.
     * @param y The row.
     * @throws out_of_range if either x or y is out of range.
     */
    mask_base& mask(unsigned x, unsigned y) throw(out_of_range)
    { return my_mask(x,y); }

    /**
     * Get the mask element at the given (x,y)
     * @param x The column.
     * @param y The row.
     * @throws out_of_range if either x or y is out of range.
     */
    mask_base mask(unsigned x, unsigned y) const throw(out_of_range)
    { return my_mask(x,y); }

    /**
     * Resize the current masked image to the given width and height.  If
     * preserve is given, the current data (if any), is copied across. If
     * either width or height is zero, the current masked image will be resized
     * to 0.
     */
    void resize(unsigned width, unsigned height, bool preserve = true)
    {
      raster<T>::resize(width, height, preserve);
      my_mask.resize(width, height, preserve);
    }

    /**
     * Resize the current masked image to the given width and height, shifting
     * old data to be centered at cx,cy in the newly sized masked image, and
     * filling the rest with the given fill data.
     */
    void resize(unsigned width, unsigned height,
                int cx, int cy, const rgbcolor<T>& fill1, const mask_base& fill2)
    {
      raster<rgbcolor<T> >::resize(width, height, cx, cy, fill1);
      my_mask.resize(width, height, cx, cy, fill2);
    }


    /**
     * Return a image which contains the elements in the range
     * (x1,y1) to (x2,y2) inclusive.
     * @throws out_of_range if any of x1, y1, x2, or y2 are out of range.
     * @returns a new image that contains the data from the specified region.
     */
    masked_image sub_image(unsigned x1, unsigned y1,
                           unsigned x2, unsigned y2) const throw(out_of_range)
    {
      return masked_image<T,mask_base>(image<T>::sub_image(x1,y1,x2,y2),
                                       my_mask.sub_raster(x1,y1,x2,y2));
    }

    /**
     * Return a image which contains the elements in the range
     * (rect.left, rect.top) to (rect.right, rect.bottom) inclusive.
     * @throws out_of_range if any of the rect coords are out of range.
     * @returns a new image that contains the data from the specified region.
     */
    masked_image sub_image(const rectangle<unsigned>& rect) const throw(out_of_range)
    {
      return masked_image<T,mask_base>(image<T>::sub_image(rect),
                                       my_mask.sub_raster(rect));
    }


  }; // class masked_image


  //-------------------------------------------
  // Default constructor for class masked_image
  //-------------------------------------------
  template <class T, class mask_base>
  masked_image<T,mask_base>::masked_image():
    image<T>(),
    my_mask()
  {

  } // masked_image()

  //-------------------------------------------
  // Sized constructor for class masked_image
  //-------------------------------------------
  template <class T, class mask_base>
  masked_image<T,mask_base>::masked_image(unsigned w, unsigned h):
    image<T>(w, h),
    my_mask(w, h)
  {

  } // masked_image(w,h)


  //-------------------------------------------
  // Secondary constructor for class masked_image
  //-------------------------------------------
  template <class T, class mask_base>
  masked_image<T,mask_base>::masked_image(const image<T>& img,
                                          const raster<mask_base>& msk):
    image<T>(img),
    my_mask(msk)
  {

    // Make sure the sizes are the same....
    my_mask.resize(this->get_width(), this->get_height(), true);

  } // masked_image(image,raster)

  template <class T, class mask_base>
  masked_image<T,mask_base>::masked_image(unsigned width, unsigned height,
                                          const rgbcolor<T>* pdata,
                                          const mask_base* mdata):
    image<T>(width, height, pdata),
    my_mask(width, height, mdata)
  {

  } // masked_image(unsigned,unsigned,rgbcolor*,mask_base*)

  //----------------------------------
  // Destructor for class masked_image
  //----------------------------------
  template <class T, class mask_base>
  masked_image<T,mask_base>::~masked_image()
  {

  } // ~masked_image()

  //----------------------------------------
  // Copy constructor for class masked_image
  //----------------------------------------
  template <class T, class mask_base>
  masked_image<T,mask_base>::masked_image(const masked_image& old):
    image<T>(old),
    my_mask(old.my_mask)
  {

  } // masked_image(masked_image)

  //-------------------------------------------
  // Assignment operator for class masked_image
  //-------------------------------------------
  template <class T, class mask_base>
  masked_image<T,mask_base>& masked_image<T,mask_base>::operator= (const masked_image& old)
  {
    // Generic check for self-assignment
    if( &old != this)
    {
      my_mask = old.my_mask;

      image<T>::operator=(old);
    }
    return (*this);
  } // masked_image::operator=(masked_image)



  template <class T, class mask_base>
  masked_image<T,mask_base> scale_image(const masked_image<T,mask_base>& image, unsigned scale)
  {

    //    printf("scale_image -- called with scale=%d\n", scale);fflush(stdout);
    masked_image<T,mask_base> ret_image(image.get_width() * scale,
                                        image.get_height() * scale);

    //    printf("ri w=%d, h=%d, orig w=%d, h=%d\n",  ret_image.get_width(),  ret_image.get_height(),  image.get_width(),  image.get_height()); fflush(stdout);

    for(unsigned y = 0; y < ret_image.get_height(); ++y)
    {
      unsigned y_norm = y / scale;
      for(unsigned x = 0; x < ret_image.get_width(); ++x)
      {
        unsigned x_norm = x / scale;
        ret_image(x,y) = image(x_norm, y_norm);
        ret_image.mask(x,y) = image.mask(x_norm, y_norm);
      }
    }
    printf("Returning the scaled image...\n"); fflush(stdout);
    return ret_image;
  }

} // namespace manygames


#endif /* !defined(__MANYGAMES__MASKED_IMAGE_HPP__) */
