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

#if       !defined(__MANYGAMES__X_INPUT_WINDOW_HPP__)
#define            __MANYGAMES__X_INPUT_WINDOW_HPP__

// --------------------------------------
// Default include of parent class header
// --------------------------------------
#include <manygames/input_window.hpp>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>    

namespace manygames
{ 

  /**
   * 
   * ***CLASS DESCRIPTION GOES HERE*** (multiple lines are ok)
   * 
   * @author Kevin Harris <kpharris@users.sourceforge.net>
   * @version $Revision$
   * 
   */
  class x_input_window : public input_window<unsigned char>
  {

  private:
    Display *display;
    bool display_created;
    int screen;
    Window window;
    GC gc;
    XImage* img;
    unsigned char* image_buffer; // Required for display on X.
    bool drawable;

    /** Copy constructor -- Not implemented */
    x_input_window(const x_input_window& old); 
    
    /** Assignment operator -- Not implemented */
    x_input_window& operator= (const x_input_window& old); 
    
  protected:

  public:
    /** Default constructor */
    x_input_window(int width = 200, int height = 200, Display* disp = NULL, int screen = -1);

    /** Destructor */
    virtual ~x_input_window();

    virtual void draw(); // overridden pure virtual function.
    
    /** Get the width of the screen */
    unsigned get_width()  const { return framebuffer<unsigned char>::get_width(); }
    /** Get the height of the screen */
    unsigned get_height() const { return framebuffer<unsigned char>::get_height(); }

    virtual void disable_repeat();
    virtual void enable_repeat(); 

    /** Check for size changes, and resize the buffers as needed. */
    virtual void size_change_check();

    /*
    virtual bool on_button_press_event(GdkEventButton* event);
    virtual bool on_button_release_event(GdkEventButton* event);  
    virtual bool on_motion_notify_event(GdkEventMotion* event);
    virtual bool on_expose_event(GdkEventExpose* e)
    {
      if( is_drawable() )
      {
        size_change_check();
        update();
        draw();
      }
      return true;
    }
    
    virtual bool on_key_press_event(GdkEventKey* event);
    virtual bool on_key_release_event(GdkEventKey* event);    

    */
    
    /** Enter the main message loop, returning only when the program is
        terminated, or if quit_window() below is called. . */
    virtual void run_window();

    /** Terminate any running message loop from above, allowing it to return */
    virtual void quit_window();    
    
  }; // class x_input_window

} // namespace manygames


#endif /* !defined(__MANYGAMES__X_INPUT_WINDOW_HPP__) */

