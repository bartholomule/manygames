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

#if       !defined(__MANYGAMES__INPUT_WINDOW_HPP__)
#define            __MANYGAMES__INPUT_WINDOW_HPP__

// --------------------------------------
// Include of parent class headers
// --------------------------------------
#include <manygames/mouse_input.hpp>
#include <manygames/keyboard_input.hpp>
#include <manygames/framebuffer.hpp>
#include <sigc++/sigc++.h>

namespace manygames
{ 

  /**
   * 
   * A class which combines a framebuffer with the ability to accept input.
   * Note that this class MUST be changed at some point in the future, as I
   * need MUCH more flexible input methods (KB, JS, mouse, whatever).
   * 
   * @author Kevin Harris <kpharris@users.sourceforge.net>
   * @version $Revision$
   * 
   */
  template <class T>
  class input_window : public framebuffer<T>, public mouse_input, public keyboard_input
  {

  private:

  protected:

  public:
    /** Default constructor */
    input_window();

    /** Default constructor */
    input_window(int width, int height);    

    /** Destructor */
    virtual ~input_window();

    /** Copy constructor */
    input_window(const input_window& old);

    /** Assignment operator */
    input_window& operator= (const input_window& old);

    virtual void update() { buffer_update(); }

    /** Enter the main message loop, returning only when the program is
        terminated, or if quit_window() below is called. . */
    virtual void run_window() = 0;

    /** Terminate any running message loop from above, allowing it to return.
        Note that this will close the window completely, so it should only be
        called when appropriate. */
    virtual void quit_window() = 0;
    
    SigC::Signal0<void> buffer_update;
    
  }; // class input_window

  //-------------------------------------------
  // Default constructor for class input_window
  //-------------------------------------------
  template <class T>  
  input_window<T>::input_window():
    framebuffer<T>(),
    mouse_input(),
    keyboard_input()
  {
  
  } // input_window()

  template <class T>  
  input_window<T>::input_window(int width, int height):
    framebuffer<T>(),
    mouse_input(),
    keyboard_input()
  {
    framebuffer<T>::resize(width, height);
  } // input_window()

  //----------------------------------
  // Destructor for class input_window
  //----------------------------------
  template <class T>
  input_window<T>::~input_window()
  {
  
  } // ~input_window()

  //----------------------------------------
  // Copy constructor for class input_window
  //----------------------------------------
  template <class T>
  input_window<T>::input_window(const input_window<T>& old):
    framebuffer<T>(old),
    mouse_input(old),
    keyboard_input(old)
  {

  } // input_window(input_window)

  //-------------------------------------------
  // Assignment operator for class input_window
  //-------------------------------------------
  template <class T>
  input_window<T>& input_window<T>::operator= (const input_window<T>& old)
  {
    // Generic check for self-assignment
    if( &old != this)
    {
      framebuffer<T>::operator=(old);
      mouse_input::operator=(old);
      keyboard_input::operator=(old);      
    }
    return (*this);
  } // input_window::operator=(input_window)
  
} // namespace manygames


#endif /* !defined(__MANYGAMES__INPUT_WINDOW_HPP__) */

