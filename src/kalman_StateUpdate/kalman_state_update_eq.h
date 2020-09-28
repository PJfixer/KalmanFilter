/*
 * kalman_state_update_eq.h
 *
 *  Created on: 21 sept. 2020
 *      Author: pjeanne
 */

#ifndef KALMAN_STATE_UPDATE_EQ_H_
#define KALMAN_STATE_UPDATE_EQ_H_

typedef struct {

	float coef;
	float kalman_gain;
	float error_measure;
	float error_estimate;
	float current_estimate;
	float prev_estimate;
	

}kalman_datastruct;

void StateKalmanFilter_init(kalman_datastruct *filterparams,float error_measure, float error_estimate, float coef);
float StateKalmanFilter_updateEstimate(kalman_datastruct *filterparams,float measure);
void StateKalmanFilter_setProcessNoiseCoef(kalman_datastruct *filterparams,float coef);
#endif /* KALMAN_STATE_UPDATE_EQ_H_ */
