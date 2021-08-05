#include "pid.h"

void pidReset(P_PID_HANDLE phdl)
{
    phdl->sum_error     = 0;
    phdl->last_error    = 0;
    filter1Reset(&phdl->hfilter1);
}


double pidProcess(P_PID_HANDLE phdl, double input, double measure)
{
    double output = 0;
    double error = input - measure;         //计算误差

    phdl->sum_error += error;

    //误差积分限幅
    if(phdl->enable_lim_sum_error == 1 && fabs(phdl->sum_error) > phdl->lim_sum_error)
    {
        if(phdl->sum_error > 0)
            phdl->sum_error = phdl->lim_sum_error;
        else
            phdl->sum_error = -phdl->lim_sum_error;
    }

    output =        phdl->kp * error
                +   phdl->ki * phdl->sum_error
                +   phdl->kd * filter1Process(&phdl->hfilter1, error - phdl->last_error);
                // +   phdl->kd * (error - phdl->last_error) / phdl->ctrlcycle;

    //输出限幅
    if(phdl->enable_lim_ouput == 1 && fabs(output) > phdl->lim_output)
    {
        if(output > 0)
            output = phdl->lim_output;
        else
            output = -phdl->lim_output;
    }
    //当误差小于某个值时，速度为0，清零积分
		if(fabs(error)<5)
		{
			output=0;
			phdl->sum_error=0;
		}
    //更新误差值
    phdl->last_error = error;

    //是否使能输出
    if(phdl->enable == 1)
        return output;
    else
        return 0;
}



