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

#include <manygames_config.hpp>
#include <manygames/textized.hpp>
#include "gtkmm_input_window.hpp"
#include <cassert>


namespace manygames
{ 

  //------------------------------------------------
  // Default constructor for class gtkmm_input_window
  //------------------------------------------------
  gtkmm_input_window::gtkmm_input_window():
    input_window<guchar>(),
    Gtk::DrawingArea()
  {
    set_flags(Gtk::CAN_FOCUS);    
    add_events(Gdk::KEY_PRESS_MASK | Gdk::KEY_RELEASE_MASK);
    add_events(Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK | Gdk::POINTER_MOTION_MASK);
    //    add_events(Gdk::VISIBILITY_NOTIFY_MASK);
    
  } // gtkmm_input_window()

  //---------------------------------------
  // Destructor for class gtkmm_input_window
  //---------------------------------------
  gtkmm_input_window::~gtkmm_input_window()
  {
  
  } // ~gtkmm_input_window()

  //---------------------------------------------
  // Copy constructor for class gtkmm_input_window
  //---------------------------------------------
  gtkmm_input_window::gtkmm_input_window(const gtkmm_input_window& old):
    input_window<guchar>(old)
  {
    add_events(Gdk::BUTTON_PRESS_MASK);
    add_events(Gdk::BUTTON_RELEASE_MASK);
    add_events(Gdk::POINTER_MOTION_MASK);
  } // gtkmm_input_window(gtkmm_input_window)

  //------------------------------------------------
  // Assignment operator for class gtkmm_input_window
  //------------------------------------------------
  gtkmm_input_window& gtkmm_input_window::operator= (const gtkmm_input_window& old)
  {
    // Generic check for self-assignment
    if( &old != this)
    {

      input_window<guchar>::operator=(old);
      
      // Gtk::DrawingArea::operator=(old);
    }
    return (*this);
  } // gtkmm_input_window::operator=(gtkmm_input_window)

  void gtkmm_input_window::draw()
  {
    if( is_drawable() && (get_width() != 0) && (get_height() != 0) )
    {
      Glib::RefPtr<Gdk::Window> window = get_window();
      
      window->draw_rgb_image(get_style()->get_fg_gc(Gtk::STATE_NORMAL),
			     0, 0,
			     foreground->get_width(), foreground->get_height(),
			     Gdk::RGB_DITHER_MAX,
			     foreground->reinterpret<guchar*>(),
			     foreground->get_width() * 3);
    }
    else
    {
      printf("draw() called, but it is not yet drawable...\n");
    }
  }
  
  unsigned translate_gtk_state(int button, unsigned state, unsigned previous_state)
  {
    // Note: I have put assertions in here, even for my own constants, so that
    // this function will detect changes (and let me know) if I change my
    // constants, or the GDK constants change. 
    unsigned result = 0;

    // Translate the buttons....
    assert( (mouse_input::mouse_button_1 == (1 << 0)) &&
            (mouse_input::mouse_button_2 == (1 << 1)) &&
            (mouse_input::mouse_button_3 == (1 << 2)) &&
            (mouse_input::mouse_button_4 == (1 << 3)) &&
            (mouse_input::mouse_button_5 == (1 << 4)) );    

    if( button > 0 )    // press
    {
      result |= previous_state & mouse_input::mouse_button_mask;
      result |= 1 << (button - 1);
    }
    else if(button < 0) // release
    {
      result |= previous_state & mouse_input::mouse_button_mask;
      result &= ~(1 << (-button - 1));
    }
    else
    {
      result |= previous_state & mouse_input::mouse_button_mask;
    }

    if( state & GDK_SHIFT_MASK )
    {
      result |= mouse_input::mouse_shift_down;
    }
    if( state & GDK_LOCK_MASK )
    {
      result |= mouse_input::mouse_capslock_down;
    }

    assert( (GDK_CONTROL_MASK == (1 << 2)) &&
            (GDK_MOD1_MASK    == (1 << 3)) &&
            (GDK_MOD2_MASK    == (1 << 4)) &&
            (GDK_MOD3_MASK    == (1 << 5)) &&
            (GDK_MOD4_MASK    == (1 << 6)) &&
            (GDK_MOD5_MASK    == (1 << 7)) );

    assert( (mouse_input::mouse_control_down == (1 << 6)) &&
            (mouse_input::mouse_mod1_down    == (1 << 7)) &&
            (mouse_input::mouse_mod2_down    == (1 << 8)) &&
            (mouse_input::mouse_mod3_down    == (1 << 9)) &&
            (mouse_input::mouse_mod4_down    == (1 << 10)) &&
            (mouse_input::mouse_mod5_down    == (1 << 11)) );

    result |= ((state >> 2) & 0x3F) << 6;

    return result;
  }
  
