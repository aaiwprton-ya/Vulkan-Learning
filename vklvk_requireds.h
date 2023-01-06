#ifndef VKL_VK_REQUIREDS_H
#define VKL_VK_REQUIREDS_H

/*
    LAYERS
*/

// Available instance layers
//    "VK_LAYER_NV_optimus"
//    "VK_LAYER_MESA_device_select"
//    "VK_LAYER_KHRONOS_validation"
//    "VK_LAYER_MESA_overlay"

#define VKLVK_PROP_MAXENABLEDINSTANCELAYERCOUNT 4
#define VKLVK_PROP_ENABLEDINSTANCELAYERCOUNT 4

static const char* VKLVK_PROP_INSTANCELAYERNAMES[VKLVK_PROP_MAXENABLEDINSTANCELAYERCOUNT] = {
    "VK_LAYER_NV_optimus", 
    "VK_LAYER_MESA_device_select", 
    "VK_LAYER_KHRONOS_validation", 
    "VK_LAYER_MESA_overlay"};

// Available device layers
//    "VK_LAYER_NV_optimus"
//    "VK_LAYER_MESA_device_select"
//    "VK_LAYER_KHRONOS_validation"
//    "VK_LAYER_MESA_overlay"

#define VKLVK_PROP_MAXENABLEDDEVICELAYERCOUNT 4
#define VKLVK_PROP_ENABLEDDEVICELAYERCOUNT 4

static const char* VKLVK_PROP_DEVICELAYERNAMES[VKLVK_PROP_MAXENABLEDDEVICELAYERCOUNT] = {
    "VK_LAYER_NV_optimus", 
    "VK_LAYER_MESA_device_select", 
    "VK_LAYER_KHRONOS_validation", 
    "VK_LAYER_MESA_overlay"};
    
/*
    EXTENSIONS
*/

// Available 19 instance extensions
//    VK_KHR_device_group_creation
//    VK_KHR_external_fence_capabilities
//    VK_KHR_external_memory_capabilities
//    VK_KHR_external_semaphore_capabilities
//    VK_KHR_get_physical_device_properties2
//    VK_KHR_get_surface_capabilities2
//    VK_KHR_surface
//    VK_KHR_surface_protected_capabilities
//    VK_KHR_wayland_surface
//    VK_KHR_xcb_surface
//    VK_KHR_xlib_surface
//    VK_EXT_debug_report
//    VK_KHR_display
//    VK_KHR_get_display_properties2
//    VK_EXT_acquire_xlib_display
//    VK_EXT_debug_utils
//    VK_EXT_direct_mode_display
//    VK_EXT_display_surface_counter
//    VK_EXT_acquire_drm_display

#define VKLVK_PROP_MAXENABLEDINSTANCEEXENSIONCOUNT 2
#define VKLVK_PROP_ENABLEDINSTANCEEXTENSIONCOUNT 2

static const char* VKLVK_PROP_INSTANCEEXTENSIONNAMES[VKLVK_PROP_MAXENABLEDINSTANCEEXENSIONCOUNT] = {
    "VK_EXT_debug_report", 
    "VK_EXT_debug_utils"};

