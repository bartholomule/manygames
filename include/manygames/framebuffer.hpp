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

#if       !defined(__MANYGAMES__FRAMEBUFFER_HPP__)
#define            __MANYGAMES__FRAMEBUFFER_HPP__

#include <manygames/image.hpp>
#include <manygames/masked_image.hpp>
#include <manygames/rgbacolor.hpp>
#include <manygames/template_functions.hpp>

namespace manygames
{ 
  /**
   * 
   * A generic framebuffer from which platform-specific versions may be
   * derived. 
   * 
   * @author Kevin Harris <kpharris@users.sourceforge.net>
   * @version $Revision$
   * 
   */
  template <class T>
  class framebuffer
  {

  private:

  protected:

    /**
     * Two buffers to be used as foreground and background... They will
     * *always* have the same size.
     */  
    image<T> buffer1, buffer2;
    
    image<T> *foreground; ///< The current foreground buffer
    image<T> *background; ///< The current background buffer
    
  public:
    /** Default constructor */
    framebuffer();

    /** Destructor */
    virtual ~framebuffer();

    /** Copy constructor */
    framebuffer(const framebuffer& old);

    /** Assignment operator */
    framebuffer& operator= (const framebuffer& old);

    /** Get the current foreground image buffer (read only) */
    const image<T>& get_foreground() const { return *foreground; }
    /** Get the current background image buffer (read only) */
    const image<T>& get_background() const { return *background; }    

    /** Swap the foreground and background buffers. */
    void flip() { my_swap(foreground, background); }

    /** Get the width of the screen */
    unsigned get_width()  const { return buffer1.get_width(); }
    /** Get the height of the screen */
    unsigned get_height() const { return buffer1.get_height(); }
    
    /**
     * Called to tell any subclasses that they need to update the buffers, and
     * flip if required.
     *
     * This function *MUST* be overridden (pure virtual).
     */
    virtual void update() = 0;
    /**
     * Called to tell any subclasses that they needs to draw the current
     * foreground buffer in whatever method they can (platform specific
     * subclasses can do this).
     *
     * This function *MUST* be overridden (pure virtual).
     */
    virtual void draw() = 0;

    /**
     * Resize the current images to the given width and height.  If preserve is
     * given, the current data (if any), is copied across. If either width or
     * height is zero, the current images will be resized to 0.
     *
     */
    void resize(unsigned width, unsigned height, bool preserve = true);

    /**
     * Resize the current images to the given width and height, shifting old
     * data to be centered at cx,cy in the newly sized images, and filling the
     * rest with the given fill data.
     * 
     */
    void resize(unsigned width, unsigned height,
		int cx, int cy, const T& fill);    


    /** Set the pixel at x,y to the given color (in the background buffer). */
    virtual void setpixel_back(unsigned x, unsigned y, const rgbcolor<T>& c)
      throw(out_of_range) 
    {
      (*background)(x,y) = c;
    }
    
    /** Set the pixel at x,y to the given color (in the foreground buffer) */
    virtual void setpixel(unsigned x, unsigned y, const rgbcolor<T>& c)
      throw(out_of_range)
    {
      (*foreground)(x,y) = c;
    }

    /** Set the pixel at x,y to the given color (in the background buffer). */
    template <class T2>
    void setpixel_back(unsigned x, unsigned y, const rgbacolor<T,T2>& c)
      throw(out_of_range) 
    {
      rgbcolor<T> cur_color = getpixel_back(x,y);
      setpixel_back(x,y, ( (c.a() * cur_color) +
			   (1 - c.a()) * convert_color(c) ) );
    }
    
    /** Set the pixel at x,y to the given color (in the foreground buffer) */
    template <class T2>
    void setpixel(unsigned x, unsigned y, const rgbacolor<T,T2>& c)
      throw(out_of_range)
    {
      rgbcolor<T> cur_color = getpixel(x,y);
      setpixel(x,y, ( (c.a() * cur_color) +
		      (1 - c.a()) * convert_color(c) ) );
    }
    
    /** Get the pixel at x,y (from the background buffer). */
    virtual rgbcolor<T> getpixel_back(unsigned x, unsigned y)
      throw(out_of_range)
    {
      return ((*background)(x,y));
    }
    
    /** Get the pixel at x,y (from the foreground buffer) */
    virtual rgbcolor<T> getpixel(unsigned x, unsigned y)
      throw(out_of_range)
    {
      return ((*foreground)(x,y));      
    }    

    virtual void fg_draw_image(const image<T>& img, int x, int y);
    virtual void bg_draw_image(const image<T>& img, int x, int y);

    virtual void fg_draw_image(const masked_image<T,bool>& img, int x, int y);
    virtual void bg_draw_image(const masked_image<T,bool>& img, int x, int y);    
    
    /*
     * [FIXME!] Add functions here (possibly virtual) for drawing images (at
     * the minimum), lines, circles, elipses, etc.  This needs to be a
     * fully-functional framebuffer (raster) with nifty features.
     */

  }; // class framebuffer


  //------------------------------------------
  // Default constructor for class framebuffer
  //------------------------------------------
  template <class T>
  framebuffer<T>::framebuffer():
    buffer1(),
    buffer2(),
    foreground(&buffer1),
    background(&buffer2)
  {
  
  } // framebuffer()

  //---------------------------------
  // Destructor for class framebuffer
  //---------------------------------
  template <class T>
  framebuffer<T>::~framebuffer()
  {
    foreground = NULL;
    background = NULL;
    
  } // ~framebuffer()

