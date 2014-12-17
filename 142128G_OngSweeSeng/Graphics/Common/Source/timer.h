#ifndef _TIMER_H
#define _TIMER_H

#include <windows.h>

/******************************************************************************/
/*!
		Class timer:
\brief	Provides methods to time how long an object can be rendered on screen and such
*/
/******************************************************************************/

class StopWatch
{
 
 private:
     
    LARGE_INTEGER frequency;
    LARGE_INTEGER prevTime, currTime;
    double LIToSecs( LARGE_INTEGER & L) ;
    UINT     wTimerRes;

 public:
     StopWatch() ;
     ~StopWatch();
     void startTimer();
     double getElapsedTime(); // get time in seconds since the last call to this function
     void waitUntil(long long time);  // wait until this time in milliseconds has passed
 };


#endif // _TIMER_H