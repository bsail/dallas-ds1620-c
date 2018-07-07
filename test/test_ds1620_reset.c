#include "unity.h"
#include "ds1620_reset.h"
#include "mock_example.h"
#include <string.h>

struct ds1620_callbacks callbacks;

void setUp(void)
{
  callbacks.clock_low_callback = example_clock_low;
  callbacks.clock_high_callback = example_clock_high;
  callbacks.reset_low_callback = example_reset_low;
  callbacks.reset_high_callback = example_reset_high;
  callbacks.dq_set_callback = example_dq_set;
  callbacks.dq_get_callback = example_dq_get;
  callbacks.dq_set_output_callback = example_dq_set_output;
  callbacks.dq_set_input_callback = example_dq_set_input;
  callbacks.setup_ports_callback = example_setup_ports;
  callbacks.delay_callback = example_delay;
}

void tearDown(void)
{
  memset(&callbacks,0,sizeof(callbacks));
}

void test_ds1620_rst_start_null_pointer_should_not_segfault(void)
{
  ds1620_rst_start(0);
}

void test_ds1620_rst_stop_null_pointer_should_not_segfault(void)
{
  ds1620_rst_stop(0);
}

void test_ds1620_rst_start_should_work(void)
{
  example_reset_low_Expect();
  example_clock_high_Expect();
  example_reset_high_Expect();
  ds1620_rst_start(&callbacks);
}

void test_ds1620_rst_stop_should_work(void)
{
  example_reset_low_Expect();
  ds1620_rst_stop(&callbacks);
}
