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
2. Launch Breezy Desktop application
3. Breezy Desktop provides integration with X11/Xorg-based desktop environments
4. Verify state file includes `device_connected` flag: `cat /dev/shm/xr_driver_state | grep device_connected`

## Breezy Desktop Support

**Breezy Desktop** supports multiple desktop environments:
- **GNOME/KDE**: Native desktop extension that integrates directly into the compositor (Mutter/KWin)
- **X11/Xorg-based desktops**: Uses Xorg modesetting driver with virtual XR connectors
- Works automatically once installed
- Creates virtual displays as part of the desktop environment
- Settings managed through desktop settings panels or Breezy Desktop UI

## Verification Checklist

- [x] Plugin compiles without errors
- [x] Plugin registered in plugin list
- [x] Plugin added to CMakeLists.txt
- [x] State file includes device_connected
- [ ] Full build with dependencies (requires libusb, etc.)
- [ ] Runtime testing with actual XReal glasses
- [ ] Integration testing with Breezy Desktop on X11/Xorg

