#ifndef FILTER_H
#define FILTER_H

#define UPPER_LIMIT 500
#define MeasureNoise_R 0.542
#define ProcessNiose_Q 0.118
void kalmanfilter(int16_t *z_measure);
void limitfilter(int16_t *measure);


#endif
