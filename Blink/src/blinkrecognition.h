#ifndef BLINKRECOGNITION_H
#define BLINKRECOGNITION_H

class BlinkRecognition
{
    typedef enum{
        InIt=0,
        Normal,
        Update
    }ThreshlodStatus;
public:
    BlinkRecognition();
    bool recognition(double);
    void start();
private:
    void dynamicThreshlod(double);
    bool normalization(double);
    unsigned int count,p,x[1025];
    int _blink_threshold,blink_threshold,baseline,eog_threshold;

    ThreshlodStatus threshlod_status;

    //动态阈值的属性
    double sum;
    int init_count;
    int dynamic_count;
    int discard_count;
    int current_count;
    bool running_status;


};

#endif // BLINKRECOGNITION_H