  bool gtkmm_input_window::on_button_press_event(GdkEventButton* event)
  {
    int x = (int)event->x;
    int y = (int)event->y;
    unsigned button = event->button;
    unsigned state = translate_gtk_state(button, event->state, get_button_state());

    // Add the old state back in....
    //    state |= get_button_state() & get_button_mask();

    return handle_mouse_event(x,y,state);
  }

  bool gtkmm_input_window::on_button_release_event(GdkEventButton* event)
  {
    int x = (int)event->x;
    int y = (int)event->y;
    unsigned button = event->button;
    unsigned state = translate_gtk_state(-button, event->state, get_button_state());

    // Add the old state back in....
    //    state |= get_button_state() & get_button_mask();
    // Remove the button from it...
    //    state &= ~(1 << (button - 1));
    
    return handle_mouse_event(x,y,state);
  }

  bool gtkmm_input_window::on_motion_notify_event(GdkEventMotion* event)
  {
    int x = (int)event->x;
    int y = (int)event->y;
    unsigned state = translate_gtk_state(0, event->state, get_button_state());
                      //  |  (get_button_state() & get_button_mask()));
    return handle_mouse_event(x,y,state);
  }

  void gtkmm_input_window::size_change_check()
  {
    Glib::RefPtr<Gdk::Window> window = get_window();
    int x, y, width, height, depth;

    window->get_geometry(x,y,width,height,depth);
    if( (width != get_width()) || (height != get_height()) )
    {
      resize(width, height);
    }
  }

  static unsigned keyboard_key_translate(unsigned key)
  {
    // FIXME! Do whatever translation is required.
    return key;
  }

  static unsigned keyboard_state_translate(unsigned state)
  {
    unsigned translated_state = 0;

    assert( (GDK_CONTROL_MASK == (1 << 2)) &&
            (GDK_MOD1_MASK    == (1 << 3)) &&
            (GDK_MOD2_MASK    == (1 << 4)) &&
            (GDK_MOD3_MASK    == (1 << 5)) &&
            (GDK_MOD4_MASK    == (1 << 6)) &&
            (GDK_MOD5_MASK    == (1 << 7)) );

    if( state & GDK_SHIFT_MASK )
    {
      state &= ~GDK_SHIFT_MASK;
      translated_state |= keyboard_input::keyboard_shift;
    }
    if( state & GDK_CONTROL_MASK )
    {
      state &= ~GDK_CONTROL_MASK;      
      translated_state |= keyboard_input::keyboard_control;
    }
    if( state & GDK_LOCK_MASK )
    {
      state &= ~GDK_LOCK_MASK;
      translated_state |= keyboard_input::keyboard_capslock;
    }
    if( state & GDK_MOD1_MASK )
    {
      state &= ~GDK_MOD1_MASK;
      translated_state |= keyboard_input::keyboard_mod1;
    }
    if( state & GDK_MOD2_MASK )
    {
      state &= ~GDK_MOD2_MASK;
      translated_state |= keyboard_input::keyboard_mod2;
    }
    if( state & GDK_MOD3_MASK )
    {
      state &= ~GDK_MOD3_MASK;
      translated_state |= keyboard_input::keyboard_mod3;
    }
    if( state & GDK_MOD4_MASK )
    {
      state &= ~GDK_MOD4_MASK;
      translated_state |= keyboard_input::keyboard_mod4;
    }
    if( state & GDK_MOD5_MASK )
    {
      state &= ~GDK_MOD5_MASK;
      translated_state |= keyboard_input::keyboard_mod5;
    }    

    // FIXME! Do whatever remaining translation is required.
    return (state << 16) | translated_state;
  }  
  
  bool gtkmm_input_window::on_key_press_event(GdkEventKey* event)
  {
    handle_keyboard_event(keyboard_key_translate(event->keyval),
			  keyboard_state_translate(event->state) | keyboard_input::keyboard_key_pressed);
  }
  
  bool gtkmm_input_window::on_key_release_event(GdkEventKey* event)
  {
    handle_keyboard_event(keyboard_key_translate(event->keyval),
			  keyboard_state_translate(event->state) & ~keyboard_input::keyboard_key_pressed);    
  }


  std::string gtkmm_input_window::keyname(unsigned key) const
  {
    assert("finish this" == NULL);
  }

  std::string gtkmm_input_window::keyname(unsigned key, unsigned modifiers, bool shortened) const
  {
    assert("finish this" == NULL);
  }  

  void gtkmm_input_window::override_keyname(unsigned key, const std::string& new_name)
  {
    assert("finish this" == NULL);
  }
  
  void gtkmm_input_window::override_keyname(unsigned key, unsigned modifiers, const std::string& new_name)
  {
    assert("finish this" == NULL);
  }  
  
} // namespace manygames

