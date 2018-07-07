#include "unity.h"
#include "ds1620_receive_data.h"
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

void test_ds1620_receive_data_null_pointer_should_not_segfault(void)
{
  TEST_ASSERT_EQUAL(0,ds1620_receive_data(0));
}

void test_ds1620_receive_data_should_work_all_zeroes(void)
{
  example_dq_set_input_Expect();
  for(uint8_t i=0;i<9;++i)
  {
    example_clock_low_Expect();
    example_dq_get_ExpectAndReturn(0);
    example_clock_high_Expect();
  }
  example_dq_set_output_Expect();
  TEST_ASSERT_EQUAL(0,ds1620_receive_data(&callbacks));
}

void test_ds1620_receive_data_should_work_all_ones(void)
{
  example_dq_set_input_Expect();
  for(uint8_t i=0;i<9;++i)
  {
    example_clock_low_Expect();
    example_dq_get_ExpectAndReturn(1);
    example_clock_high_Expect();
  }
  example_dq_set_output_Expect();
  TEST_ASSERT_EQUAL(0x1FF,ds1620_receive_data(&callbacks));
}

void test_ds1620_receive_data_should_work(void)
{
  example_dq_set_input_Expect();
  for(uint8_t i=0;i<9;++i)
  {
    example_clock_low_Expect();
    if(i%2)
      example_dq_get_ExpectAndReturn(1);
    else
      example_dq_get_ExpectAndReturn(0);
    example_clock_high_Expect();
  }
  example_dq_set_output_Expect();
  TEST_ASSERT_EQUAL(0xAA,ds1620_receive_data(&callbacks));
}

