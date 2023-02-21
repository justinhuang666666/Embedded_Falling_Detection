For Machine Learning part, we mainly use the RNN model to train based on the open source falling detection dataset
To use RNN is mainly because all the data in this case has relationship in time series, which is exactly suitable in this case.
It mainly contains four parts:
1. the data extraction file which is used to extract the data
2. the model file which is used to define, train, evaluation, and save the model
3. SQL file which send the saved model to bigquery
4. Open Source Dataset
