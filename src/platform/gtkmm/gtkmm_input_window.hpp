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

#if       !defined(__MANYGAMES__GTKMM_INPUT_WINDOW_HPP__)
#define            __MANYGAMES__GTKMM_INPUT_WINDOW_HPP__

// --------------------------------------
// Default include of parent class header
// --------------------------------------
#include <manygames/input_window.hpp>
#include <glib/gtypes.h>
#include <gtkmm/drawingarea.h>

namespace manygames
{ 

// BEGIN(DELETEME)
//-----------------------------------------------------------
//#error You must customize this automatically generated class.
// To do this, you must: 
// (1) Provide the proper include for class input_window<unsigned char> (above).
// (2) Enter a class description below, on the line requested.
// (3) Add your own class members to the class.
// (4) Provide the required operations in the copy constructor and assignment
//  operator (in the corresponding .cpp file).
//-----------------------------------------------------------
// END(DELETEME)

  /**
   * 
   * ***CLASS DESCRIPTION GOES HERE*** (multiple lines are ok)
   * 
   * @author Kevin Harris <kpharris@users.sourceforge.net>
   * @version $Revision$
   * 
   */
  class gtkmm_input_window : public input_window<guchar>,
			    public Gtk::DrawingArea 
  {

  private:

  protected:

  public:
    /** Default constructor */
    gtkmm_input_window();

    /** Destructor */
    virtual ~gtkmm_input_window();

    /** Copy constructor */
    gtkmm_input_window(const gtkmm_input_window& old);

    /** Assignment operator */
    gtkmm_input_window& operator= (const gtkmm_input_window& old);

    virtual void draw(); // overridden pure virtual function.

    virtual bool on_button_press_event(GdkEventButton* event);
    virtual bool on_button_release_event(GdkEventButton* event);  
    virtual bool on_motion_notify_event(GdkEventMotion* event);
    
    virtual bool on_expose_event(GdkEventExpose* e)
    {
      update(); /* temp */
      draw();
      return true;
    }    
  }; // class gtkmm_input_window

} // namespace manygames


#endif /* !defined(__MANYGAMES__GTKMM_INPUT_WINDOW_HPP__) */

