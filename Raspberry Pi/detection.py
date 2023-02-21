import math
import time
import filtering 

def fall_detection_1():
  rms_T = 2.5
  rms = math.sqrt(data.accx()**2 + data.accx()**2 + data.accx()**2)
  if rms > rms_T:
      start_time = time.time()
      while (time.time() - start_time) < 300:
        if abs(data.pitch()) > 20 or abs(data.roll()) > 20:
          return True
      return False

