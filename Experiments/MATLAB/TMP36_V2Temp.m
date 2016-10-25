function [ temp ] = TMP36_V2Temp( voltage )
%TMP36_V2Temp Convert voltage reading to temperature sensed for TMP36
%   Simple.

%from the BBB code
%tempC = (TMPvIn - 0.5) * 100 #convert from 10mv/deg with 500mV offset
%tempF = (tempC * 9.0 / 5.0) + 32.0
temp = (voltage - 0.5) * 100;
end

