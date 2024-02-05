#include <iostream>
#include <string.h>
#include <cmath>

#include "../inc/i2c.h"
#include "../inc/timer.h"
#include "../inc/stats.h"
#include "../inc/accel.h"
#include "../inc/gyro.h"
#include "../inc/mag.h"


int main(int argc, char* argv[])
{
    if (gpioInitialise()<0) //initialises pigpio.h
    {
        //if pigpio initialisation failed
        std::cout<<"pigpio.h initialisation failed\n";
        return -1;
    }

    //variables commonly used in main()
    int device_handle, mag_device_handle, wake_handle;
    std::string current_time;
    double accel_x =0.0, accel_y=0.0, accel_z=0.0;
    double pre_accel_x , pre_accel_y, pre_accel_z;
    double gyro_x, gyro_y, gyro_z;

    //attempt to open I2C devices
    device_handle = i2cOpen(I2C_DEVICE,I2C_DEVICE_ADDR,I2C_FLAGS);
    if (device_handle < 0)
    {
        std::string err = "Failed to open i2c communication to IMU\n";
        std::cout<<err<<"\n";
        return -2;
    }
    mag_device_handle = i2cOpen(I2C_DEVICE,I2C_MAGDEVICE_ADDR,I2C_FLAGS);
    if (mag_device_handle < 0)
    {
        std::string err = "Failed to open i2c communication to mag\n";
        std::cout<<err<<"\n";
        return -3;
    }

    //attempt to disable sleep modes
    wake_handle = i2cWriteByteData(device_handle,PWR_MGMT_1_ADDR,PWR_MGMT_1_VAL);
    if (wake_handle<0)
    {
        std::string err = "Failed to wake IMU device\n";
        std::cout<<err<<"\n";
        return -4;
    }

    device_wait(100); //to allow device to be ready to take readings
    std::cout << "Device is ready to take readings\n\n";

    //attempt to set scales
    set_gyro(device_handle,250);
    set_accel(device_handle,2);
    
    double velocity_x = 0.0; 
    double velocity_y = 0.0; 
    double velocity_z = 0.0;
    double time_interval = 0.01; // unit : sec
    double velocity = 0.0;
    
    //infinite loop to get readings from device
    while (true)
    {
        pre_accel_x = accel_x;
        pre_accel_y = accel_y;
        
        //get readings
        accel_x = -(get_accel_x(device_handle));
        accel_y = -(get_accel_y(device_handle));
        accel_z = -(get_accel_z(device_handle));
        gyro_x = get_gyro_x(device_handle);
        gyro_y = get_gyro_y(device_handle);
        gyro_z = get_gyro_z(device_handle);
        
        if(0 < accel_x < 1.5){
            accel_x = 0;
        }
        
        if(abs(accel_y) < 1.0){
            accel_y = 0;
        }
        
        // velocity
        velocity_x = (accel_x + pre_accel_x) * time_interval /2;
        velocity_y = (accel_y + pre_accel_y) * time_interval/2;
        //velocity_z = accel_z * time_interval;
    
        if(accel_x < 0) {
            velocity -= sqrt(velocity_x*velocity_x + velocity_y*velocity_y);
        }else{
            velocity += sqrt(velocity_x*velocity_x + velocity_y*velocity_y);
        }
    
        //output readings
        std::cout << "Accel:  x: "<<accel_x<<"  y: "<<accel_y<<"  z: "<<accel_z<<"  [m/s^2]\n";
        std::cout << "Gyro:  x: "<<gyro_x<<"  y: "<<gyro_y<<"  z: "<<gyro_z<<"  [deg/sec]\n";
        std::cout << "Velocity:  x: " << velocity_x << "  y: " << velocity_y << "  z: " << velocity_z << "  [m/s]\n";
        std::cout << "total v: " << velocity << std::endl;
        std::cout <<"\n";
        
        get_stats();
        
        device_wait(10); 
    }
    
    return 0;
}
