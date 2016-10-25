function [ temp ] = Therm_R2Temp( R )
%Therm_R2Temp Use LUT to convert thermistor res to temperature
%   Interpolate between each of the values in the LUT

%% convert ohms to kohms
R = R /1000;

%% Load LUT values 
load('LUT.mat');
%%
%R = 10;

%% Find the 2 values that are closest 
% Use binary search to find the closest value that is strictly larger
% (the larger resistance, thus smaller temp)
index = 40;
step = 20;
while(1)
    if(step == 0)
        break;
    end
    if(R > LUT(index) )
        index = index - step;
        step = round( (step-1) /2);
    else
        index = index + step;
        step = round( (step-1) /2);
    end
end

if(index == 0)
   temp = 0;
   return
end

%this may be off by one or two so double check
if(R > LUT(index))   %if the actual resistance is larger than the LUT value
    %decrement the index until we are sure we found it
   while(R > LUT(index) )
       index = index - 1;
   end
   %now we have it because this is the first LUT value to be larger
else
   %increment the index until we are sure we found the upper bound
   while(R < LUT(index) )
       index = index + 1;
   end
   %once R > LUT(index) weve gone too far by 1
   index = index - 1;
end

%assume the value directly below this is closest smaller one
indexLower = index + 1;

%% Linearly interpolate between them
fraction = (LUT(index) - R) / (LUT(index) - LUT(indexLower));

temp = index + fraction;

end

