# Build Notes for X11/Xorg Compatibility

## Dependencies Required

To build XRLinuxDriver with X11/Xorg compatibility, you need:

```bash
sudo apt install \
    build-essential \
    cmake \
    pkg-config \
    libusb-1.0-0-dev \
    libevdev-dev \
    libssl-dev \
    libjson-c-dev \
    libcurl4-openssl-dev \
    libwayland-dev
```

## Build Steps

```bash
cd /home/rebroad/src/XRLinuxDriver
mkdir -p build
cd build
cmake ..
make
```

After building, the binary will be in `build/xrDriver`. Copy it to the bin directory:
```bash
cp build/xrDriver bin/xrDriver
```

## Installation

After building and copying the binary, install using the user install script:
```bash
bin/user/install
```

**Note:** The `bin/xr_driver_setup` script downloads a pre-built binary, which won't include your source modifications. You must build from source if you've modified the code.

## Testing X11/Xorg Compatibility

1. Start the XR driver (if not already running): `systemctl --user start xr-driver`
2. Launch xfce4-xr-desktop application (it can be set to autostart)
3. The application provides a GUI window for controlling XR settings
4. Verify state file includes `device_connected` flag: `cat /dev/shm/xr_driver_state | grep device_connected`

## Differences from Breezy Desktop

**Breezy Desktop** (GNOME/KDE only):
- Native desktop extension that integrates directly into the compositor (Mutter/KWin)
- Works automatically once installed - no GUI window needed
- Creates virtual displays as part of the desktop environment
- Settings managed through desktop settings panels
- More deeply integrated, potentially better performance

**xfce4-xr-desktop** (X11/Xorg-based desktops):
- Standalone GUI application (can autostart)
- User interacts through a control window
- Provides manual control over XR settings
- Less integrated but more flexible for X11-based desktop users
- Performance should be similar for basic operations

## Verification Checklist

- [x] Plugin compiles without errors
- [x] Plugin registered in plugin list
- [x] Plugin added to CMakeLists.txt
- [x] State file includes device_connected
- [ ] Full build with dependencies (requires libusb, etc.)
- [ ] Runtime testing with actual XReal glasses
- [ ] Integration testing with xfce4-xr-desktop

