function result = get_cca(double_value)
    freq =[8,8.6,9,9.6]; %% 刺激范式用到的频率

    %channelUse=[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32]; % ssvep信号分类用到的通道编号

    time=5; % 刺激时间

    fs=1000;%脑电采样率

    result = my_cca(double_value', fs, freq, time);

end