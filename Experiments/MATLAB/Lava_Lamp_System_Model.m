%This script will calculate the Constants for our system model so we can
%simulate the open loop behavior.

%Need to give values for 
%R1,R2,R3,R5,R6,C_HEAT,C_LAVA
R1 = 0.9628; %K/W
R2 = 184.5; %K/W
R3 = 192.6; %K/W
R5 = 192.6; %K/W
R6 = 8.022; %K/W
C_LAVA = 29990; %J/degC
C_HEAT = 757.2; %J/degC

R123 = (R1*R2*R3)/(R1*R2 + R1*R3 + R2*R3);
R156 = (R1*R5*R6)/(R1*R5 + R1*R6 + R5*R6);

C1 = 1 / C_HEAT;
C2 = 1 / (R123 * C_HEAT);
C3 = 1 / (R1 * C_LAVA);
C4 = 1 / (R156 * C_LAVA);
C5 = 1/ (R1 * C_HEAT);

%%
q = 40; %40 W light bulb
%%
%set the gain
K = 10;  %for starters, see what happens

%%
%set the desired T offset (room temp = 25 degC, op temp = 65 degC)
opTemp = 65;
roomTemp = 25;
T = (opTemp - roomTemp);