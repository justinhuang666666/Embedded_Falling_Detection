# mpu6050
from get_value import get_value_1
from filtering import Filters
import time
import math

# mqtt
from Fall_Detection import TBM_algorithm
import threading
import paho.mqtt.client as mqtt

# BigQuery
from Bigquery_ML import Send_To_BigQuery

broker_address = "test.mosquitto.org"
port = 8884

# encryption
client = mqtt.Client()
client.tls_set(ca_certs="mosquitto.org.crt", certfile="client.crt", keyfile="client.key")
client.connect("test.mosquitto.org", port=8884)

# mqtt topics
topic_gps_LAT = "IC.embedded/fall_detection/GPS_LAT"
topic_gps_LNG = "IC.embedded/fall_detection/GPS_LNG"
topic_fall = "IC.embedded/fall_detection/Fall"
topic_SVM_acc = "IC.embedded/fall_detection/SVM_acc"
topic_SVM_gyr = "IC.embedded/fall_detection/SVM_gyr"
topic_angle = "IC.embedded/fall_detection/Angle"

# GPIO setting
import RPi.GPIO as GPIO  # Import Raspberry Pi GPIO library

GPIO.setwarnings(False)  # Ignore warning for now
GPIO.setmode(GPIO.BOARD)  # Use physical pin numbering
GPIO.setup(11, GPIO.OUT, initial=GPIO.LOW)  # Set pin 7 to be an output pin and set initial value to low (off)
GPIO.setup(18, GPIO.IN)  # Set pin 11 to be an input pin

# GPS
from GPS import GPSParser

gps_parser = GPSParser("/dev/ttyAMA0")

# TODO: add BigQ
# from sendmsg import Send_To_BigQuery

mpu = get_value_1(0x69)
TBM = TBM_algorithm()
Bigquery = Send_To_BigQuery()

print('callibration starting')
mpu.calibration_filter()
filters = Filters(mpu.accx_offset, mpu.accy_offset, mpu.accz_offset, mpu.gyroy_offset, mpu.gyrox_offset,
                  mpu.gyroz_offset)

lock = threading.Lock()


def threading_firststage():
    lock.acquire()
    i = 0
    start = time.time()
    print("first thread")

    while TBM.Falling == 1:
        print("button:" + str(GPIO.input(18)))
        # print("first thread while loop")
        accel_data = mpu.get_accel_data()
        acc_x = accel_data['x']
        acc_y = accel_data['y']
        acc_z = accel_data['z']
        # accel_data = mpu.get_accel_data()
        gyro_data = mpu.get_gyro_data()
        gyr_x = gyro_data['x']
        gyr_y = gyro_data['y']
        gyr_z = gyro_data['z']

        filters.Complementary_Filter(acc_x, acc_y, acc_z, gyr_y, gyr_x, gyr_z)
        PITCH = filters.Pitch_CF
        ROLL = filters.Roll_CF

        ANGLE = max(PITCH, ROLL)
        SVM_acc = math.sqrt(abs(acc_x) * abs(acc_x) + abs(acc_y) * abs(acc_y) + abs(acc_z) * abs(acc_z))
        SVM_gyr = math.sqrt(abs(gyr_x) * abs(gyr_x) + abs(gyr_y) * abs(gyr_y) + abs(gyr_z) * abs(gyr_z))

        TBM.Check_Falling(acc_x, acc_y, acc_z)
        if time.time() - start >= 0.1:
            client.publish(topic_angle, ANGLE)

            client.publish(topic_SVM_acc, SVM_acc)
            client.publish(topic_SVM_gyr, SVM_gyr)
            # print("send data")
            start = time.time()

    lock.release()
    thread_2 = threading.Thread(target=threading_secondstage, name='falling_check_second_stage')
    thread_2.start()

    # threading.current_thread().join()


def threading_secondstage():
    lock.acquire()
    print("second thread")
    while TBM.TWO_HUNDRED_IN_FULL < 200:
        print("second thread while loop")
        accel_data = mpu.get_accel_data()
        acc_x = accel_data['x']
        acc_y = accel_data['y']
        acc_z = accel_data['z']
        gyro_data = mpu.get_gyro_data()
        gyr_x = gyro_data['x']
        gyr_y = gyro_data['y']
        gyr_z = gyro_data['z']

        SVM_Gyr = math.sqrt(gyr_x*gyr_x + gyr_y*gyr_y + gyr_z*gyr_z)
        filters.Complementary_Filter(acc_x, acc_y, acc_z, gyr_y, gyr_x, gyr_z)
        PITCH = filters.Pitch_CF
        ROLL = filters.Roll_CF

        # print("Pitch: " + str(PITCH))
        # print("ROLL: " + str(ROLL))
        TBM.FIFO_Appending(acc_x, acc_y, acc_z, gyr_y, gyr_x, gyr_z, PITCH, ROLL)
        Bigquery.insert_rows(TBM.FIFO_SVM_DW2[TBM.TWO_HUNDRED_IN_FULL], SVM_Gyr, PITCH, ROLL)

    Falling_thread2 = TBM.Event_Classification()
    client.publish(topic_fall, Falling_thread2)
    print("Falling: " + str(Falling_thread2))
    print("feature2: " + str(TBM.Feature2))
    print("feature6: " + str(TBM.Feature6))
    start = time.time()

    if Falling_thread2 == 1:
        Bigquery.Do_DeepLearning()
        Bigquery.Getting_Value_from_DL()
        TBM.Falling_thread2 = Bigquery.FALL

    while Falling_thread2 == 1:
        GPIO.output(11, GPIO.HIGH)
        if GPIO.input(18):
            print("bonjour")
            Falling_thread2 = 0
            Bigquery.FALL = 0
            Bigquery.Delete_Table()
            GPIO.output(11, GPIO.LOW)  # Turn off
            client.publish(topic_fall, Falling_thread2)
        if time.time() - start >= 0.1:
            gps_parser.run()
            client.publish(topic_fall, Falling_thread2)
            #GPS = {gps_parser.lat, gps_parser.lat_dir, gps_parser.lon, gps_parser.lon_dir}
            client.publish(topic_gps_LAT, gps_parser.lat)
            client.publish(topic_gps_LNG, gps_parser.lon)
            start = time.time()
    Bigquery.FALL = 0
    Bigquery.Delete_Table()
    TBM.clear()
    TBM.Falling = 1
    TBM.TWO_HUNDRED_IN_FULL = 0
    lock.release()
    thread_1 = threading.Thread(target=threading_firststage, name='falling_check_first_stage')
    thread_1.start()
    # threading.current_thread().join()


thread_first = threading.Thread(target=threading_firststage, name='first_falling_check_first_stage')

while True:
    if not thread_first.is_alive():
        thread_first.start()





