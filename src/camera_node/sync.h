/*
  *** camera_node ***
  sync.h

  contains means for syncing threads and shared data

  shared data:
  - camera order,
  - camera status,
  - camera parameters,
  - camera data,
*/

enum
{
  CAM_ORDER_NONE = 0,
  CAM_ORDER_START,
  CAM_ORDER_STOP,
};

enum
{
  CAM_STATUS_NONE = 0,
  CAM_STATUS_RUNNING,
  CAM_STATUS_STOPPED,
  CAM_STATUS_ERROR,
};

enum
{
  CAM_PARAMETER_NONE = 0,
  // todo: add useful parameters...
};

void set_camera_order(uint8_t order);
uint8_t get_camera_order(void);
void set_camera_status(uint8_t status);
uint8_t get_camera_status(void);
