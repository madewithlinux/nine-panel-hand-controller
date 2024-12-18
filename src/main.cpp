#include <stdio.h>
#include "hardware/clocks.h"
#include "hardware/timer.h"
#include "pico/stdlib.h"

#include "bsp/board.h"
#include "tusb.h"
#include "usb_descriptors.h"

int64_t alarm_callback(alarm_id_t id, void* user_data) {
  // Put your timeout handler code in here
  return 0;
}

int main() {
  board_init();
  tud_init(BOARD_TUD_RHPORT);
  stdio_init_all();

  // Timer example code - This example fires off the callback after 2000ms
  add_alarm_in_ms(2000, alarm_callback, NULL, false);
  // For more examples of timer use see https://github.com/raspberrypi/pico-examples/tree/master/timer

  printf("System Clock Frequency is %d Hz\n", clock_get_hz(clk_sys));
  printf("USB Clock Frequency is %d Hz\n", clock_get_hz(clk_usb));
  // For more examples of clocks use see https://github.com/raspberrypi/pico-examples/tree/master/clocks

  while (true) {
    tud_task();  // tinyusb device task
                 // printf("Hello, world!\n");
                 // sleep_ms(1000);
  }
}

// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t tud_hid_get_report_cb(uint8_t instance,
                               uint8_t report_id,
                               hid_report_type_t report_type,
                               uint8_t* buffer,
                               uint16_t reqlen) {
  // TODO not Implemented
  (void)instance;
  (void)report_id;
  (void)report_type;
  (void)buffer;
  (void)reqlen;

  return 0;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void tud_hid_set_report_cb(uint8_t instance,
                           uint8_t report_id,
                           hid_report_type_t report_type,
                           uint8_t const* buffer,
                           uint16_t bufsize) {
  (void)instance;
  // do nothing
}
