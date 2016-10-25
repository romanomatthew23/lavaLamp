%%Plot all of our data for the open loop sim
load('Open_Loop_Data.mat');
T25W = T_LAVA_25W_OPEN_LOOP;
T40W = T_LAVA_40W_OPEN_LOOP;
T64W = T_LAVA_64W_OPEN_LOOP;

%%
figure(1);
plot(T25W(:,1)/3600,T25W(:,2)+25);
hold on;
plot(T40W(:,1)/3600,T40W(:,2)+25);
plot(T64W(:,1)/3600,T64W(:,2)+25);
plot(get(gca,'xlim'), [65 65],'--','Color','k'); % Adapts to x limits of current axes
hold off;
legend('25W','40W','64W','Predicted Operating Temperature (65°C)','Location','Best');
xlabel('Time (hours)');
ylabel('T_L_a_v_a (°C)');
title('Open Loop Control under Various Inputs (T_A_i_r = 25°C)');

%%
% Plot all of our data from the proportional controller
load('Proportional_Control_Data.mat');
T10 = T_Lava_Proportional_10;
T20 = T_Lava_Proportional_20;
T50 = T_Lava_Proportional_50;
T100 = T_Lava_Proportional_100;

C10 = Control_Effort_Proportional_10;
C20 = Control_Effort_Proportional_20;
C50 = Control_Effort_Proportional_50;
C100 = Control_Effort_Proportional_100;
%%
figure(1);
plot(T10(:,1)/3600,T10(:,2)+25);
hold on;
plot(T20(:,1)/3600,T20(:,2)+25);
plot(T50(:,1)/3600,T50(:,2)+25);
plot(T100(:,1)/3600,T100(:,2)+25);
plot(get(gca,'xlim'), [65 65],'--','Color','k'); % Adapts to x limits of current axes
hold off;
legend('K=10','K=20','K=50','K=100','Predicted Operating Temperature (65°C)','Location','Best');
xlabel('Time (hours)');
ylabel('T_L_a_v_a (°C)');
title('Proportional Control under Various Inputs (T_A_i_r = 25°C)');

%%
%Calculate steady state errors
E10 = 40 - T10(end,2);
E20 = 40 - T20(end,2);
E50 = 40 - T50(end,2);
E100 = 40 - T100(end,2);

%%
%Plot the control efforts
figure(1);
plot(C10(:,1)/3600,C10(:,2));
hold on;
plot(C20(:,1)/3600,C20(:,2));
plot(C50(:,1)/3600,C50(:,2));
plot(C100(:,1)/3600,C100(:,2));
hold off;
legend('K=10','K=20','K=50','K=100','Location','Best');
xlabel('Time (hours)');
ylabel('Control Effort (W)');
title('Control Effort for Proportional Control under Various Inputs (T_A_i_r = 25°C)');