#include "epocDevice.hpp"

epocDevice::epocDevice()
{
	device = emokit_create() ;
}

epocDevice::~epocDevice()
{
	emokit_delete(device) ;
}

void epocDevice::disconnect()
{
    emokit_close(device) ;
}


int epocDevice::connect()
{
	return emokit_open(device, EMOKIT_VID, EMOKIT_PID, 1) ;
}


int epocDevice::update()
{
	if(emokit_read_data(device) > 0)
	{
		frame = emokit_get_next_frame(device) ;
        _counter = frame.counter ;
        _AF3 = frame.AF3 ;
        _AF4 = frame.AF4 ;
        _F3 = frame.F3 ;
        _F4 = frame.F4 ;
        _F7 = frame.F7 ;
        _F8 = frame.F8 ;
        _FC5 = frame.FC5 ;
        _FC6 = frame.FC6 ;
        _T7 = frame.T7 ;
        _T8 = frame.T8 ;
        _P7 = frame.P7 ;
        _P8 = frame.P8 ;
        _O1 = frame.O1 ;
        _O2 = frame.O2 ;

        return 0 ;
	}
    else
        return -1 ;
}


int epocDevice::getCounter()
{
    return _counter ;
}

int epocDevice::getAF3()
{
    return _AF3 ;
}

int epocDevice::getAF4()
{
    return _AF4 ;
}

int epocDevice::getF3()
{
    return _F3 ;
}

int epocDevice::getF4()
{
    return _F4 ;
}

int epocDevice::getF7()
{
    return _F7 ;
}

int epocDevice::getF8()
{
    return _F8 ;
}

int epocDevice::getFC5()
{
    return _FC5 ;
}

int epocDevice::getFC6()
{
    return _FC6 ;
}

int epocDevice::getT7()
{
    return _T7 ;
}

int epocDevice::getT8()
{
    return _T8 ;
}

int epocDevice::getP7()
{
    return _P7 ;
}

int epocDevice::getP8()
{
    return _P8 ;
}

int epocDevice::getO1()
{
    return _O1 ;
}

int epocDevice::getO2()
{
    return _O2 ;
}
