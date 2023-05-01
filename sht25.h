// @File		SHT25.H		 		
// @Author		JOSIMAR PEREIRA LEITE
// @country		Brazil
// @Date		01/05/23
//
//
// Copyright (C) 2023  JOSIMAR PEREIRA LEITE
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
#ifndef SHT25_H
#define SHT25_H

#define SHT25_SLA_W 0x80 
#define SHT25_SLA_R 0x81

#define SHT25_Trigger_T_measurement 0xE3 // HOLD
#define SHT25_Trigger_RH_measurement 0xE5 // HOLD
#define SHT25_Trigger_T_measurement_NH 0xF3 // NOHOLD
#define SHT25_Trigger_RH_measurement_NH 0xF5 // NOHOLD
#define SHT25_Write_user_register 0xE6
#define SHT25_Read_user_register 0xE7
#define SHT25_Soft_reset 0xFE

#define SHT25_14Bits 0x00 
#define SHT25_12Bits 0x01 
#define SHT25_13Bits 0x80 
#define SHT25_11Bits 0x81 
#define SHT25_Status_vdd 0x40 
#define SHT25_Enable_on_chip_heater 0x04  
#define SHT25_Disable_OTP_Reload 0x02 

unsigned char SHT25_Read_Register()
{
    unsigned char data = 0;
    
    Wire_Start();
    Wire_Write( SHT25_SLA_W );
    Wire_Write( SHT25_Read_user_register );
    Wire_Start();
    Wire_Write( SHT25_SLA_R );
    data = Wire_Nack();
    Wire_Stop();
    
    return ( data );
}

void SHT25_Write_Register(unsigned char data)
{
    Wire_Start();
    Wire_Write( SHT25_SLA_W );
    Wire_Write( data );
    Wire_Stop();
}

void SHT25_Soft_Reset(void)
{
    Wire_Start();
    Wire_Write( SHT25_SLA_W );
    Wire_Write( SHT25_Soft_reset );
    Wire_Stop();
}

double SHT25_Read_Temp(void)
{
    short data = 0x0000;
    
    Wire_Start();
    Wire_Write( SHT25_SLA_W );
    Wire_Write( 0xE3 ); 
    Wire_Start();
    Wire_Write( SHT25_SLA_R );   
    data |= Wire_Ack(); 
    data <<= 8;
    data |= Wire_Ack(); 
    data |= Wire_Ack(); 
    Wire_Nack(); 
    Wire_Stop();

    double c = ((double)(-46.85 + 175.72 * ( data / 65536.0)));
    
    return ( c );
}

double SHT25_Read_Humi(void)
{
    short data = 0x0000;
    
    Wire_Start();
    Wire_Write( SHT25_SLA_W );
    Wire_Write( 0xE5 ); 
    Wire_Start();
    Wire_Write( SHT25_SLA_R );   
    data |= Wire_Ack(); 
    data <<= 8;
    data |= Wire_Ack(); 
    Wire_Nack(); 
    Wire_Stop();

    double r = ((double) (-6 + 125.0 * ( data / 65536.0)) );
    
    return ( r );
}

#endif
