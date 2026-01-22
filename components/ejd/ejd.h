#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/json/json_util.h"
#include "esphome/core/automation.h"

namespace esphome {
namespace ejd {

class ejdComponent : public Component, public uart::UARTDevice {
  public:
    void set_eg_sensor(sensor::Sensor *eg_sensor) { eg_sensor_ = eg_sensor; }
    void set_ev_sensor(sensor::Sensor *ev_sensor) { ev_sensor_ = ev_sensor; }
    void set_vg_sensor(sensor::Sensor *vg_sensor) { vg_sensor_ = vg_sensor; }
    void set_pa1_sensor(sensor::Sensor *pa1_sensor) { pa1_sensor_ = pa1_sensor; }
    void set_pa2_sensor(sensor::Sensor *pa2_sensor) { pa2_sensor_ = pa2_sensor; }
    void set_pa3_sensor(sensor::Sensor *pa3_sensor) { pa3_sensor_ = pa3_sensor; }

    Trigger<> *get_done_trigger() const { return done_trigger_; }

    void dump_config() override;
    void loop() override;

    float get_setup_priority() const { return setup_priority::DATA; }

  protected:
    void parse_json_data_();
    void handle_char_(uint8_t c);

    Trigger<> *done_trigger_ = new Trigger<>();

    std::vector<uint8_t> rx_message_;
    std::string json_string_;
    std::string startup_text_ = "NEreboot";

    sensor::Sensor *eg_sensor_{nullptr};
    sensor::Sensor *ev_sensor_{nullptr};
    sensor::Sensor *vg_sensor_{nullptr};
    sensor::Sensor *pa1_sensor_{nullptr};
    sensor::Sensor *pa2_sensor_{nullptr};
    sensor::Sensor *pa3_sensor_{nullptr};
};

}  // namespace ejd
}  // namespace esphome