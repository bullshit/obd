#ifndef __ODBDISPLAY_H__
#define __ODBDISPLAY_H__

#if defined(ARDUINO) && ARDUINO >= 100
	#include <Arduino.h>
#else
	#include <WProgram.h>
#endif
#include "Nextion.h"



class Display
{
  public:
    bool init(void);
    void nextLoop(void);
  protected:
    void _initUI(void);
  private:
    NexTouch *_n_nex_listen_list[];
  
    NexPage _n_initPage = NexPage(0,0,"initPage");
    NexText _n_initMessage = NexText(0,1,"initMessage");
};




#endif
