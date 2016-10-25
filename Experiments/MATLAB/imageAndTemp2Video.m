%combines all of our little scripts into a big one that combines the 
% temp data and images into one video that is beautiful.

%note this is currently set up for experiment 1

%basic outline:
% 1) run 'readTempData.m' besides the plotting part to get our data
% 2) run 'images2video.m' up until the loop
% 3) Loop over every image 
    % a) Obtain the index from the given image and plot temp data up 
            %to that index
    % b) fuse together this figure and the image side by side
    % c) write this image to the video file

%% 1) run 'readTempData.m' besides the plotting part to get our data
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

%% 2) run 'images2video.m' up until the loop
% Find all the JPEG file names in the images folder. Convert the set of image names to a cell array.
workingDir = pwd;
imageNames = dir(fullfile(workingDir,'images','*.jpg'));
imageNames = {imageNames.name}';

%Construct a VideoWriter object, which creates a Motion-JPEG AVI file by default.
outputVideo = VideoWriter(fullfile(workingDir,'combined_lava.avi'));
outputVideo.FrameRate = 10;
open(outputVideo)

%%
%Loop through the image sequence, load each image, and then write it to the video.
for ii = 1:length(imageNames)
%for ii = 1:100
    img = imread(fullfile(workingDir,'images',imageNames{ii}));
    % a) Obtain the index from the given image and plot temp data up to it
    idx = str2double( imageNames{ii}(1:4) );
   
    %plot temp data up to index
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
    %convert figure to image matrix
    F = getframe(gcf);
    [X, Map] = frame2im(F);
    %resize figure image
    X = imresize(X,8/7);
    % b) fuse together this figure and the image side by side
    combImg = imfuse(img,X,'montage');
    % c) write this image to the video file
    writeVideo(outputVideo,combImg);
    close all;
end

close(outputVideo);