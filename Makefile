# SPDX-License-Identifier: GPL-2.0-only
#
obj-y 				+= rpi_debugfs.o
obj-$(CONFIG_BCM2835_POWER)	+= bcm2835-power.o
obj-$(CONFIG_RASPBERRYPI_POWER)	+= raspberrypi-power.o
obj-y				+= bcm63xx/
obj-$(CONFIG_SOC_BRCMSTB)	+= brcmstb/
