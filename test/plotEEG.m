clc
clear all
close all
%% 需要修改的参数
path='D:\project\ssvep系统对接\脑纹数据采集\脑纹数据采集\ssvep数据\wxr\wxr1\by\';
% path='.\result\';
freq =[8,8.6,9,9.6];  %% 刺激范式用到的频率
channelUse=[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32]; % ssvep信号分类用到的通道编号
time=5; % 刺激时间

plotflag=1;%% 是否画功率谱图

fs=1000;%脑电采样率
rawdata(:,1) = load([path,'Channel_1.txt']);
rawdata(:,2) = load([path,'Channel_2.txt']);
rawdata(:,3) = load([path,'Channel_3.txt']);
rawdata(:,4) = load([path,'Channel_4.txt']);
rawdata(:,5) = load([path,'Channel_5.txt']);
rawdata(:,6) = load([path,'Channel_6.txt']);
rawdata(:,7) = load([path,'Channel_7.txt']);
rawdata(:,8) = load([path,'Channel_8.txt']);
rawdata(:,9) = load([path,'Channel_9.txt']);
rawdata(:,10) = load([path,'Channel_10.txt']);
rawdata(:,11) = load([path,'Channel_11.txt']);
rawdata(:,12) = load([path,'Channel_12.txt']);
rawdata(:,13) = load([path,'Channel_13.txt']);
rawdata(:,14) = load([path,'Channel_14.txt']);
rawdata(:,15) = load([path,'Channel_15.txt']);
rawdata(:,16) = load([path,'Channel_16.txt']);
rawdata(:,17) = load([path,'Channel_17.txt']);
rawdata(:,18) = load([path,'Channel_18.txt']);
rawdata(:,19) = load([path,'Channel_19.txt']);
rawdata(:,20) = load([path,'Channel_20.txt']);
rawdata(:,21) = load([path,'Channel_21.txt']);
rawdata(:,22) = load([path,'Channel_22.txt']);
rawdata(:,23) = load([path,'Channel_23.txt']);
rawdata(:,24) = load([path,'Channel_24.txt']);
rawdata(:,25) = load([path,'Channel_25.txt']);
rawdata(:,26) = load([path,'Channel_26.txt']);
rawdata(:,27) = load([path,'Channel_27.txt']);
rawdata(:,28) = load([path,'Channel_28.txt']);
rawdata(:,29) = load([path,'Channel_29.txt']);
rawdata(:,30) = load([path,'Channel_30.txt']);
rawdata(:,31) = load([path,'Channel_31.txt']);
rawdata(:,32) = load([path,'Channel_32.txt']);
data = rawdata';
figure;
plot(data(1,1:20000));
%% 这里滤波图省事，直接调用eeglab中的滤波函数，缺点需要在matlab路径添加eeglab工具箱
eeglab;
EEG = pop_importdata('dataformat','array','nbchan',0,'data','data','srate',1000,'pnts',0,'xmin',0);
EEG = pop_eegfiltnew(EEG, 'locutoff',1,'hicutoff',30,'plotfreqz',0);
fdata = double(EEG.data);
% figure;
% plot(fdata(1,:))
