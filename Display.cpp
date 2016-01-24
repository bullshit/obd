#include "Display.h"


bool Display::init(void) {
  if (nexInit()) {
    _initUI();
    return true;
  }
  return false;
}


void Display::nextLoop(void) {
  nexLoop(_n_nex_listen_list);  
}

void Display::_initUI(void) {
  NexTouch *nex_listen_list[] = {
    
  };
}


