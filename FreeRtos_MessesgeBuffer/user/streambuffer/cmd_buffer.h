/*
 * cmd_buffer.h
 *
 *  Created on: Aug 24, 2023
 *      Author: khoi7
 */
#include "main.h"
#ifndef CMD_BUFFER_H_
#define CMD_BUFFER_H_

void cmd_buffer_init(void);
uint32_t received_messagebuffer( uint8_t* ucRxData, uint32_t need_len);
void send_xbyte_buffer(const uint32_t* ucArrayToSend);
void send_string_buffer(const char* pcStringToSend);
void Send_Data_Isr( const char* pcStringToSend, uint32_t len);
#endif /* CMD_BUFFER_H_ */
