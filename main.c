/* A ethernet try for RPI */
#include <uspi.h>
#include <uspienv/util.h>
#include <uspienv.h>
unsigned char preamble[]= {  0x55, 0x55, 0x55 ,0x55 ,0x55 ,0x55 ,0x55, 0xD5  };
unsigned char destmac[] = { 0xFF , 0xFF ,0xFF ,0xFF ,0xFF ,0xFF }; /* broadcast */
int main(void) {
	if (!USPiEnvInitialize ())
	{
		return EXIT_HALT;
	}
	if (!USPiInitialize ())
	{
//		LogWrite (FromSample, LOG_ERROR, "Cannot initialize USPi");
		USPiEnvClose ();
		return EXIT_HALT;
	}
	TimerSimpleMsDelay (2000); /* wait for Ethernet */
	if (!USPiEthernetAvailable ())
        {
 //               LogWrite (FromSample, LOG_ERROR, "Ethernet not supported");
                USPiEnvClose ();
                return EXIT_HALT;
        }
	while(1==1) {
		TimerSimpleMsDelay(100);
		sendFrame();
	}
}
void sendFrame() {
	unsigned char eFrame[70];
	memcpy(eFrame,preamble,8);
	unsigned char data[46];
	memset(data, 0xCD, 1);
	unsigned char *pointer= eFrame + 8;
	memcpy(pointer,destmac,6);
	pointer += 6;
	unsigned char mymac[6];
	USPiGetMACAddress(mymac);
	memcpy(pointer,mymac,6);
	pointer += 6;
	unsigned short *size;
	size=(unsigned short *)pointer;
	size[0]=46;
	pointer += 2;
	memcpy(pointer,data,46);
	USPiSendFrame(eFrame,70);
}
