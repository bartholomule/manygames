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

/*
  TODO:
    constructor, copy constructor, assignment: copy press state...
 */

#include <manygames/mouse_input.hpp>
#include <cstdio>

namespace manygames
{ 

  //------------------------------------------
  // Default constructor for class mouse_input
  //------------------------------------------
  mouse_input::mouse_input():
    maximum_click_distance(2),
    valid_data(false)
  {
  
  } // mouse_input()

  //---------------------------------
  // Destructor for class mouse_input
  //---------------------------------
  mouse_input::~mouse_input()
  {
  
  } // ~mouse_input()

  //---------------------------------------
  // Copy constructor for class mouse_input
  //---------------------------------------
  mouse_input::mouse_input(const mouse_input& old):
    mouse_x(old.mouse_x), mouse_y(old.mouse_y),
    last_x(old.last_x), last_y(old.last_y),
    last_state(old.last_state),
    maximum_click_distance(old.maximum_click_distance),
    valid_data(old.valid_data),
    mouse_clicked(old.mouse_clicked),
    mouse_dragged(old.mouse_dragged),
    mouse_moved(old.mouse_moved),
    mouse_pressed(old.mouse_pressed),
    mouse_released(old.mouse_released)    
  {

  } // mouse_input(mouse_input)

  //------------------------------------------
  // Assignment operator for class mouse_input
  //------------------------------------------
  mouse_input& mouse_input::operator= (const mouse_input& old)
  {
    // Generic check for self-assignment
    if( &old != this)
    {
      mouse_x = old.mouse_x;
      mouse_y = old.mouse_y;
      last_x = old.last_x;
      last_y = old.last_y;
      last_state = old.last_state;
      maximum_click_distance = old.maximum_click_distance;
      valid_data = old.valid_data;

      // These do NOT have valid assignment operators.
      /*
      clicked = old.clicked;
      dragged = old.dragged;
      moved = old.moved;
      pressed = old.pressed;
      released = old.released;
      */
    }
    return (*this);
  } // mouse_input::operator=(mouse_input)

  int which_button(unsigned change)
  {
    for(int i = 0; i < 5; ++i, change >>= 1)
    {
      if( change & 1 )
      {
        return i;
      }
    }
    return -1;
  }
  
  bool mouse_input::handle_mouse_event(int x, int y, unsigned state)
  {
    //    printf("handle_mouse_event(%d,%d,0x%06x)\n", x,y,state);
    
    // Notes: the way that this 'handled' variable is used should ALWAYS be put
    // on the RIGHT side of the ||, so as to avoid short circuiting.
    // CHECKME! If it is desirable to allow handling of 'release' to prevent
    // calling of 'clicked' or 'dragged', then this could be moved to the left
    // side.

    // Not initially handled... The callbacks must do that.
    bool handled = false;

    // Initialize stuff, so that everything will work properly.
    if( !valid_data )
    {
      last_state = 0;
      
      mouse_x = x;
      mouse_y = y;

      valid_data = true;
    }

    // Store current stuff as previous
    last_x = mouse_x;
    last_y = mouse_y;

    // Store new stuff as current.
    mouse_x = x;
    mouse_y = y;
    
    // Find all differences in buttons...
    unsigned state_difference = (last_state ^ state);
    last_state = state;
    
    // If there is a button difference... Either a press or release.
    unsigned button_state_change = state_difference & mouse_button_mask;
    if( button_state_change != 0 )
    {
      if( state & button_state_change )
      {
        // It was a press!
        int button_pressed = which_button(button_state_change);
        if( button_pressed >= 0 )
        {
          press_data[button_pressed].x = mouse_x;
          press_data[button_pressed].y = mouse_y;
          press_data[button_pressed].press_state = state;
        }
        handled = mouse_pressed(mouse_x, mouse_y, state, state_difference) || handled;
      } // if a press
      else
      {
        // It was a release!
        handled = mouse_released(x,y,state,state_difference) || handled;

        // Check to see if it could be a click...
        int button_released = which_button(button_state_change);

        if( button_released >= 0 )
        {
          int diff_x = x - press_data[button_released].x;
          int diff_y = y - press_data[button_released].y;
          
          if( ((diff_x <  maximum_click_distance) &&
               (diff_x > -maximum_click_distance)) &&
              ((diff_y <  maximum_click_distance) &&
               (diff_y > -maximum_click_distance)) )
          {
            // It's a click!
            handled = mouse_clicked(x, y,
                                    press_data[button_released].press_state,
                                    state) || handled;
          }
          else
          {
            // It's a drag!
            // Reset the state difference to be that between when it was
            // pressed and when it was released.
            state_difference = (press_data[button_released].press_state ^ state);
            
            handled = mouse_dragged(press_data[button_released].x,
                                    press_data[button_released].y,
                                    mouse_x, mouse_y, state_difference) || handled;
          }
        } // button >= 0 (if it's valid)
      } // if a release
    } // button changed
    else
    {
      // Just a mouse movement...
      handled = mouse_moved(mouse_x, mouse_y,
                            mouse_x - last_x,
                            mouse_y - last_y) || handled;
    } // no buttons changed
    
    return handled;
  } // mouse_input::handle_mouse_event(int,int,int)


  unsigned mouse_input::get_button_state() const
  {
    if( valid_data )
    {
      return last_state;
    }
    return 0;
  } // mouse_input::get_button_state()

  bool mouse_input::get_mouse_position(int& x, int& y) const
  {
    if( valid_data )
    {
      x = mouse_x;
      y = mouse_y;
      return true;
    }
    return false;
    
  } // mouse_input::get_mouse_position(int,int)
  
  bool mouse_input::get_last_position(int& x, int& y) const
  {
    if( valid_data )
    {
      x = last_x;
      y = last_y;
      return true;
    }
    return false;
  } // mouse_input::get_last_position(int,int)
  
} // namespace manygames

