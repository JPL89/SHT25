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

#ifndef KS0066_H
#define KS0066_H

#include <xc.h>

#define RS PORTBbits.RB0
#define RW PORTBbits.RB1
#define EN PORTBbits.RB2
#define D4 PORTBbits.RB3
#define D5 PORTBbits.RB4
#define D6 PORTBbits.RB5
#define D7 PORTBbits.RB6

#define RS_TRIS TRISB     
#define RW_TRIS TRISB     
#define EN_TRIS TRISB     
#define D4_TRIS TRISB     
#define D5_TRIS TRISB     
#define D6_TRIS TRISB     
#define D7_TRIS TRISB 

void KS0066_Command(unsigned char data);
void KS0066_Char(unsigned char data);
void KS0066_Goto(unsigned char x, unsigned char y);
void KS0066_StringXY(const char *data, unsigned char x, unsigned char y);
void KS0066_String(const char *data);
void KS0066_IntXY(int num, unsigned char x, unsigned char y);
void KS0066_Int(int num);
void KS0066_FloatXY(double f, long decimal, unsigned char x, unsigned char y);
void KS0066_Float(double f, long decimal);
void KS0066_Clear(unsigned char Line);
void KS0066_Custom(unsigned char loc, const unsigned char data[]);
void KS0066_Init(void);

#endif // KS0066_H