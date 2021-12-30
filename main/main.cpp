// std library

// other libraries
#include <lvgl.h>
#include <lvgl_helpers.h>

// project header files
#include "power_manager.hpp"

extern "C" void app_main(void) {
  PowerManager::instance().setup();
}
