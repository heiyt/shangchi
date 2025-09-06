#include "shangchi_debug.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "sdkconfig.h"

#include "esp_console.h"
#include "argtable3/argtable3.h"

#include "esp_vfs_dev.h"
#include "linenoise/linenoise.h"

#include "flash_info.h"
#include "oled.h"
#include "aht10.h"
#include "axp2101.h"

// AXP2101命令
static int axp_status(int argc, char **argv) {
    printf("AXP2101 Status:\n");
    printf("  Battery: %d%%\n", shangchi_axp2101::PMU.getBatteryPercent());
    printf("  Charging: %s\n", shangchi_axp2101::PMU.isCharging() ? "Yes" : "No");
    printf("  Battery Voltage: %dmV\n", shangchi_axp2101::PMU.getBattVoltage());

    bool dc1_enable  = shangchi_axp2101::PMU.isEnableDC1();
    printf("  DCDC1 Enabled: %s", dc1_enable ? "Yes" : "No");
    if(dc1_enable) {
        printf(" (%dmV)", shangchi_axp2101::PMU.getDC1Voltage());
    }
    printf("\n");
    bool dc2_enable  = shangchi_axp2101::PMU.isEnableDC2();
    printf("  DCDC2 Enabled: %s", dc2_enable ? "Yes" : "No");
    if(dc2_enable) {
        printf(" (%dmV)", shangchi_axp2101::PMU.getDC2Voltage());
    }
    printf("\n");
    bool dc3_enable = shangchi_axp2101::PMU.isEnableDC3();
    printf("  DCDC3 Enabled: %s", dc3_enable ? "Yes" : "No");
    if(dc3_enable) {
        printf(" (%dmV)", shangchi_axp2101::PMU.getDC3Voltage());
    }
    printf("\n");
    bool dc4_enable = shangchi_axp2101::PMU.isEnableDC4();
    printf("  DCDC4 Enabled: %s", dc4_enable ? "Yes" : "No");
    if(dc4_enable) {
        printf(" (%dmV)", shangchi_axp2101::PMU.getDC4Voltage());
    }
    printf("\n");
    bool dc5_enable = shangchi_axp2101::PMU.isEnableDC5();
    printf("  DCDC5 Enabled: %s", dc5_enable ? "Yes" : "No");
    if(dc5_enable) {
        printf(" (%dmV)", shangchi_axp2101::PMU.getDC5Voltage());
    }
    printf("\n");

    bool aldo1_enable = shangchi_axp2101::PMU.isEnableALDO1();
    printf("  ALDO1 Enabled: %s", aldo1_enable ? "Yes" : "No");
    if(aldo1_enable) {
        printf(" (%dmV)", shangchi_axp2101::PMU.getALDO1Voltage());
    }
    printf("\n");
    bool aldo2_enable = shangchi_axp2101::PMU.isEnableALDO2();
    printf("  ALDO2 Enabled: %s", aldo2_enable ? "Yes" : "No");
    if(aldo2_enable) {
        printf(" (%dmV)", shangchi_axp2101::PMU.getALDO2Voltage());
    }
    printf("\n");
    bool aldo3_enable = shangchi_axp2101::PMU.isEnableALDO3();
    printf("  ALDO3 Enabled: %s", aldo3_enable ? "Yes" : "No");
    if(aldo3_enable) {
        printf(" (%dmV)", shangchi_axp2101::PMU.getALDO3Voltage());
    }
    printf("\n");
    bool aldo4_enable = shangchi_axp2101::PMU.isEnableALDO4();
    printf("  ALDO4 Enabled: %s", aldo4_enable ? "Yes" : "No");
    if(aldo4_enable) {
        printf(" (%dmV)", shangchi_axp2101::PMU.getALDO4Voltage());
    }
    printf("\n");
    bool bldo1_enable = shangchi_axp2101::PMU.isEnableBLDO1();
    printf("  BLDO1 Enabled: %s", bldo1_enable ? "Yes" : "No");
    if(bldo1_enable) {
        printf(" (%dmV)", shangchi_axp2101::PMU.getBLDO1Voltage());
    }
    printf("\n");
    bool bldo2_enable = shangchi_axp2101::PMU.isEnableBLDO2();
    printf("  BLDO2 Enabled: %s", bldo2_enable ? "Yes" : "No");
    if(bldo2_enable) {
        printf(" (%dmV)", shangchi_axp2101::PMU.getBLDO2Voltage());
    }
    printf("\n");

    return 0;
}

