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

#if       !defined(__FB_TEST_HPP__)
#define            __FB_TEST_HPP__

// --------------------------------------
// Default include of parent class header
// --------------------------------------
#include "gtkmm_input_window.hpp"

/**
 * 
 * simplified (dumb) GTK Framebuffer test program.
 * 
 * @author Kevin Harris <kpharris@users.sourceforge.net>
 * @version $Revision$
 * 
 */
class fb_test : public manygames::gtkmm_input_window
{

private:

protected:

  long last_time;
  bool dragging;

public:
  /** Default constructor */
  fb_test();

  /** Destructor */
  virtual ~fb_test();

  /** Copy constructor */
  fb_test(const fb_test& old);

  virtual void update();



}; // class fb_test



#endif /* !defined(__FB_TEST_HPP__) */

