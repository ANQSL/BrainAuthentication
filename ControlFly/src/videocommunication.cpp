#include "videocommunication.h"
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
}
#include "QImage"
#include "QDebug"
#include "QFile"
VideoCommunication::VideoCommunication(QObject *parent) : QThread(parent)
{
    IP.setAddress("192.168.1.11");
    port=11111;
    h264decoder=new H264Decoder;
    converter_rgb24=new ConverterRGB24;
}

VideoCommunication::~VideoCommunication()
{
    delete h264decoder;
    delete converter_rgb24;
    if (frame_buffer)
    {
        free(frame_buffer);
    }
}

void VideoCommunication::start()
{
    status=true;
    QThread::start();
}

void VideoCommunication::run()
{
    socket=new QUdpSocket;
    socket->bind(QHostAddress::Any,port);
    while (status) {
        bool is_read=socket->hasPendingDatagrams();
        if(is_read)
        {
            QByteArray receive_data;
            receive_data.resize(socket->pendingDatagramSize());
            socket->readDatagram(receive_data.data(),socket->pendingDatagramSize(),&IP,&port);
            video_buffer.append(receive_data);
            if(video_buffer.size()>=14600)
            {
                decode((unsigned char*)video_buffer.data(), video_buffer.size());
                video_buffer.clear();
            }
        }
        msleep(1);
    }
    delete socket;
}
AVFrame VideoCommunication::decode_frame_impl(const unsigned char* data_in, size_t len, size_t& num_consumed, bool& is_frame_available)
{
    num_consumed = this->h264decoder->parse((unsigned char*)data_in, len);
    AVFrame frame;
    is_frame_available = h264decoder->is_frame_available();
    if (is_frame_available)
    {
        frame=h264decoder->decode_frame();
        std::pair<int,int> w_h = width_height(frame);
        int out_size=converter_rgb24->predict_size(w_h.first, w_h.second);
        unsigned char* out_rgb = (unsigned char*)malloc(out_size);
        //frame = converter_rgb24->convert(frame, out_rgb);
        free(out_rgb);
        return frame;
    }
    return frame;
}
void VideoCommunication::decode(const unsigned char* data_in, size_t len)
{
    while (len>0)
    {   
        size_t num_consumed = 0;
        bool _is_frame_available = false;
        bool is_frame_available = false;
        try {
            AVFrame frame = decode_frame_impl(data_in, len, num_consumed, is_frame_available);
            if (is_frame_available)
            {
                QImage img = avFrameToQImage(&frame);
                emit receiveFrameFinished(img);
            }
        } catch (H264DecodeFailure failure) {

        }
        len -= num_consumed;
        data_in += num_consumed;
    }
}
QImage VideoCommunication::avFrameToQImage(AVFrame* frame) {
    // 将AVFrame转换为RGB格式
    SwsContext* sws_ctx = sws_getContext(
        frame->width, frame->height, (AVPixelFormat)frame->format,
        frame->width, frame->height, AV_PIX_FMT_RGB24,
        SWS_BILINEAR, nullptr, nullptr, nullptr);

    if (!sws_ctx) {
        return QImage();
    }

    uint8_t* rgb_data[4];
    int rgb_linesize[4];
    int num_bytes = av_image_get_buffer_size(AV_PIX_FMT_RGB24, frame->width, frame->height, 1);

    if (num_bytes < 0) {
        sws_freeContext(sws_ctx);
        return QImage();
    }
    if (!frame_buffer)
    {
        frame_buffer = (uint8_t*)malloc(num_bytes * sizeof(uint8_t));
    }
    
    av_image_fill_arrays(rgb_data, rgb_linesize, frame_buffer, AV_PIX_FMT_RGB24, frame->width, frame->height, 1);

    sws_scale(sws_ctx, frame->data, frame->linesize, 0, frame->height, rgb_data, rgb_linesize);

    // 使用QImage构造函数将RGB数据加载到QImage中
    QImage img(rgb_data[0], frame->width, frame->height, rgb_linesize[0], QImage::Format_RGB888);

    // 释放SwsContext和RGB数据
    sws_freeContext(sws_ctx);
    return img;
}