#ifndef __doNothing_h__
#define __doNothing_h__

#include "detect.h"

struct doNothing{
	DetectAPT* apt;
	doNothing(){
		apt = new DetectAPT(1024);	
	}
	~doNothing(){
		delete apt;	
	}
};

#endif
