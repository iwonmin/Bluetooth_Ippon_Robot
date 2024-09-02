#include "mbed.h"
DigitalOut DirR(PC_2);
DigitalOut DirL(PC_3);
Serial pc(USBTX, USBRX, 115200);
Serial bt(PC_10,PC_11,9600);
PwmOut PwmR(PA_0);
PwmOut PwmL(PA_1);
void SetSpeed(float, float);

int main() {
    char c = '*';
    char c_direction = '*';
    char c_velocity = '*';
    float v = 0.f;
    PwmL.period_us(66);
    PwmR.period_us(66);
    while(1) {
        c = bt.getc();
        if(c == '+' || c == '-' || c == 'L' || c == 'R' || c == 'B') c_direction = c;
        if(c == 'a' || c == 'b' || c == 'c' || c == 'd') c_velocity = c;
        switch(c_velocity) {
            case 'a':
                v = 0.2f;
                break;
            case 'b':
                v = 0.5f;
                break;
            case 'c':
                v = 0.75f;
                break;
            case 'd':
                v = 1.0f;
                break;
            default:
                SetSpeed(0.f,0.f);
                break;
            }
        switch(c_direction) {
            case '+':
                SetSpeed(v,v);
                break;
            case '-':
                SetSpeed(-v,-v);
                break;
            case 'L':
                SetSpeed(-v,v);
                break;
            case 'R':
                SetSpeed(v,-v);
                break;
            case 'B':
                SetSpeed(0.f,0.f);
                break;
            default:
                SetSpeed(0.f,0.f);
                break;
        }
        pc.printf("%c\r\n",c);
        ThisThread::sleep_for(10);
    }
}
void SetSpeed(float sL, float sR) {

    if (sL < 0)
        DirL = 0;
    else
        DirL = 1;
    if (sR < 0)
        DirR = 0;
    else
        DirR = 1;

    PwmL = abs(sL);
    PwmR = abs(sR);
}