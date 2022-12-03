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
#include "ks0066.h"

static void _NOP()
{
    for(volatile int i = 0; i < 20; i++) 
    {
        __asm__ __volatile__("nop");
    }
}       

void KS0066_Command(unsigned char data)
{
    RS = 0;
    RW = 0;
    EN = 1;
    
    _NOP();
    // // CLEAR  DATA BUS
	D7 = 0;
	D6 = 0;
	D5 = 0;
	D4 = 0;
	
    _NOP();
	
	// Set Data
	D7 = ((data >> 7) & 1);
	D6 = ((data >> 6) & 1);
	D5 = ((data >> 5) & 1);
	D4 = ((data >> 4) & 1);
	
	// Clear ENABLE pIN
    _NOP();
	EN = 0;
	_NOP();
	
	// Set Pins
	EN = 1;
	
    _NOP();
    
    // CLEAR  DATA BUS
	D7 = 0;
	D6 = 0;
	D5 = 0;
	D4 = 0;
	
	_NOP();
	
	// Set Data
	D7 = ((data >> 3) & 1);
	D6 = ((data >> 2) & 1);
	D5 = ((data >> 1) & 1);
	D4 = ((data >> 0) & 1);
	
    _NOP();
	EN = 0;
	_NOP();
}

void KS0066_Char(unsigned char data)
{
    RS = 1;
    RW = 0;
    EN = 1;
    
    _NOP();
    
    // // CLEAR  DATA BUS
	D7 = 0;
	D6 = 0;
	D5 = 0;
	D4 = 0;
	
	_NOP();
	
	// Set Data
	D7 = ((data >> 7) & 1);
	D6 = ((data >> 6) & 1);
	D5 = ((data >> 5) & 1);
	D4 = ((data >> 4) & 1);
	
	// Clear ENABLE pIN
    _NOP();
	EN = 0;
	_NOP();
	
	// Set Pins
	EN  = 1;
	
    _NOP();
    
    // CLEAR  DATA BUS
	D7 = 0;
	D6 = 0;
	D5 = 0;
	D4 = 0;
	
	// Set Data
	D7 = ((data >> 3) & 1);
	D6 = ((data >> 2) & 1);
	D5 = ((data >> 1) & 1);
	D4 = ((data >> 0) & 1);
	
	_NOP();
	EN = 0;
	_NOP();  
}

void KS0066_Goto(unsigned char x, unsigned char y)
{
    if(y == 0) y=0x80;
	else if(y == 1) y=0xC0;
	else if(y == 2) y=0x90;
	else (y=0xD0);
	
	x |= y;

	KS0066_Command( x );
}

void KS0066_StringXY(const char *data, unsigned char x, unsigned char y)
{
    KS0066_Goto(x,y);
    while(*data) KS0066_Char(*data++);
}

void KS0066_String(const char *data)
{
    while(*data) KS0066_Char(*data++);
}

void KS0066_IntXY(int num, unsigned char x, unsigned char y)
{	
    KS0066_Goto(x,y);
    
    if( num == 0) {
        KS0066_Char( 48 );
        return;
    }
    
    int temp = num;
    int decimal = 1;

    while(temp) 
    {
        decimal *= 10;
        temp /= 10;
    }

    decimal /= 10;
    
    while(decimal)
    {
        KS0066_Char( ( (num / decimal) % 10) + 48 );
        decimal /= 10;
    }
}

void KS0066_Int(int num)
{	
    if( num == 0) {
        KS0066_Char( 48 );
        return;
    }
    
    int temp = num;
    int decimal = 1;

    while(temp) 
    {
        decimal *= 10;
        temp /= 10;
    }

    decimal /= 10;
    
    while(decimal)
    {
        KS0066_Char( ( (num / decimal) % 10) + 48 );
        decimal /= 10;
    }
}

void KS0066_FloatXY(double f, long decimal, unsigned char x, unsigned char y)
{
    if(decimal > 5) decimal = 5; // e.g 100000
    
    int cd = 1;
    while(decimal--) cd*=10;
	
    int i = (int) f;
    f = (double) (f - i);
    f = (double) ( f * cd);
    int ii = (int) f;
    
    KS0066_Goto(x, y);
    KS0066_Int(i); 
    KS0066_String("."); 
    KS0066_Int( ii);     
}

void KS0066_Float(double f, long decimal)
{
    if(decimal > 5) decimal = 5; // e.g 100000
    
    int cd = 1;
    while(decimal--) cd*=10;
	
    int i = (int) f;
    f = (double) (f - i);
    f = (double) ( f * cd);
    int ii = (int) f;
    
    KS0066_Int(i); 
    KS0066_String("."); 
    KS0066_Int( ii);     
}

void KS0066_Clear(unsigned char Line)
{
    KS0066_Goto(0,Line);
    
    for(unsigned char col=0; col<16; col++)
    {
        KS0066_Char(0x20);
    }
}

void KS0066_Custom(unsigned char loc, const unsigned char data[])
{
    loc %= 8;    
    KS0066_Command(0x40 + (loc*8) );  
    for(unsigned char i=0;i<8;i++) KS0066_Char(data[i]);
}

void KS0066_Init(void)
{
	// SET PIN 
    RS_TRIS = 0; 
    RW_TRIS = 0;     
    EN_TRIS = 0;     
    D4_TRIS = 0;      
    D5_TRIS = 0;     
    D6_TRIS = 0;    
    D7_TRIS = 0; 

    KS0066_Command(0x02);
    KS0066_Command(0x28);
    KS0066_Command(0x0C);
    KS0066_Command(0x06);
}