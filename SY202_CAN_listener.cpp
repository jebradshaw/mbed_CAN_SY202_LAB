// Program to test the CAN bus using pins 29 and 30 on the mbed connected
// to an MCP2551 CAN transceiver bus IC
//  Note that this program will only continue to transmit while the TX message is <= 8 bytes long

#include "mbed.h"

#define THIS_CAN_ID     3   //Address of this CAN device
#define DEST_CAN_ID     4   //Address of destination

Serial pc(USBTX, USBRX);    //tx, and rx for tera term
DigitalOut heartbeat_led(LED1, 0);      //heartbeat
DigitalOut can_read_led(LED2, 0);      //CAN read activity
DigitalOut can_write_led(LED3, 0);      //CAN write activity
CAN can(p30,p29);      //CAN interface
Ticker pulse;

/*
void sendFalseInfo(int servoPulse){
    servoPulse = 1500;
    char msg_send[20];
    sprintf(msg_send, "s%d", servoPulse);    //format output message string

    if(can.write(CANMessage(DEST_CAN_ID, msg_send, strlen(msg_send)))){                
        pc.printf("Message Sent: %s", msg_send);
        led1 = !led1;              
    }
    else{
        can.reset();
    }    
}
*/
void alive(void){
    heartbeat_led = !heartbeat_led;
    if(heartbeat_led)
        pulse.attach(&alive, .2); // the address of the function to be attached (flip) and the interval (2 seconds)     
    else
        pulse.attach(&alive, 1.3); // the address of the function to be attached (flip) and the interval (2 seconds)
}
    
int main() {
    int i=0;
    CANMessage msg_read;      
    wait(.2);
    pulse.attach(&alive, 2.0); // the address of the function to be attached (alive) and the interval (2 seconds)
    can.frequency(500000);
    pc.baud(115200);    
            
    pc.printf("%s\r\n", __FILE__);    
    while(1) {                        
        while(can.read(msg_read)){ //if message is available, read into msg
            pc.printf("message num %d = %s\r\n",  i++, msg_read.data);
            can_read_led = !can_read_led;
        }                               
    }//while(1)
}//main
