#include "unity.h"
#include "ds1620_read.h"
#include "mock_example-ds1620.h"
#include "mock_ds1620_send_command.h"
#include "mock_ds1620_receive_data.h"
#include "mock_ds1620_reset.h"
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

void test_ds1620_read_null_pointer_should_not_segfault(void)
{
  TEST_ASSERT_EQUAL(0,ds1620_read(0,0));
}

void test_ds1620_read_should_work(void)
{
  int command = 0xAA;
  int value = 0xBD;
  ds1620_rst_start_Expect(&callbacks);
  ds1620_send_command_Expect(command,&callbacks);
  ds1620_receive_data_ExpectAndReturn(&callbacks,value);
  ds1620_rst_stop_Expect(&callbacks);

  TEST_ASSERT_EQUAL(value,ds1620_read(command,&callbacks));
}
