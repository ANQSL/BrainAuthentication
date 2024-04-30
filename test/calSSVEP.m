% % result1中存放频率1对应数据的CCA分类结果，全为1
% % result2中存放频率2对应数据的CCA分类结果，全为2
% % result3中存放频率3对应数据的CCA分类结果，全为3
% % result4中存放频率4对应数据的CCA分类结果，全为4
% % 
% % 功率谱图只画了每种频率下第3个试次所有通道的结果，可以看下刺激诱发的效果好不好


clc
clear all
close all
%% 需要修改的参数
load('D:\project\BrainAuthentication\build\eegdata\lx\2024-04-30\18\lx_20240430195249_123_0.mat')
% path='.\result\';
freq =[8,8.6,9,9.6];  %% 刺激范式用到的频率
channelUse=[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32]; % ssvep信号分类用到的通道编号
time=5; % 刺激时间
event=EEG.event;
plotflag=0;%% 是否画功率谱图

fs=1000;%脑电采样率
rawdata=EEG.data;
data = rawdata;
%% 这里滤波图省事，直接调用eeglab中的滤波函数，缺点需要在matlab路径添加eeglab工具箱
eeglab;
EEG = pop_importdata('dataformat','array','nbchan',0,'data','data','srate',1000,'pnts',0,'xmin',0);
EEG = pop_eegfiltnew(EEG, 'locutoff',1,'hicutoff',30,'plotfreqz',0);
fdata = double(EEG.data);
close all;
m1=[];
m2=[];
m3=[];
m4=[];
for i=1:length(event)
   if event(i).type==1
       m1(end+1)=event(i).latency;
   elseif event(i).type==2
       m2(end+1)=event(i).latency;
   elseif event(i).type==3
       m3(end+1)=event(i).latency;
   elseif event(i).type==4
       m4(end+1)=event(i).latency;
   end
end
for i = 1:length(m1)
    tmpdata = fdata(channelUse,m1(i):m1(i)+fs*time-1)';
    epochdata1(:,:,i) = fdata(:,m1(i):m1(i)+fs*time-1);
    result1(i) = my_cca(tmpdata,fs,freq,time);
end


for i = 1:length(m2)
    tmpdata = fdata(channelUse,m2(i):m2(i)+fs*time-1)';
    epochdata2(:,:,i) = fdata(:,m2(i):m2(i)+fs*time-1);
    result2(i) = my_cca(tmpdata,fs,freq,time);
end

for i = 1:length(m3)
    tmpdata =  fdata(channelUse,m3(i):m3(i)+fs*time-1)';
    epochdata3(:,:,i) =fdata(:,m3(i):m3(i)+fs*time-1);
    result3(i) = my_cca(tmpdata,fs,freq,time);
end

for i = 1:length(m4)
    tmpdata =  fdata(channelUse,m4(i):m4(i)+fs*time-1)';
    epochdata4(:,:,i) = fdata(:,m4(i):m4(i)+fs*time-1);
    result4(i) = my_cca(tmpdata,fs,freq,time);
end


if plotflag
    plottime2freq(epochdata1,fs,time)
    plottime2freq(epochdata2,fs,time)
    plottime2freq(epochdata3,fs,time)
    plottime2freq(epochdata4,fs,time)
end




function plottime2freq(epochdata,fs,time)
[~,~,trials] = size(epochdata);
figure;
[p1,freq1] = pwelch(epochdata(:,:,6)',hanning(fs*time),[],fs*time,fs);
for i =1:32
    subplot(6,6,i);
    plot(freq1,p1(:,i));
    axis([0 30 0 inf])
    title(['channel ',num2str(i)]);
end
end