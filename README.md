# Embedded System - Falling Detection

This repository contains an implementation of a falling detection device called SAFA, designed by Alsteens Lou, Jubo Xu, Justin Huang and Nick Zheng for the embedded system coursework.   

The SAFA is based upon Raspberry Pi Zero, MPU6050 and NEO-6M GPS.

SAFA uses a fusion fall detection algorithm combining threshold-based method (TBM) and machine learning  (ML) method. When an abnormal event occurs, the SAFA exploits the TBM to preliminarily identify the event based on triaxial acceleration samples collected by the MPU6050. The MPU6050 captures a series of critical phases (the falling phase, the impact phase, and the resting phase) of a fall. If this event is identified as a suspected fall event, a three-dimensional time series containing 300 triaxial acceleration samples (3s) is transmitted to the server, and finally the ML algorithm is applied to classify the suspected fall event to determine whether it is a fall.

SAFA has a user-friendly GUI which has functionalities such as real-time data plotting, map navigation and falling animation.

## Directory structure
- ```Raspberry Pi``` - contains the code on the Raspberry Pi Zero
- ```Machine Learning``` - contains the code and dataset for machine learning
- ```GUI``` - contains source code for the graphic user interface
