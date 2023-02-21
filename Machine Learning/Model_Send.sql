CREATE MODEL FallDetectionmodel
OPTIONS (
  model_type='TENSORFLOW',
  model_path='gs://falling_detection_bucket/saved_model',
  input_tensor_schema='SVM_ACC:FLOAT, SVM_GYR:FLOAT, PITCH:FLOAT, ROLL:FLOAT',
  output_tensor_schema='Prediction:FLOAT'
) AS
SELECT * FROM DatafromAccandGyro.DATA