static int axp_batt(int argc, char **argv) {
    printf("Battery: %d%%\n", shangchi_axp2101::PMU.getBatteryPercent());
    return 0;
}

static int axp_set_voltage(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: axp_set_voltage <power_rail> <voltage_mv>\n");
        printf("  power_rail: dcdc1, dcdc2, dcdc3, dcdc4, dcdc5, aldo1, aldo2, aldo3, aldo4, bldo1, bldo2\n");
        printf("  voltage_mv: voltage in millivolts\n");
        return 1;
    }
    const char* rail = argv[1];
    uint32_t voltage = atoi(argv[2]);
    bool success = false;
    if (strcmp(rail, "dcdc1") == 0) {
        success = shangchi_axp2101::PMU.setDC1Voltage(voltage);
    } else if (strcmp(rail, "dcdc2") == 0) {
        success = shangchi_axp2101::PMU.setDC2Voltage(voltage);
    } else if (strcmp(rail, "dcdc3") == 0) {
        success = shangchi_axp2101::PMU.setDC3Voltage(voltage);
    } else if (strcmp(rail, "dcdc4") == 0) {
        success = shangchi_axp2101::PMU.setDC4Voltage(voltage);
    } else if (strcmp(rail, "dcdc5") == 0) {
        success = shangchi_axp2101::PMU.setDC5Voltage(voltage);
    } else if (strcmp(rail, "aldo1") == 0) {
        success = shangchi_axp2101::PMU.setALDO1Voltage(voltage);
    } else if (strcmp(rail, "aldo2") == 0) {
        success = shangchi_axp2101::PMU.setALDO2Voltage(voltage);
    } else if (strcmp(rail, "aldo3") == 0) {
        success = shangchi_axp2101::PMU.setALDO3Voltage(voltage);
    } else if (strcmp(rail, "aldo4") == 0) {
        success = shangchi_axp2101::PMU.setALDO4Voltage(voltage);
    } else if (strcmp(rail, "bldo1") == 0) {
        success = shangchi_axp2101::PMU.setBLDO1Voltage(voltage);
    } else if (strcmp(rail, "bldo2") == 0) {
        success = shangchi_axp2101::PMU.setBLDO2Voltage(voltage);
    } else {
        printf("Invalid power rail: %s\n", rail);
        return 1;
    }
    if (success) {
        printf("Set %s voltage to %ldmV\n", rail, voltage);
    } else {
        printf("Failed to set %s voltage\n", rail);
        return 1;
    }
    return 0;
}

static int axp_get_voltage(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: axp_get_voltage <power_rail>\n");
        printf("  power_rail: dcdc1, dcdc2, dcdc3, dcdc4, dcdc5, aldo1, aldo2, aldo3, aldo4, bldo1, bldo2, vbus, batt\n");
        return 1;
    }

    const char* rail = argv[1];
    uint32_t voltage = 0;

    if (strcmp(rail, "dcdc1") == 0) {
        voltage = shangchi_axp2101::PMU.getDC1Voltage();
    } else if (strcmp(rail, "dcdc2") == 0) {
        voltage = shangchi_axp2101::PMU.getDC2Voltage();
    } else if (strcmp(rail, "dcdc3") == 0) {
        voltage = shangchi_axp2101::PMU.getDC3Voltage();
    } else if (strcmp(rail, "dcdc4") == 0) {
        voltage = shangchi_axp2101::PMU.getDC4Voltage();
    } else if (strcmp(rail, "dcdc5") == 0) {
        voltage = shangchi_axp2101::PMU.getDC5Voltage();
    } else if (strcmp(rail, "aldo1") == 0) {
        voltage = shangchi_axp2101::PMU.getALDO1Voltage();
    } else if (strcmp(rail, "aldo2") == 0) {
        voltage = shangchi_axp2101::PMU.getALDO2Voltage();
    } else if (strcmp(rail, "aldo3") == 0) {
        voltage = shangchi_axp2101::PMU.getALDO3Voltage();
    } else if (strcmp(rail, "aldo4") == 0) {
        voltage = shangchi_axp2101::PMU.getALDO4Voltage();
    } else if (strcmp(rail, "bldo1") == 0) {
        voltage = shangchi_axp2101::PMU.getBLDO1Voltage();
    } else if (strcmp(rail, "bldo2") == 0) {
        voltage = shangchi_axp2101::PMU.getBLDO2Voltage();
    } else if (strcmp(rail, "vbus") == 0) {
        voltage = shangchi_axp2101::PMU.getVbusVoltage();
    } else if (strcmp(rail, "batt") == 0) {
        voltage = shangchi_axp2101::PMU.getBattVoltage();
    } else {
        printf("Invalid power rail: %s\n", rail);
        return 1;
    }

    printf("%s voltage: %ldmV\n", rail, voltage);
    return 0;
}

