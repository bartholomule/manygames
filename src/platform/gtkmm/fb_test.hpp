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
#include "gtkmm_framebuffer.hpp"

/**
 * 
 * simplified (dumb) GTK Framebuffer test program.
 * 
 * @author Kevin Harris <kpharris@users.sourceforge.net>
 * @version $Revision$
 * 
 */
class fb_test : public manygames::gtkmm_framebuffer
{

private:

protected:

  long last_time;
  int last_x, last_y;
  int x_shift, y_shift;
  bool dragging;

public:
  /** Default constructor */
  fb_test();

  /** Destructor */
  virtual ~fb_test();

  /** Copy constructor */
  fb_test(const fb_test& old);

  /** Assignment operator */
  fb_test& operator= (const fb_test& old);

  virtual void update();

  virtual bool on_expose_event(GdkEventExpose* e)
  {
    update(); /* temp */
    draw();
    return true;
  }
  
  virtual bool on_button_press_event(GdkEventButton* event);
  virtual bool on_button_release_event(GdkEventButton* event);  
  virtual bool on_motion_notify_event(GdkEventMotion* event);
}; // class fb_test



#endif /* !defined(__FB_TEST_HPP__) */

