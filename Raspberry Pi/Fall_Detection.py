import math
from collections import deque


class TBM_algorithm:
    FIFO_ACC_X_DW1 = deque(maxlen=100)
    FIFO_ACC_Y_DW1 = deque(maxlen=100)
    FIFO_ACC_Z_DW1 = deque(maxlen=100)
    FIFO_ACC_X_DW2 = deque(maxlen=200)
    FIFO_ACC_Y_DW2 = deque(maxlen=200)
    FIFO_ACC_Z_DW2 = deque(maxlen=200)

    FIFO_W_DW2     = deque(maxlen=200)
    FIFO_SVM_DW1   = deque(maxlen=100)
    FIFO_SVM_DW2   = deque(maxlen=200)

    Falling = 1
    TWO_HUNDRED_IN_FULL = 0

    Threshold_0 = 4  
    Threshold_0_Diff = 0.5

    N_FIFO_ACC_DW1 = 100
    N_FIFO_ACC_DW2 = 200
    N_FIFO_GYR_DW2 = 200

    Max_SVM_DIFF = 0.0
    SVM_AVR_DYN  = 0.0
    SVM_AVR_STA  = 0.0

    ROLL_TOTAL   = 0.0
    PITCH_TOTAL  = 0.0

    # do not change 
    Feature1 = 0.0
    Feature2 = 0.0
    Feature3 = 0.0
    Feature4 = 0.0
    Feature5 = 0.0
    Feature6 = 0.0
    Feature7 = 0.0
    


    # to modify 
    Threshold_1 = 0
    Threshold_2 = 2.2*9.8
    Threshold_3 = 0.5
    Threshold_4 = 0.5
    Threshold_5 = 0.5
    Threshold_6 = 40
    Threshold_7 = 0.5


    def __init__(self): 
        for i in range(100):
            self.FIFO_ACC_X_DW1.append(0)
            self.FIFO_ACC_Y_DW1.append(0)
            self.FIFO_ACC_Z_DW1.append(0)
            self.FIFO_ACC_X_DW2.append(0)
            self.FIFO_ACC_Y_DW2.append(0)
            self.FIFO_ACC_Z_DW2.append(0)
            self.FIFO_W_DW2 .append(0)   
            self.FIFO_SVM_DW1.append(0)
            self.FIFO_SVM_DW2.append(0)
        for i in range(100): 
            self.FIFO_SVM_DW2.append(0)
            self.FIFO_ACC_X_DW2.append(0)
            self.FIFO_ACC_Y_DW2.append(0)
            self.FIFO_ACC_Z_DW2.append(0)
        print('init fall detection  done ')


            

    def Check_Falling(self, Acc_X, Acc_Y, Acc_Z):
        self.FIFO_ACC_X_DW1.append(Acc_X)
        self.FIFO_ACC_Y_DW1.append(Acc_Y)
        self.FIFO_ACC_Z_DW1.append(Acc_Z)
        SVM = math.sqrt(abs(Acc_X)*abs(Acc_X) + abs(Acc_Y)*abs(Acc_Y) + abs(Acc_Z)*abs(Acc_Z))
        SVM_diff = abs((SVM - self.FIFO_SVM_DW1[len(self.FIFO_SVM_DW1)-1]))
        self.Max_SVM_DIFF = SVM_diff if SVM_diff > self.Max_SVM_DIFF else self.Max_SVM_DIFF
        self.SVM_AVR_STA += SVM
        self.FIFO_SVM_DW1.append(SVM)   
        if abs(max(abs(Acc_X),abs( Acc_Y),abs( Acc_Z))) < self.Threshold_0 and (abs(self.FIFO_ACC_X_DW1[len(self.FIFO_ACC_X_DW1)-1] - self.FIFO_ACC_X_DW1[len(self.FIFO_ACC_X_DW1) - 2]) > self.Threshold_0_Diff\
                or abs(self.FIFO_ACC_Y_DW1[len(self.FIFO_ACC_Y_DW1)-1] - self.FIFO_ACC_Y_DW1[len(self.FIFO_ACC_Y_DW1)-2]) > self.Threshold_0_Diff\
                or abs(self.FIFO_ACC_Z_DW1[len(self.FIFO_ACC_Z_DW1)-1] - self.FIFO_ACC_Z_DW1[len(self.FIFO_ACC_Z_DW1)-2]) > self.Threshold_0_Diff):
            self.Falling = 0
        else:
            self.Falling = 1
    def FIFO_Appending(self, Acc_X, Acc_Y, Acc_Z, Gyr_X, Gyr_Y, Gyr_Z, PITCH, ROLL):
        self.FIFO_ACC_X_DW2.append(Acc_X)
        self.FIFO_ACC_Y_DW2.append(Acc_Y)
        self.FIFO_ACC_Z_DW2.append(Acc_Z)

        self.FIFO_W_DW2.append(math.sqrt(abs(Gyr_X)*abs(Gyr_X) + abs(Gyr_Y)*abs(Gyr_Y) + abs(Gyr_Z)*abs(Gyr_Z)))
        SVM = math.sqrt(abs(Acc_X) * abs(Acc_X) + abs(Acc_Y) * abs(Acc_Y) + abs(Acc_Z) * abs(Acc_Z))
        SVM_diff = abs((SVM - self.FIFO_SVM_DW2[len(self.FIFO_SVM_DW2)-1]))
        self.Max_SVM_DIFF = SVM_diff if SVM_diff > self.Max_SVM_DIFF else self.Max_SVM_DIFF
        self.SVM_AVR_DYN += SVM
        self.FIFO_SVM_DW2.append(SVM)
        self.ROLL_TOTAL += ROLL
        self.PITCH_TOTAL += PITCH
        self.TWO_HUNDRED_IN_FULL += 1

    def Getting_Feature1(self):
        min1 = self.FIFO_SVM_DW1[self.FIFO_SVM_DW1.index(min(self.FIFO_SVM_DW1))]
        min2 = self.FIFO_SVM_DW2[self.FIFO_SVM_DW2.index(min(self.FIFO_SVM_DW2))]
        self.Feature1 = min(min1, min2)

    def Getting_Feature2(self):
        max1 = self.FIFO_SVM_DW1[self.FIFO_SVM_DW1.index(max(self.FIFO_SVM_DW1))]
        max2 = self.FIFO_SVM_DW2[self.FIFO_SVM_DW2.index(max(self.FIFO_SVM_DW2))]
        self.Feature2 = max(max1, max2)

    def Getting_Feature3(self):
        self.Feature3 = self.Max_SVM_DIFF

    def Getting_Feature4(self):
        for i in range(len(self.FIFO_SVM_DW2)):
            DIFF = self.FIFO_SVM_DW2[i] - self.SVM_AVR_DYN/self.N_FIFO_ACC_DW2
            self.Feature4 += DIFF*DIFF
        self.Feature4 = self.Feature4/self.N_FIFO_ACC_DW2

    def Getting_Feature5(self):
        for i in range(len(self.FIFO_SVM_DW1)):
            DIFF = self.FIFO_SVM_DW1[i] - self.SVM_AVR_STA/self.N_FIFO_ACC_DW1
            self.Feature5 += DIFF*DIFF
        self.Feature5 = self.Feature4/self.N_FIFO_ACC_DW2

    def Getting_Feature6(self):
        self.Feature6 = max(abs(self.ROLL_TOTAL), abs(self.PITCH_TOTAL))/self.N_FIFO_ACC_DW2
        #print("feature6: " + str(self.Feature6))

    def Getting_Feature7(self):
        self.Feature7 = max(self.FIFO_W_DW2)

    def Event_Classification(self):
        self.Getting_Feature1()
        self.Getting_Feature2()
        self.Getting_Feature3()
        self.Getting_Feature4()
        self.Getting_Feature5()
        self.Getting_Feature6()
        self.Getting_Feature7()

        if self.Feature2 > self.Threshold_2 and self.Feature6 > self.Threshold_6:
            return 1
        else:
            return 0 
    def clear(self):
        for i in range(100):
            self.FIFO_ACC_X_DW1.append(0)
            self.FIFO_ACC_Y_DW1.append(0)
            self.FIFO_ACC_Z_DW1.append(0)
            self.FIFO_ACC_X_DW2.append(0)
            self.FIFO_ACC_Y_DW2.append(0)
            self.FIFO_ACC_Z_DW2.append(0)
            self.FIFO_W_DW2 .append(0)   
            self.FIFO_SVM_DW1.append(0)
            self.FIFO_SVM_DW2.append(0)
        for i in range(100): 
            self.FIFO_SVM_DW2.append(0)
            self.FIFO_ACC_X_DW2.append(0)
            self.FIFO_ACC_Y_DW2.append(0)
            self.FIFO_ACC_Z_DW2.append(0)
        self.TWO_HUNDRED_IN_FULL = 0
        self.Falling = 1

        self.Max_SVM_DIFF = 0.0
        self.SVM_AVR_DYN  = 0.0
        self.SVM_AVR_STA  = 0.0

        self.ROLL_TOTAL   = 0.0
        self.PITCH_TOTAL  = 0.0
        # do not change 
        self.Feature1 = 0.0
        self.Feature2 = 0.0
        self.Feature3 = 0.0
        self.Feature4 = 0.0
        self.Feature5 = 0.0
        self.Feature6 = 0.0
        self.Feature7 = 0.0

