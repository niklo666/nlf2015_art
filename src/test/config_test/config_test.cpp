
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../main_node/config.h"

int main(int argc, char* argv[])
{
  config_read(argv[1]);

  config_dump();

  return 0;
}
