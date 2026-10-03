# For M33TD please follow the table below to initialize BOOTDEVICE_LABELS parameter.
# Possible values are (without white spaces):
#  sdcard
#  emmc
#  nor-nor-sdcard
#  nor-sdcard
#  nor-emmc
#  emmc
#  nor-nor-sdcard
#  nor-snand
# +---------+----------+---------+----------+-----------+-----------+-------------------+
# |           Boot ROM | TF-A    | MCUBOOT  | BOOT_M33  | BOOT_A35  | BOOTDEVICES_LABEL |
# +---------+----------+---------+----------+-----------+-----------+-------------------+
# | SDMMC1  | TRUE     | TRUE    | TRUE     | SDCARD    | SDCARD    | sdcard            |
# |-------------------------------------------------------------------------------------|
# | SDMMC2  | TRUE     | TRUE    | TRUE     | EMMC      | EMMC      | emmc              |
# |-------------------------------------------------------------------------------------|
# | OSPI1   | TRUE     | TRUE    | FALSE    | NOR       | NOR       | nor-nor-sdcard    |
# | OSPI2   | TRUE     | TRUE    | FALSE    | NOR       | NOR       | nor-nor-sdcard    |
# |-------------------------------------------------------------------------------------|
# | OSPI2   | TRUE     | FALSE   | TRUE     | NOR       | SDCARD    | nor-sdcard        |
# | SDMMC1  | TRUE     | TRUE    | TRUE     | SDCARD    | SDCARD    | sdcard            |
# |-------------------------------------------------------------------------------------|
# | OSPI2   | TRUE     | FALSE   | TRUE     | NOR       | EMMC      | nor-emmc          |
# | SDMMC2  | TRUE     | TRUE    | FALSE    | EMMC      | EMMC      | emmc              |
# |-------------------------------------------------------------------------------------|
# | OSPI1   | TRUE     | TRUE    | FALSE    | NOR       | NOR       | nor-nor-sdcard    |
# | OSPI2   | TRUE     | FALSE   | TRUE     | NOR       | SNAND     | nor-snand         |
# +---------+----------+---------+----------+-----------+-----------+-------------------+
# For A35TD please follow the table below to initialize BOOTDEVICE_LABELS parameter.
# Possible values are (without white spaces):
#  sdcard
#  emmc
#  nor-sdcard
#  nand-custom
# +---------+-------- -+--------+-----------------------+
# |           Boot ROM | TF-A   | BOOTDEVICES_LABEL     |
# +---------+--------- +--------+-----------------------+
# | SDMMC1  | TRUE     | TRUE   | sdcard                |
# |-----------------------------------------------------|
# | SDMMC2  | TRUE     | TRUE   | emmc                  |
# |-----------------------------------------------------|
# | OSPI1   | TRUE     | TRUE   | nor-sdcard            |
# |-----------------------------------------------------|
# | OSPI1   | TRUE     | TRUE   | nand-custom           |
# +---------+------- --+--------+-----------------------+
#
BOOTDEVICE_LABELS:append = " emmc "
#
#In case of "nand-custom" two extra flag to add:
#CUSTOM_NAND_CONFIG = "<PageSize>-<BlockSize>-<StorageSize>"
#i.e. CUSTOM_NAND_CONFIG = "2-256-512"
#EXTRA_UBIFS_SIZE_nand_custom to fill according to https://wiki.st.com/stm32mpu/wiki/How_to_add_a_new_parallel_or_serial_NAND_flash_memory_device_in_Yocto
#
#
#MACHINE_FEATURES Description:
#  'm33td': To boot via M33 processor
#  'm33copro': when you would like to use some application on M33 coprocessor in parallel of A35 execution (Linux userland)
# will be generated automatically by CubeMX
#
MACHINE_FEATURES:append = " m33copro"

