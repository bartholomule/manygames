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
#include <manygames/textized.hpp>


namespace manygames
{

  //---------------------------------------------
  // Default constructor for class keyboard_input
  //---------------------------------------------
  keyboard_input::keyboard_input():
    allow_repeat(true),
    modifier_ignore_mask(0),
    keyname_overrides_with_modifier(),
    keyname_overrides(),
    modifier_name_overrides()
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
    modifier_ignore_mask(old.modifier_ignore_mask),
    buttons_currently_held(old.buttons_currently_held),
    keyname_overrides_with_modifier(old.keyname_overrides_with_modifier),
    keyname_overrides(old.keyname_overrides),
    modifier_name_overrides(old.modifier_name_overrides)
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

      modifier_ignore_mask = old.modifier_ignore_mask;
      allow_repeat = old.allow_repeat;
      buttons_currently_held = old.buttons_currently_held;

      keyname_overrides_with_modifier = old.keyname_overrides_with_modifier;
      keyname_overrides = old.keyname_overrides;
      modifier_name_overrides = old.modifier_name_overrides;

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

#include <ctype.h>

  std::string get_key_name(unsigned key)
  {
    // I noticed that the isprint function (or macro) ignores the upper bits,
    // so I have to qualify the if statement, checking to see if it is truly an
    // ascii printable character
    if( (key < 0x7F) && isprint(key) )
    {
      char s[2];
      s[0] = (char)key;
      s[1] = '\0';
      return std::string(s);
    }

    //----------------------------------------------
    // Non-Printable (or non-US keyboard) characters
    //----------------------------------------------
    switch(key)
    {
    case keyboard_input::KEY_backspace:      return intl("Backspace");
    case keyboard_input::KEY_tab:            return intl("Tab");
    case keyboard_input::KEY_return:         return intl("Return");

    case keyboard_input::KEY_insert:         return intl("Insert");
    case keyboard_input::KEY_delete:         return intl("Delete");
    case keyboard_input::KEY_home:           return intl("Home");
    case keyboard_input::KEY_end:            return intl("End");
    case keyboard_input::KEY_page_up:        return intl("PageUp");
    case keyboard_input::KEY_page_down:      return intl("PageDown");

    case keyboard_input::KEY_escape:         return intl("Escape");
    case keyboard_input::KEY_print:          return intl("Print");
    case keyboard_input::KEY_sys_req:        return intl("SysReq");
    case keyboard_input::KEY_scroll_lock:    return intl("ScrollLock");
    case keyboard_input::KEY_pause:          return intl("Pause");
    case keyboard_input::KEY_break:          return intl("Break");
    case keyboard_input::KEY_num_lock:       return intl("NumLock");

    case keyboard_input::KEY_left:           return intl("Left");
    case keyboard_input::KEY_right:          return intl("Right");
    case keyboard_input::KEY_up:             return intl("Up");
    case keyboard_input::KEY_down:           return intl("Down");


      // Function keys...:
    case keyboard_input::KEY_F1:             return intl("F1");
    case keyboard_input::KEY_F2:             return intl("F2");
    case keyboard_input::KEY_F3:             return intl("F3");
    case keyboard_input::KEY_F4:             return intl("F4");
    case keyboard_input::KEY_F5:             return intl("F5");
    case keyboard_input::KEY_F6:             return intl("F6");
    case keyboard_input::KEY_F7:             return intl("F7");
    case keyboard_input::KEY_F8:             return intl("F8");
    case keyboard_input::KEY_F9:             return intl("F9");
    case keyboard_input::KEY_F10:            return intl("F10");
    case keyboard_input::KEY_F11:            return intl("F11");
    case keyboard_input::KEY_F12:            return intl("F12");
    case keyboard_input::KEY_F13:            return intl("F13");
    case keyboard_input::KEY_F14:            return intl("F14");
    case keyboard_input::KEY_F15:            return intl("F15");
    case keyboard_input::KEY_F16:            return intl("F16");
    case keyboard_input::KEY_F17:            return intl("F17");
    case keyboard_input::KEY_F18:            return intl("F18");
    case keyboard_input::KEY_F19:            return intl("F19");
    case keyboard_input::KEY_F20:            return intl("F20");
    case keyboard_input::KEY_F21:            return intl("F21");
    case keyboard_input::KEY_F22:            return intl("F22");
    case keyboard_input::KEY_F23:            return intl("F23");
    case keyboard_input::KEY_F24:            return intl("F24");
    case keyboard_input::KEY_F25:            return intl("F25");
    case keyboard_input::KEY_F26:            return intl("F26");
    case keyboard_input::KEY_F27:            return intl("F27");
    case keyboard_input::KEY_F28:            return intl("F28");
    case keyboard_input::KEY_F29:            return intl("F29");
    case keyboard_input::KEY_F30:            return intl("F30");
    case keyboard_input::KEY_F31:            return intl("F31");
    case keyboard_input::KEY_F32:            return intl("F32");
    case keyboard_input::KEY_F33:            return intl("F33");
    case keyboard_input::KEY_F34:            return intl("F34");
    case keyboard_input::KEY_F35:            return intl("F35");

      //-----------------
      // Modifier keys...
      //-----------------
    case keyboard_input::KEY_shift_left:     return intl("Shift-L");
    case keyboard_input::KEY_shift_right:    return intl("Shift-R");
    case keyboard_input::KEY_control_left:   return intl("Control-L");
    case keyboard_input::KEY_control_right:  return intl("Control-R");
    case keyboard_input::KEY_caps_lock:      return intl("CapsLock");
    case keyboard_input::KEY_shift_Lock:     return intl("ShiftLock");

    case keyboard_input::KEY_meta_left:      return intl("Meta-L");
    case keyboard_input::KEY_meta_right:     return intl("Meta-R");
    case keyboard_input::KEY_alt_left:       return intl("Alt-L");
    case keyboard_input::KEY_alt_right:      return intl("Alt-R");
    case keyboard_input::KEY_super_left:     return intl("Super-L");
    case keyboard_input::KEY_super_right:    return intl("Super-R");
    case keyboard_input::KEY_hyper_left:     return intl("Hyper-L");
    case keyboard_input::KEY_hyper_right:    return intl("Hyper-R");


      // Keypad keys
    case keyboard_input::KEY_keypad_0:         return intl("kp_0");
    case keyboard_input::KEY_keypad_1:         return intl("kp_1");
    case keyboard_input::KEY_keypad_2:         return intl("kp_2");
    case keyboard_input::KEY_keypad_3:         return intl("kp_3");
    case keyboard_input::KEY_keypad_4:         return intl("kp_4");
    case keyboard_input::KEY_keypad_5:         return intl("kp_5");
    case keyboard_input::KEY_keypad_6:         return intl("kp_6");
    case keyboard_input::KEY_keypad_7:         return intl("kp_7");
    case keyboard_input::KEY_keypad_8:         return intl("kp_8");
    case keyboard_input::KEY_keypad_9:         return intl("kp_9");

    case keyboard_input::KEY_keypad_subtract:  return intl("kp_Subtract");
    case keyboard_input::KEY_keypad_multiply:  return intl("kp_Multiply");
    case keyboard_input::KEY_keypad_add:       return intl("kp_Add");
    case keyboard_input::KEY_keypad_divide:    return intl("kp_Divide");
    case keyboard_input::KEY_keypad_decimal:   return intl("kp_Decimal");
    case keyboard_input::KEY_keypad_equal:     return intl("kp_Equal");

    case keyboard_input::KEY_keypad_left:      return intl("kp_Left");
    case keyboard_input::KEY_keypad_right:     return intl("kp_Right");
    case keyboard_input::KEY_keypad_up:        return intl("kp_Up");
    case keyboard_input::KEY_keypad_down:      return intl("kp_Down");

    case keyboard_input::KEY_keypad_home:      return intl("kp_Home");
    case keyboard_input::KEY_keypad_end:       return intl("kp_End");
    case keyboard_input::KEY_keypad_page_up:   return intl("kp_PageUp");
    case keyboard_input::KEY_keypad_page_down: return intl("kp_PageDown");
    case keyboard_input::KEY_keypad_insert:    return intl("kp_Insert");
    case keyboard_input::KEY_keypad_delete:    return intl("kp_Delete");
    case keyboard_input::KEY_keypad_enter:     return intl("kp_Enter");

      //These are less common...
    case keyboard_input::KEY_keypad_space:     return intl("kp_space");
    case keyboard_input::KEY_keypad_tab:       return intl("kp_tab");
    case keyboard_input::KEY_keypad_F1:        return intl("kp_F1");
    case keyboard_input::KEY_keypad_F2:        return intl("kp_F2");
    case keyboard_input::KEY_keypad_F3:        return intl("kp_F3");
    case keyboard_input::KEY_keypad_F4:        return intl("kp_F4");
    case keyboard_input::KEY_keypad_begin:     return intl("kp_begin");
    case keyboard_input::KEY_keypad_separator: return intl("kp_separator");
      
      // Buttons I don't have, but others might...
    case keyboard_input::KEY_nobreakspace:   return intl("nobreakspace");
    case keyboard_input::KEY_exclamdown:     return intl("exclamdown");
    case keyboard_input::KEY_cent:           return intl("cent");
    case keyboard_input::KEY_sterling:       return intl("sterling");
    case keyboard_input::KEY_currency:       return intl("currency");
    case keyboard_input::KEY_yen:            return intl("yen");
    case keyboard_input::KEY_brokenbar:      return intl("brokenbar");
    case keyboard_input::KEY_section:        return intl("section");
    case keyboard_input::KEY_diaeresis:      return intl("diaeresis");
    case keyboard_input::KEY_copyright:      return intl("copyright");
    case keyboard_input::KEY_registered:     return intl("registered");
    case keyboard_input::KEY_ordfeminine:    return intl("ordfeminine");
    case keyboard_input::KEY_guillemotleft:  return intl("guillemoleft");
    case keyboard_input::KEY_notsign:        return intl("notsign");
    case keyboard_input::KEY_hyphen:         return intl("hyphen");
    case keyboard_input::KEY_macron:         return intl("macron");
    case keyboard_input::KEY_degree:         return intl("degree");
    case keyboard_input::KEY_plusminus:      return intl("plusminus");
    case keyboard_input::KEY_onesuperior:    return intl("onesuperior");
    case keyboard_input::KEY_twosuperior:    return intl("twosuperior");
    case keyboard_input::KEY_threesuperior:  return intl("threesuperior");
    case keyboard_input::KEY_acute:          return intl("acute");
    case keyboard_input::KEY_mu:             return intl("mu");
    case keyboard_input::KEY_paragraph:      return intl("paragraph");
    case keyboard_input::KEY_periodcentered: return intl("periodcentered");
    case keyboard_input::KEY_cedilla:        return intl("cedilla");
    case keyboard_input::KEY_masculine:      return intl("masculine");
    case keyboard_input::KEY_guillemotright: return intl("guillemotright");
    case keyboard_input::KEY_onequarter:     return intl("onequarter");
    case keyboard_input::KEY_onehalf:        return intl("onehalf");
    case keyboard_input::KEY_threequarters:  return intl("threequarters");
    case keyboard_input::KEY_questiondown:   return intl("questiondown");
    case keyboard_input::KEY_Agrave:         return intl("Agrave");
    case keyboard_input::KEY_Aacute:         return intl("Aacute");
    case keyboard_input::KEY_Acircumflex:    return intl("Acircumflex");
    case keyboard_input::KEY_Atilde:         return intl("Atilde");
    case keyboard_input::KEY_Adiaeresis:     return intl("Adiaeresis");
    case keyboard_input::KEY_Aring:          return intl("Aring");
    case keyboard_input::KEY_AE:             return intl("AE");
    case keyboard_input::KEY_Ccedilla:       return intl("Ccedilla");
    case keyboard_input::KEY_Egrave:         return intl("Egrave");
    case keyboard_input::KEY_Eacute:         return intl("Eacute");
    case keyboard_input::KEY_Ecircumflex:    return intl("Ecircumflex");
    case keyboard_input::KEY_Ediaeresis:     return intl("Ediaeresis");
    case keyboard_input::KEY_Igrave:         return intl("Igrave");
    case keyboard_input::KEY_Iacute:         return intl("Iacute");
    case keyboard_input::KEY_Icircumflex:    return intl("Icircumflex");
    case keyboard_input::KEY_Idiaeresis:     return intl("Idiaeresis");
    case keyboard_input::KEY_ETH:            return intl("ETH");
    case keyboard_input::KEY_Ntilde:         return intl("Ntilde");
    case keyboard_input::KEY_Ograve:         return intl("Ograve");
    case keyboard_input::KEY_Oacute:         return intl("Oacute");
    case keyboard_input::KEY_Ocircumflex:    return intl("Ocircumflex");
    case keyboard_input::KEY_Otilde:         return intl("Otilde");
    case keyboard_input::KEY_Odiaeresis:     return intl("Odiaeresis");
    case keyboard_input::KEY_multiply:       return intl("multiply");
    case keyboard_input::KEY_Ooblique:       return intl("Ooblique");
    case keyboard_input::KEY_Ugrave:         return intl("Ugrave");
    case keyboard_input::KEY_Uacute:         return intl("Uacute");
    case keyboard_input::KEY_Ucircumflex:    return intl("Ucircumflex");
    case keyboard_input::KEY_Udiaeresis:     return intl("Udiaeresis");
    case keyboard_input::KEY_Yacute:         return intl("Yacute");
    case keyboard_input::KEY_THORN:          return intl("THORN");
    case keyboard_input::KEY_ssharp:         return intl("ssharp");
    case keyboard_input::KEY_agrave:         return intl("agrave");
    case keyboard_input::KEY_aacute:         return intl("aacute");
    case keyboard_input::KEY_acircumflex:    return intl("acircumflex");
    case keyboard_input::KEY_atilde:         return intl("atilde");
    case keyboard_input::KEY_adiaeresis:     return intl("adiaeresis");
    case keyboard_input::KEY_aring:          return intl("aring");
    case keyboard_input::KEY_ae:             return intl("ae");
    case keyboard_input::KEY_ccedilla:       return intl("ccedilla");
    case keyboard_input::KEY_egrave:         return intl("egrave");
    case keyboard_input::KEY_eacute:         return intl("eacute");
    case keyboard_input::KEY_ecircumflex:    return intl("ecircumflex");
    case keyboard_input::KEY_ediaeresis:     return intl("ediaeresis");
    case keyboard_input::KEY_igrave:         return intl("igrave");
    case keyboard_input::KEY_iacute:         return intl("iacute");
    case keyboard_input::KEY_icircumflex:    return intl("icircumflex");
    case keyboard_input::KEY_idiaeresis:     return intl("idiaeresis");
    case keyboard_input::KEY_eth:            return intl("eth");
    case keyboard_input::KEY_ntilde:         return intl("ntilde");
    case keyboard_input::KEY_ograve:         return intl("ograve");
    case keyboard_input::KEY_oacute:         return intl("oacute");
    case keyboard_input::KEY_ocircumflex:    return intl("ocircumflex");
    case keyboard_input::KEY_otilde:         return intl("otilde");
    case keyboard_input::KEY_odiaeresis:     return intl("odiaeresis");
    case keyboard_input::KEY_division:       return intl("division");
    case keyboard_input::KEY_oslash:         return intl("oslash");
    case keyboard_input::KEY_ugrave:         return intl("ugrave");
    case keyboard_input::KEY_uacute:         return intl("uacute");
    case keyboard_input::KEY_ucircumflex:    return intl("ucircumflex");
    case keyboard_input::KEY_udiaeresis:     return intl("udiaeresis");
    case keyboard_input::KEY_yacute:         return intl("yacute");
    case keyboard_input::KEY_thorn:          return intl("thorn");
    case keyboard_input::KEY_ydiaeresis:     return intl("ydiaeresis");

      // Not on my keyboard, but on some HPs, Suns, or SGIs, these exist.
    case keyboard_input::KEY_linefeed:         return intl("Linefeed");
    case keyboard_input::KEY_clear:            return intl("Clear");
    case keyboard_input::KEY_begin:            return intl("Begin");
    case keyboard_input::KEY_select:           return intl("Select");
    case keyboard_input::KEY_execute:          return intl("Execute");
    case keyboard_input::KEY_undo:             return intl("Undo");
    case keyboard_input::KEY_redo:             return intl("Redo");
    case keyboard_input::KEY_menu:             return intl("Menu");
    case keyboard_input::KEY_find:             return intl("Find");
    case keyboard_input::KEY_cancel:           return intl("Cancel");
    case keyboard_input::KEY_help:             return intl("Help");
    case keyboard_input::KEY_mode_switch:      return intl("ModeSwitch");
    }

    //FIXME! Add in everything else...
    char buffer[128];
    snprintf(buffer, 128, "Unknown-0x%04x", key);

    return buffer;
  }

