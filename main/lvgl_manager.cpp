// std library

// other libraries
#include <lvgl.h>
#include <lvgl_helpers.h>

// project header files
#include "lvgl_manager.hpp"
#include "sdkconfig.h"

// global variables
static lv_disp_drv_t disp_drv;
static lv_indev_drv_t indev_drv;
static lv_disp_buf_t disp_buf;
static lv_color16_t color_buf[2][DISP_BUF_SIZE];

void LvglManager::init() {
  // init lvgl and its driver
  lv_init();
  lvgl_driver_init();

  // init display
  lv_disp_buf_init(&disp_buf, &color_buf[0], &color_buf[1], DISP_BUF_SIZE);

  // init display driver
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = LV_HOR_RES_MAX;
  disp_drv.ver_res = LV_VER_RES_MAX;
  disp_drv.flush_cb = disp_driver_flush;
  disp_drv.buffer = &disp_buf;
  lv_disp_drv_register(&disp_drv);

  // init input device
#if CONFIG_LV_TOUCH_CONTROLLER != TOUCH_CONTROLLER_NONE
  lv_indev_drv_init(&indev_drv);
	indev_drv.read_cb = touch_driver_read;
	indev_drv.type = LV_INDEV_TYPE_POINTER;
	lv_indev_drv_register(&indev_drv);
#else
#error "Touch Controller Not Found"
#endif
}