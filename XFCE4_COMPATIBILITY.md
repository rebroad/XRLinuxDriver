# X11/Xorg Compatibility

XRLinuxDriver's command interface is designed to work with X11/Xorg-based desktop applications. Applications use XRLinuxDriver's internal command names directly.

## Command Names for X11/Xorg Applications

X11/Xorg-based applications (like Breezy Desktop) use XRLinuxDriver's native command names:

| Command | Value Format | Description |
|---------|--------------|-------------|
| `breezy_desktop_display_distance` | `<float>` | Display distance in meters |
| `enable_breezy_desktop_smooth_follow` | `true/false` | Enable/disable smooth follow mode |
| `breezy_desktop_follow_threshold` | `<float>` | Follow threshold in radians |
| `recenter_screen` | `true` | Recenter the display |
| `sbs_mode` | `enable/disable` | Enable/disable widescreen (SBS) mode |

## State File Updates

The state file (`/dev/shm/xr_driver_state`) now includes:
- `device_connected=true/false` - Indicates if a device is currently connected

## Files Modified

1. **Modified Files:**
   - `src/state.c` - Added `device_connected` to state file output

## Building

Build XRLinuxDriver normally:

```bash
mkdir build && cd build
cmake ..
make
```

## Testing

Test by writing commands directly to the control file:
```bash
echo "breezy_desktop_display_distance=1.5" > /dev/shm/xr_driver_control
echo "enable_breezy_desktop_smooth_follow=true" > /dev/shm/xr_driver_control
echo "recenter_screen=true" > /dev/shm/xr_driver_control
```

Check the driver log and state file to verify commands are processed.

## Integration with X11/Xorg Applications

X11/Xorg-based applications (like Breezy Desktop) use XRLinuxDriver's native command names directly. No compatibility layer is needed - applications write commands in XRLinuxDriver's format.

