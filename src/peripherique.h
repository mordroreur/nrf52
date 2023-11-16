/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef MATH_INCLUDE_BLUETOOTH_SERVICES_PERIPH_H_
#define MATH_INCLUDE_BLUETOOTH_SERVICES_PERIPH_H_

/**
 * @brief Button Service 
 * @defgroup bt 
 * @ingroup bluetooth
 * @{
 *
 * [Experimental] Users should note that the APIs can change
 * as a part of ongoing development.
 */

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Read the button value.
 *
 * Read the characteristic value of the button
 *
 *  @return The button is a boolean.
 */
char bt_buz_get_sound_value(void);


/** @brief Update button value.
 *
 * Update the characteristic value of the button
 * This will send a GATT notification to all current subscribers.
 *
 *  @param value The button value.
 *
 *  @return Zero in case of success and error code in case of error.
 */
int bt_buz_set_sound_value(uint8_t level);



/** @brief Read the button value.
 *
 * Read the characteristic value of the button
 *
 *  @return The button is a boolean.
 */
char bt_but_get_button_value(void);


/** @brief Update button value.
 *
 * Update the characteristic value of the button
 * This will send a GATT notification to all current subscribers.
 *
 *  @param value The button value.
 *
 *  @return Zero in case of success and error code in case of error.
 */
int bt_but_set_button_value(uint8_t level);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* MATH_INCLUDE_BLUETOOTH_SERVICES_BUZ_H_ */
