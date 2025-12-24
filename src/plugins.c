#include "logging.h"
#include "plugins.h"
#include "plugins/custom_banner.h"
#include "plugins/breezy_desktop.h"
#include "plugins/gamescope_reshade_wayland.h"
#include "plugins/metrics.h"
#include "plugins/sideview.h"
#include "plugins/smooth_follow.h"
#include "plugins/virtual_display.h"
#include "plugins/neck_saver.h"
#include "plugins/opentrack_source.h"
#include "plugins/opentrack_listener.h"
#include "state.h"

#include <stdlib.h>

#define PLUGIN_COUNT 10
const plugin_type* all_plugins[PLUGIN_COUNT] = {
    &virtual_display_plugin,
    &sideview_plugin,
    &metrics_plugin,
    &custom_banner_plugin,
    &smooth_follow_plugin,
    &breezy_desktop_plugin,
    &gamescope_reshade_wayland_plugin,
    &neck_saver_plugin,
    &opentrack_source_plugin,
    &opentrack_listener_plugin
};

// Macro to iterate over plugins and call a void callback
#define FOR_EACH_PLUGIN_CALL_VOID(callback_field) \
    for (int i = 0; i < PLUGIN_COUNT; i++) { \
        if (all_plugins[i]->callback_field == NULL) continue; \
        all_plugins[i]->callback_field(); \
    }

// Macro to iterate over plugins and call a callback with arguments
#define FOR_EACH_PLUGIN_CALL_VOID_ARGS(callback_field, ...) \
    for (int i = 0; i < PLUGIN_COUNT; i++) { \
        if (all_plugins[i]->callback_field == NULL) continue; \
        all_plugins[i]->callback_field(__VA_ARGS__); \
    }

void all_plugins_start_func() {
    FOR_EACH_PLUGIN_CALL_VOID(start)
}
void* all_plugins_default_config_func() {
    void** configs = calloc(PLUGIN_COUNT, sizeof(void*));
    for (int i = 0; i < PLUGIN_COUNT; i++) {
        if (all_plugins[i]->default_config == NULL) continue;
        configs[i] = all_plugins[i]->default_config();
    }

    return configs;
}
void all_plugins_handle_config_line_func(void* config, char* key, char* value) {
    void **configs = (void**)config;
    for (int i = 0; i < PLUGIN_COUNT; i++) {
        if (all_plugins[i]->handle_config_line == NULL) continue;
        all_plugins[i]->handle_config_line(configs[i], key, value);
    }
}
void all_plugins_handle_control_flag_line_func(char* key, char* value) {
    FOR_EACH_PLUGIN_CALL_VOID_ARGS(handle_control_flag_line, key, value)
}
void all_plugins_set_config_func(void* config) {
    void **configs = (void**)config;
    for (int i = 0; i < PLUGIN_COUNT; i++) {
        if (all_plugins[i]->set_config == NULL) continue;
        all_plugins[i]->set_config(configs[i]);
    }
}
bool all_plugins_setup_ipc_func() {
    for (int i = 0; i < PLUGIN_COUNT; i++) {
        if (all_plugins[i]->setup_ipc == NULL) continue;
        if (!all_plugins[i]->setup_ipc()) {
            log_error("Failed to setup IPC for plugin %s\n", all_plugins[i]->id);
            exit(1);
        }
    }

    return true;
}
void all_plugins_handle_ipc_change_func() {
    FOR_EACH_PLUGIN_CALL_VOID(handle_ipc_change)
}
bool all_plugins_modify_reference_pose_func(imu_pose_type pose, imu_pose_type* ref_pose) {
    bool modified = false;
    for (int i = 0; i < PLUGIN_COUNT; i++) {
        if (all_plugins[i]->modify_reference_pose == NULL) continue;
        modified |= all_plugins[i]->modify_reference_pose(pose, ref_pose);
    }
    return modified;
}

void all_plugins_modify_pose_func(imu_pose_type* pose) {
    FOR_EACH_PLUGIN_CALL_VOID_ARGS(modify_pose, pose)
}
void all_plugins_handle_pose_data_func(imu_pose_type pose, imu_euler_type velocities, bool imu_calibrated, ipc_values_type *ipc_values) {
    FOR_EACH_PLUGIN_CALL_VOID_ARGS(handle_pose_data, pose, velocities, imu_calibrated, ipc_values)
}

void all_plugins_reset_pose_data_func() {
    FOR_EACH_PLUGIN_CALL_VOID(reset_pose_data)
}
void all_plugins_handle_state_func() {
    FOR_EACH_PLUGIN_CALL_VOID(handle_state)
}
void all_plugins_handle_device_connect_func() {
    FOR_EACH_PLUGIN_CALL_VOID(handle_device_connect)
}
void all_plugins_handle_device_disconnect_func() {
    FOR_EACH_PLUGIN_CALL_VOID(handle_device_disconnect)
}

const plugin_type plugins = {
    .id = "all_plugins",
    .start = all_plugins_start_func,
    .default_config = all_plugins_default_config_func,
    .handle_config_line = all_plugins_handle_config_line_func,
    .handle_control_flag_line = all_plugins_handle_control_flag_line_func,
    .set_config = all_plugins_set_config_func,
    .setup_ipc = all_plugins_setup_ipc_func,
    .handle_ipc_change = all_plugins_handle_ipc_change_func,
    .modify_reference_pose = all_plugins_modify_reference_pose_func,
    .modify_pose = all_plugins_modify_pose_func,
    .handle_pose_data = all_plugins_handle_pose_data_func,
    .reset_pose_data = all_plugins_reset_pose_data_func,
    .handle_state = all_plugins_handle_state_func,
    .handle_device_connect = all_plugins_handle_device_connect_func,
    .handle_device_disconnect = all_plugins_handle_device_disconnect_func
};