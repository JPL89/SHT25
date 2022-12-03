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
#include "i2c.h"

#define _NOP() __asm__ __volatile__("nop")

void I2C_Start(void)
{
    SCL_HIGH;
    _NOP();
    SDA_HIGH;
    _NOP();
    SDA_LOW;
    _NOP(); 
    SCL_LOW;
}

void I2C_Stop(void)
{
    SDA_LOW;
    _NOP();
    SCL_HIGH;
    _NOP(); 
    SDA_HIGH;
    
}

unsigned char I2C_Ack(void)
{
    unsigned char byte = 0;
    
    TRISA1 = 1;
    
    SDA_HIGH;
    
    for (unsigned char bit = 0; bit < 8; bit++)
    {
        byte <<= 1;
        
        SCL_HIGH;        
        if(PORTAbits.RA1 == 1) byte |= 1; 
        SCL_LOW;
    }
	
     TRISA1 = 0;

    SDA_LOW;
    _NOP();
    SCL_HIGH;
    _NOP();
    SCL_LOW;
    _NOP();
    
    return byte;
}

unsigned char I2C_Nack(void)
{
    unsigned char byte = 0;
    
    TRISA1 = 1;
    
    SDA_HIGH;
    
    for (unsigned char bit = 0; bit < 8; bit++)
    {
        byte <<= 1;
        
        SCL_HIGH;        
        if(PORTAbits.RA1 == 1) byte |= 1; 
        SCL_LOW;
    }
	
     TRISA1 = 0;

    SDA_HIGH;
    _NOP();
    SCL_HIGH;
    _NOP();
    SCL_LOW;
    _NOP();
	
    return byte;
}

void I2C_Write(unsigned char data)
{
    for(unsigned char bit=0; bit<8; ++bit)
    {
	if(data & 0x80) SDA_HIGH; else SDA_LOW;
	data <<= 1;
	
        SCL_HIGH;
	_NOP();
	SCL_LOW;
	_NOP();
    }
    
    // Read ACK
    TRISA1 = 1;
    
    SDA_HIGH;
    _NOP();
    SCL_HIGH;
    _NOP();
    SCL_LOW;
    _NOP();
    
    TRISA1 = 0;
}

unsigned char I2C_Test(unsigned char Slave)
{
    unsigned char ack = 0;
	
    I2C_Start();
    
    for(unsigned char bit=0; bit<8; ++bit)
    {
        if(Slave & 0x80) SDA_HIGH; else SDA_LOW;
        
        Slave <<= 1;
        
        SCL_HIGH;
        _NOP();
        SCL_LOW;
        _NOP();
    }
        
    // Read ACK
    TRISA1 = 1;
    
    SDA_HIGH;
    _NOP();
    SCL_HIGH;
    _NOP();
    if(PORTAbits.RA1 == 1) ack = 1; 
    SCL_LOW;
    _NOP();
    
    TRISA1 = 0;
    
    I2C_Stop();
    
    return ack;
}

unsigned char I2C_Ack_Polling(unsigned char address)
{
    unsigned char ack = 0;
	
    I2C_Start();
    
    for(unsigned char bit=0; bit<8; ++bit)
    {
        if(address & 0x80) SDA_HIGH; else SDA_LOW;
        
        address <<= 1;
        
        SCL_HIGH;
        _NOP();
        SCL_LOW;
        _NOP();
    }
        
    // Read ACK
    TRISA1 = 1;
    
    SDA_HIGH;
    _NOP();
    SCL_HIGH;
    _NOP();
    if(PORTAbits.RA1 == 1) ack = 1; 
    SCL_LOW;
    _NOP();
    
    TRISA1 = 0;
    
    I2C_Stop();
    
    return ack;    
}

void I2C_Init(void)
{
    TRISA0 = 0;
    TRISA1 = 0;
}

