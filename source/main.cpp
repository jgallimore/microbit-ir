#include "mbed.h"
 
Serial pc(USBTX, USBRX); // tx, rx
Serial device(p2, p1);  // tx, rx
int main() {
    char temp=0;
    device.baud(2400);
    while (1) {
        //RF Receive Code
        if (device.readable()) {
            temp=device.getc();
            //Ignore Sync pattern and do not pass on to PC
            if (temp!=0xAA) pc.putc(temp);
        }
    }
}