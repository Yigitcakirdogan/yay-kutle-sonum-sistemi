/**
 * @file    discrete_pid.h
 * @author  Yigit Cakirdogan
 * @brief   Deterministic Discrete-Time PID Controller and Finite-Difference
 *          Mass-Spring-Damper LTI Plant Model for Embedded Microcontrollers.
 */

#ifndef DISCRETE_PID_H
#define DISCRETE_PID_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    float kp;
    float ki;
    float kd;
    float ts_sec;
    float out_min;
    float out_max;
    float integral_term;
    float prev_measurement;
} discrete_pid_t;

typedef struct {
    float mass_kg;
    float damping_c;
    float stiffness_k;
    float ts_sec;
    float x_prev1; /* x[n-1] */
    float x_prev2; /* x[n-2] */
} mass_spring_damper_t;

void  discrete_pid_init(discrete_pid_t *pid, float kp, float ki, float kd, float ts_sec, float out_min, float out_max);
float discrete_pid_update(discrete_pid_t *pid, float setpoint, float measurement);

void  msd_plant_init(mass_spring_damper_t *plant, float mass_kg, float damping_c, float stiffness_k, float ts_sec);
float msd_plant_step(mass_spring_damper_t *plant, float force_n);

#ifdef __cplusplus
}
#endif

#endif /* DISCRETE_PID_H */
