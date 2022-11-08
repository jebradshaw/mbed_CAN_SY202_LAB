// Program to test the CAN bus using pins 29 and 30 on the mbed connected
// to an MCP2551 CAN transceiver bus IC
//  Note that this program will only continue to transmit while the TX message is <= 8 bytes long

#include "mbed.h"
#include "BNO055.h"

#define THIS_CAN_ID     2   //Address of this CAN device
#define DEST_CAN_ID     3   //Address of destination

Serial pc(USBTX, USBRX);    //tx, and rx for tera term
DigitalOut led1(LED1);      //heartbeat
DigitalOut led2(LED2);      //CAN read activity
DigitalOut led3(LED3);      //CAN write activity
BNO055 bno(p9, p10);   // (SDA, SCL) or... SDA is p28, SCL is p27
CAN can(p30,p29);      //CAN interface
Ticker pulse;

void alive(void){
    led1 = !led1;
    if(led1)
        pulse.attach(&alive, .2); // the address of the function to be attached (flip) and the interval (2 seconds)     
    else
        pulse.attach(&alive, 1.3); // the address of the function to be attached (flip) and the interval (2 seconds)
}

void bno_init(void){    
    if(bno.check()){
        pc.printf("BNO055 connected\r\n");
        bno.reset();
        wait(.5);
        bno.setmode(OPERATION_MODE_CONFIG);
        bno.SetExternalCrystal(1);
        //bno.set_orientation(1);
        bno.setmode(OPERATION_MODE_NDOF);  //Uses magnetometer
        //bno.setmode(OPERATION_MODE_NDOF_FMC_OFF);   //no magnetometer
        bno.set_angle_units(RADIANS);
    }
    else{
        pc.printf("BNO055 NOT connected\r\n Program Trap.");
        while(1);
    }    
}
 

int main() {
    char msg_send[20];
    wait(.2);
    
    pulse.attach(&alive, 2.0); // the address of the function to be attached (alive) and the interval (2 seconds)
    bno_init();
    can.frequency(500000);
    pc.baud(115200);    
                
    pc.printf("%s\r\n", __FILE__);
    
    while(1) {
        bno.get_angles();
        //sprintf(bnoStr, "%.2f %.2f %.2f",bno.euler.roll, bno.euler.pitch, bno.euler.yaw);
        sprintf(msg_send, "b%.2f\r\n", bno.euler.pitch);    //format output message string
        if(strlen(msg_send) > 8){   //if the message length exceeds 8 bytes
            sprintf(msg_send, "bError");  //re-format the string as an error
        }

        if(can.write(CANMessage(3, msg_send, strlen(msg_send)))){                
            pc.printf("\r\n%s", msg_send);
            led2 = !led2;
            //set up a random delay time of up to .79 seconds
            //delayT = ((rand() % 7) * 31.0)  + ((rand() % 9) * .1) + runTime.sec_total;            
        }
        else{
            can.reset();
        }           
        wait(.05);
    }//while(1)
}//main
