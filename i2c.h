// @File		 		
// @Author		JOSIMAR PEREIRA LEITE
// @country		Brazil
// @Date		17/11/22
//
//
// Copyright (C) 2021  JOSIMAR PEREIRA LEITE
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//

#ifndef WIRE_H
#define WIRE_H

#include <xc.h>

#define SCL_HIGH            PORTAbits.RA0=1
#define SCL_LOW             PORTAbits.RA0=0

#define SDA_HIGH            PORTAbits.RA1=1
#define SDA_LOW             PORTAbits.RA1=0

unsigned char I2C_Ack_Polling(unsigned char address);
unsigned char I2C_Test(unsigned char Slave);
unsigned char I2C_Nack(void);
unsigned char I2C_Ack(void);
void I2C_Stop(void);
void I2C_Start(void);
void I2C_Write(unsigned char data);
void I2C_Init(void);

#endif	

