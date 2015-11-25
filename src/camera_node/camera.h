/*
  *** camera_node ***
  camera.h
*/

#include <stdint.h>
#include <inttypes.h>
#include "../../shared/camera_protocol.h"

#ifndef CAMERA_H
#define CAMERA_H


// todo: move to prototcol or include from prototcol!?
typedef struct
{
  // todo: add useful parameters...
  double alpha_fast;
  double alpha_slow;
  double threshold;
  double threshold_max;
}camera_parameters_t;


/*void *cam_thread_function( void *ptr );*/
int camera_init(void);
int camera_reset(void);
int camera_set_parameter(uint8_t parameter_id, double value);
int camera_get_parameter(uint8_t parameter_id, double *value);
int camera_get_data(camera_data_t* data);
int camera_get_image(char** buffer, int* size);

#endif // CAMERA_H
