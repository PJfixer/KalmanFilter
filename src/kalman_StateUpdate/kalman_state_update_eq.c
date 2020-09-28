/*
 * kalman_state_update_eq.c
 *
 *  Created on: 21 sept. 2020
 *      Author: pjeanne
 */

#include "kalman_state_update_eq.h"
#include <math.h>

void StateKalmanFilter_init(kalman_datastruct *filterparams,float error_measure, float error_estimate, float coef)
{

	filterparams->error_measure=error_measure;
	filterparams->error_estimate=error_estimate;
	filterparams->coef = coef;
}

float StateKalmanFilter_updateEstimate(kalman_datastruct *filterparams,float measure)
{
	filterparams->kalman_gain = filterparams->error_estimate/(filterparams->error_estimate + filterparams->error_measure);
	filterparams->current_estimate = filterparams->prev_estimate + filterparams->kalman_gain * (measure - filterparams->prev_estimate);
	filterparams->error_estimate =  (1.0 - filterparams->kalman_gain)*filterparams->error_estimate + fabs(filterparams->prev_estimate-filterparams->current_estimate)*filterparams->coef;
	filterparams->prev_estimate=filterparams->current_estimate;

  return filterparams->current_estimate;
}



void StateKalmanFilter_setProcessNoiseCoef(kalman_datastruct *filterparams,float coef)
{
	filterparams->coef=coef;
}





