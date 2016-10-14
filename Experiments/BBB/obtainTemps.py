import Adafruit_BBIO.ADC as ADC
from time import sleep
 
ADC.setup()
TMP36 = "P9_40"     #White Wire to T0-92 package
Th1 = "P9_38"   #White Wire to Voltage Divider (Middle of board)
Th2 = "P9_36"   #Brown Wire to Voltage Divider (End of board)

R1 = 10020 # Res for Therm 1 (Ohms)
R2 = 9980 # Res for Therm 2 (Ohms)


#Read from the TMP36 for Air Temperature
value = ADC.read(TMP36)
value = ADC.read(TMP36) #the library has a bug that requires sampling twice
TMPvIn = value * 1.8 #1.8V
tempC = (TMPvIn - 0.5) * 100 #convert from 10mv/deg with 500mV offset
tempF = (tempC * 9.0 / 5.0) + 32.0
#print "value = %f" % value
#print "voltage = %f" % TMPvIn
#print "Air Temp (deg C) = %f" % tempC
#print "temp (deg F) = %f" % tempF

#Read from Thermistor #1
value = ADC.read(Th1)
value = ADC.read(Th1) #the library has a bug that requires sampling twice
vIn = value * 1.8 #1.8V
RTh1 = vIn * R1 / (1.8 - vIn)
#print "RTh1 = %f" % RTh1

#Read from Thermistor #2
value = ADC.read(Th2)
value = ADC.read(Th2) #the library has a bug that requires sampling twice
vIn = value * 1.8 #1.8V
RTh2 = vIn * R2 / (1.8 - vIn)
#print "RTh2 = %f" % RTh2
#print " "

# Now print the values to the output
print TMPvIn
print RTh1
print RTh2
#print('%(TMP) %(R1) %(R2)' % {'TMP': TMPvIn, 'R1': RTh1, 'R2': RTh2})
#while(True):
#    sleep(1)
