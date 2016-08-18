#ifndef __ANALOG_GRAY_H__
#define __ANALOG_GRAY_H__

#include "arduino.h"
#include <../Queue/Queue.h>

#ifndef uchr
#define uchr unsigned char
#endif

#ifndef uint
#define uint unsigned int
#endif

#ifndef ColorThreshold
#define ColorThreshold      4
#endif

class AnalogGray
{
protected:
    uchr pin;
public:
    AnalogGray(uchr p):pin(p)
    {
        pinMode(pin,INPUT);
    }
    uint read()
    {
        return analogRead(pin);
    }
};

class AnalogGray_Color:public AnalogGray
{
protected:
    uchr cntColor;
    int *colorPtr;
    CircleQueue_Avg<int> Que;
public:
    AnalogGray_Color(uchr p,uchr cnt):AnalogGray(p),cntColor(cnt),Que(CircleQueue_Avg<int>(4))
    {
        colorPtr = new int[cnt];
    }

    /******************************
    �������ƣ�smoothRead
    �������ܣ�����CircleQueue_Avg�Զ�ȡ��ֵ����ƽ������
    �����������
    ����ֵ��ƽ����������ɫֵ
    ******************************/
    int smoothRead()
    {
        Que.push(read());
        return Que.avg();
    }

    /******************************
    �������ƣ�setColor
    �������ܣ�����Ԥ����ɫ
    �����������ɫ����ָ��*p
    ����ֵ����
    ******************************/
    void setColor(uint *p)
    {
        for(uint i = 0; i < cntColor; ++i)
            *(colorPtr + i) = * (p + i);
    }
    /******************************
    �������ƣ�setColor
    �������ܣ�����Ԥ����ɫ
    �����������ɫ���k����ɫֵval
    ����ֵ����
    ******************************/
    void setColor(uchr k,uint val)
    {
        if(k >= cntColor)
        {
            return;
        }
        *(colorPtr + k) = val;
    }

    /******************************
    �������ƣ�color
    �������ܣ���ȡ�Ҷ�ֵ���ж���ɫ
    �����������
    ����ֵ�����ϵ���ɫ��ţ��Ҳ����򷵻�0xff
    ******************************/
    uchr color(int val)
    {
        for(uchr i = 0; i < cntColor; ++i)
        {
            if(abs(val - colorPtr[i]) <= ColorThreshold)
                return i;
        }
        return 0xff;
    }
    uchr color()
    {
        int val = read();
        return color(val);
    }
};

#endif // __ANALOG_GRAY_H__