static int axp_set_enable(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: axp_set_enable <power_rail> <0|1>\n");
        printf("  power_rail: dcdc1, dcdc2, dcdc3, dcdc4, dcdc5, aldo1, aldo2, aldo3, aldo4, bldo1, bldo2\n");
        printf("  0: disable, 1: enable\n");
        return 1;
    }
    const char* rail = argv[1];
    bool enable = (atoi(argv[2]) != 0);
    bool success = false;
    if (strcmp(rail, "dcdc1") == 0) {
        success = enable ? shangchi_axp2101::PMU.enableDC1() : shangchi_axp2101::PMU.disableDC1();
    } else if (strcmp(rail, "dcdc2") == 0) {
        success = enable ? shangchi_axp2101::PMU.enableDC2() : shangchi_axp2101::PMU.disableDC2();
    } else if (strcmp(rail, "dcdc3") == 0) {
        success = enable ? shangchi_axp2101::PMU.enableDC3() : shangchi_axp2101::PMU.disableDC3();
    } else if (strcmp(rail, "dcdc4") == 0) {
        success = enable ? shangchi_axp2101::PMU.enableDC4() : shangchi_axp2101::PMU.disableDC4();
    } else if (strcmp(rail, "dcdc5") == 0) {
        success = enable ? shangchi_axp2101::PMU.enableDC5() : shangchi_axp2101::PMU.disableDC5();
    } else if (strcmp(rail, "aldo1") == 0) {
        success = enable ? shangchi_axp2101::PMU.enableALDO1() : shangchi_axp2101::PMU.disableALDO1();
    } else if (strcmp(rail, "aldo2") == 0) {
        success = enable ? shangchi_axp2101::PMU.enableALDO2() : shangchi_axp2101::PMU.disableALDO2();
    } else if (strcmp(rail, "aldo3") == 0) {
        success = enable ? shangchi_axp2101::PMU.enableALDO3() : shangchi_axp2101::PMU.disableALDO3();
    } else if (strcmp(rail, "aldo4") == 0) {
        success = enable ? shangchi_axp2101::PMU.enableALDO4() : shangchi_axp2101::PMU.disableALDO4();
    } else if (strcmp(rail, "bldo1") == 0) {
        success = enable ? shangchi_axp2101::PMU.enableBLDO1() : shangchi_axp2101::PMU.disableBLDO1();
    } else if (strcmp(rail, "bldo2") == 0) {
        success = enable ? shangchi_axp2101::PMU.enableBLDO2() : shangchi_axp2101::PMU.disableBLDO2();
    } else {
        printf("Invalid power rail: %s\n", rail);
        return 1;
    }
    if (success) {
        printf("%s %s\n", rail, enable ? "enabled" : "disabled");
    } else {
        printf("Failed to %s %s\n", enable ? "enable" : "disable", rail);
        return 1;
    }
    return 0;
}

