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
#include "x_input_window.hpp"
#include <cassert>

namespace manygames
{ 

  //------------------------------------------------
  // Default constructor for class x_input_window
  //------------------------------------------------
  x_input_window::x_input_window(int width, int height, Display* disp, int scr) :
    input_window<unsigned char>(width, height),
    display(disp),
    screen(scr),
    img(NULL),
    image_buffer(NULL)
  {
    if( !display )
    {
      display = XOpenDisplay((char*)0);
      if( display )
      {
	screen = DefaultScreen(display);
      
	display_created = true;
      }
    }
    if( display )
    {
      if( screen < 0 )
      {
	screen = DefaultScreen(display);
      }
      
      unsigned long black, white;
      
      black = BlackPixel(display, screen);
      white = WhitePixel(display, screen);
      
      unsigned long border_color = black;
      int border_width = 5;
      unsigned long background = white;
      
      window = XCreateSimpleWindow(display, DefaultRootWindow(display), 0, 0,
				   width, height, border_width, border_color,
				   background);
      
      XSetStandardProperties(display, window,
			     "Default window title",
			     "Minimized window title",
			     None,
			     NULL,0,NULL); // Hints, params (argc,argv), etc.
      
      XSelectInput(display, window,
		   ExposureMask |
		   ButtonPressMask | ButtonReleaseMask |
		   KeyPressMask | KeyReleaseMask |
		   PointerMotionMask |
		   Button1MotionMask | Button2MotionMask | Button3MotionMask |
		   Button4MotionMask | Button5MotionMask);
      
      gc = XCreateGC(display, window, 0, 0);
      XSetBackground(display, gc, black);
      XSetForeground(display, gc, white);
      XClearWindow(display, window);
      XMapRaised(display, window);
    }    
  } // x_input_window()

  //---------------------------------------
  // Destructor for class x_input_window
  //---------------------------------------
  x_input_window::~x_input_window()
  {
    if( img )
    {
      XDestroyImage(img);
      img = NULL;
    }

    if( display )
    {
      XFreeGC(display, gc);
      XDestroyWindow(display, window);
      
      if( display_created )
      {
	XCloseDisplay(display);
      }
    }
  } // ~x_input_window()


  void x_input_window::draw()
  {
    if( display && img )
    {
      unsigned width = get_width();
      unsigned height = get_height();
      unsigned* image_buf2 = reinterpret_cast<unsigned*>(image_buffer);
      const unsigned char* image_data = foreground->reinterpret<unsigned char*>();
      for(unsigned y = 0; y < height; ++y)
      {
	unsigned y_offset = y * width;
	for(unsigned x = 0; x < width; ++x)
	{
	  unsigned linear = y_offset + x;
	  image_buf2[linear] = ( unsigned(image_data[linear*3 + 0]) << 16 |
				 unsigned(image_data[linear*3 + 1]) << 8 |
				 unsigned(image_data[linear*3 + 2]) << 0 );
	}
      }
      
      // Draw it to the screen now (ignore any errors here)...
      XPutImage(display, window, gc, img,
		0, 0, // Source X & Y (useful for subimages)
		0, 0, // Dest   X & Y
		width, height); // Width and height to draw (useful for subimages)          
    }
  }

  unsigned translate_x_state(int button, unsigned state, unsigned previous_state)
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

    if( state & ShiftMask )
    {
      result |= mouse_input::mouse_shift_down;
    }
    if( state & LockMask )
    {
      result |= mouse_input::mouse_capslock_on;
    }

    assert( (ControlMask == (1 << 2)) &&
            (Mod1Mask    == (1 << 3)) &&
            (Mod2Mask    == (1 << 4)) &&
            (Mod3Mask    == (1 << 5)) &&
            (Mod4Mask    == (1 << 6)) &&
            (Mod5Mask    == (1 << 7)) );

    assert( (mouse_input::mouse_control_down == (1 << 6)) &&
            (mouse_input::mouse_alt_down     == (1 << 7)) &&
            (mouse_input::mouse_numlock_on   == (1 << 8)) &&
            (mouse_input::mouse_mod3_down    == (1 << 9)) &&
            (mouse_input::mouse_super_down   == (1 << 10)) &&
            (mouse_input::mouse_mod5_down    == (1 << 11)) );

    result |= ((state >> 2) & 0x3F) << 6;