  std::string get_mod_names(unsigned key, unsigned modifiers, const std::string& merger = "+", bool shortened = false)
  {
    std::string ret_string;
#define ADD_MERGER() if( !ret_string.empty() ) { ret_string += merger; }

    if( modifiers & keyboard_input::keyboard_control )
    {
      if( (key != keyboard_input::KEY_control_left) &&
          (key != keyboard_input::KEY_control_right) )
      {
        ADD_MERGER();
        
        if( !modifiers & keyboard_input::keyboard_right_control )
        {
          if( !shortened )
          {
            ret_string += "<Control-L>";
          }
          else
          {
            ret_string += "<CTRL-L>";
          }
        }
        else if( !modifiers & keyboard_input::keyboard_left_control )
        {
          if( !shortened )
          {
            ret_string += "<Control-R>";
          }
          else
          {
            ret_string += "<CTRL-R>";
          }
        }
        else
        {
          if( !shortened )
          {
            ret_string += "<Control>";
          }
          else
          {
            ret_string += "<CTRL>";
          }     
        }
      } // key NOT a control
    } // control modifier set

    if( modifiers & keyboard_input::keyboard_shift )
    {
      if( (key != keyboard_input::KEY_shift_left) &&
          (key != keyboard_input::KEY_shift_right) )
      {      
        ADD_MERGER();
        if( !modifiers & keyboard_input::keyboard_right_shift )
        {
          if( !shortened )
          {
            ret_string += "<Shift-L>";
          }
          else
          {
            ret_string += "<SHFT-L>";
          }
        }
        else if( !modifiers & keyboard_input::keyboard_left_shift )
        {
          if( !shortened )
          {
            ret_string += "<Shift-R>";
          }
          else
          {
            ret_string += "<SHFT-R>";
          }
        }
        else
        {
          if( !shortened )
          {
            ret_string += "<Shift>";
          }
          else
          {
            ret_string += "<SHFT>";
          }     
        }
      } // key NOT a shift
    } // shift modifier set

    if( modifiers & keyboard_input::keyboard_super )
    {
      if( (key != keyboard_input::KEY_super_left) &&
          (key != keyboard_input::KEY_super_right) )
      {      
        ADD_MERGER();
        if( !modifiers & keyboard_input::keyboard_right_super )
        {
          if( !shortened )
          {
            ret_string += "<Super-L>";
          }
          else
          {
            ret_string += "<SPR-L>";
          }
        }
        else if( !modifiers & keyboard_input::keyboard_left_super )
        {
          if( !shortened )
          {
            ret_string += "<Super-R>";
          }
          else
          {
            ret_string += "<SPR-R>";
          }
        }
        else
        {
          if( !shortened )
          {
            ret_string += "<Super>";
          }
          else
          {
            ret_string += "<SPR>";
          }     
        }
      } // key is NOT a super
    } // super modifier is set
    
    if( modifiers & keyboard_input::keyboard_alt )
    {
      if( (key != keyboard_input::KEY_alt_left) &&
          (key != keyboard_input::KEY_alt_right) )
      {      
        ADD_MERGER();
        if( !modifiers & keyboard_input::keyboard_right_alt )
        {
          ret_string += "<Alt-L>";
        }
        else if( !modifiers & keyboard_input::keyboard_left_alt )
        {
          ret_string += "<Alt-R>";
        }
        else
        {
          ret_string += "<Alt>";
        }
      } // key NOT an alt
    } // alt modifier set

    if( modifiers & keyboard_input::keyboard_numlock )
    {
      ADD_MERGER();
      ret_string += "<Numlock>";
    }

    if( modifiers & keyboard_input::keyboard_mod3 )
    {
      ADD_MERGER();
      ret_string += "<Mod3>";
    }

    if( modifiers & keyboard_input::keyboard_mod5 )
    {
      ADD_MERGER();
      ret_string += "<Mod5>";
    }
    return ret_string;
  }

