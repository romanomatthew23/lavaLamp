%fuse images together
A = imread('images/0004.jpg');
figure();
image(A);
B = imread('E1_tempData.png');
B = imresize(B,8/7);
figure();
image(B);

 C = imfuse(A,B,'montage');
 figure();
 image(C);
 