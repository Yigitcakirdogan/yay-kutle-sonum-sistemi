/**
 * @file    discrete_pid.c
 * @author  Yigit Cakirdogan
 * @brief   Implementation of anti-windup discrete PID controller and
 *          finite-difference mass-spring-damper difference equation solver.
 */

#include "discrete_pid.h"

void discrete_pid_init(discrete_pid_t *pid,
                       float kp, float ki, float kd,
                       float ts_sec, float out_min, float out_max)
{
    if (pid == 0) {
        return;
    }
    pid->kp               = kp;
    pid->ki               = ki;
    pid->kd               = kd;
    pid->ts_sec           = (ts_sec > 1e-6f) ? ts_sec : 0.001f;
    pid->out_min          = out_min;
    pid->out_max          = out_max;
    pid->integral_term    = 0.0f;
    pid->prev_measurement = 0.0f;
}

float discrete_pid_update(discrete_pid_t *pid, float setpoint, float measurement)
{
    float error = setpoint - measurement;

    /* Proportional term */
    float p_term = pid->kp * error;

    /* Integral term with clamping anti-windup */
    pid->integral_term += pid->ki * error * pid->ts_sec;
    if (pid->integral_term > pid->out_max) {
        pid->integral_term = pid->out_max;
    } else if (pid->integral_term < pid->out_min) {
        pid->integral_term = pid->out_min;
    }

    /* Derivative-on-measurement to prevent setpoint step derivative kick */
    float d_term = -pid->kd * ((measurement - pid->prev_measurement) / pid->ts_sec);
    pid->prev_measurement = measurement;

    float output = p_term + pid->integral_term + d_term;
    if (output > pid->out_max) {
        output = pid->out_max;
    } else if (output < pid->out_min) {
        output = pid->out_min;
    }

    return output;
}

void msd_plant_init(mass_spring_damper_t *plant,
                    float mass_kg, float damping_c, float stiffness_k, float ts_sec)
{
    if (plant == 0) {
        return;
    }
    plant->mass_kg     = mass_kg;
    plant->damping_c   = damping_c;
    plant->stiffness_k = stiffness_k;
    plant->ts_sec      = ts_sec;
    plant->x_prev1     = 0.0f;
    plant->x_prev2     = 0.0f;
}

float msd_plant_step(mass_spring_damper_t *plant, float force_n)
{
    float m   = plant->mass_kg;
    float c   = plant->damping_c;
    float k   = plant->stiffness_k;
    float dt  = plant->ts_sec;
    float dt2 = dt * dt;

    float denom = m + (c * dt) + (k * dt2);
    float x_now = ((dt2 * force_n) + ((2.0f * m + c * dt) * plant->x_prev1) - (m * plant->x_prev2)) / denom;

    plant->x_prev2 = plant->x_prev1;
    plant->x_prev1 = x_now;
    return x_now;
}