// Available 119 device extensions
//    VK_KHR_16bit_storage
//    VK_KHR_8bit_storage
//    VK_KHR_bind_memory2
//    VK_KHR_buffer_device_address
//    VK_KHR_copy_commands2
//    VK_KHR_create_renderpass2
//    VK_KHR_dedicated_allocation
//    VK_KHR_depth_stencil_resolve
//    VK_KHR_descriptor_update_template
//    VK_KHR_device_group
//    VK_KHR_draw_indirect_count
//    VK_KHR_driver_properties
//    VK_KHR_external_fence
//    VK_KHR_external_fence_fd
//    VK_KHR_external_memory
//    VK_KHR_external_memory_fd
//    VK_KHR_external_semaphore
//    VK_KHR_external_semaphore_fd
//    VK_KHR_get_memory_requirements2
//    VK_KHR_image_format_list
//    VK_KHR_imageless_framebuffer
//    VK_KHR_maintenance1
//    VK_KHR_maintenance2
//    VK_KHR_maintenance3
//    VK_KHR_multiview
//    VK_KHR_pipeline_executable_properties
//    VK_KHR_push_descriptor
//    VK_KHR_relaxed_block_layout
//    VK_KHR_sampler_mirror_clamp_to_edge
//    VK_KHR_sampler_ycbcr_conversion
//    VK_KHR_separate_depth_stencil_layouts
//    VK_KHR_shader_atomic_int64
//    VK_KHR_shader_clock
//    VK_KHR_shader_draw_parameters
//    VK_KHR_shader_float16_int8
//    VK_KHR_shader_float_controls
//    VK_KHR_shader_non_semantic_info
//    VK_KHR_shader_subgroup_extended_types
//    VK_KHR_shader_terminate_invocation
//    VK_KHR_spirv_1_4
//    VK_KHR_storage_buffer_storage_class
//    VK_KHR_swapchain
//    VK_KHR_swapchain_mutable_format
//    VK_KHR_synchronization2
//    VK_KHR_timeline_semaphore
//    VK_KHR_uniform_buffer_standard_layout
//    VK_KHR_variable_pointers
//    VK_KHR_vulkan_memory_model
//    VK_KHR_workgroup_memory_explicit_layout
//    VK_KHR_zero_initialize_workgroup_memory
//    VK_EXT_4444_formats
//    VK_EXT_blend_operation_advanced
//    VK_EXT_buffer_device_address
//    VK_EXT_calibrated_timestamps
//    VK_EXT_color_write_enable
//    VK_EXT_conditional_rendering
//    VK_EXT_conservative_rasterization
//    VK_EXT_custom_border_color
//    VK_EXT_depth_clip_enable
//    VK_EXT_depth_range_unrestricted
//    VK_EXT_descriptor_indexing
//    VK_EXT_discard_rectangles
//    VK_EXT_display_control
//    VK_EXT_extended_dynamic_state
//    VK_EXT_extended_dynamic_state2
//    VK_EXT_external_memory_host
//    VK_EXT_fragment_shader_interlock
//    VK_EXT_global_priority
//    VK_EXT_global_priority_query
//    VK_EXT_host_query_reset
//    VK_EXT_image_robustness
//    VK_EXT_index_type_uint8
//    VK_EXT_inline_uniform_block
//    VK_EXT_line_rasterization
//    VK_EXT_memory_budget
//    VK_EXT_pci_bus_info
//    VK_EXT_physical_device_drm
//    VK_EXT_pipeline_creation_cache_control
//    VK_EXT_pipeline_creation_feedback
//    VK_EXT_post_depth_coverage
//    VK_EXT_private_data
//    VK_EXT_provoking_vertex
//    VK_EXT_queue_family_foreign
//    VK_EXT_robustness2
//    VK_EXT_sample_locations
//    VK_EXT_sampler_filter_minmax
//    VK_EXT_scalar_block_layout
//    VK_EXT_separate_stencil_usage
//    VK_EXT_shader_atomic_float
//    VK_EXT_shader_demote_to_helper_invocation
//    VK_EXT_shader_image_atomic_int64
//    VK_EXT_shader_subgroup_ballot
//    VK_EXT_shader_subgroup_vote
//    VK_EXT_shader_viewport_index_layer
//    VK_EXT_subgroup_size_control
//    VK_EXT_texel_buffer_alignment
//    VK_EXT_tooling_info
//    VK_EXT_transform_feedback
//    VK_EXT_vertex_attribute_divisor
//    VK_EXT_vertex_input_dynamic_state
//    VK_EXT_ycbcr_image_arrays
//    VK_NV_clip_space_w_scaling
//    VK_NV_coverage_reduction_mode
//    VK_NV_dedicated_allocation
//    VK_NV_dedicated_allocation_image_aliasing
//    VK_NV_device_diagnostic_checkpoints
//    VK_NV_device_diagnostics_config
//    VK_NV_device_generated_commands
//    VK_NV_fill_rectangle
//    VK_NV_fragment_coverage_to_color
//    VK_NV_framebuffer_mixed_samples
//    VK_NV_geometry_shader_passthrough
//    VK_NV_inherited_viewport_scissor
//    VK_NV_sample_mask_override_coverage
//    VK_NV_shader_sm_builtins
//    VK_NV_shader_subgroup_partitioned
//    VK_NV_viewport_array2
//    VK_NV_viewport_swizzle
//    VK_NVX_multiview_per_view_attributes

#define VKLVK_PROP_MAXENABLEDDEVICEEXTENSIONCOUNT 1
#define VKLVK_PROP_ENABLEDDEVICEEXTENSIONCOUNT 1

static const char* VKLVK_PROP_DEVICEEXTENSIONNAMES[VKLVK_PROP_MAXENABLEDDEVICEEXTENSIONCOUNT] = {
    "VK_KHR_driver_properties"};

#endif // VKL_VK_REQUIREDS_H

