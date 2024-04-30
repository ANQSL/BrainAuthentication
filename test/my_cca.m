function result = my_cca(data,fs,freq,time)

lowfreq = 4;
higefreq = 35;
filterorder = 4;
freqcutoff = [lowfreq*2/fs higefreq*2/fs];
[B, A] = butter(filterorder,freqcutoff);
data=filter(B,A,data);

nharmonics = 5;%Ð³²¨Êý£º5
condition = length(freq);
n = [1:time*fs]./fs;
for ii = 1:length(freq)
    s1 = sin(2*pi*freq(ii)*n);
    s2 = cos(2*pi*freq(ii)*n);
    s3 = sin(2*pi*2*freq(ii)*n);
    s4 = cos(2*pi*2*freq(ii)*n);
    s5 = sin(2*pi*3*freq(ii)*n);
    s6 = cos(2*pi*3*freq(ii)*n);
    s7 = sin(2*pi*4*freq(ii)*n);
    s8 = cos(2*pi*4*freq(ii)*n);
    s9 = sin(2*pi*5*freq(ii)*n);
    s10 = cos(2*pi*5*freq(ii)*n);
    s11 = sin(2*pi*6*freq(ii)*n);
    s12 = cos(2*pi*6*freq(ii)*n);
    s13 = sin(2*pi*7*freq(ii)*n);
    s14 = cos(2*pi*7*freq(ii)*n);
    s15 = sin(2*pi*8*freq(ii)*n);
    s16 = cos(2*pi*8*freq(ii)*n);
    s17 = sin(2*pi*9*freq(ii)*n);
    s18 = cos(2*pi*9*freq(ii)*n);
    s19 = sin(2*pi*10*freq(ii)*n);
    s20 = cos(2*pi*10*freq(ii)*n);
    condY(:,:,ii) = cat(2,s1',s2',s3',s4',s5',s6',s7',s8',s9',s10',s11',s12',s13',s14',s15',s16',s17',s18',s19',s20');
end
for cond = 1:condition
    Y1 = condY(:,1:2*nharmonics,cond);
    [~,~,r] = canoncorr(data(1:time*fs,:),Y1);
    p(cond) = r(1);
end
[~,result] = max(p);
end