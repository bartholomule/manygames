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

#include <manygames/keyboard_input.hpp>


namespace manygames
{ 

  //---------------------------------------------
  // Default constructor for class keyboard_input
  //---------------------------------------------
  keyboard_input::keyboard_input():
    allow_repeat(true)
  {
  
  } // keyboard_input()

  //------------------------------------
  // Destructor for class keyboard_input
  //------------------------------------
  keyboard_input::~keyboard_input()
  {
  
  } // ~keyboard_input()

  //------------------------------------------
  // Copy constructor for class keyboard_input
  //------------------------------------------
  keyboard_input::keyboard_input(const keyboard_input& old) :
    allow_repeat(old.allow_repeat),
    buttons_currently_held(old.buttons_currently_held)    
  {
    // Insert any copy-assignment here. DELETEME
  } // keyboard_input(keyboard_input)

  //---------------------------------------------
  // Assignment operator for class keyboard_input
  //---------------------------------------------
  keyboard_input& keyboard_input::operator= (const keyboard_input& old)
  {
    // Generic check for self-assignment
    if( &old != this)
    {
      buttons_currently_held = old.buttons_currently_held;

    }
    return (*this);
  } // keyboard_input::operator=(keyboard_input)


  bool keyboard_input::handle_keyboard_event(unsigned button, unsigned modifiers)
  {
    std::map<unsigned,unsigned>::iterator current_location = buttons_currently_held.find(button);

    // Not previously held down...
    if( current_location == buttons_currently_held.end() )
    {
      if( modifiers & keyboard_input::keyboard_key_pressed )
      {
	buttons_currently_held[button] = modifiers;
	return key_pressed(button, modifiers);
      }
      else
      {
	// CHECKME!
	// Should the released signal be relayed, even though there were no buttons down?
	return key_released(button, 0, modifiers);
      }
    }
    else if( modifiers & keyboard_input::keyboard_key_pressed ) // down, but repeated
    {
      if( allow_repeat )
      {
	buttons_currently_held[button] = modifiers;
	return key_pressed(button, modifiers);
      }
      return true;
    }
    else // currently down, and being released...
    {
      unsigned press_mods = current_location->second;

      buttons_currently_held.erase(current_location);

      return key_released(button, press_mods, modifiers);
    }
  } // handle_keyboard_event()

  bool keyboard_input::key_down(unsigned key) const
  {
    return buttons_currently_held.find(key) != buttons_currently_held.end();
  }
  
  bool keyboard_input::key_down(unsigned key, unsigned& modifiers) const
  {
    std::map<unsigned,unsigned>::const_iterator i = buttons_currently_held.find(key);

    if( i != buttons_currently_held.end() )
    {
      modifiers = i->second;
      return true;
    }
    return false;
  }
  
  unsigned keyboard_input::num_keys_down() const
  {
    return buttons_currently_held.size();
  }
  
  std::vector<std::pair<unsigned,unsigned> > keyboard_input::get_all_held_keys() const
  {

    std::vector<std::pair<unsigned,unsigned> > retvec(buttons_currently_held.begin(),
						      buttons_currently_held.end());
    return retvec;
  }
  
} // namespace manygames

