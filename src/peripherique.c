/** @file peripherique.c
 *  @brief service de gestion des peripheriques
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

LOG_MODULE_REGISTER(Peripherique);

static uint8_t buttonValue = 0;
static uint8_t SoundValue = 0;

static void blvl_ccc_cfg_button_changed(const struct bt_gatt_attr *attr,
				       uint16_t value)
{
	ARG_UNUSED(attr);

	bool notif_enabled = (value == BT_GATT_CCC_NOTIFY);

	LOG_INF("BAS Notifications %s", notif_enabled ? "enabled" : "disabled");
}

static ssize_t on_buz_receive(struct bt_conn *conn,
			  const struct bt_gatt_attr *attr,
			  const void *buf,
			  uint16_t len,
			  uint16_t offset,
			  uint8_t flags)
{
    const uint8_t * buffer = buf;

    
	printk("Received data, handle %d, conn %p, data: 0x", attr->handle, conn);
    for(uint8_t i = 0; i < len; i++){
        printk("%02X", buffer[i]);
		SoundValue = buffer[i];//printk("%d", buffer[i]);
    }
    printk("\n");

	return len;
}


static ssize_t read_buttonlvl(struct bt_conn *conn,
			       const struct bt_gatt_attr *attr, void *buf,
			       uint16_t len, uint16_t offset)
{
	uint8_t lvl8 = buttonValue;

	return bt_gatt_attr_read(conn, attr, buf, len, offset, &lvl8,
				 sizeof(lvl8));
}

static ssize_t read_buzlvl(struct bt_conn *conn,
			       const struct bt_gatt_attr *attr, void *buf,
			       uint16_t len, uint16_t offset)
{
	uint8_t lvl8 = SoundValue;

	return bt_gatt_attr_read(conn, attr, buf, len, offset, &lvl8,
				 sizeof(lvl8));
}

BT_GATT_SERVICE_DEFINE(Peripherique,
	BT_GATT_PRIMARY_SERVICE(BT_UUID_DECLARE_16(0x1401)),
    BT_GATT_CHARACTERISTIC(BT_UUID_DECLARE_16(0x1404),
			       BT_GATT_CHRC_NOTIFY,
			       BT_GATT_PERM_READ, read_buttonlvl, NULL,
			       &buttonValue),
    BT_GATT_CCC(blvl_ccc_cfg_button_changed,
		    BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),
	BT_GATT_CHARACTERISTIC(BT_UUID_DECLARE_16(0x1405),
			       BT_GATT_CHRC_WRITE | BT_GATT_CHRC_WRITE_WITHOUT_RESP,
			       BT_GATT_PERM_READ | BT_GATT_PERM_WRITE,
                   read_buzlvl, on_buz_receive,
			       &SoundValue),
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

	rc = bt_gatt_notify(NULL, &Peripherique.attrs[1], &level, sizeof(level));

	return rc == -ENOTCONN ? 0 : rc;
}


static int buz_init(void)
{

	return 0;
}

char bt_buz_get_sound_value(void)
{
	return SoundValue;
}

int bt_buz_set_sound_value(uint8_t level)
{
	int rc;


	SoundValue = level;

	rc = bt_gatt_notify(NULL, &Peripherique.attrs[1], &level, sizeof(level));

	return rc == -ENOTCONN ? 0 : rc;
}


SYS_INIT(but_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);

SYS_INIT(buz_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);