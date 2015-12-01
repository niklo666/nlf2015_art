/*
  comm.h
*/

#include "../../shared/camera_protocol.h"

#ifndef COMM_H
#define COMM_H

// void* comm_thread_function(void* ptr);

int comm_connect(char* hostname, int portno);

int comm_set_camera_parameter(int parameter, double value);
int comm_get_camera_data(camera_data_t* camera_data);


#endif // COMM_H