static int axp_get_enable(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: axp_get_enable <power_rail>\n");
        printf("  power_rail: dcdc1, dcdc2, dcdc3, dcdc4, dcdc5, aldo1, aldo2, aldo3, aldo4, bldo1, bldo2\n");
        return 1;
    }
    const char* rail = argv[1];
    bool enabled = false;
    if (strcmp(rail, "dcdc1") == 0) {
        enabled = shangchi_axp2101::PMU.isEnableDC1();
    } else if (strcmp(rail, "dcdc2") == 0) {
        enabled = shangchi_axp2101::PMU.isEnableDC2();
    } else if (strcmp(rail, "dcdc3") == 0) {
        enabled = shangchi_axp2101::PMU.isEnableDC3();
    } else if (strcmp(rail, "dcdc4") == 0) {
        enabled = shangchi_axp2101::PMU.isEnableDC4();
    } else if (strcmp(rail, "dcdc5") == 0) {
        enabled = shangchi_axp2101::PMU.isEnableDC5();
    } else if (strcmp(rail, "aldo1") == 0) {
        enabled = shangchi_axp2101::PMU.isEnableALDO1();
    } else if (strcmp(rail, "aldo2") == 0) {
        enabled = shangchi_axp2101::PMU.isEnableALDO2();
    } else if (strcmp(rail, "aldo3") == 0) {
        enabled = shangchi_axp2101::PMU.isEnableALDO3();
    } else if (strcmp(rail, "aldo4") == 0) {
        enabled = shangchi_axp2101::PMU.isEnableALDO4();
    } else if (strcmp(rail, "bldo1") == 0) {
        enabled = shangchi_axp2101::PMU.isEnableBLDO1();
    } else if (strcmp(rail, "bldo2") == 0) {
        enabled = shangchi_axp2101::PMU.isEnableBLDO2();
    } else {
        printf("Invalid power rail: %s\n", rail);
        return 1;
    }
    printf("%s is %s\n", rail, enabled ? "enabled" : "disabled");
    return 0;
}
// AHT10命令
static int aht10_read(int argc, char **argv) {
    if (shangchi_flash_info::aht10_instance == nullptr) {
        printf("AHT10 not initialized. Set sensors_enable to 2 first.\n");
        return 1;
    }
    float humi, temp;
    shangchi_aht10::aht10_read_data(&humi, &temp);
    printf("AHT10 Reading:\n");
    printf("  Temperature: %.1f C\n", temp);
    printf("  Humidity: %.1f %%\n", humi);
    return 0;
}
// OLED命令
static int oled_clear(int argc, char **argv) {
    if (shangchi_flash_info::oled_instance == nullptr) {
        printf("OLED not initialized. Set sensors_enable to 1 first.\n");
        return 1;
    }
    shangchi_oled::oled_clear();
    printf("OLED cleared\n");
    return 0;
}
static int oled_text(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: oled_text <row> <text>\n");
        return 1;
    }
    if (shangchi_flash_info::oled_instance == nullptr) {
        printf("OLED not initialized. Set sensors_enable to 1 first.\n");
        return 1;
    }
    uint8_t row = atoi(argv[1]);
    shangchi_oled::oled_show_string(0, row, argv[2]);
    printf("Text displayed on row %d: %s\n", row, argv[2]);
    return 0;
}
// 系统命令
static int set_sensor(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: set_sensor <0|1|2>\n");
        printf("  0: No sensors\n");
        printf("  1: OLED\n");
        printf("  2: AHT10\n");
        return 1;
    }
    uint8_t value = atoi(argv[1]);
    if (value > 2) {
        printf("Invalid value. Must be 0, 1, or 2.\n");
        return 1;
    }
    shangchi_flash_info::flash_info_update("sensors_enable", value);
    printf("sensors_enable set to %d. Restart to apply changes.\n", value);
    return 0;
}

static int get_sensor(int argc, char **argv) {
    uint8_t value;
    shangchi_flash_info::flash_info_get("sensors_enable", &value);
    printf("sensors_enable: %d ", value);
    printf("%s\n", value == 0 ? "No sensors" : (value == 1 ? "OLED" : (value == 2 ? "AHT10" : "Unknown value")));
    return value;
}

static int restart(int argc, char **argv) {
    printf("Restarting...\n");
    esp_restart();
}

