#include <mbed.h>
#include "ReceiverIR.h"
#include "MicroBit.h"

Serial pc(USBTX, USBRX); // tx, rx
ReceiverIR ir_rx(p3);
Ticker ledTicker;

int receive(RemoteIR::Format *format, uint8_t *buf, int bufsiz, int timeout = 100) {
    int cnt = 0;
    while (ir_rx.getState() != ReceiverIR::Received) {
        cnt++;
        if (timeout < cnt) {
            return -1;
        }
    }
	
    return ir_rx.getData(format, buf, bufsiz * 8);
}

int main(void) {
	
    MicroBitDisplay display;
	display.scroll("Press a button on the remote :)");
	
	
    while (1) {
        uint8_t buf1[32];
        int bitlength1;
        RemoteIR::Format format;

        memset(buf1, 0x00, sizeof(buf1));
        {
            bitlength1 = receive(&format, buf1, sizeof(buf1));
            if (bitlength1 < 0) {
                continue;
            }
		    
			const int n = bitlength1 / 8 + (((bitlength1 % 8) != 0) ? 1 : 0);
			
			if (buf1[0] == 0x00 && buf1[1] == 0xBF) {
				if (buf1[2] == 0x00 && buf1[3] == 0xFF) {
					display.printChar('1');
				}
				if (buf1[2] == 0x01 && buf1[3] == 0xFE) {
					display.printChar('2');
				}
				if (buf1[2] == 0x02 && buf1[3] == 0xFD) {
					display.printChar('3');
				}
				if (buf1[2] == 0x04 && buf1[3] == 0xFB) {
					display.printChar('4');
				}
				if (buf1[2] == 0x05 && buf1[3] == 0xFA) {
					display.printChar('5');
				}
				if (buf1[2] == 0x06 && buf1[3] == 0xF9) {
					display.printChar('6');
				}
				if (buf1[2] == 0x08 && buf1[3] == 0xF7) {
					display.printChar('7');
				}
				if (buf1[2] == 0x09 && buf1[3] == 0xF6) {
					display.printChar('8');
				}
				if (buf1[2] == 0x0A && buf1[3] == 0xF5) {
					display.printChar('9');
				}
				if (buf1[2] == 0x0D && buf1[3] == 0xF2) {
					display.printChar('0');
				}
				if (buf1[2] == 0x0C && buf1[3] == 0xF3) {
					display.printChar('*');
				}
				if (buf1[2] == 0x0E && buf1[3] == 0xF1) {
					display.printChar('#');
				}
				if (buf1[2] == 0x14 && buf1[3] == 0xEB) {
					display.printChar('L');
				}
				if (buf1[2] == 0x16 && buf1[3] == 0xE9) {
					display.printChar('R');
				}
				if (buf1[2] == 0x11 && buf1[3] == 0xEE) {
					display.printChar('U');
				}
				if (buf1[2] == 0x19 && buf1[3] == 0xE6) {
					display.printChar('D');
				}
				if (buf1[2] == 0x15 && buf1[3] == 0xEA) {
					display.scroll("OK!");
				}
			}
			
			// echo to serial port
		    for (int i = 0; i < n; i++) {
		        pc.printf("%02X", buf1[i]);
		    }
			
			pc.printf("\n\r");
        }
    }
}
