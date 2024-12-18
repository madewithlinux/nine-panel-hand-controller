#include <stdio.h>
#include "hardware/clocks.h"
#include "hardware/timer.h"
#include "pico/stdlib.h"

#include "bsp/board.h"
#include "tusb.h"
#include "usb_descriptors.h"

int gpios[] = {
    // these are in whatever order I happened to solder the wires in
    12, 11, 13,

    5,  6,  7,

    9,  10, 8,

    18,
};

constexpr int num_gpios = count_of(gpios);

uint8_t keycode_map[] = {
    HID_KEY_Q,     HID_KEY_W, HID_KEY_E,

    HID_KEY_A,     HID_KEY_S, HID_KEY_D,

    HID_KEY_Z,     HID_KEY_X, HID_KEY_C,

    HID_KEY_ENTER,
};

void hid_task(void) {
  // Remote wakeup
  if (tud_suspended()) {
    // Wake up host if we are in suspend mode
    // and REMOTE_WAKEUP feature is enabled by host
    tud_remote_wakeup();
  }

  // skip if hid is not ready yet
  if (!tud_hid_ready()) {
    return;
  }

  uint8_t hid_report_keycodes[6] = {0};
  int hid_keycode_idx = 0;
  for (int i = 0; i < num_gpios; i++) {
    int gpio = gpios[i];
    // we invert the GPIO because it pulls to ground when pressed
    if (!gpio_get(gpio)) {
      hid_report_keycodes[hid_keycode_idx] = keycode_map[i];
      hid_keycode_idx++;
    }
  }
  tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, hid_report_keycodes);
}

int main() {
  board_init();
  tud_init(BOARD_TUD_RHPORT);
  stdio_init_all();

  printf("System Clock Frequency is %d Hz\n", clock_get_hz(clk_sys));
  printf("USB Clock Frequency is %d Hz\n", clock_get_hz(clk_usb));
  // For more examples of clocks use see https://github.com/raspberrypi/pico-examples/tree/master/clocks

  for (int i = 0; i < num_gpios; i++) {
    int gpio = gpios[i];
    gpio_init(gpio);
    gpio_set_dir(gpio, GPIO_IN);
    gpio_pull_up(gpio);
  }

  while (true) {
    tud_task();  // tinyusb device task
    hid_task();
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
