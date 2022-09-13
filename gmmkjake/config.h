/* Change USB Polling Rate to 1000hz and a larger keys per scan for elite gaming*/
#undef USB_POLLING_INTERVAL_MS
#undef QMK_KEYS_PER_SCAN
#define USB_POLLING_INTERVAL_MS 1
#define QMK_KEYS_PER_SCAN 12
#define RGBLIGHT_SLEEP
#define RGB_DISABLE_WHEN_USB_SUSPENDED true