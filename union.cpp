#include <array>
#include <iostream>
#include <utility>

using MCP3421_config = union Config {
  uint8_t byte;
  //   struct cfg {
  uint8_t gain_selection : 2;
  uint8_t sample_rate_selection : 2;
  uint8_t continuous_conversion : 1;
  uint8_t unused : 2;
  uint8_t ready : 1;
  //   };
};

const std::size_t data_rate_18bits_size{4};
using MCP3421_write_18bits = union Adc18 {
  uint8_t bytes[data_rate_18bits_size];
  //   struct payload {
  uint8_t byte2;
  uint8_t byte1;
  uint8_t byte0;
  MCP3421_config config;
  //   };
};

int main() {
  MCP3421_write_18bits adc{};
  adc.byte2 = 0xff;
  adc.config.ready = 1;

  adc.config.gain_selection = 0b10;

  printf("a.config.ready %x\n", adc.config.ready);
  printf("a.config.gain_selection %x\n", adc.config.gain_selection);
}