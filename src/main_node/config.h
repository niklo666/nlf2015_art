

#ifndef CONFIG_H
#define CONFIG_H

int config_read(char* config_file);
void config_dump(void);
int config_get_string_value(char* key, char* value);
int config_get_int_value(char* key, int* value);
int config_get_double_value(char* key, double* value);
int config_find_key(char* key);

#endif
