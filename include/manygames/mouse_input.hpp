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

#if       !defined(__MANYGAMES__MOUSE_INPUT_HPP__)
#define            __MANYGAMES__MOUSE_INPUT_HPP__

#include <sigc++/sigc++.h>

namespace manygames
{ 
  /**
   * 
   * A basic class for mouse input (to be subclassed by the class which
   * actually has the capibility to detect mouse stuff).
   * 
   * @author Kevin Harris <kpharris@users.sourceforge.net>
   * @version $Revision$
   * 
   */
  class mouse_input
  {
  public:
    enum MouseStateMasks { MouseButton1      = 1 << 0,
			   MouseButton2      = 1 << 1,
			   MouseButton3      = 1 << 2,
			   MouseButton4      = 1 << 3,
			   MouseButton5      = 1 << 4,
			   MouseShiftDown    = 1 << 5,
			   MouseControlDown  = 1 << 6,
			   MouseMod1Down     = 1 << 7,
			   MouseMod2Down     = 1 << 8,
			   MouseMod3Down     = 1 << 9,
			   MouseMod4Down     = 1 << 10,
			   MouseMod5Down     = 1 << 11,
			   MouseLockDown     = 1 << 12,
			   MouseButtonMask   = 0x001F,
			   MouseModifierMask = 0x1FE0,
			   MaxMouseButton   = 5
    };
  private:

  protected:
    /** Dish out any required operations to the callback functions, update
        state, etc.
        Note that this is NOT public, because only subclasses should tell this
        class that some mouse event occurred.
    */
    virtual bool handle_mouse_event(int x, int y, unsigned state);

    int mouse_x, mouse_y; // 
    int last_x,  last_y;  // 
    unsigned last_state;       //
    int press_x, press_y; // 
    unsigned press_state, release_state; // 
    int maximum_click_distance; // The max # of pixels dragable when clicking.
    bool valid_data;            //
    
  public:
    /** Default constructor */
    mouse_input();

    /** Destructor */
    virtual ~mouse_input();

    /** Copy constructor */
    mouse_input(const mouse_input& old);

    /** Assignment operator */
    mouse_input& operator= (const mouse_input& old);


    /** Return the current button state (if there is one). */
    virtual unsigned get_button_state() const;
    
    /** Return the number of buttons the mouse has. */
    //    virtual int num_mouse_buttons() const = 0;

    /** Return the current mouse position (in x and y), valid IFF it returns
	true */
    virtual bool get_mouse_position(int& x, int& y) const;
    
    /** Return the last (previous) mouse position (in x and y), valid IFF it
	returns true */    
    virtual bool get_last_position(int& x, int& y) const;

    /** Get the maximum distance between press and release to be counted as a
	click. */
    int get_max_click_distance() const { return maximum_click_distance; }
    
    /** Set the maximum distance between press and release to be counted as a
	click. */    
    void set_max_click_distance(int d) { maximum_click_distance = d; }

    //bool mouse_clicked(int x, int y, unsigned press_state, unsigned release_state);
    //bool mouse_dragged(int x1, int y1, int x2, int y2, unsigned state_diff);
    //bool mouse_moved(int x, int y, int dx, int dy);
    //bool mouse_pressed(int x, int y, unsigned press_state, unsigned state_diff);
    //bool mouse_released(int x, int y, unsigned release_state, unsigned state_diff);

    // Here's how the callbacks will work:
    // Upon button press, the state will be set, then 'pressed' will be called.
    // Upon button release, state will be updated, released called, then either
    //      clicked or dragged will be called (depending on the distance
    //      moved).
    // Note: if the internals of the callback function for 'dragged' need to
    //   find out what the current state is, then it will need to call the
    //   get_button_state function.  SicC++ only allowed up to 5 arguments for
    //   signals. :( 

    // See above comments for the arguments to these callbacks.
    SigC::Signal4<bool,int,int,unsigned,unsigned> clicked;
    SigC::Signal5<bool,int,int,int,int,unsigned> dragged;
    SigC::Signal4<bool,int,int,int,int> moved;
    SigC::Signal4<bool,int,int,unsigned,unsigned> pressed;
    SigC::Signal4<bool,int,int,unsigned,unsigned> released;
  }; // class mouse_input

} // namespace manygames


#endif /* !defined(__MANYGAMES__MOUSE_INPUT_HPP__) */
