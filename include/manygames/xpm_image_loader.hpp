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

#if       !defined(__MANYGAMES__XPM_IMAGE_LOADER_HPP__)
#define            __MANYGAMES__XPM_IMAGE_LOADER_HPP__

#include <cstdio>
#include <cstring>
#include <cassert>
#include <map>
#include <utility>
#include <algorithm>
#include <manygames/rgbcolor.hpp>
#include <manygames/masked_image.hpp>
#include <manygames/image_converter.hpp>

namespace manygames
{
  // ----------------------------------------------------------------------
  // Converts an XPM text array (as per the output of YYYtoxpm), to a masked
  // image.  
  // ----------------------------------------------------------------------
  template <class T, class mask_base>
  masked_image<T, mask_base> xpm_convert_image(const char*const* xpm_text);

  
  // Internally used function! Do not call!
  template <class T>
  std::pair<std::string, rgbcolor<T> > get_color_def(const char* line_text, unsigned chars_per_pixel, bool& is_color)
  {
    std::pair<std::string, rgbcolor<T> > retval;
    is_color = false;

    if( line_text )
    {
      //      printf("I'm supposed to parse the line \"%s\"\n", line_text);
    
      std::string s;
      for(unsigned i = 0; i < chars_per_pixel; ++i)
      {
	s += *(line_text++);
      }
      
      retval.first = s;
      //      printf("I found the string \"%s\"\n", s.c_str());
      
      // eat up white space...
      while(isspace(*line_text))
      {
	++line_text;
      }

      //      printf("The next character is '%c'\n", *line_text);
      if(*line_text != 'c')
      {
	is_color = false;
	return retval;
      }
      ++line_text;

      // eat up white space...
      while(isspace(*line_text))
      {
	++line_text;
      }

      if( *line_text == '#' )
      {
	std::string r_text, g_text, b_text;
	++line_text;

	int text_len = strlen(line_text);

	// Sanity check... Make sure there's enough space for all 6 bytes (or 12)...
	if( text_len >= 6 )
	{
	  r_text += *(line_text++);
	  r_text += *(line_text++);
	  
	  if( text_len >= 12 )
	  {
	    r_text += *(line_text++);
	    r_text += *(line_text++);
	  }
	  
	  g_text += *(line_text++);
	  g_text += *(line_text++);

	  if( text_len >= 12 )
	  {
	    g_text += *(line_text++);
	    g_text += *(line_text++);
	  }
	  
	  b_text += *(line_text++);
	  b_text += *(line_text++);

	  if( text_len >= 12 )
	  {	  
	    b_text += *(line_text++);
	    b_text += *(line_text++);
	  }

	  //	  printf("In parsing: r=\"%s\", g=\"%s\", b=\"%s\"\n", r_text.c_str(), g_text.c_str(), b_text.c_str());
	  
	  unsigned long r = strtoul(r_text.c_str(), NULL, 16);
	  unsigned long g = strtoul(g_text.c_str(), NULL, 16);
	  unsigned long b = strtoul(b_text.c_str(), NULL, 16);
	  //	  printf("r=%d, g=%d, b=%d\n", r, g, b);

	  if( text_len >= 12 )
	  {
	    double rd = double(r) / (unsigned long) 0xFFFF;
	    double gd = double(g) / (unsigned long) 0xFFFF;
	    double bd = double(b) / (unsigned long) 0xFFFF;
	    //	    printf("rd=%f, gd=%f, bd=%f\n", rd, gd, bd);
	    retval.second = convert_color<T>(rgbcolor<double>(rd,gd,bd));
	  }
	  else
	  {
	    retval.second = convert_color<T>(rgbcolor<unsigned char>(r,g,b));
	  }
	  
	  is_color = true;
	}
      }
      else if( line_text == std::string("None") )
      {
	is_color = false;
	retval.second.set(0,0,0);
      }
    }
    return retval;
  }
  
  template <class T, class mask_base>
  masked_image<T, mask_base> xpm_convert_image(const char*const* xpm_text)
  {
    masked_image<T, mask_base> ret_image;
    if( !xpm_text || !*xpm_text )
    {
      return ret_image;
    }
    const char *const * xpm_text_ptr = xpm_text;
    
    unsigned width, height;
    unsigned num_colors, chars_per_pixel;

    const char* source_line = *(xpm_text_ptr++);

    // Read the header.....
    assert(sscanf(source_line, "%u %u %u %u", &width, &height, &num_colors, &chars_per_pixel) == 4);

    std::map<std::string, rgbcolor<T> > color_map;
    std::list<std::string> empty_items;

    // Parse color map data...
    for(unsigned color = 0; color < num_colors; ++color)
    {
      const char* line_text = *(xpm_text_ptr++);

      bool is_color = false;
      std::pair<std::string, rgbcolor<T> > value = get_color_def<T>(line_text, chars_per_pixel, is_color);

      if( !value.first.empty() )
      {
	if( is_color )
	{
	  //	  printf("Defining color \"%s\" to be %f,%f,%f\n", value.first.c_str(), double(value.second.r()), double(value.second.g()), double(value.second.b()));
	  color_map[value.first] = value.second;
	}
	else
	{
	  //	  printf("\"%s\" doesn't appear to be in color format!\n", value.first.c_str());
	  empty_items.push_back(value.first);
	}
      }
      
    }

    rgbcolor<T> black(0,0,0);

    ret_image.resize(width, height, 0, 0, black, mask_base(0));
    
    // Parse the pixel data...

    //    printf("Parsing pixel data...\n");
    for(unsigned y = 0; y < height; ++y)
    {
      const char* line_text = *(xpm_text_ptr++);
      const int line_length = strlen(line_text);
      
      unsigned items_to_read = std::min(width, line_length / chars_per_pixel); 
      
      unsigned x = 0;
      //      printf("Need to read %d items...\n", items_to_read);
      for(; x < items_to_read; ++x)
      {
	std::string s;
	for(unsigned i = 0; i < chars_per_pixel; ++i)
	{
	  s += *(line_text++);
	}
	//	printf("Pixel (%d,%d)=%s ", x,y,s.c_str());
	
	typename std::map<std::string, rgbcolor<T> >::const_iterator it = color_map.find(s);
	if( it != color_map.end() )
	{
	  //	  printf("It's a color: %f,%f,%f",double(it->second.r()),double(it->second.g()),double(it->second.b()));
	  ret_image(x,y) = it->second;
	  ret_image.mask(x,y) = mask_base(1);
	}
	else if( std::find(empty_items.begin(), empty_items.end(), s) != empty_items.end() )
	{
	  ret_image(x,y) = black;
	  ret_image.mask(x,y) = mask_base(0);
	}
	else
	{
	  // FIXME!
	  // Warning: string not found!
	  // For now, blank it
	  ret_image(x,y) = black;
	  ret_image.mask(x,y) = mask_base(0);
	}
	//	printf("\n");
      }

      for(; x < width; ++x)
      {
	ret_image(x,y) = black;
	ret_image.mask(x,y) = mask_base(0);
      }
    } // y loop

    return ret_image;
  } // xpm_convert_image(char**)
  
} // namespace manygames


#endif /* !defined(__MANYGAMES__XPM_IMAGE_LOADER_HPP__) */
