import Adafruit_BBIO.ADC as ADC
from time import sleep
 
ADC.setup()
TMP1 = "P9_40"     #White Wire to T0-92 package (end)
TMP2 = "P9_39"     #Orange Wire (between)
TMP3 = "P9_35"     #Yellow Wire (middle of board side)

Th1 = "P9_38"       #White Wire to Voltage Divider (Middle of board)
Th2 = "P9_36"       #Brown Wire to Voltage Divider (End of board)

R1 = 10020 # Res for Therm 1 (Ohms)
R2 = 9980 # Res for Therm 2 (Ohms)


#Read from TMP1
value = ADC.read(TMP1)
value = ADC.read(TMP1) #the library has a bug that requires sampling twice
TMPvIn1 = value * 1.8 #1.8V
tempC1 = (TMPvIn1 - 0.5) * 100 #convert from 10mv/deg with 500mV offset
#tempF = (tempC * 9.0 / 5.0) + 32.0

#Read from TMP2
value = ADC.read(TMP2)
value = ADC.read(TMP2) #the library has a bug that requires sampling twice
TMPvIn2 = value * 1.8 #1.8V
tempC2 = (TMPvIn2 - 0.5) * 100 #convert from 10mv/deg with 500mV offset

#Read from the TMP36 for Air Temperature
value = ADC.read(TMP3)
value = ADC.read(TMP3) #the library has a bug that requires sampling twice
TMPvIn3 = value * 1.8 #1.8V
tempC3 = (TMPvIn3 - 0.5) * 100 #convert from 10mv/deg with 500mV offset

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
print TMPvIn1
print TMPvIn2
print TMPvIn3
print RTh1
print RTh2
#print('%(TMP) %(R1) %(R2)' % {'TMP': TMPvIn, 'R1': RTh1, 'R2': RTh2})
#while(True):
#    sleep(1)
