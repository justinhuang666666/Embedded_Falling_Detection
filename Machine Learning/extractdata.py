import tensorflow as tf
import pandas as pd
import numpy as np


# 0 is SVM
# 1 is pitch
# 2 is roll
# 3 is SVM_Gyro
def extractfalldata(Backward, LateralPosition, S1_1, index=0):
    df = pd.read_csv("C:/Users/nickz/Desktop/Data/Fall/Backward/LateralPosition/FileTXT/S1_1.txt",
                     encoding='ISO-8859-1',
                     sep=';', skiprows=1, names=['Time', 'acc_x', 'acc_y', 'acc_z', 'gyr_x', 'gyr_y', 'gyr_z', 'mag_x',
                                                 'mag_y', 'mag_z', 'SVM', 'yaw', 'pitch', 'roll'])
    df['SVM_Gyro'] = np.sqrt(df['gyr_x'] ** 2 + df['gyr_y'] ** 2 + df['gyr_z'] ** 2)
    dataset = df.drop(columns=['Time', 'mag_x', 'mag_y', 'mag_z', 'yaw', 'gyr_x', 'gyr_y',
                               'gyr_z', 'acc_x', 'acc_y', 'acc_z'])
    dataset = dataset.sample(n=200, axis=0)
    dataset = dataset.sort_index(axis=0)
    input_data = dataset.values[:, index].astype('float32')
    return input_data


def extractadldata(LyingStand,S1_1, int=0):
    df = pd.read_csv("C:/Users/nickz/Desktop/Data/ADL/LyingStand/FileTXT/S1_1.txt",
                     encoding='ISO-8859-1',
                     sep=';', skiprows=1, names=['Time', 'acc_x', 'acc_y', 'acc_z', 'gyr_x', 'gyr_y', 'gyr_z', 'mag_x',
                                                 'mag_y', 'mag_z', 'SVM', 'yaw', 'pitch', 'roll'])
    df['SVM_Gyro'] = np.sqrt(df['gyr_x'] ** 2 + df['gyr_y'] ** 2 + df['gyr_z'] ** 2)
    dataset = df.drop(columns=['Time', 'mag_x', 'mag_y', 'mag_z', 'yaw', 'gyr_x', 'gyr_y',
                               'gyr_z', 'acc_x', 'acc_y', 'acc_z'])
    dataset = dataset.sample(n=200, axis=0)
    dataset = dataset.sort_index(axis=0)
    input_data = dataset.values[:, int].astype('float32')
    return input_data



def falldataset():
    falldata=[]
    for u in [0, 1, 2, 3]:
        falldata_u=[]
        for i in ['Backward','Forward','LateralLeft','LateralRight','Syncope']:
            for j in ['LateralPosition']:
                for k in['S1_1','S2_1','S3_1','S4_1','S5_1','S6_1','S7_1','S8_1']:
                    falldata_u.append(extractfalldata(i,j,k,u))
        falldata.append(falldata_u)

    return falldata



def adldataset():
    adldata=[]
    for u in [0, 1, 2, 3]:
        adldata_u=[]
        for i in ['LyingStand','PickStand','SittingStand','StepUpDown','Walk']:
            for j in['S1_1','S2_1','S3_1','S4_1','S5_1','S6_1','S7_1','S8_1']:
                    adldata_u.append(extractadldata(i,j,u))
        adldata.append(adldata_u)
    return adldata


def createdataset(dataset1,dataset2):
    datax, datay = [], []
    for i in np.arange(40):
        datax.append(dataset1[0][i][:])
        datax.append(dataset1[1][i][:])
        datax.append(dataset1[2][i][:])
        datax.append(dataset1[3][i][:])
        datay.append(0.0)
    for j in np.arange(40):
        datax.append(dataset2[0][j][:])
        datax.append(dataset2[1][j][:])
        datax.append(dataset2[2][j][:])
        datax.append(dataset2[3][j][:])
        datay.append(1.0)

    datax=np.reshape(datax, (80, 4, 200))
    combined = list(zip(datax, datay))
    np.random.shuffle(combined)
    datax[:], datay[:] = zip(*combined)

    return datax,datay







