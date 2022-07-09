// You may use, distribute and modify this code under the
// terms of the GPLv2 license, which unfortunately won't be
// written for another century.
//
// SPDX-License-Identifier: GPL-2.0-or-later
//
#pragma once

#include "tusb.h"
#include "hardware/pio.h"
#include "hardware/gpio.h"

typedef struct {
  uint8_t code;
  bool release;
  uint8_t page;
} Ps2KbdAction;

class Ps2Kbd {
private:
  PIO _pio;                        // pio0 or pio1
  uint _sm;                        // pio state machine index
  uint _base_gpio;                 // data signal gpio
  hid_keyboard_report_t _report;   // HID report structure
  Ps2KbdAction _actions[2];
  uint _action;
  bool _double;
  
  inline void clearActions() {
    _actions[0].page = 0;
    _actions[0].release = false;
    _actions[0].code = 0;
    _actions[1].page = 0;
    _actions[1].release = false;
    _actions[1].code = 0;
    _action = 0;
  }
  
  void __not_in_flash_func(handleHidKeyPress)(uint8_t hidKeyCode);
  void __not_in_flash_func(handleHidKeyRelease)(uint8_t hidKeyCode);
  
  void __not_in_flash_func(handleActions)();
  uint8_t __not_in_flash_func(hidCodePage0)(uint8_t ps2code);
  uint8_t __not_in_flash_func(hidCodePage1)(uint8_t ps2code);
  
public:

  Ps2Kbd(PIO pio, uint base_gpio);
  
  void init_gpio();
  
  void __not_in_flash_func(tick)();
};
