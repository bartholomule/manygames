#include <iostream>
using std::cout;
using std::endl;

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
#include "fb_test.hpp"



//--------------------------------------
// Default constructor for class fb_test
//--------------------------------------
fb_test::fb_test():
  manygames::gtkmm_framebuffer()
  // Class initializers go here. DELETEME
{
  x_shift = y_shift = 0;
  dragging = false;

  add_events(Gdk::BUTTON_PRESS_MASK);
  add_events(Gdk::BUTTON_RELEASE_MASK);
  add_events(Gdk::POINTER_MOTION_MASK);
  
} // fb_test()

//-----------------------------
// Destructor for class fb_test
//-----------------------------
fb_test::~fb_test()
{

} // ~fb_test()

//-----------------------------------
// Copy constructor for class fb_test
//-----------------------------------
fb_test::fb_test(const fb_test& old):
  manygames::gtkmm_framebuffer(old)
  // Class initializers go here. DELETEME
{
  // Insert any copy-assignment here. DELETEME
} // fb_test(fb_test)

//--------------------------------------
// Assignment operator for class fb_test
//--------------------------------------
fb_test& fb_test::operator= (const fb_test& old)
{
  // Generic check for self-assignment
  if( &old != this)
  {
    // Insert assignment here. DELETEME

    manygames::gtkmm_framebuffer::operator=(old);
  }
  return (*this);
} // fb_test::operator=(fb_test)



void fb_test::update()
{
   
  Glib::RefPtr<Gdk::Window> window = get_window();
  int width,height;
  window->get_size(width,height);

  // [FIXME] Find an event or signal to catch which will auto resize this
  // thing... 
  if( get_background().get_width() != width ||
      get_background().get_height() != height )
  {
    resize(width, height, false);
  }

  static const manygames::rgbcolor<unsigned char> red(255,0,0);
  static const manygames::rgbcolor<unsigned char> blue(0,0,255);
  for(int y = 0; y < height; ++y)
  {
    int distance = 0;
    for(int x = 0; x < width; ++x)
    {
      if( (((y - y_shift)* 2) & ((x - x_shift) * 2)) )
      {
	const double fraction = 1.0 / 3.0;
	int value = int(fraction * 255 +
			((255 *(1 - fraction)) * distance / float(width)));
	manygames::rgbcolor<unsigned char> temp(0, value, 0);
	setpixel_back(x,y,temp);
	++distance;
      }
      else
      {
	setpixel_back(x,y,blue);
	distance = 0;
      }
    }
  }
  flip();
}

bool fb_test::on_button_press_event(GdkEventButton* event)
{
  //  cout << "Button Press..." << endl;
  dragging = true;

  last_x = (int)event->x;
  last_y = (int)event->y;
  last_time = event->time;
  
  return true;
}

bool fb_test::on_button_release_event(GdkEventButton* event)
{
  int diff_x = (int)event->x - last_x;
  int diff_y = (int)event->y - last_y;
  
  x_shift += diff_x;
  y_shift += diff_y;
    
  //  cout << "Button release..." << endl;  
  update();
  draw();

  dragging = false;
  
  return true;
}
bool fb_test::on_motion_notify_event(GdkEventMotion* event)
{
  if( dragging )
  {
    //    cout << "Dragging... x=" << event->x << " y=" << event->y << endl;
    //    cout << "time=" << event->time - last_time << endl;

    if( (event->time - last_time) > 65 ) // no more than about 15fps...
    {
      //      cout << "drawn..." << endl;
      int diff_x = (int)event->x - last_x;
      int diff_y = (int)event->y - last_y;
      
      last_x = (int)event->x;
      last_y = (int)event->y;
      
      x_shift += diff_x;
      y_shift += diff_y;    
      update();
      draw();

      last_time = event->time;
    }
  }
  
  return true;
}


#include <gtkmm/main.h>
#include <gtkmm/window.h>

int main(int argc, char** argv)
{
   Gtk::Main kit(argc, argv);

   Gtk::Window win;

   fb_test fb;
   
   win.add(fb);
   fb.show();

   Gtk::Main::run(win);

   return 0;
}
