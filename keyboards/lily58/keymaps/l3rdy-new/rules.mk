LTO_ENABLE = yes            # Link Time Optimization enabled
BOOTMAGIC_ENABLE = yes       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = no        # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes            # N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
AUDIO_ENABLE = no           # Audio output
RGBLIGHT_ENABLE = no        # Enable WS2812 RGB underlight.
SWAP_HANDS_ENABLE = no      # Enable one-hand typing
OLED_ENABLE = yes           # OLED display
KEYMAP_INTROSPECTION_ENABLE := no
INTROSPECTION_ENABLE := no
WPM_ENABLE = yes
TAP_DANCE_ENABLE = yes

UNICODE_ENABLE = yes
# pick the mode your OS uses—on Windows you’d do:
UNICODE_SELECTED_MODES = UNICODE_WINCOMPOSE
# on macOS: UNICODE_OSX
# on Linux you can also use UNICODE_LINUX_LAYER or WINCOMPOSE

# If you want to change the display of OLED, you need to change here
SRC += luna.c \
       ./lib/rgb_state_reader.c \
       ./lib/layer_state_reader.c \
       ./lib/logo_reader.c \
       ./lib/keylogger.c \
        # ./lib/mode_icon_reader.c \
        # ./lib/host_led_state_reader.c \
        # ./lib/timelogger.c \
