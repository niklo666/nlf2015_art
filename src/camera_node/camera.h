/*
  *** camera_node ***
  camera.h
*/

#ifndef CAMERA_H
#define CAMERA_H

/*void *cam_thread_function( void *ptr );*/
int camera_set_parameter(uint8_t parameter, double value);
int camera_get_parameter(uint8_t parameter, double &value);
int camera_get_derived_image_data(/* slow and fast datasets...*/);
int camera_get_raw_image_data(char** buffer, int* size);

#endif // CAMERA_H
