/** @file boutton.c
 *  @brief Button service
 */



#include <errno.h>
#include <zephyr/init.h>
#include <zephyr/sys/__assert.h>
#include <stdbool.h>
#include <zephyr/types.h>

#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/services/bas.h>
#define LOG_LEVEL CONFIG_BT_BAS_LOG_LEVEL
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(Button);

static uint8_t buttonValue = 0;

static void blvl_ccc_cfg_changed(const struct bt_gatt_attr *attr,
				       uint16_t value)
{
	ARG_UNUSED(attr);

	bool notif_enabled = (value == BT_GATT_CCC_NOTIFY);

	LOG_INF("BAS Notifications %s", notif_enabled ? "enabled" : "disabled");
}


static ssize_t read_blvl(struct bt_conn *conn,
			       const struct bt_gatt_attr *attr, void *buf,
			       uint16_t len, uint16_t offset)
{
	uint8_t lvl8 = buttonValue;

	return bt_gatt_attr_read(conn, attr, buf, len, offset, &lvl8,
				 sizeof(lvl8));
}

BT_GATT_SERVICE_DEFINE(Button,
	BT_GATT_PRIMARY_SERVICE(BT_UUID_DECLARE_16(0x1401)),
	BT_GATT_CHARACTERISTIC(BT_UUID_DECLARE_16(0x1404),
			       BT_GATT_CHRC_NOTIFY,
			       BT_GATT_PERM_READ, read_blvl, NULL,
			       &buttonValue),
	BT_GATT_CCC(blvl_ccc_cfg_changed,
		    BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),
);

static int but_init(void)
{

	return 0;
}

char bt_but_get_button_value(void)
{
	return buttonValue;
}

int bt_but_set_button_value(uint8_t level)
{
	int rc;

	printk("%d\n", level);
	buttonValue = level;

	rc = bt_gatt_notify(NULL, &Button.attrs[1], &level, sizeof(level));

	return rc == -ENOTCONN ? 0 : rc;
}


SYS_INIT(but_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);