// 注册命令
void register_axp2101_commands() {
    esp_console_cmd_t axp_status_cmd = {
        .command = "axp_status",
        .help = "Show AXP2101 status",
        .hint = nullptr,
        .func = &axp_status,
        .argtable = nullptr,
        .func_w_context = nullptr,
        .context = nullptr
    };
    ESP_ERROR_CHECK(esp_console_cmd_register(&axp_status_cmd));

    esp_console_cmd_t axp_batt_cmd = {
        .command = "axp_batt",
        .help = "Show battery percentage",
        .hint = nullptr,
        .func = &axp_batt,
        .argtable = nullptr,
        .func_w_context = nullptr,
        .context = nullptr
    };
    ESP_ERROR_CHECK(esp_console_cmd_register(&axp_batt_cmd));

    static arg_str *rail_arg_set = arg_str1(nullptr, nullptr, "<rail>", "Power rail (dcdc1,dcdc2,dcdc3,dcdc4,dcdc5,aldo1,aldo2,aldo3,aldo4,bldo1,bldo2)");
    static arg_int *voltage_arg = arg_int1(nullptr, nullptr, "<voltage>", "Voltage in mV");
    static struct arg_end *end_set = arg_end(2);
    static void *argtable_set[] = {rail_arg_set, voltage_arg, end_set};
    esp_console_cmd_t axp_set_voltage_cmd = {
        .command = "axp_set_voltage",
        .help = "Set power rail voltage",
        .hint = nullptr,
        .func = &axp_set_voltage,
        .argtable = argtable_set,
        .func_w_context = nullptr,
        .context = nullptr
    };
    ESP_ERROR_CHECK(esp_console_cmd_register(&axp_set_voltage_cmd));

    static arg_str *rail_arg_get = arg_str1(nullptr, nullptr, "<rail>", "Power rail (dcdc1,dcdc2,dcdc3,dcdc4,dcdc5,aldo1,aldo2,aldo3,aldo4,bldo1,bldo2,vbus,batt)");
    static struct arg_end *end_get = arg_end(1);
    static void *argtable_get[] = {rail_arg_get, end_get};
    esp_console_cmd_t axp_get_voltage_cmd = {
        .command = "axp_get_voltage",
        .help = "Get power rail voltage",
        .hint = nullptr,
        .func = &axp_get_voltage,
        .argtable = argtable_get,
        .func_w_context = nullptr,
        .context = nullptr
    };
    ESP_ERROR_CHECK(esp_console_cmd_register(&axp_get_voltage_cmd));

    static arg_str *rail_arg_enable = arg_str1(nullptr, nullptr, "<rail>", "Power rail (dcdc1,dcdc2,dcdc3,dcdc4,dcdc5,aldo1,aldo2,aldo3,aldo4,bldo1,bldo2)");
    static arg_int *enable_arg = arg_int1(nullptr, nullptr, "<0|1>", "0: disable, 1: enable");
    static struct arg_end *end_enable = arg_end(2);
    static void *argtable_enable[] = {rail_arg_enable, enable_arg, end_enable};
    esp_console_cmd_t axp_set_enable_cmd = {
        .command = "axp_set_enable",
        .help = "Enable/disable power rail",
        .hint = nullptr,
        .func = &axp_set_enable,
        .argtable = argtable_enable,
        .func_w_context = nullptr,
        .context = nullptr
    };
    ESP_ERROR_CHECK(esp_console_cmd_register(&axp_set_enable_cmd));

    static arg_str *rail_arg_status = arg_str1(nullptr, nullptr, "<rail>", "Power rail (dcdc1,dcdc2,dcdc3,dcdc4,dcdc5,aldo1,aldo2,aldo3,aldo4,bldo1,bldo2)");
    static struct arg_end *end_status = arg_end(1);
    static void *argtable_status[] = {rail_arg_status, end_status};
    esp_console_cmd_t axp_get_enable_cmd = {
        .command = "axp_get_enable",
        .help = "Get power rail status",
        .hint = nullptr,
        .func = &axp_get_enable,
        .argtable = argtable_status,
        .func_w_context = nullptr,
        .context = nullptr
    };
    ESP_ERROR_CHECK(esp_console_cmd_register(&axp_get_enable_cmd));
}

void register_aht10_commands() {
    esp_console_cmd_t aht10_read_cmd = {
        .command = "aht10_read",
        .help = "Read temperature and humidity",
        .hint = nullptr,
        .func = &aht10_read,
        .argtable = nullptr,
        .func_w_context = nullptr,
        .context = nullptr
    };
    ESP_ERROR_CHECK(esp_console_cmd_register(&aht10_read_cmd));
}