  std::string keyboard_input::keyname(unsigned key) const
  {
    std::map<unsigned, std::string>::const_iterator override;

    override = keyname_overrides.find(key);

    if( override != keyname_overrides.end() )
    {
      return override->second;
    }

    // No override...
    return get_key_name(key);
  }

  std::string keyboard_input::keyname(unsigned key, unsigned modifiers, bool shortened) const
  {
    // Try to find it in the modded override map...
    key_and_mod km(key,modifiers);

    std::map<key_and_mod, std::string>::const_iterator modded_override;

    modded_override = keyname_overrides_with_modifier.find(km);

    if( modded_override != keyname_overrides_with_modifier.end() )
    {
      // It was found, so just return the overridden name.
      return modded_override->second;
    }

    std::string mod_names;
    // No override... Merge the modifiers and the normal keyname (even if it
    // has a non-modded override).
    if( modifiers & ~keyboard_key_pressed )
    {
      std::map<unsigned, std::string>::const_iterator mod_overrides = modifier_name_overrides.find(modifiers&~keyboard_key_pressed);
      if( mod_overrides != modifier_name_overrides.end() )
      {
        mod_names = mod_overrides->second;
      }
      else
      {
        unsigned modifier_mask = ~modifier_ignore_mask & ~keyboard_key_pressed;

        if( !shortened )
        {
          mod_names = get_mod_names(key, modifiers & modifier_mask, "+", shortened);
        }
        else
        {
          // No "+" in the concatenation.
          mod_names = get_mod_names(key, modifiers & modifier_mask, "", shortened);       
        }
      }
    }
    if( !mod_names.empty() )
    {
      return mod_names + "+" + keyname(key);
    }
    return keyname(key);
  }

  // Force the key name for the given key to be displayed as new_name
  // (only while the overridden class is still active).
  void keyboard_input::override_keyname(unsigned key, const std::string& new_name)
  {
    keyname_overrides[key] = new_name;
  }
  // Force the key name for the given key, ONLY when the given modifiers are attached.
  void keyboard_input::override_keyname(unsigned key, unsigned modifiers, const std::string& new_name)
  {
    keyname_overrides_with_modifier[key_and_mod(key,modifiers&~keyboard_key_pressed)] = new_name;
  }

  void keyboard_input::override_modifier(unsigned modifier, const std::string& new_name)
  {
    modifier_name_overrides[modifier&~keyboard_key_pressed] = new_name;
  }

  void keyboard_input::clear_modifier_ignore_mask()
  {
    modifier_ignore_mask = 0;
  }

  void keyboard_input::add_modifier_ignore_mask(unsigned mask)
  {
    modifier_ignore_mask |= mask;
  }

  unsigned keyboard_input::get_modifier_ignore_mask() const
  {
    return modifier_ignore_mask;
  }


} // namespace manygames

