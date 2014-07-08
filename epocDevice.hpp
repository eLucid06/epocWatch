#ifndef EPOCDEVICE_HPP
#define EPOCDEVICE_HPP


/* Emotic EPOC daemon that decrypt stream using ECB and RIJNDAEL-128 cipher
 * (well, not yet a daemon...)
 *
 * Usage: epocd (consumer/research) /dev/emotiv/encrypted output_file
 *
 * Make sure to pick the right type of device, as this determins the key
 * */

#include "emokit/emokit.h"

class epocDevice
{
public:
	epocDevice() ;
	~epocDevice() ;

	int connect() ;
    void disconnect() ;
    int update() ;

    int getCounter() ;
    int getAF3() ;
    int getAF4() ;
    int getF3() ;
    int getF4() ;
    int getF7() ;
    int getF8() ;
    int getFC5() ;
    int getFC6() ;
    int getT7() ;
    int getT8() ;
    int getP7() ;
    int getP8() ;
    int getO1() ;
    int getO2() ;

private:

	struct emokit_device * device ;
	struct emokit_frame frame ;

    int _counter ;
    int _AF3 ;
    int _AF4 ;
    int _F3 ;
    int _F4 ;
    int _F7 ;
    int _F8 ;
    int _FC5 ;
    int _FC6 ;
    int _T7 ;
    int _T8 ;
    int _P7 ;
    int _P8 ;
    int _O1 ;
    int _O2 ;
} ;

#endif
