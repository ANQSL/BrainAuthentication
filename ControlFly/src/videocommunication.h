#ifndef VIDEOCOMMUNICATION_H
#define VIDEOCOMMUNICATION_H

#include <QObject>
#include "QThread"
#include "QUdpSocket"
#include "h264decoder.hpp"
class VideoCommunication : public QThread
{
    Q_OBJECT
public:
    explicit VideoCommunication(QObject *parent = nullptr);
    ~VideoCommunication();
    void start();
    void run() override;
signals:
    void receiveFrameFinished(QImage);
private:
    QUdpSocket *socket;
    QHostAddress IP;
    quint16 port;
    bool status;
    QByteArray video_buffer;
    //视频解码器
    H264Decoder *h264decoder;
    //帧转换
    ConverterRGB24 *converter_rgb24;
    AVFrame decode_frame_impl(const unsigned char* data_in, size_t len, size_t& num_consumed, bool& is_frame_available);
    void decode(const unsigned char* data_in,size_t len);
    QImage avFrameToQImage(AVFrame *frame);
    uint8_t* frame_buffer=NULL;
};

#endif // VIDEOCOMMUNICATION_H
