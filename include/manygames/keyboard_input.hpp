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
    Allow iterations over name overrides, for storing in config file, etc.
    Allow removal of name overrides.
    Allow iteration over currently pressed keys...
*/


#if       !defined(__MANYGAMES__KEYBOARD_INPUT_HPP__)
#define            __MANYGAMES__KEYBOARD_INPUT_HPP__

#include <sigc++/sigc++.h>
#include <map>
#include <string>
#include <vector>
#include <utility>

namespace manygames
{ 

// BEGIN(DELETEME)
//-----------------------------------------------------------
//#error You must customize this automatically generated class.
// To do this, you must: 
// (1) Enter a class description below, on the line requested.
// (2) Add your own class members to the class.
// (3) Provide the required operations in the copy constructor and assignment
//  operator (in the corresponding .cpp file).
//-----------------------------------------------------------
// END(DELETEME)

  /**
   * 
   * A basic class for keyboard input (to be subclassed by the class which
   * actually has the capibility to detect keyboard stuff). 
   * 
   * @author Kevin Harris <kpharris@users.sourceforge.net>
   * @version $Revision$
   * 
   */
  class keyboard_input
  {
  public:
    enum KeyboardModifiers { keyboard_left_control  = 1 << 0,
			     keyboard_left_shift    = 1 << 1,
			     keyboard_left_mod1     = 1 << 2,
			     keyboard_left_mod2     = 1 << 3,
			     keyboard_left_mod3     = 1 << 4,
			     keyboard_left_mod4     = 1 << 5,
			     keyboard_left_mod5     = 1 << 6,
			     keyboard_right_control = 1 << 8,
			     keyboard_right_shift   = 1 << 9,
			     keyboard_right_mod1    = 1 << 10,
			     keyboard_right_mod2    = 1 << 11,
			     keyboard_right_mod3    = 1 << 12,
			     keyboard_right_mod4    = 1 << 13,
			     keyboard_right_mod5    = 1 << 14,
			     keyboard_capslock      = 1 << 15,
			     keyboard_key_pressed   = 1 << 16,
			     keyboard_control       = keyboard_left_control | keyboard_right_control,
			     keyboard_shift         = keyboard_left_shift   | keyboard_right_shift,
			     keyboard_mod1          = keyboard_left_mod1    | keyboard_right_mod1,
			     keyboard_mod2          = keyboard_left_mod2    | keyboard_right_mod2,
			     keyboard_mod3          = keyboard_left_mod3    | keyboard_right_mod3,
			     keyboard_mod4          = keyboard_left_mod4    | keyboard_right_mod4,
			     keyboard_mod5          = keyboard_left_mod5    | keyboard_right_mod5
    };
  private:
    bool allow_repeat;
    
  protected:
    virtual bool handle_keyboard_event(unsigned button, unsigned modifiers);

    // Map a key (currently held) to the modifiers held when it was pressed.
    std::map<unsigned, unsigned> buttons_currently_held;

  public:
    /** Default constructor */
    keyboard_input();

    /** Destructor */
    virtual ~keyboard_input();

    /** Copy constructor */
    keyboard_input(const keyboard_input& old);

    /** Assignment operator */
    keyboard_input& operator= (const keyboard_input& old);

    // Would return something like "A", "W", "Tab", etc.  That is, for printable characters, it SHOULD return the single character that it represents.  For longer keys, it would be the 
    virtual std::string keyname(unsigned key) const = 0;
    // would return something like "CTRL+A" (short) or "Shift+Z", "Mod1+Control+I" (normal)
    virtual std::string keyname(unsigned key, unsigned modifiers, bool shortened) const = 0;

    // Force the key name for the given key to be displayed as new_name
    // (only while the overridden class is still active). 
    virtual void override_keyname(unsigned key, const std::string& new_name) = 0;
    // Force the key name for the given key, ONLY when the given modifiers are attached.
    virtual void override_keyname(unsigned key, unsigned modifiers, const std::string& new_name) = 0;


    void disable_repeat() { allow_repeat = false; }
    void enable_repeat()  { allow_repeat = true; }
    bool repeat_enabled() const { return allow_repeat; }

    bool key_down(unsigned key) const;
    bool key_down(unsigned key, unsigned& modifiers) const;
    unsigned num_keys_down() const;
    std::vector<std::pair<unsigned,unsigned> > get_all_held_keys() const;
    
    // bool keyboard_pressed(unsigned key, unsigned modifiers)
    // bool keyboard_released(unsigned key, unsigned press_modifiers, unsigned release_modifiers)
    SigC::Signal2<bool,unsigned,unsigned> key_pressed; 
    SigC::Signal3<bool,unsigned,unsigned,unsigned> key_released;    
    
  }; // class keyboard_input

} // namespace manygames


#endif /* !defined(__MANYGAMES__KEYBOARD_INPUT_HPP__) */

