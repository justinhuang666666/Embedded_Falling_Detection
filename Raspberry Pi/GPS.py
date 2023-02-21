import serial
import pynmea2

class GPSParser:
    lat = ''
    lat_dir = ''
    lon = ''
    lon_dir = ''

    def __init__(self, port, baudrate=9600, timeout=0.5):
        self.serial_port = serial.Serial(port, baudrate, timeout=timeout)

    def parse_gps_data(self, data):
        if b'GGA' in data:
            print("GGA")
            msg = pynmea2.parse(data.decode('utf-8'))
            self.lat = msg.lat
            self.lat_dir = msg.lat_dir
            self.lon = msg.lon
            self.lon_dir = msg.lon_dir

            #print("Timestamp: %s -- Lat: %s %s -- Lon: %s %s -- Altitude: %s %s" % (msg.timestamp, msg.lat, msg.lat_dir, msg.lon, msg.lon_dir, msg.altitude, msg.altitude_units))

    def run(self):
        print("GPS session")
        while True:
            data = self.serial_port.readline()
            self.parse_gps_data(data)

if __name__ == "__main__":
    gps_parser = GPSParser("/dev/ttyAMA0")
    gps_parser.run()
