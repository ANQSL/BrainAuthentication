#include "blinkrecognition.h"
#include "iostream"
BlinkRecognition::BlinkRecognition()
{
    running_status=false;
    threshlod_status=InIt;
    count=0;
    p=0;

    baseline=0;
    blink_threshold=100;

    sum=0;
    init_count=500;
    eog_threshold=70;
    dynamic_count=500;
    discard_count=500;
    current_count=0;
}

bool BlinkRecognition::recognition(double value)
{
    if(running_status)
    {
        dynamicThreshlod(value);
        return normalization(value);

    }
    return false;
}

void BlinkRecognition::start()
{
    running_status=true;
    threshlod_status=InIt;
}

void BlinkRecognition::stop()
{
    running_status=false;
}
void BlinkRecognition::dynamicThreshlod(double value)
{

    current_count++;
    if(threshlod_status==InIt)
    {
        sum+=value;
        if(init_count==current_count)
        {
            baseline=sum/current_count;
            blink_threshold=baseline+eog_threshold;
            threshlod_status=Normal;
            current_count=0;
            sum=0;
        }
    }
    else if(threshlod_status==Update)
    {
        if(current_count-discard_count>=0)
        {
            sum+=value;
            if(current_count-discard_count==dynamic_count)
            {
                baseline=sum/current_count;
                blink_threshold=baseline+eog_threshold;
                threshlod_status=Normal;
                current_count=0;
                sum=0;
            }
        }
    }
}
bool BlinkRecognition::normalization(double value)
{

    if(value>blink_threshold&&threshlod_status==Normal)
    {
        count++;
        if(count==40)
        {
           count=0;
           p++;
           x[p]=1;
           int dx=x[p]-x[p-1];
           if(dx>0)
           {
               if(p>1024)
               {
                   p=0;
                   x[p]=0;
               }
               current_count=0;
               sum=0;
               static int time=1;

               std::cout<<"current blink_threshold is:"<<blink_threshold<<std::endl;
               std::cout<<"this is"<<time<<"";
               time++;
               return true;
           }
           else
           {
               return false;
           }
        }
    }
    else
    {
        count=0;
        p++;
        x[p]=0;
        int dx=x[p]-x[p-1];
        if(dx<0)
        {
           threshlod_status=Update;
        }
        if(p>1024)
        {
            p=0;
            x[p]=0;
        }
        return  false;
    }
    return false;
}
