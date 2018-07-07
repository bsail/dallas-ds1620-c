#include "unity.h"
#include "ds1620_send_data.h"
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

void test_ds1620_send_data_NeedToImplement(void)
{
    TEST_IGNORE_MESSAGE("Need to Implement ds1620_send_data");
}
