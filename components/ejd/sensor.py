import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, uart #, json
from esphome import automation
from esphome.const import (
    CONF_ID,
    #UNIT_VOLT,
    #UNIT_BAR,
    UNIT_EMPTY,
    # ICON_CURRENT_AC,
    # ICON_FLASH,
    # ICON_THERMOMETER,
    # ICON_PERCENT,
    # ICON_EMPTY,
    # ICON_PULSE,
    #DEVICE_CLASS_VOLTAGE,
    #DEVICE_CLASS_PRESSURE,
    DEVICE_CLASS_EMPTY,
    STATE_CLASS_MEASUREMENT,
    # CONF_TRIGGER_ID,
)

DEPENDENCIES = ["uart"]
AUTO_LOAD = ["json"]

ejd_ns = cg.esphome_ns.namespace("ejd")
ejdComponent = ejd_ns.class_("ejdComponent", uart.UARTDevice, cg.Component)

CONF_EG = "eg"
CONF_EV = "ev"
CONF_VG = "vg"
CONF_PA1 = "pa1"
CONF_PA2 = "pa2"
CONF_PA3 = "pa3"
CONF_ON_DATA = "on_data"

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(ejdComponent),
            cv.Optional(CONF_ON_DATA): automation.validate_automation(single=True),

            cv.Optional(CONF_EG): sensor.sensor_schema(
                unit_of_measurement=UNIT_EMPTY,
                accuracy_decimals=0,
            ),
            cv.Optional(CONF_EV): sensor.sensor_schema(
                unit_of_measurement=UNIT_EMPTY,
                accuracy_decimals=0,
            ),
            cv.Optional(CONF_VG): sensor.sensor_schema(
                unit_of_measurement=UNIT_EMPTY,
                accuracy_decimals=0,
            ),
            cv.Optional(CONF_PA1): sensor.sensor_schema(
                unit_of_measurement=UNIT_EMPTY,
                accuracy_decimals=0,
            ),
            cv.Optional(CONF_PA2): sensor.sensor_schema(
                unit_of_measurement=UNIT_EMPTY,
                accuracy_decimals=0,
            ),
            cv.Optional(CONF_PA3): sensor.sensor_schema(
                unit_of_measurement=UNIT_EMPTY,
                accuracy_decimals=0,
            ),
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
    .extend(uart.UART_DEVICE_SCHEMA)
)

# FINAL_VALIDATE_SCHEMA = uart.final_validate_device_schema(
#     "cse7766", baud_rate=4800, require_rx=True
# )

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

    if CONF_EG in config:
        sens = await sensor.new_sensor(config[CONF_EG])
        cg.add(var.set_eg_sensor(sens))

    if CONF_EV in config:
        sens = await sensor.new_sensor(config[CONF_EV])
        cg.add(var.set_ev_sensor(sens))

    if CONF_VG in config:
        sens = await sensor.new_sensor(config[CONF_VG])
        cg.add(var.set_vg_sensor(sens))

    if CONF_PA1 in config:
        sens = await sensor.new_sensor(config[CONF_PA1])
        cg.add(var.set_pa1_sensor(sens))

    if CONF_PA2 in config:
        sens = await sensor.new_sensor(config[CONF_PA2])
        cg.add(var.set_pa2_sensor(sens))

    if CONF_PA3 in config:
        sens = await sensor.new_sensor(config[CONF_PA3])
        cg.add(var.set_pa3_sensor(sens))

    # Trigger definition, must be at the end of 'to_code'
    if CONF_ON_DATA in config:
        await automation.build_automation(
            var.get_done_trigger(), [], config[CONF_ON_DATA]
        )

