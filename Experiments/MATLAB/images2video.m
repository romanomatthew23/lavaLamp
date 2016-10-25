%Converting images to video
%referencing https://www.mathworks.com/help/matlab/examples/convert-between-image-sequences-and-video.html

% Find all the JPEG file names in the images folder. Convert the set of image names to a cell array.
workingDir = pwd;
%%
imageNames = dir(fullfile(workingDir,'images','*.jpg'));
imageNames = {imageNames.name}';

%%
%Construct a VideoWriter object, which creates a Motion-JPEG AVI file by default.
outputVideo = VideoWriter(fullfile(workingDir,'lava_out_50Hz.avi'));
outputVideo.FrameRate = 10;
open(outputVideo)

%Loop through the image sequence, load each image, and then write it to the video.
for ii = 1:length(imageNames)
   img = imread(fullfile(workingDir,'images',imageNames{ii}));
   writeVideo(outputVideo,img)
end

%Finalize the video file.
close(outputVideo)

%we have 2560 frames, and I actually took 8.5 hours at 5 second intervals
%so ignoring holes I started at 0.2 Hz, and went to 30 hz, so 150x? Lets do
% 20Hz so its x100 with holes. We could also try 10Hz so its x50.