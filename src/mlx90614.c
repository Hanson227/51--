#include <REGX52.H>
#include <intrins.h>

sbit SCL=P2^1;
sbit SDA=P2^0;


#define Nack_counter 1

//************数据定义****************

unsigned char bit_out=1;
unsigned char bit_in=1;

unsigned char DataH,DataL,Pecreg;

void start_bit(void)
{
        SDA=1;
        _nop_();_nop_();_nop_();_nop_();_nop_();
        SCL=1;
        _nop_();_nop_();_nop_();_nop_();_nop_();
        SDA=0;
        _nop_();_nop_();_nop_();_nop_();_nop_();
        SCL=0;
        _nop_();_nop_();_nop_();_nop_();_nop_();
}

void stop_bit(void)
{
        SCL=0;
        _nop_();_nop_();_nop_();_nop_();_nop_();
        SDA=0;
        _nop_();_nop_();_nop_();_nop_();_nop_();
        SCL=1;
        _nop_();_nop_();_nop_();_nop_();_nop_();
        SDA=1;
}


//---------发送一个字节---------
void tx_byte(unsigned char dat_byte)
{
        char i,n,dat;
        n=Nack_counter;

        dat=dat_byte;
        for(i=0;i<8;i++)
        {
                if(dat&0x80)
                bit_out=1;
                else
                bit_out=0;
                send_bit();
                dat=dat<<1;
        }
        receive_bit();
        if(bit_in==1)
        {
                stop_bit();
                if(n!=0)
                {
                   n--;   
                }
                else
                        return;
        }
        else
                return;
        start_bit();
        tx_byte(dat_byte);                //函数自身回调
}

//-----------发送一个位---------
void send_bit(void)
{
        if(bit_out==0)
        {
                SDA=0;
        }      
        else
        {
                SDA=1;  
        }        
        _nop_();
        SCL=1;
        _nop_();_nop_();_nop_();_nop_();
        _nop_();_nop_();_nop_();_nop_();
        SCL=0;
        _nop_();_nop_();_nop_();_nop_();
        _nop_();_nop_();_nop_();_nop_();
}
//----------接收一个字节--------
unsigned char rx_byte(void)
{
        unsigned char i,dat;
        dat=0;
        for(i=0;i<8;i++)
        {
                dat=dat<<1;
                receive_bit();
                if(bit_in==1)
                dat=dat+1;
        }
        send_bit();
        return dat;
}

//----------接收一个位----------
void receive_bit(void)
{
        SDA=1;bit_in=1;
        SCL=1;
        _nop_();_nop_();_nop_();_nop_();
        _nop_();_nop_();_nop_();_nop_();
        bit_in=SDA;
        _nop_();
        SCL=0;
        _nop_();_nop_();_nop_();_nop_();
        _nop_();_nop_();_nop_();_nop_();
}

unsigned int ReadObjectTemp(void)
{
        start_bit();
        tx_byte(0x00); //Send SlaveAddress
        tx_byte(0x07); //Send Command
        start_bit();
        tx_byte(0x01);
        bit_out=0;
        DataL=rx_byte();
        bit_out=0;
        DataH=rx_byte();
        bit_out=1;
        Pecreg=rx_byte();
        stop_bit();
        return(DataH*256+DataL);
}

unsigned int ReadEnvironTemp(void)
{
        start_bit();
        tx_byte(0x00); //Send SlaveAddress
        tx_byte(0x06); //Send Command
        start_bit();
        tx_byte(0x01);
        bit_out=0;
        DataL=rx_byte();
        bit_out=0;
        DataH=rx_byte();
        bit_out=1;
        Pecreg=rx_byte();
        stop_bit();
        return(DataH*256+DataL);
}

