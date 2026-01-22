#include "ejd.h"
#include "esphome/core/log.h"

namespace esphome {
namespace ejd {

static const char *TAG = "ejd";

// bool first_run = false;
std::string startup_text = "";

void ejdComponent::dump_config() {
    ESP_LOGCONFIG(TAG, "ejd:");
    LOG_SENSOR("  ", "EG", eg_sensor_);
    LOG_SENSOR("  ", "EV", ev_sensor_);
    LOG_SENSOR("  ", "VG", vg_sensor_);
    LOG_SENSOR("  ", "PA1", pa1_sensor_);
    LOG_SENSOR("  ", "PA2", pa2_sensor_);
    LOG_SENSOR("  ", "PA3", pa3_sensor_);
    ESP_LOGI(TAG, "%s", this->startup_text_.c_str());
}

void ejdComponent::loop() {

    while (this->available()) {
        uint8_t c;
        this->read_byte(&c);
        this->handle_char_(c);
    }
}

void ejdComponent::handle_char_(uint8_t c) {
  if (c == '\r')
    return;
  if (c == '\n') {
    std::string s(this->rx_message_.begin(), this->rx_message_.end());
    char x = s[0];
    if (x == '{') { // JSON data string
        ESP_LOGD(TAG, "JSON string received: %s", s.c_str());
        this->json_string_ = s;
        parse_json_data_();
    } else { // Startup information
        startup_text = startup_text + s + "\n";
        this->startup_text_ = startup_text;
    }

    this->rx_message_.clear();
    return;
  }
  this->rx_message_.push_back(c);
}

void ejdComponent::parse_json_data_(){
// TODO - add code in to check for exisence of the Data. Possible to specify the sensor
// without the JSON being available
    json::parse_json(this->json_string_, [this](JsonObject json_data) {
        if (eg_sensor_ != nullptr) {
            eg_sensor_->publish_state(json_data["ext_gnd"]);
        }
        if (ev_sensor_ != nullptr) {
            ev_sensor_->publish_state(json_data["ext_vdd"]);
        }
        if (vg_sensor_ != nullptr) {
            vg_sensor_->publish_state(json_data["vdd_gnd"]);
        }
        if (pa1_sensor_ != nullptr) {
            pa1_sensor_->publish_state(json_data["pa1"]);
        }
        if (pa2_sensor_ != nullptr) {
            pa2_sensor_->publish_state(json_data["pa2"]);
        }
        if (pa3_sensor_ != nullptr) {
            pa3_sensor_->publish_state(json_data["pa3"]);
        }

        this->done_trigger_->trigger();
    });
}

}  // namespace ejd
}  // namespace esphome