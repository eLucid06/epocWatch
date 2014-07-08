epocWatch
=========

First run qmake in order to generate the Makefile
Then run make to generate the executable
Finally run ./epocWatch as a sudo user (problem with using bluetooth, if someone knows how to fix it ...)


Dependencies
=========
QT5 has to be installed
fft3w for the fast fourrier transform
mcrypt and hidraw for the decyption/communication with the device
(see https://github.com/qdot/emokit)


TO DO
=========
fixing the communication ith bluetooth (using the program as a non-sudo user)
adding information of the quality of the signal for each electrode (by using the image at the bottom right)

enhancing the representation of the signal ; maybe adding some processing in option