void register_oled_commands() {
    esp_console_cmd_t oled_clear_cmd = {
        .command = "oled_clear",
        .help = "Clear OLED display",
        .hint = nullptr,
        .func = &oled_clear,
        .argtable = nullptr,
        .func_w_context = nullptr,
        .context = nullptr
    };
    ESP_ERROR_CHECK(esp_console_cmd_register(&oled_clear_cmd));

    static arg_int *row_arg = arg_int1(nullptr, nullptr, "<row>", "Row number (0-7)");
    static arg_str *text_arg = arg_str1(nullptr, nullptr, "<text>", "Text to display");
    static struct arg_end *end = arg_end(2);
    static void *argtable[] = {row_arg, text_arg, end};
    esp_console_cmd_t oled_text_cmd = {
        .command = "oled_text",
        .help = "Display text on OLED",
        .hint = nullptr,
        .func = &oled_text,
        .argtable = argtable,
        .func_w_context = nullptr,
        .context = nullptr
    };
    ESP_ERROR_CHECK(esp_console_cmd_register(&oled_text_cmd));
}

void register_system_commands() {
    static arg_int *sensor_arg = arg_int1(nullptr, nullptr, "<value>", "Sensor value (0-2)");
    static struct arg_end *end = arg_end(1);
    static void *argtable[] = {sensor_arg, end};
    esp_console_cmd_t set_sensor_cmd = {
        .command = "set_sensor",
        .help = "Set sensors_enable value",
        .hint = nullptr,
        .func = &set_sensor,
        .argtable = argtable,
        .func_w_context = nullptr,
        .context = nullptr
    };
    ESP_ERROR_CHECK(esp_console_cmd_register(&set_sensor_cmd));

    esp_console_cmd_t get_sensor_cmd = {
        .command = "get_sensor",
        .help = "Get sensors_enable value",
        .hint = nullptr,
        .func = &get_sensor,
        .argtable = nullptr,
        .func_w_context = nullptr,
        .context = nullptr
    };
    ESP_ERROR_CHECK(esp_console_cmd_register(&get_sensor_cmd));

    esp_console_cmd_t restart_cmd = {
        .command = "restart",
        .help = "Restart the system",
        .hint = nullptr,
        .func = &restart,
        .argtable = nullptr,
        .func_w_context = nullptr,
        .context = nullptr
    };
    ESP_ERROR_CHECK(esp_console_cmd_register(&restart_cmd));
}

void debug_task(void *pvParameters) {
    esp_console_repl_config_t repl_config = ESP_CONSOLE_REPL_CONFIG_DEFAULT();
    repl_config.prompt = "shangchi>";
    repl_config.max_cmdline_length = 256;

    esp_console_dev_usb_serial_jtag_config_t usb_config = ESP_CONSOLE_DEV_USB_SERIAL_JTAG_CONFIG_DEFAULT();
    esp_console_repl_t *repl;
    ESP_ERROR_CHECK(esp_console_new_repl_usb_serial_jtag(&usb_config, &repl_config, &repl));

    register_axp2101_commands();
    register_aht10_commands();
    register_oled_commands();
    register_system_commands();

    ESP_ERROR_CHECK(esp_console_register_help_command());

    // 提示信息
    printf("\n ===============================================================\n");
    printf(" |                   ShangChi Debug Console                    |\n");
    printf(" ===============================================================\n");
    printf(" | 可用命令:                                                  |\n");
    printf(" |   axp_status, axp_batt                                    |\n");
    printf(" |   axp_set_voltage <rail> <mv>, axp_get_voltage <rail>     |\n");
    printf(" |   axp_set_enable <rail> <0|1>, axp_get_enable <rail>      |\n");
    printf(" |   oled_clear, oled_text <row> <text>                      |\n");
    printf(" |   aht10_read                                              |\n");
    printf(" |   set_sensor <0|1|2>, get_sensor, restart                 |\n");
    printf(" ===============================================================\n\n");

    ESP_ERROR_CHECK(esp_console_start_repl(repl));
    vTaskDelete(nullptr);
}