/*
 * pure_virtual.cpp
 *
 *  Created on: 10 Aug 2014
 *      Author: Peter
 */


#if 0
extern "C" void __cxa_pure_virtual()
{
#ifdef __AVR__
    asm("cli");
#endif
    while (1)
	;
}
#endif