  //---------------------------------------
  // Copy constructor for class framebuffer
  //---------------------------------------
  template <class T>
  framebuffer<T>::framebuffer(const framebuffer<T>& old):
    buffer1(old.buffer1),
    buffer2(old.buffer2)
  {
    if( old.foreground == &old.buffer1 )
    {
      foreground = &buffer1;
      background = &buffer2;
    }
    else if( old.foreground == &old.buffer2 )
    {
      foreground = &buffer2;
      background = &buffer1;      
    }
    else
    {
      // Something is fooed up! [FIXME] Potentially report an error.
      foreground = &buffer1;
      foreground = &buffer2;      
    }
  } // framebuffer(framebuffer)

  //------------------------------------------
  // Assignment operator for class framebuffer
  //------------------------------------------
  template <class T>
  framebuffer<T>& framebuffer<T>::operator= (const framebuffer<T>& old)
  {
    // Generic check for self-assignment
    if( &old != this)
    {
      buffer1 = old.buffer1;
      buffer2 = old.buffer2;

      // Preserve the fore-background order of the old buffers.
      if( old.foreground == &old.buffer1 )
      {
	foreground = &buffer1;
	background = &buffer2;
      }
      else if( old.foreground == &old.buffer2 )
      {
	foreground = &buffer2;
	background = &buffer1;      
      }
      else
      {
	// Something is fooed up! [FIXME] Potentially report an error.
	foreground = &buffer1;
	foreground = &buffer2;      
      }
    }
    return (*this);
  } // framebuffer::operator=(framebuffer)


  template <class T>
  void framebuffer<T>::resize(unsigned width, unsigned height, bool preserve)
  {
    buffer1.resize(width, height, preserve);
    buffer2.resize(width, height, preserve);    
  } // framebuffer::resize(width,height,preserve)

  template <class T>
  void framebuffer<T>::resize(unsigned width, unsigned height,
			      int cx, int cy, const T& fill)
  {
    buffer1.resize(width, height, cx, cy, fill);
    buffer2.resize(width, height, cx, cy, fill);
  } // framebuffer::resize(width,height,cx,cy,fill)

  template <class T>
  void framebuffer<T>::fg_draw_image(const image<T>& img, int x, int y)
  {
    if( !img.empty() )
    {
      unsigned width = buffer1.get_width();
      unsigned height = buffer1.get_height();

      int x_min = std::min(width, unsigned(std::max(0, x)));
      int x_max = std::min(width, unsigned(std::max(0, int(img.get_width()) + x)));
      int y_min = std::min(height, unsigned(std::max(0, y)));
      int y_max = std::min(height, unsigned(std::max(0, int(img.get_height()) + y)));

      for(unsigned y1 = y_min; y1 < y_max; ++y1)
      {
	for(unsigned x1 = x_min; x1 < x_max; ++x1)
	{
	  (*foreground)(x1,y1) = img(x1 - x, y1 - y);
	}
      }
    }
  }

  template <class T>
  void framebuffer<T>::bg_draw_image(const image<T>& img, int x, int y)
  {
    if( !img.empty() )
    {
      unsigned width = buffer1.get_width();
      unsigned height = buffer1.get_height();

      int x_min = std::min(width, unsigned(std::max(0, x)));
      int x_max = std::min(width, unsigned(std::max(0, int(img.get_width()) + x)));
      int y_min = std::min(height, unsigned(std::max(0, y)));
      int y_max = std::min(height, unsigned(std::max(0, int(img.get_height()) + y)));

      for(unsigned y1 = y_min; y1 < y_max; ++y1)
      {
	for(unsigned x1 = x_min; x1 < x_max; ++x1)
	{
	  (*background)(x1,y1) = img(x1 - x, y1 - y);
	}
      }
    }
  }

  template <class T>
  void framebuffer<T>::fg_draw_image(const masked_image<T,bool>& img, int x, int y)
  {
    if( !img.empty() )
    {
      unsigned width = buffer1.get_width();
      unsigned height = buffer1.get_height();

      int x_min = std::min(width, unsigned(std::max(0, x)));
      int x_max = std::min(width, unsigned(std::max(0, int(img.get_width()) + x)));
      int y_min = std::min(height, unsigned(std::max(0, y)));
      int y_max = std::min(height, unsigned(std::max(0, int(img.get_height()) + y)));

      for(unsigned y1 = y_min; y1 < y_max; ++y1)
      {
	for(unsigned x1 = x_min; x1 < x_max; ++x1)
	{
	  if( img.mask(x1 - x, y1 - y) )
	  {
	    (*foreground)(x1,y1) = img(x1 - x, y1 - y);
	  }
	}
      }
    }
  }

  template <class T>
  void framebuffer<T>::bg_draw_image(const masked_image<T,bool>& img, int x, int y)
  {
    if( !img.empty() )
    {
      unsigned width = buffer1.get_width();
      unsigned height = buffer1.get_height();

      int x_min = std::min(width, unsigned(std::max(0, x)));
      int x_max = std::min(width, unsigned(std::max(0, int(img.get_width()) + x)));
      int y_min = std::min(height, unsigned(std::max(0, y)));
      int y_max = std::min(height, unsigned(std::max(0, int(img.get_height()) + y)));

      for(unsigned y1 = y_min; y1 < y_max; ++y1)
      {
	for(unsigned x1 = x_min; x1 < x_max; ++x1)
	{
	  if( img.mask(x1 - x, y1 - y) )
	  {
	    (*background)(x1,y1) = img(x1 - x, y1 - y);
	  }
	}
      }
    }
  }  

} // namespace manygames


#endif /* !defined(__MANYGAMES__FRAMEBUFFER_HPP__) */