    return result;
  }


  void x_input_window::size_change_check()
  {
    if( display )
    {
      bool size_changed = false;
      
      int x, y;
      unsigned width, height, border, depth;
      Window root;
      
      x = y = width = height = border = depth;
      
      XGetGeometry(display, window, &root, &x, &y, &width, &height, &border, &depth);
      
      //    printf("Geometry returned x,y=[%d,%d], w,h=[%d,%d], b=%d, d=%d\n", x, y, width, height, border, depth);
      
      if( (width != get_width()) || (height != get_height()) )
      {
	resize(width, height);
	size_changed = true;
      }
      
      // If the size changed...
      if( size_changed || !img || !image_buffer )
      {
	int bytes_per_pixel = 4;
	
	if( (get_width() > 0) && (get_height() > 0) )
	  
	{
	  if( img )
	  {
	    XDestroyImage(img);
	    img = NULL;
	  }
	  image_buffer = (unsigned char*)malloc(get_width() * get_height() * bytes_per_pixel);
	  
	  img = XCreateImage(display,
			     XDefaultVisual(display, screen),
			     depth, // This one has to match the depth of
			     // the screen or a crash will happen. 
			     ZPixmap,
			     0,  // offset...
			     (char*)image_buffer,
			     get_width(), get_height(),
			     32, // bits per pixel (32 for 24 bit image)
			     0); // Scanline width
	}
	else
	{
	  if( img )
	  {
	    XDestroyImage(img);
	    img = NULL;
	  }
	  image_buffer = NULL;
	}
      }
    } // display is valid...
  }

  static unsigned keyboard_key_translate(unsigned key)
  {
    // FIXME! Do whatever translation is required.
    return key;
  }

  static unsigned keyboard_state_translate(unsigned state)
  {
    unsigned translated_state = 0;
    
    if( state & ShiftMask )
    {
      state &= ~ShiftMask;
      translated_state |= keyboard_input::keyboard_shift;
    }
    if( state & ControlMask )
    {
      state &= ~ControlMask;      
      translated_state |= keyboard_input::keyboard_control;
    }
    if( state & LockMask )
    {
      state &= ~LockMask;
      translated_state |= keyboard_input::keyboard_capslock;
    }
    if( state & Mod1Mask )
    {
      state &= ~Mod1Mask;
      translated_state |= keyboard_input::keyboard_alt;
    }
    if( state & Mod2Mask )
    {
      state &= ~Mod2Mask;
      translated_state |= keyboard_input::keyboard_numlock;
    }
    if( state & Mod3Mask )
    {
      state &= ~Mod3Mask;
      translated_state |= keyboard_input::keyboard_mod3;
    }
    if( state & Mod4Mask )
    {
      state &= ~Mod4Mask;
      translated_state |= keyboard_input::keyboard_super;
    }
    if( state & Mod5Mask )
    {
      state &= ~Mod5Mask;
      translated_state |= keyboard_input::keyboard_mod5;
    }    

    // FIXME! Do whatever remaining translation is required.
    return (state << 16) | translated_state;
  }  

  void x_input_window::run_window()
  {
    // Event loop!
    
    XEvent event;		/* the XEvent declaration !!! */
    KeySym key;		/* something to aid in handling KeyPress Events */
    char text[255];	/* a buffer for KeyPress Events (as text)*/
    
    /* look for events forever... */
    while( display )
    {		
      /* get the next event and stuff it into our event variable.
	 Note:  only events we set the mask for are detected!
      */
      XNextEvent(display, &event);
      
      switch( event.type )
      {
      case Expose:
	if( event.xexpose.count == 0 )
	{
	  /* the window was exposed redraw it! */
	  size_change_check();
	  update();
	  draw();
	}
	break;
      case KeyPress:
	{
	  // Note: I don't actually care if the lookup was successful.  All I 
	  // want this to do is to get the key symbol (button) filled in, so
	  // that it can be used. I'm generating my own strings anyways.
	  XLookupString(&event.xkey,text,255,&key,0);
	  handle_keyboard_event(keyboard_key_translate(key),
				keyboard_state_translate(event.xkey.state) |
				keyboard_input::keyboard_key_pressed);
	}
	break;
      case KeyRelease:
	{
	  // See comments for key press above.
	  XLookupString(&event.xkey,text,255,&key,0) != NoSymbol;
	  handle_keyboard_event(keyboard_key_translate(key),
				keyboard_state_translate(event.xkey.state) &
				~keyboard_input::keyboard_key_pressed);
	}
	break;
      case ButtonPress:
	{
	  /* tell where the mouse Button was Pressed */
	  int x=event.xbutton.x;
	  int y=event.xbutton.y;
	  unsigned state = event.xbutton.state;
	  unsigned button = event.xbutton.button;
	  
	  state = translate_x_state(button, state, get_button_state());

	  handle_mouse_event(x,y,state);
	}
	break;
      case ButtonRelease:
	{
	  /* tell where the mouse Button was Released */
	  int x=event.xbutton.x;
	  int y=event.xbutton.y;
	  unsigned state = event.xbutton.state;
	  unsigned button = event.xbutton.button;
	  
	  state = translate_x_state(-button, state, get_button_state());

	  handle_mouse_event(x,y,state);	  
	}
	break;
      case MotionNotify:
	{
	  /* tell where the mouse is currently located */
	  int x=event.xmotion.x;
	  int y=event.xmotion.y;

	  unsigned state = translate_x_state(0, event.xmotion.state, get_button_state());
	  handle_mouse_event(x,y,state);
	}
	break;      
      default:
	{
	  printf("X supplied event type %d\n", event.type);
	}
	break;	
      }
    } // while 1
  }

  void x_input_window::quit_window()
  {
    if( img )
    {
      XDestroyImage(img);
      img = NULL;
    }
    
    if( display )
    {
      XFreeGC(display, gc);
      XDestroyWindow(display, window);
      
      if( display_created )
      {
	XCloseDisplay(display);
      }      
    }
    display = NULL;
  }  
  
} // namespace manygames

