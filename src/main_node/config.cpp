#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "config.h"


#define MAXBUF 1024
#define DELIM "="
#define MAXCONFITEMS 64

typedef struct
{
  char* key;
  char* value;
}key_value_pair_t;

key_value_pair_t g_config_items[MAXCONFITEMS];
int g_config_item_counter = 0;

int config_read(char* config_file)
{

  FILE *file = fopen (config_file, "r");
  if (file == NULL)
  {
    return -1;
  }

  char line[MAXBUF];

  // init...
  for (int i=0;i<MAXCONFITEMS;i++)
  {
    g_config_items[i].key   = 0;
    g_config_items[i].value = 0;
  }


  while(fgets(line, MAXBUF, file) != NULL)
  {
    char *cfline;
    char* key;
    char* value;

    key = line;
    cfline = strstr((char *)line, DELIM);
    *cfline = '\0';
    value = cfline + strlen(DELIM);

    //printf("key: %s value: %s", key, value);

    g_config_items[g_config_item_counter].key = (char*)malloc(strlen(key) + 1);
    strncpy(g_config_items[g_config_item_counter].key , key, strlen(key));

    g_config_items[g_config_item_counter].value = (char*)malloc(strlen(value) + 1);
    strncpy(g_config_items[g_config_item_counter].value , value, strlen(value));

    g_config_item_counter++;
  } // End while

  fclose(file);

  return 0;
}

int config_get_string_value(char* key, char* value)
{
  int index = 0;

  index = config_find_key(key);
  if (index == -1)
  {
    return -1;
  }

  strcpy(value, g_config_items[index].value);

  return 0;
}

int config_get_int_value(char* key, int* value)
{
  int index = 0;

  index = config_find_key(key);
  if (index == -1)
  {
    return -1;
  }

  *value = atoi(g_config_items[index].value);

  return 0;
}

int config_get_double_value(char* key, double* value)
{
  int index = 0;

  index = config_find_key(key);
  if (index == -1)
  {
    return -1;
  }

  *value = atof(g_config_items[index].value);

  return 0;
}

int config_find_key(char* key)
{
  for (int i = 0; i < g_config_item_counter; i++)
  {
      if (!strcmp(key, g_config_items[i].value))
      {
        return i;
      }
  }

  return -1;
}


void config_dump(void)
{
  for (int i = 0; i < g_config_item_counter; i++)
  {
    printf("key: %s value: %s", g_config_items[i].key, g_config_items[i].value);
  }
}
