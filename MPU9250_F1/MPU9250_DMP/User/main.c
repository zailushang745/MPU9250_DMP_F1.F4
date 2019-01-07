/***************************************************
创建者：Nick Zhang
创建时间： 2019.1.7
符合sparkfun协议的stm32+mpu9250的IMU
***************************************************/
 
#include "delay.h"
#include "usart.h"

int main(void)
{  
    USART1_Config();  
	  USART_SendString(USART1,"USART INIT\r");
    i2cInit();      
	  USART_SendString(USART1,"IIC INIT\r");
    delay_ms(5);
		Mpu_Init(1);
		USART_SendString(USART1,"MPU INIT\r");
		output_stream_on = true;
    while(1)
    {
//			computeEulerAngles();
       Update_attitude_Angle();
			
				updateAccel();
	// Conversion from g to similar unit as older versions of Razor...
	accel[0] = -250.0f*calcAccel(ax);
	accel[1] = 250.0f*calcAccel(ay);
	accel[2] = 250.0f*calcAccel(az);
			
			
				updateGyro();
	// Conversion from degrees/s to rad/s.
	gyro[0] = calcGyro(gx)*PI/180.0f;
	gyro[1] = -calcGyro(gy)*PI/180.0f;
	gyro[2] = -calcGyro(gz)*PI/180.0f;	

			
				updateCompass();
	// Conversion from uT to mGauss.
	magnetom[0] = (10.0f*calcMag(my));
	magnetom[1] = (-10.0f*calcMag(mx));
	magnetom[2] = (10.0f*calcMag(mz));		
	
				updateTemperature();
				
//			computeEulerAngles();

  if (output_mode == OUTPUT__MODE_CALIBRATE_SENSORS)  // We're in calibration mode
		{
		//      check_reset_calibration_session();  // Check if this session needs a reset
					if (output_stream_on || output_single_on) 
						 output_calibration(curr_calibration_sensor);
		}
				
  else if (output_mode == OUTPUT__MODE_ANGLES)  // Output angles
    {
      // Apply sensor calibration
      compensate_sensor_errors();

//      // Run DCM algorithm
//      Compass_Heading(); // Calculate magnetic heading
//      Matrix_update();
//      Normalize();
//      Drift_correction();
//      Euler_angles();   
			
      if (output_stream_on || output_single_on) 
				output_angles();
    }
  else if (output_mode == OUTPUT__MODE_ANGLES_AG_SENSORS)  // Output angles + accel + rot. vel
    {
      // Apply sensor calibration
      compensate_sensor_errors();
			
				//      // Run DCM algorithm
		//      Compass_Heading(); // Calculate magnetic heading
		//      Matrix_update();
		//      Normalize();
		//      Drift_correction();
		//      Euler_angles();  
      
      if (output_stream_on || output_single_on)
				output_both_angles_and_sensors_text();
    }
		
  else  // Output sensor values
    {      
      if (output_stream_on || output_single_on)
				output_sensors();
    }
    
    
		output_single_on = false;
    
//  }
//           printf("Pitch:");
//            printf("%f ",Pitch);


//            printf("Roll:");
//            printf("%f ",Roll);     


//            printf("Yaw:");        
//            printf("%f ",Yaw);
  
				
//						Update_Magnetometer();
//						printf("M:%d \n",Direction);
    }
}

 


