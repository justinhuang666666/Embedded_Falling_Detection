import smbus
from time import sleep 
from filtering  import Filters

class get_value_1:
    address = None 

    #offset
    accx_offset = 0
    accy_offset = 0
    accz_offset = 0
    gyrox_offset = 0
    gyroy_offset = 0
    gyroz_offset = 0

    def  __init__(self, address) -> None:
        self.address = address
        self.bus = smbus.SMBus(1)
        # Wake up the MPU-6050 since it starts in sleep mode
        self.bus.write_byte_data(self.address, 0x6B, 0x00)
        #gyro 
        self.bus.write_byte_data(self.address,0x1B, 0x18)
        #accelerometer 
        self.bus.write_byte_data(self.address,0x1C, 0x18)
    def combine_2_register(self, register):
        high = self.bus.read_byte_data(self.address, register)
        low = self.bus.read_byte_data(self.address, register + 1)

        value = (high << 8) + low

        if (value >= 0x8000):
            return -((65535 - value) + 1)
        else:
            return value
    
    def get_accel_data(self):
        #return the acc in g 
        acc_X = self.combine_2_register(0x3B)/2048.0
        acc_Y = self.combine_2_register(0x3D)/2048.0
        acc_Z = self.combine_2_register(0x3F)/2048.0
        #return {'x': acc_X, 'y': acc_Y, 'z': acc_Z}
        return {'x': acc_X*9.80665, 'y': acc_Y*9.80665, 'z': acc_Z*9.80665}

    def get_gyro_data(self):
        #return the angular velocity in 

        gyro_X = self.combine_2_register(0x43)/16.4
        gyro_Y = self.combine_2_register(0x45)/16.4
        gyro_Z = self.combine_2_register(0x47)/16.4
        return {'x':gyro_X , 'y': gyro_Y, 'z':gyro_Z }

    def calibration_filter(self):
        accx = 0
        accy = 0
        accz = 0

        gyrox = 0
        gyroy =0
        gyroz = 0
        for i in range(100):
            # accel_data = self.get_accel_data()
            # accx += accel_data['x']
            # accy += accel_data['y']
            # accz += accel_data['z']
            

            gyro_data = self.get_gyro_data()
            gyrox += gyro_data['x']
            gyroy += gyro_data['y']
            gyroz += gyro_data['z']
            sleep(0.1)

        self.accx_offset = accx / 100
        self.accy_offset = accy / 100
        self.accz_offset = accz / 100

        self.gyrox_offset = gyrox / 100
        self.gyroy_offset = gyroy / 100
        self.gyroz_offset = gyroz / 100

        # print("acc_X offset: " + str(filters.Acc_Bias_X))
        # print("acc_Y_offset: " + str(filters.Acc_Bias_Y))
        # print("acc_Z_offset: " + str(filters.Acc_Bias_Z))
        # print("gyr_X_offset: " + str(filters.Gyr_Bias_X))
        # print("gyr_Y_offset: " + str(filters.Gyr_Bias_Y))
        # print("gyr_Z_offset: " + str(filters.Gyr_Bias_Z))

        # print("original pitch is: " + str(filters.Pitch_CF))
        
        sleep(5)
       
        
        
        

 
