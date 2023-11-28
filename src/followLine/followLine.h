#ifndef followLine_H_
#define followLine_H_

#include <LibRobus.h>
#include <RFID/RFID.h>

void followLineSetup(int*, String*, float*, String* = 0, String* = 0);
void followLineloop();

#endif //laisser a la fin 