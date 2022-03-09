#ifndef __mlx90614_H__
#define __mlx90614_H__

void start_bit(void);
void stop_bit(void);
void tx_byte(unsigned char dat_byte);
void send_bit(void);
unsigned char rx_byte(void);
void receive_bit(void);
unsigned int ReadObjectTemp(void);
unsigned int ReadEnvironTemp(void);

#endif