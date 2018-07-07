#include "mbed.h"
#include "SoftwarePWM.h"
#include "Servo.h"
// main de los main
Serial pc(USBTX,USBRX);

//DigitalOut led(LED1);
DigitalOut led1(LED2);

//Ultrasonido
DigitalOut URTRIG(PTD1);          // A low pull on pin COMP/TRIG
InterruptIn event(PTD3);
Timer timer;
int begin, end;
unsigned int dist = 0;

void PWM_rise()                  //invocado por PWM_Mode para medicion de ultrasonido
{
    end = timer.read_us();
    timer.stop();
    unsigned int DistanceMeasured = end - begin;

    if(DistanceMeasured>=10200) {
        // the reading is invalid.
        dist = 0;
        //printf("Invalid \n");
    } else {
        dist=DistanceMeasured/50;           // every 50us low level stands for 1cm

    }
}
void PWM_Mode()                //invocado por event.fall() para lectura de ultrasonido
{

    URTRIG = 1;
    URTRIG = 0;         // reading Pin PWM will output pulses
    timer.start();
    begin = timer.read_us();
    event.rise(&PWM_rise);
}

int main()
{
    while(1) {
        event.fall(&PWM_Mode);    //linea 47
        PWM_Mode();       //no borrar por ningun motivo, aunque este bien fundamentado
        printf("distancia:  %d\n",dist);

////////////////////////////////////////////////   DECREMENTO
        if(dist >= 150 || dist == 0) {
            //vel(1);
            printf("adelante    %d\n", dist);
        }
        else if{
            if(dist < 150 && dist > 110)
            {
                vel(((dist-62)/2.37));
                printf("reg:    %d    vel:  %f\n\r",dist,((dist-62)/2.37)*0.01);
            }
            else
            {
                vel(((dist-20)/4.5));
                printf("reg:    %d    vel:  %f\n\r",dist,((dist-20)/4.5)*0.01);
            }

            printf("reg:    %d    vel:  %f\n\r",(dist,);

            //vel(dist*razon/100);
            //  printf("%.2f cm \n", dist);
        }
        else(dist < 20)
        {
            printf("atras    %d\n", dist);
            //vel(-0.2);
            //wait(0.1);
            //vel(0);
            //wait(1);
            /*while(dist < 20 && dist != 0)
            {
                event.fall(&PWM_Mode);    //linea 47
                PWM_Mode();       //no borrar por ningun motivo, aunque est� bien fundamentado
            }*/
        }

//////////////////////////////////////////////// FIN DECREMENTO


        wait_ms(20);
    }
}
