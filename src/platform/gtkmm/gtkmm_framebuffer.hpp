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

#if       !defined(__MANYGAMES__GTKMM_FRAMEBUFFER_HPP__)
#define            __MANYGAMES__GTKMM_FRAMEBUFFER_HPP__

// --------------------------------------
// Default include of parent class header
// --------------------------------------
#include "manygames/framebuffer.hpp"
#include <glib/gtypes.h>
#include <gtkmm/drawingarea.h>

namespace manygames
{ 

// BEGIN(DELETEME)
//-----------------------------------------------------------
//#error You must customize this automatically generated class.
// To do this, you must: 
// (1) Provide the proper include for class framebuffer<unsigned char> (above).
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
  class gtkmm_framebuffer : public framebuffer<guchar>,
			    public Gtk::DrawingArea 
  {

  private:

  protected:

  public:
    /** Default constructor */
    gtkmm_framebuffer();

    /** Destructor */
    virtual ~gtkmm_framebuffer();

    /** Copy constructor */
    gtkmm_framebuffer(const gtkmm_framebuffer& old);

    /** Assignment operator */
    gtkmm_framebuffer& operator= (const gtkmm_framebuffer& old);

    virtual void update() = 0;
    virtual void draw(); // overridden pure virtual function.

  }; // class gtkmm_framebuffer

} // namespace manygames


#endif /* !defined(__MANYGAMES__GTKMM_FRAMEBUFFER_HPP__) */

