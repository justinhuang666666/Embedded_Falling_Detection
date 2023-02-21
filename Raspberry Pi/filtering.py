import math
import numpy as np
from time import sleep
from mpu6050 import mpu6050

class Filters:
    #Global Variables
    dt = 0.01
    #Bias
    N_bias = 100
    #Low Pass Filter
    Sampling_frequency = 1000
    Cutoff_frequency_Low = 100
    #Complementary filter
    alpha = 0.1
    Roll_CF = 0.0
    Pitch_CF = 0.0
    #EKF
    Roll_EKF = 0.0
    Pitch_EKF = 0.0
    g = 9.81
    P = np.eye(2)
    Q = np.eye(2)
    R = np.eye(2)

    #sensor offsets
    Acc_Bias_X = 0.0
    Acc_Bias_Y = 0.0
    Acc_Bias_Z = 0.0

    Gyr_Bias_X = 0.0
    Gyr_Bias_Y = 0.0
    Gyr_Bias_Z = 0.0
    def __init__(self, Acc_Offset_X, Acc_Offset_Y, Acc_Offset_Z, Gyr_Offset_X, Gyr_Offset_Y, Gyr_Offset_Z):
        #First Getting the Offset for Accelerometer and Gyroscope
        self.Acc_Bias_X = Acc_Offset_X
        self.Acc_Bias_Y = Acc_Offset_Y
        self.Acc_Bias_Z = Acc_Offset_Z
        self.Gyr_Bias_X = Gyr_Offset_X
        self.Gyr_Bias_Y = Gyr_Offset_Y
        self.Gyr_Bias_Z = Gyr_Offset_Z

    def Low_Pass_Filter(self, X, Y):
        Y_Next = Y + (1/(1+1/(2.0*math.pi*(1/self.Sampling_frequency)*self.Cutoff_frequency_Low)))*(X - Y)
        return Y_Next
    #def High_Pass_Filter(self, X, Y):

    def Complementary_Filter(self, acc_X, acc_Y, acc_Z, gyro_X, gyro_Y, gyro_Z):
        acc_X -= self.Acc_Bias_X
        acc_Y -= self.Acc_Bias_Y
        acc_Z -= self.Acc_Bias_Z
        gyro_X -= self.Gyr_Bias_X
        gyro_Y -= self.Gyr_Bias_Y
        gyro_Z -= self.Gyr_Bias_Z

        #Convert degrees to radian
        gyro_X = gyro_X*math.pi/180.0
        gyro_Y = gyro_Y*math.pi/180.0
        gyro_Z = gyro_Z*math.pi/180.0
        self.Roll_CF = self.Roll_CF*math.pi/180.0
        self.Pitch_CF = self.Pitch_CF*math.pi/180.0

        #Calculate Euler roll and pitch angle based on accelerometer
        Acc_Roll = math.atan2(acc_Y, math.sqrt(acc_X ** 2.0 + acc_Z ** 2.0))
        Acc_Pitch = math.atan2(-acc_X, math.sqrt(acc_Y ** 2.0 + acc_Z ** 2.0))

        #Calculate Euler angle derivatives
        roll_deriv = gyro_X + math.sin(self.Roll_CF)*math.tan(self.Pitch_CF)*gyro_Y + math.cos(self.Roll_CF)*math.tan(self.Pitch_CF)*gyro_Z
        pitch_deriv = math.cos(self.Roll_CF)*gyro_Y - math.sin(self.Roll_CF)*gyro_Z

        #Update the values of roll and pitch
        self.Roll_CF = self.alpha*Acc_Roll + (1-self.alpha)*(self.Roll_CF + self.dt*roll_deriv)
        self.Pitch_CF = self.alpha*Acc_Pitch + (1-self.alpha)*(self.Pitch_CF + self.dt*pitch_deriv)

        #convert rad into degree
        #recheck the datasheet to see the unit of the output of accelerometer and gyroscope, maybe we need to convert the unit
        #in previous and also convert the unit here
        #return self.Roll_CF, self.Pitch_CF
        self.Roll_CF = self.Roll_CF*180.0/math.pi
        self.Pitch_CF = self.Pitch_CF*180.0/math.pi

    #Implement the Extended Kalman Filter:
    def EKF(self,acc_X, acc_Y, acc_Z, gyro_X, gyro_Y, gyro_Z):
        acc_X -= self.Acc_Bias_X
        acc_Y -= self.Acc_Bias_Y
        acc_Z -= self.Acc_Bias_Z
        gyro_X -= self.Gyr_Bias_X
        gyro_Y -= self.Gyr_Bias_Y
        gyro_Z -= self.Gyr_Bias_Z

        #Convert degrees to radians
        gyro_X = gyro_X*math.pi/180.0
        gyro_Y = gyro_Y*math.pi/180.0
        gyro_Z = gyro_Z*math.pi/180.0
        self.Roll_EKF = self.Roll_EKF*math.pi/180.0
        self.Pitch_EKF = self.Pitch_EKF*math.pi/180.0
        # Calculate Euler roll and pitch angle based on accelerometer
        #Acc_Roll = math.atan2(acc_Y, math.sqrt(acc_X ** 2.0 + acc_Z ** 2.0))
        #Acc_Pitch = math.atan2(-acc_X, math.sqrt(acc_Y ** 2.0 + acc_Z ** 2.0))

        # Calculate Euler angle derivatives based on gyroscope--> this also the f(x,u)
        roll_deriv = gyro_X + math.sin(self.Roll_EKF) * math.tan(self.Pitch_EKF) * gyro_Y + math.cos(self.Roll_EKF) * math.tan(self.Pitch_EKF) * gyro_Z
        pitch_deriv = math.cos(self.Roll_EKF) * gyro_Y - math.sin(self.Roll_EKF) * gyro_Z

        state =np.array([[self.Roll_EKF], [self.Pitch_EKF]]) + np.array([[self.dt*roll_deriv], [self.dt*pitch_deriv]])

        #calculate the Jacobian of f(x,u)
        A = np.array([[(math.cos(state[0])*math.tan(state[1])*gyro_Y - math.sin(state[0])*math.tan(state[1])*gyro_Z),(math.cos(state[0])*mpmath.sec(state[1])*mpmath.sec(state[1])*gyro_Y - math.sin(state[0])*mpmath.sec(state[1])*mpmath.sec(state[1])*gyro_Z)],[(-math.sin(state[0])*gyro_Y - math.cos(state[0])*gyro_Z) , 0]])
        #update P
        self.P = self.P + self.dt * (A.dot(self.P) + self.P.dot(np.transpose(A)) + self.Q)

        #now calculate the Jacobian of h from the angles we get by estimation
        C = self.g* np.array([[0, (math.cos(state[0]))], [-math.cos(state[1])*math.cos(state[0]), math.sin(state[0])*math.sin(state[1])], [math.cos(state[1])*math.cos(state[0]), math.sin(state[1])*math.cos(state[0])]])

        #Calculate the Kalman gain
        S = C.dot(self.P.dot(np.transpose(C))) + self.R
        K = self.P.dot(np.transpose(C).dot(np.linalg.inv(S)))

        #Calculate the error between the measured angle derived by accelerometer and estimated angle
        e = np.array([[acc_X], [acc_Y], [acc_Z]]) - self.g*np.array([[math.sin(state[0])], [-math.cos(state[1])*math.sin(state[0])],[-math.cos(state[1])*math.cos(state[0])]])
        #update state
        state = state + K.dot(e)

        #update P
        self.P = self.P - K.dot(C.dot(self.P))

        self.Roll_EKF = state[0]*180.0/math.pi
        self.Pitch_EKF = state[1]*180.0/math.pi
















