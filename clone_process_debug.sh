#!/bin/bash

echo 0 > /sys/kernel/debug/tracing/tracing_on
sleep 1
echo "tracing_off"

echo 0 > /sys/kernel/debug/tracing/events/enable
sleep 1
echo "events disabled"

echo function > /sys/kernel/debug/tracing/current_tracer
sleep 1
echo "function tracer enabled"

echo cpu_startup_entry > /sys/kernel/debug/tracing/set_ftrace_filter
sleep 1
echo "cpu_startup_entry enabled"

#echo rpi_get_interrupt_info > /sys/kernel/debug/tracing/set_ftrace_filter
#echo "rpi_get_interrupt_info enabled"


echo __arm64_sys_clone do_exit > /sys/kernel/debug/tracing/set_ftrace_filter
echo kernel_clone copy_process* >> /sys/kernel/debug/tracing/set_ftrace_filter
sleep 1
echo "set ftrace filter  enabled"


echo 1 > /sys/kernel/debug/tracing/events/sched/sched_switch/enable
echo 1 > /sys/kernel/debug/tracing/events/sched/sched_wakeup/enable
echo 1 > /sys/kernel/debug/tracing/events/sched/sched_process_fork/enable
echo 1 > /sys/kernel/debug/tracing/events/sched/sched_process_exit/enable
echo 1 > /sys/kernel/debug/tracing/events/signal/enable
echo 1 > /sys/kernel/debug/tracing/events/task/task_rename/enable


echo 1 > /sys/kernel/debug/tracing/options/func_stack_trace
echo "function stack trace enabled"

echo 1 > /sys/kernel/debug/tracing/options/sym-offset
echo "sys-offset enabled"

echo 1 > /sys/kernel/debug/tracing/tracing_on
echo "tracing_on"
