import Adafruit_BBIO.ADC as ADC
from time import sleep
 
ADC.setup()

delay = 1

while(True):
    value = ADC.read("P9_40")
    value = ADC.read("P9_40") #the library has a bug that requires sampling twice
    voltage = value * 1.8 #1.8V
    tempC = (voltage - 0.5) * 100 #convert from 10mv/deg with 500mV offset
    tempF = (tempC * 9.0 / 5.0) + 32.0
    #print "value = %f" % value
    print "voltage = %f" % voltage
    print "temp (deg C) = %f" % tempC
    print "temp (deg F) = %f" % tempF
    sleep(delay)
