# XFCE4 Compatibility

XRLinuxDriver has been updated to work with xfce4-xr-desktop. The xfce4-xr-desktop application now uses XRLinuxDriver's internal command names directly.

## Command Names Used by xfce4-xr-desktop

xfce4-xr-desktop now uses XRLinuxDriver's native command names:

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

## Integration with xfce4-xr-desktop

xfce4-xr-desktop has been updated to use XRLinuxDriver's native command names directly. No compatibility layer is needed - the application writes commands in XRLinuxDriver's format.

