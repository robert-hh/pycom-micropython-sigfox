/*
 * Copyright (c) 2021, Pycom Limited.
 *
 * This software is licensed under the GNU GPL version 3 or any
 * later version, with permitted additional terms. For more information
 * see the Pycom Licence v1.0 document supplied with this file, or
 * available at https://www.pycom.io/opensource/licensing
 */

#include "esp_system.h"
#include "esp_spiram.h"
#include "esp_spi_flash.h"

static esp_chip_info_t chip_info;

void esp32_init_chip_info(void)
{
    // Get chip Info
    esp_chip_info(&chip_info);
}

uint8_t esp32_get_chip_rev(void)
{
    return chip_info.revision;
}

uint32_t esp32_get_spiram_size(void)
{
    switch (esp_spiram_get_chip_size()) {
        case ESP_SPIRAM_SIZE_16MBITS:
            return 0x200000;
        case ESP_SPIRAM_SIZE_32MBITS:
        case ESP_SPIRAM_SIZE_64MBITS:
            return 0x400000;
        default:
            return 0;
    }
}

uint32_t esp32_get_flash_size(void)
{
#ifdef MICROPY_HW_FLASH_SIZE
    // Set the HW flash size based on the build flag.
    return (MICROPY_HW_FLASH_SIZE);
#else
    // differentiate the Flash Size (either 8MB or 4MB) based on ESP32 rev id
    // At that point, the esp_idf may report a wrong chip size, if it is not
    // properly set in the bootloader header.
    return (esp32_get_chip_rev() > 0 ? 0x800000 : 0x400000);
#endif    
}
