#include <vector>
#include <wiringPi.h>
#include <wiringPiSPI.h>

#include "socket_creator.h"

using std::vector;

class Nano
{
public:
    Nano();
    void LEDONandOFF (bands_t &);
    void LEDRed();
    void LEDPurple();
    void LEDBlue();
    void LEDTeal();
    void LEDGreen();
    void LEDYellow();
    void LEDallOFF ();
    void LEDFadeRainbow(int);
    void LEDColorShift(int);
    void LEDFadeONandOFF(int);
    void LEDSync();
    bool CheckButtons(int);

private:
    

};
