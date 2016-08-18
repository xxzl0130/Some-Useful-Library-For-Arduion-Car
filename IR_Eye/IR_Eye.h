#ifndef __IR_EYE_H__
#define __IR_EYE_H__

#include "arduino.h"
#include "limits.h"
#include "string.h"

#ifndef uchr
#define uchr unsigned char
#endif // uchr

#ifndef uint
#define uint unsigned int
#endif // uint

class IR_Eye
{
private:
    uchr sPin;
    /**起始通道的接口，其余顺延**/
    uchr cntEye;
    /**复眼数目**/
    float degreePerEye;
    /**每只眼对应的角度**/
    uint *value;
public:
    uint environIR;
    /**环境光干扰**/
    IR_Eye(uchr Pin = A0,uchr Cnt = 6,uint Angel = 180):sPin(Pin),cntEye(Cnt),environIR(1024)
    {
        for(uchr i = 0; i < cntEye; ++i)
        {
            pinMode(sPin + i, INPUT);
        }

        degreePerEye = (float)Angel / (cntEye - 1);

        value = new uint[cntEye];
        memset(value,0,sizeof(uint) * cntEye);
    }

    /******************************
    函数名称：printAll2Ser
    函数功能：将所有通道的值打印至串口
    传入参数：无
    返回值：无
    ******************************/
#ifdef DEBUG
    //void printAll2Ser();
#endif

    /******************************
    函数名称：getMinNo
    函数功能：读取所有通道并返回值最小的通道编号
    传入参数：无
    返回值：返回值最小的通道编号
    ******************************/
    //uchr getMinNo(void);
    //uchr getMinNo(uint *arr);

    /******************************
    函数名称：getMinDir
    函数功能：读取所有通道并计算值最小的通道所对应的角度
    传入参数：无
    返回值：值最小的通道所对应的角度
    ******************************/
    //uint getMinDir(void);
    //uchr getMinDir(uint *arr);

    /******************************
    函数名称：getAllValue
    函数功能：读取所有通道的值
    传入参数：用于存放数据的数组指针*arr
    返回值：无
    ******************************/
    //uint* getAllValue(uint *arr);
    //inline uint* getAllValue(void);

    /******************************
    函数名称：getMinValue
    函数功能：读取所有通道并返回值最小的值
    传入参数：无
    返回值：无
    ******************************/
    //uint getMinValue(void);
    //uint getMinValue(uint *arr);

    //inline uint degreesPerEye(void) const;
    //inline uint getEnvironIR(void) const;
    //inline uint getCntEye(void) const;
    //inline void setEnvironIR(uint IR);
    /******************************
    函数名称：getAllValue
    函数功能：读取所有通道的值
    传入参数：用于存放数据的数组指针*arr
    返回值：无
    ******************************/
    uint* getAllValue(uint *arr)
    {
        for(uchr i = 0; i < cntEye; ++i)
        {
            arr[i] = analogRead(sPin + i);
        }
        return arr;
    }

    inline uint* getAllValue(void)
    {
        return getAllValue(value);
    }

#ifdef DEBUG
    void printAll2Ser()
    {
        for(uchr i = 0; i < cntEye; ++i)
        {
            debugSerial.print(analogRead(sPin + i));
            debugSerial.print(" | ");
        }
        debugSerial.print("\n");
    }
    void printAll2Ser(uint *arr)
    {
        for(uchr i = 0; i < cntEye - 1; ++i)
        {
            debugSerial.print(arr[i]);
            debugSerial.print(" | ");
        }
        debugSerial.println(arr[cntEye - 1]);
    }
#endif
    /******************************
    函数名称：getMinNo
    函数功能：读取所有通道并返回值最小的通道编号
    传入参数：无
    返回值：返回值最小的通道编号
    ******************************/
    uchr getMinNo(void)
    {
        getAllValue(value);
        return getMinNo(value);
    }

    uchr getMinNo(uint *arr)
    {
        uint Min = arr[0];
        uchr no = 0;

        for(uchr i = 1; i < cntEye; ++i)
        {
            if(arr[i] < Min)
            {
                Min = arr[i];
                no = i;
            }
        }

        return no;
    }

    /******************************
    函数名称：getMinDir
    函数功能：读取所有通道并计算值最小的通道所对应的角度
    传入参数：无
    返回值：值最小的通道所对应的角度
    ******************************/
    float getMinDir(void)
    {
        return degreePerEye * getMinNo();
    }

    float getMinDir(uint *arr)
    {
        return degreePerEye * getMinNo(arr);
    }

    inline uint degreesPerEye(void) const
    {
        return this -> degreePerEye;
    }

    uint getMinValue(void)
    {
        getAllValue(value);
        return value[getMinNo(value)];
    }

    uint getMinValue(uint *arr)
    {
        return arr[getMinNo(arr)];
    }

    inline uint getEnvironIR(void) const
    {
        return environIR;
    }

    inline void setEnvironIR(uint IR)
    {
        environIR = IR;
    }

    inline uint getCntEye(void) const
    {
        return cntEye;
    }

    uint read(uchr channel = 0)
    {
        return analogRead(sPin + channel);
    }
};

#endif // __IR_EYE_H__
