#ifndef __PID_H__
#define __PID_H__

class PID
{
protected:
    double dState; // Last position input
    double iState; // Integrator state
    double iMax, iMin; // Maximum and minimum allowable integrator state
    double iGain, // integral gain
           pGain, // proportional gain
           dGain; // derivative gain
public:
    PID() {}

    PID(double Kp = 0.0,double Ki = 0.0,double Kd = 0.0,double Max = 1e7,double Min = -1e7)
    {
        pGain = Kp;
        iGain = Ki;
        dGain = Kd;
        iMax = Max;
        iMin = Min;
        dState = 0.0;
		iState = 0.0;
    }

    double Update(double error, double position)
    {
        double pTerm,dTerm, iTerm;
        // calculate the proportional term
        pTerm = pGain * error;
        // calculate the integral state with appropriate limiting
        iState += error;
        if (iState > iMax)
            iState = iMax;
        else if (iState < iMin)
            iState = iMin;
        iTerm = iGain * iState; // calculate the integral term
        dTerm = dGain * (position - dState);
        dState = position;
        return pTerm + iTerm - dTerm;
    }

    inline void reset(void)
    {
        dState = iState = 0.0;
    }
};

#endif // __PID_H__
