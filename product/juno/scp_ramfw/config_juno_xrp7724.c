/*
 * Arm SCP/MCP Software
 * Copyright (c) 2019, Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <fwk_element.h>
#include <fwk_id.h>
#include <fwk_module.h>
#include <fwk_module_idx.h>
#include <mod_i2c.h>
#include <mod_juno_xrp7724.h>
#include <mod_sensor.h>
#include <mod_timer.h>
#include <config_sensor.h>
#include <config_juno_xrp7724.h>

enum mod_juno_xrp7724_gpio_idx  {
    MOD_JUNO_XRP7724_GPIO_IDX_ASSERT,
    MOD_JUNO_XRP7724_GPIO_IDX_MODE,
    MOD_JUNO_XRP7724_GPIO_IDX_COUNT,
};

/*
 * Temperature sensor information
 */
static struct mod_sensor_info juno_xrp7724_info_temperature = {
    .type = MOD_SENSOR_TYPE_DEGREES_C,
    .update_interval = 0,
    .update_interval_multiplier = 0,
    .unit_multiplier = -3,
};

static const struct fwk_element juno_xrp7724_element_table[] = {
    [MOD_JUNO_XRP7724_ELEMENT_IDX_SENSOR] = {
        .name = "TEMPERATURE SENSOR",
        .data = &(const struct mod_juno_xrp7724_dev_config) {
            .driver_response_id = FWK_ID_ELEMENT_INIT(FWK_MODULE_IDX_SENSOR,
                MOD_JUNO_SENSOR_XRP7724_PMIC_TEMP_IDX),
            .driver_response_api_id = FWK_ID_API_INIT(FWK_MODULE_IDX_SENSOR,
                MOD_SENSOR_API_IDX_DRIVER_RESPONSE),
            .sensor_info = &juno_xrp7724_info_temperature,
            .type = MOD_JUNO_XRP7724_ELEMENT_TYPE_SENSOR,
        },
    },
    [MOD_JUNO_XRP7724_ELEMENT_IDX_GPIO] = {
        .name = "GPIOs",
        .sub_element_count = MOD_JUNO_XRP7724_GPIO_IDX_COUNT,
        .data = &(const struct mod_juno_xrp7724_dev_config) {
            .type = MOD_JUNO_XRP7724_ELEMENT_TYPE_GPIO,
        },
     },

    [MOD_JUNO_XRP7724_ELEMENT_IDX_COUNT] = { 0 },
};

static const struct fwk_element *juno_xrp7724_get_element_table(
    fwk_id_t module_id)
{
    return juno_xrp7724_element_table;
}

const struct fwk_module_config config_juno_xrp7724 = {
    .get_element_table = juno_xrp7724_get_element_table,
    .data = &((struct mod_juno_xrp7724_config) {
        .slave_address = 0x28,
        .i2c_hal_id = FWK_ID_ELEMENT_INIT(FWK_MODULE_IDX_I2C, 0),
        .timer_hal_id = FWK_ID_ELEMENT_INIT(FWK_MODULE_IDX_TIMER, 0),
        .gpio_assert_id = FWK_ID_SUB_ELEMENT_INIT(FWK_MODULE_IDX_JUNO_XRP7724,
            MOD_JUNO_XRP7724_ELEMENT_IDX_GPIO,
            MOD_JUNO_XRP7724_GPIO_IDX_ASSERT),
        .gpio_mode_id = FWK_ID_SUB_ELEMENT_INIT(FWK_MODULE_IDX_JUNO_XRP7724,
            MOD_JUNO_XRP7724_ELEMENT_IDX_GPIO,
            MOD_JUNO_XRP7724_GPIO_IDX_MODE),
    }),
};