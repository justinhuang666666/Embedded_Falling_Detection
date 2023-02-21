import tensorflow as tf
import pandas as pd
import numpy as np
from extractdata import createdataset,adldataset,falldataset

datax,datay=createdataset(adldataset(),falldataset())
#The datax_eva and datay_eva is used for the evaluation and would be extracted based on different dataset, we can change the dataset we use in extractdata.py
datax_eva, datay_eva = createdataset(adldataset(), falldataset())

traning_perc=0.8
trainx=datax[:64]
validx=datax[64:]
trainy=datay[:64]
validy=datay[64:]

evalx = datax_eva[:64]
evaly = datay_eva[:64]

model = tf.keras.Sequential([
    tf.keras.layers.LSTM(64, input_shape=(4, 200), return_sequences=False),
    tf.keras.layers.Dense(1, activation='sigmoid')
])

print(model.summary())

#loss and optimizer
loss = tf.keras.losses.BinaryCrossentropy(from_logits=True)
optim = tf.keras.optimizers.Adam(lr=0.001)
metrics = ["accuracy"]

model.compile(loss=loss, optimizer=optim, metrics=metrics)

#training
batch_size = 20
epochs = 5
print("Start Training")
model.fit(x=trainx,
          y=trainy,
          validation_data=(valix,validy),
          epochs=epochs,
          batch_size=batch_size,
          verbose=2)
#evaluate
model.evaluate(x=evalx,
               y=evaly,
               batch_size=batch_size,
               verbose=2)

import sys; sys.exit()

model.save('FallDetection_model', save_format='tf')