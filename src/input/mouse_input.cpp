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
    press_state(old.press_state),
    release_state(old.release_state),
    maximum_click_distance(old.maximum_click_distance),
    valid_data(old.valid_data),
    clicked(old.clicked),
    dragged(old.dragged),
    moved(old.moved),
    pressed(old.pressed),
    released(old.released)    
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
      press_state = old.press_state;
      release_state = old.release_state;
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

    //    printf("state_difference=0x%06x (state=0x%06x, last=0x%06x)\n", state_difference, state, last_state);

    last_state = state;
    
    // If there is a button difference... Either a press or release.
    int button_changed = state_difference & MouseButtonMask;
    if( button_changed != 0 )
    {
      if( state & button_changed )
      {
        //      printf("Button %d changed (press)!\n", button_changed);
        // It was a press!
        press_state = state;
        press_x = mouse_x;
        press_y = mouse_y;
        handled = pressed(mouse_x, mouse_y, press_state, state_difference) || handled;
      }
      else
      {
        //      printf("Button %d changed (release)!\n", button_changed);
        
        // It was a release!
        release_state = state;
        handled = released(x,y,release_state,state_difference) || handled;

        // Check to see if it could be a click...
        int diff_x = x - press_x;
        int diff_y = y - press_y;

        if( ((diff_x <  maximum_click_distance) &&
             (diff_x > -maximum_click_distance)) &&
            ((diff_y <  maximum_click_distance) &&
             (diff_y > -maximum_click_distance)) )
        {
          // It's a click!
          handled = clicked(x, y, press_state, release_state) || handled;
        }
        else
        {
          // It's a drag!
          handled = dragged(press_x, press_y, mouse_x, mouse_y, state_difference) || handled;
        }
      }
    } // button changed
    else
    {
      // Just a mouse movement...
      handled = moved(mouse_x, mouse_y,
                      mouse_x - last_x,
                      mouse_y - last_y) || handled;
    }
    
    //    printf("\n");
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

