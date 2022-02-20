#include<REGX52.H>

sbit LED=P2^0;

int main()
{
    while (1)
    {
        LED=1;
        LED=0;
    }
    
}