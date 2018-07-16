#include "unity.h"
#include "ds1620.h"
#include "mock_example-ds1620.h"
#include "mock_ds1620_send_command.h"
#include "mock_ds1620_receive_data.h"
#include "mock_ds1620_send_data.h"
#include "mock_ds1620_reset.h"
#include "mock_ds1620_read.h"
#include <string.h>

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

void test_ds1620_init_null_pointer_should_not_segfault(void)
{
  ds1620_setup_ports_set_callback(0);
  ds1620_init();
}

void test_ds1620_init_should_call_setup_ports(void)
{
  example_setup_ports_Expect();
  ds1620_init();
}

void test_ds1620_read_th_should_work(void)
{
  int value = 0xAB;
  ds1620_read_ExpectAndReturn(READ_TH,0,value);
  ds1620_read_IgnoreArg_callbacks();
  TEST_ASSERT_EQUAL(value/2,ds1620_read_th());
}

void test_ds1620_read_tl_should_work(void)
{
  int value = 0xAB;
  ds1620_read_ExpectAndReturn(READ_TL,0,value);
  ds1620_read_IgnoreArg_callbacks();
  TEST_ASSERT_EQUAL(value/2,ds1620_read_tl());
}

void test_ds1620_read_counter_should_work(void)
{
  int value = 0xAB;
  ds1620_read_ExpectAndReturn(READ_CNTR,0,value);
  ds1620_read_IgnoreArg_callbacks();
  TEST_ASSERT_EQUAL(value,ds1620_read_counter());
}

void test_ds1620_read_slope_should_work(void)
{
  int value = 0xAB;
  ds1620_read_ExpectAndReturn(READ_SLOPE,0,value);
  ds1620_read_IgnoreArg_callbacks();
  TEST_ASSERT_EQUAL(value,ds1620_read_slope());
}

void test_ds1620_read_config_should_work(void)
{
  int value = 0xAB;
  ds1620_read_ExpectAndReturn(READ_CFG,0,value);
  ds1620_read_IgnoreArg_callbacks();
  TEST_ASSERT_EQUAL(value,ds1620_read_config());
}

void test_ds1620_read_temp_should_work_positive(void)
{
  int value = 0xAB;
  int result = 0xAB/2;
  ds1620_read_ExpectAndReturn(READ_TEMP,0,value);
  ds1620_read_IgnoreArg_callbacks();
  TEST_ASSERT_EQUAL(result,ds1620_read_temp());
}

void test_ds1620_read_temp_should_work_negative(void)
{
  int value = 0x1AB;
  int result = -(0xFF-0xAB)/2;
  ds1620_read_ExpectAndReturn(READ_TEMP,0,value);
  ds1620_read_IgnoreArg_callbacks();
  TEST_ASSERT_EQUAL(result,ds1620_read_temp());
}

void test_ds1620_start_conv_should_work(void)
{
  ds1620_rst_start_Expect(0);
  ds1620_rst_start_IgnoreArg_callbacks();
  ds1620_send_command_Expect(START_CNV,0);
  ds1620_send_command_IgnoreArg_callbacks();
  ds1620_rst_stop_Expect(0);
  ds1620_rst_stop_IgnoreArg_callbacks();

  ds1620_start_conv();
}

void test_ds1620_stop_conv_should_work(void)
{
  ds1620_rst_start_Expect(0);
  ds1620_rst_start_IgnoreArg_callbacks();
  ds1620_send_command_Expect(STOP_CNV,0);
  ds1620_send_command_IgnoreArg_callbacks();
  ds1620_rst_stop_Expect(0);
  ds1620_rst_stop_IgnoreArg_callbacks();

  ds1620_stop_conv();
}

void test_ds1620_write_config_null_pointer_should_not_segfault(void)
{
  int value = 0xAB;
  ds1620_delay_set_callback(0);
  TEST_ASSERT_EQUAL(2,ds1620_write_config(value));
}

void test_ds1620_write_config_should_work(void)
{
  int value = 0xAB;
  int returned = value;

  ds1620_rst_start_Expect(0);
  ds1620_rst_start_IgnoreArg_callbacks();
  ds1620_send_command_Expect(WRITE_CFG,0);
  ds1620_send_command_IgnoreArg_callbacks();
  ds1620_send_command_Expect(value,0);
  ds1620_send_command_IgnoreArg_callbacks();
  example_delay_Expect(WRITE_DELAY);
  ds1620_rst_stop_Expect(0);
  ds1620_rst_stop_IgnoreArg_callbacks();
  ds1620_read_ExpectAndReturn(READ_CFG,0,returned);
  ds1620_read_IgnoreArg_callbacks();

  TEST_ASSERT_EQUAL(0,ds1620_write_config(value));
}

void test_ds1620_write_config_unsuccessfull(void)
{
  int value = 0xAB;
  int returned = 0xBA;

  ds1620_rst_start_Expect(0);
  ds1620_rst_start_IgnoreArg_callbacks();
  ds1620_send_command_Expect(WRITE_CFG,0);
  ds1620_send_command_IgnoreArg_callbacks();
  ds1620_send_command_Expect(value,0);
  ds1620_send_command_IgnoreArg_callbacks();
  example_delay_Expect(WRITE_DELAY);
  ds1620_rst_stop_Expect(0);
  ds1620_rst_stop_IgnoreArg_callbacks();
  ds1620_read_ExpectAndReturn(READ_CFG,0,returned);
  ds1620_read_IgnoreArg_callbacks();

  TEST_ASSERT_EQUAL(1,ds1620_write_config(value));
}

void test_ds1620_write_th_null_pointer_should_not_segfault(void)
{
  int value = 0xAB;
  ds1620_delay_set_callback(0);
  ds1620_write_th(value);
}

void test_ds1620_write_tl_null_pointer_should_not_segfault(void)
{
  int value = 0xAB;
  ds1620_delay_set_callback(0);
  ds1620_write_tl(value);
}

void test_ds1620_write_th_should_work(void)
{
  int value = 0xAB;
  ds1620_rst_start_Expect(0);
  ds1620_rst_start_IgnoreArg_callbacks();
  ds1620_send_command_Expect(WRITE_TH,0);
  ds1620_send_command_IgnoreArg_callbacks();
  ds1620_send_data_Expect(value*2,0);
  ds1620_send_data_IgnoreArg_callbacks();
  example_delay_Expect(WRITE_DELAY);
  ds1620_rst_stop_Expect(0);
  ds1620_rst_stop_IgnoreArg_callbacks();

  ds1620_write_th(value);
}

void test_ds1620_write_tlh_should_work(void)
{
  int value = 0xAB;
  ds1620_rst_start_Expect(0);
  ds1620_rst_start_IgnoreArg_callbacks();
  ds1620_send_command_Expect(WRITE_TL,0);
  ds1620_send_command_IgnoreArg_callbacks();
  ds1620_send_data_Expect(value*2,0);
  ds1620_send_data_IgnoreArg_callbacks();
  example_delay_Expect(WRITE_DELAY);
  ds1620_rst_stop_Expect(0);
  ds1620_rst_stop_IgnoreArg_callbacks();

  ds1620_write_tl(value);
}

