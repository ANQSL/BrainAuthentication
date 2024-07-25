#include "blinkrecognition.h"

BlinkRecognition::BlinkRecognition()
{
    running_status=false;
    count=0;
    p=0;

    baseline=0;

    sum=0;
    init_count=2000;
    eog_threshold=200;
    dynamic_count=160;
    discard_count=280;
    current_count=0;

    status=InIt;
}

bool BlinkRecognition::recognition(double value)
{
    if(running_status)
    {
        if(status==Recogniton)
        {
            return normalization(value);
        }
        if(status==Threshold||status==InIt)
        {
            dynamicThreshlod(value);
        }
    }
    return false;
}

void BlinkRecognition::start()
{
    running_status=true;
}
void BlinkRecognition::dynamicThreshlod(double value)
{

    current_count++;
    if(status==InIt)
    {
        sum+=value;
        if(init_count==current_count)
        {
            baseline=sum/current_count;
            blink_threshold=baseline+eog_threshold;
            status=Recogniton;
            current_count=0;
            sum=0;
        }
    }
    else
    {
        if(current_count-discard_count>=0)
        {
            sum+=value;
            if(current_count-discard_count==dynamic_count)
            {
                baseline=sum/current_count;
                blink_threshold=baseline+eog_threshold;
                status=Recogniton;
                current_count=0;
                sum=0;
            }
        }
    }
}
bool BlinkRecognition::normalization(double value)
{
    if(value>blink_threshold)
    {
        count++;
        if(count==120)
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
           status=Threshold;
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
