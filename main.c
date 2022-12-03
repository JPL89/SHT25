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

#include "config.h"
#include "ks0066.h"
#include "i2c.h"
#include "sht25.h"

int main(void) 
{
    __delay_ms(250);
   
    // CLEAR PORTS
    PORTA = 0x00;
    PORTB = 0x00;
    PORTC = 0x00;
    
    // CLEAR DATA LATCHES
    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x00;
    
    // A/D PORT CONFIGURAION CONTROL BIT
    // (0x0F) DIGITAL I/O
    ADCON1 = 0x0F;
    
    // TURN OFF THE COMPARATORS
    CMCON = 0x07;      

    // I2C_INIT
    I2C_Init();

    // INIT DISPLAY
    KS0066_Init();
    KS0066_Clear(0);
    KS0066_Clear(1);
     
    KS0066_Goto(0, 0);
    
    while(1)
    {
        SHT25_Get_Temp();
        
        KS0066_Clear(0);
        KS0066_Clear(1);
        KS0066_Goto(0,0);
        KS0066_Int( (int) Temperature);
        
        __delay_ms(1000);
    }
}