#include "unity.h"
#include "ds1620.h"
#include "mock_example.h"
#include "mock_ds1620_send_command.h"
#include "mock_ds1620_receive_data.h"
#include "mock_ds1620_reset.h"

void setUp(void)
{
  ds1620_clock_low_set_callback(&example_clock_low);
  ds1620_clock_high_set_callback(&example_clock_high);
  ds1620_reset_low_set_callback(&example_reset_low);
  ds1620_reset_high_set_callback(&example_reset_high);
  ds1620_dq_set_set_callback(&example_dq_set);
  ds1620_dq_get_set_callback(&example_dq_get);
  ds1620_dq_set_output_set_callback(&example_dq_set_output);
  ds1620_dq_set_input_set_callback(&example_dq_set_input);
  ds1620_setup_ports_set_callback(&example_setup_ports);
  ds1620_delay_set_callback(&example_delay);
}

void tearDown(void)
{
}

void test_ds1620_init_should_call_setup_ports(void)
{
  example_setup_ports_Expect();
  ds1620_init();
}
