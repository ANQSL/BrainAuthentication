function double_value = readBinaryFileToDouble(filename, numChannels, numSamples)
    % 打开文件进行读取
    fid = fopen(filename, 'rb');
    if fid == -1
        error('File not found.');
    end
    
    % 读取二进制数据
    raw_data = fread(fid, numSamples * numChannels , 'double', 'ieee-le');
    %raw_data = fread(fid, [numChannels numSamples], 'double', 'ieee-le');
    % 数据读取完毕
    fclose(fid);

    %double_value = reshape(raw_data, numChannels, numSamples);
    double_value = reshape(raw_data, [numSamples, numChannels]);
    double_value = double_value';
end
%double_value = readBinaryFileToDouble("2024_05_07_1_ssvep.bin", 32, 5000);
