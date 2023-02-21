from google.cloud import pubsub_v1
import datetime
import json
import time
from google.cloud import bigquery
import os


#pre-setup of the environment in raspberry pi
#virtualenv venv #this is to create a virtual environment
#source venv/bin/activate   #this is to activate the virtual environment
#pip install google-cloud-pubsub
#pip install google-cloud-bigquery
#export GOOGLE_APPLICATION_CREDENTIALS="fallingdetection-376711-4e5bac0ce08a.json"  #this is to set the JSON file as the value of an envrionment variable
#for the above command, to check the path of json file, if the file is in the current path, then just this, otherwise, add the path
#we could set the environment variable in the command line, but I just set it in the init function of class Send_To_BigQuery

class Send_To_BigQuery(pubsub_v1, bigquery):
    project_id = "<falling detection-376711>"
    topic_name = "<MyTopic>"

    publisher
    topic_path

    futures = dict()
    #client  = bigquery.Client()

    def __int__(self):
        pubsub_v1.__init__(self)
        bigquery.__init__(self)
        self.publisher = pubsub_v1.PublisherClient()
        self.topic_path = self.publisher.topic_path(self.project_id, self.topic_name)
        os.environ["GOOGLE_APPLICATION_CREDENTIALS"] = "fallingdetection-376711-4e5bac0ce08a.json" #check the path of json file

    def get_callback(self, data):
        def callback():
            try:
                self.futures.pop(data)
            except:
                print("please handle {} for {}.".format(self.futures.exception(), data))

        return callback

    def sendmessage(self, acc_x, acc_y, acc_z, gyr_x, gyr_y, gyr_z, roll, pitch):
        timenow = float(time.time())
        data = {"Time": timenow, "Acc_X": acc_x, "Acc_Y": acc_y, "Acc_Z": acc_z, "Gyro_X": gyr_x, "Gyro_Y": gyr_y, "Gyro_Z": gyr_z, "pitch": pitch, "roll": roll}
        self.futures = self.publisher.publish(
            self.topic_path, data=(json.dumps(data).encode("utf-8"))
        )
        self.futures.add_done_callback(self.get_callback(self.futures, data))
        sleep(0.1)
######not finished yet, still need to add SQL queries that can manipulate the bigquery table, the machine learning model will be
######written in SQL form and send to the database

