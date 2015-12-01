

#ifndef CONFIG_H
#define CONFIG_H

/*
  what config items do we need?

  comm related:
  - camera ips
  - camera ports

  camera related:
  - alpha fast, averaging "mix" in parameter for fast response...
  - alpha slow, averaging "mix" in parameter for slow response...
  - threshold fast, threshold for generating fast response movement contours...
  - threshold slow, threshold for generating slow response movement contours...
  - threshold max, ???
  - contour min area fast,
  - contour min area slow,
  - contours max fast, cap the number of contours to deal with - fast
  - contours max slow, cap the number of contours to deal with - slow
  - ...

*/


int config_read(char* config_file);
void config_dump(void);
int config_get_string_value(char* key, char* value);
int config_get_int_value(char* key, int* value);
int config_get_double_value(char* key, double* value);
int config_find_key(char* key);

#endif
