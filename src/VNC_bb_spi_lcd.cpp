/*
 * @file VNC_bb_spi_lcd.cpp
 * @date June 8, 2024
 * @author Larry Bank
 *
 * Copyright (c) 2024 Larry Bank. All rights reserved.
 * This file is part of the VNC client for Arduino.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, a copy can be downloaded from
 * http://www.gnu.org/licenses/gpl.html, or obtained by writing to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 *
 */

#include "VNC_config.h"

#include "VNC.h"

#include <bb_spi_lcd.h>
#include "VNC_bb_spi_lcd.h"

BB_SPI_LCD_VNC::BB_SPI_LCD_VNC(int iDisplayName) {
        lcd.begin(iDisplayName);
}

bool BB_SPI_LCD_VNC::hasCopyRect(void) {
    return false;
}

uint32_t BB_SPI_LCD_VNC::getHeight(void) {
    return lcd.height();
}

uint32_t BB_SPI_LCD_VNC::getWidth(void) {
    return lcd.width();
}

void BB_SPI_LCD_VNC::draw_area(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t *data) {
    lcd.pushImage(x, y, w, h, (uint16_t *)data);
}


void BB_SPI_LCD_VNC::draw_rect(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint16_t color) {
    lcd.fillRect(x, y, w, h, color);
}

void BB_SPI_LCD_VNC::copy_rect(uint32_t src_x, uint32_t src_y, uint32_t dest_x, uint32_t dest_y, uint32_t w, uint32_t h) {

}

void BB_SPI_LCD_VNC::area_update_start(uint32_t x, uint32_t y, uint32_t w, uint32_t h) {
    area_x = x;
    area_y = y;
    area_w = w;
    area_h = h;
}

void BB_SPI_LCD_VNC::area_update_data(char *data, uint32_t pixel){
    lcd.pushImage(area_x, area_y, area_w, area_h, (uint16_t *)data);
}

void BB_SPI_LCD_VNC::area_update_end(void){
}

