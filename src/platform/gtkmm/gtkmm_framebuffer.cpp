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

#include <manygames_config.hpp>
#include <manygames/textized.hpp>
#include "gtkmm_framebuffer.hpp"


namespace manygames
{ 

  //------------------------------------------------
  // Default constructor for class gtkmm_framebuffer
  //------------------------------------------------
  gtkmm_framebuffer::gtkmm_framebuffer():
    framebuffer<guchar>()
    // Class initializers go here. DELETEME
  {
  
  } // gtkmm_framebuffer()

  //---------------------------------------
  // Destructor for class gtkmm_framebuffer
  //---------------------------------------
  gtkmm_framebuffer::~gtkmm_framebuffer()
  {
  
  } // ~gtkmm_framebuffer()

  //---------------------------------------------
  // Copy constructor for class gtkmm_framebuffer
  //---------------------------------------------
  gtkmm_framebuffer::gtkmm_framebuffer(const gtkmm_framebuffer& old):
    framebuffer<guchar>(old)
    // Class initializers go here. DELETEME
  {
    // Insert any copy-assignment here. DELETEME
  } // gtkmm_framebuffer(gtkmm_framebuffer)

  //------------------------------------------------
  // Assignment operator for class gtkmm_framebuffer
  //------------------------------------------------
  gtkmm_framebuffer& gtkmm_framebuffer::operator= (const gtkmm_framebuffer& old)
  {
    // Generic check for self-assignment
    if( &old != this)
    {
      // Insert assignment here. DELETEME

      framebuffer<guchar>::operator=(old);
    }
    return (*this);
  } // gtkmm_framebuffer::operator=(gtkmm_framebuffer)

  void gtkmm_framebuffer::draw()
  {
    Glib::RefPtr<Gdk::Window> window = get_window();

    window->draw_rgb_image(get_style()->get_fg_gc(Gtk::STATE_NORMAL),
			   0, 0,
			   foreground->get_width(), foreground->get_height(),
			   Gdk::RGB_DITHER_MAX,
			   foreground->reinterpret<guchar*>(),
			   foreground->get_width() * 3);
  }

} // namespace manygames

