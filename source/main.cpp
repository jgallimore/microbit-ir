#include <mbed.h>
#include "ReceiverIR.h"

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
		    for (int i = 0; i < n; i++) {
		        pc.printf("%02X", buf1[i]);
		    }
        }
    }
}