%messing around with formatting temp data in a figure for video
%open the file and store the values into C
fileID = fopen('tempData.txt');
C = textscan(fileID,'%f %f %f %f %f',...
'Delimiter','_');
fclose(fileID);

% turn C into an array rather than a cell thing
% Because I'm OCD I guess
tempData = zeros(C{4}(end),5);
for i=1:5
    tempData(:,i) = C{i};
end

% Convert TMP data to temperatures
for i=1:length(tempData)
   tempData(i,1) = TMP36_V2Temp( tempData(i,1) ); 
end

% Convert Thermistor data to temperatures
for i=1:length(tempData)
   tempData(i,2) = Therm_R2Temp( tempData(i,2) );
   tempData(i,3) = Therm_R2Temp( tempData(i,3) );
end

%%
idx = 5;
%% plot temp data up to index
figure();
plot(tempData(1:idx,5)/3600,tempData(1:idx,1));
hold on;
plot(tempData(1:idx,5)/3600,tempData(1:idx,2));
plot(tempData(1:idx,5)/3600,tempData(1:idx,3));
hold off;
title('Temperature vs. Time');
ylabel('Temperature (deg C)');
xlabel('Time (hours)');
legend('Air Temp','Temp 1','Temp 2','location','Best');