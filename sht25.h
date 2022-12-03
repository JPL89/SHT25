#ifndef SHT25_H
#define SHT25_H

// SHT25 SLAVE ADDRESS
#define SHT25_SLA_W 0x80// SLA W
#define SHT25_SLA_R 0x81 // SLA R

// SHT25 COMMANDS
#define SHT25_Trigger_T_measurement 0xE3 // HOLD
#define SHT25_Trigger_RH_measurement 0xE5 // HOLD
#define SHT25_Trigger_T_measurement_NH 0xF3 // NOHOLD
#define SHT25_Trigger_RH_measurement_NH 0xF5 // NOHOLD
#define SHT25_Write_user_register 0xE6
#define SHT25_Read_user_register 0xE7
#define SHT25_Soft_reset 0xFE

float Temperature;
float Humidity;

float T(int data){
    return -46.85 + 175.72 * (data/(65536.0));
}

float RH(int data){
    return 6.0 + 125.0 * (data / 65536.0);
}

void SHT25_Get_Temp()
{
    char data[6];
    
    I2C_Start();
    I2C_Write( SHT25_SLA_W );
    I2C_Write( SHT25_Trigger_T_measurement_NH );    
    I2C_Start();
    I2C_Write( SHT25_SLA_R );    
    data[0] = I2C_Ack(); // Temperature     
    data[1] = I2C_Ack(); // Temperature    
    data[2] = I2C_Ack(); // CRC    
    data[3] = I2C_Ack(); // humidity    
    data[4] = I2C_Ack(); // humidity    
    data[5] = I2C_Nack(); // CRC 
    I2C_Stop();

    Temperature = T( data[0] << 8 | data[1] ) + 0.1;
    Humidity = RH( data[3] << 8 | data[4] );
}

#endif // SHT25_H