#ifndef __MLX90614_H__
#define __MLX90614_H__

void start_bit();
void stop_bit();
void tx_byte(unsigned char dat_byte);
void MLX90614_send_bit();
unsigned char rx_byte();
void MLX90614_receive_bit();
unsigned int ReadObjectTemp();
unsigned int ReadEnvironTemp();

#endif