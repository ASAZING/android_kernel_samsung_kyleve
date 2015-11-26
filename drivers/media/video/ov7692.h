/*
 * OmniVision OV7692 sensor driver
 *
 * This program is free software; you can redistribute it and/or
 *modify it under the terms of the GNU General Public License as
 *published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 *kind, whether express or implied; without even the implied warranty
 *of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef __OV7692_H__
#define __OV7692_H__

#define ENABLE_COLOR_PATTERN 0

#define OV7692_SATURATION_MIN			0
#define OV7692_SATURATION_MAX			200
#define OV7692_SATURATION_STEP          100
#define OV7692_SATURATION_DEF			100

#define OV7692_SHARPNESS_MIN			0
#define OV7692_SHARPNESS_MAX			200
#define OV7692_SHARPNESS_STEP           100
#define OV7692_SHARPNESS_DEF			100

/**
 *struct ov7692_reg - ov7692 register format
 *@reg: 16-bit offset to register
 *@val: 8/16/32-bit register value
 *@length: length of the register
 *
 * Define a structure for OV7692 register initialization values
 */
struct ov7692_reg {
	u8 reg; 
	u8 val;
};

/* TODO: Divide this properly */
static const struct ov7692_reg configscript_common1[] = {
    {0x12, 0x80},
    {0x0e, 0x08}, // software sleep, driver 1x  //bit[3]=1=sleep, =0=wake up  
    {0x69, 0x52}, // BLC enable
    {0x1e, 0xb3}, // Do AEC/AGC when 50/60 change, less than 1 frame dummy lines,AEC step no limit
    {0x48, 0x42},
    {0xff, 0x01}, // select MIPI register bank
    {0xae, 0xa0}, // MIPI start offset
    {0xa8, 0x26}, // MIPI LP GPIO
    {0xb4, 0xc0}, // MIPI Enable, 8-bit
    {0xb5, 0x40}, // wake up MIPI, wake up MIPI low power transmitter.
    {0xff, 0x00}, // select DVP register bank
#ifdef CONFIG_MACH_HAWAII_GARNET_EDN010
{0x0c, 0x10},
#else
{0x0c, 0xd0},
#endif
    {0x62, 0x10}, // Always do BLC
    {0x12, 0x00}, // YUV output
    {0x17, 0x65}, // Hstart
    {0x18, 0xa4}, // Hsize
    {0x19, 0x0a}, // Vstart
    {0x1a, 0xf6}, // Vsize
    {0x3e, 0x30}, // PCLK free running, Divided PCLK by reg 0x5E[5:4], MIPI YUV
    {0x64, 0x0a}, // PCLK = 2 x SCLK
    {0xff, 0x01}, // select MIPI register bank
    {0x86, 0x48},  // OV sh FAE add 20120428
    {0xb4, 0xc0}, // MIPI enable, 8-bit
    {0xff, 0x00}, // select DVP register bank
    {0x67, 0x20}, // VFIFO offset on start size
    {0x81, 0x3f}, // SDE on, UV adjust on, scale on,
    {0xcc, 0x02}, // ISPHO
    {0xcd, 0x80}, // ISPHO
    {0xce, 0x01}, // ISPVO
    {0xcf, 0xe0}, // ISPVO
    {0xc8, 0x02}, // ISPHI
    {0xc9, 0x80}, // ISPHI
    {0xca, 0x01}, // ISPVI
    {0xcb, 0xe0}, // ISPVI
    {0xd0, 0x48}, // Voff/Hoff
    {0x82, 0x03}, // color bar off, YUV 422
    {0x0e, 0x00}, // wake up
    // 50/60 detect
    {0x70, 0x00},
    {0x71, 0x34},
    {0x74, 0x28},
    {0x75, 0x98},
    {0x76, 0x00},
    {0x77, 0x64},
    {0x78, 0x01},
    {0x79, 0xc2},
    {0x7a, 0x4e},
    {0x7b, 0x1f},
    {0x7c, 0x00},
    {0x31, 0x83}, // 15fps=0x87, 7.5fps=0x8f  
	{0x15, 0xb4},
	{0x11, 0x00}, /* clock pre-scaler */
	{0x20, 0x00}, /* max_band_50_h/max_band_60_h */
	{0x21, 0x57}, /* max_band_50/max_band_B60 */
	{0x50, 0x4d}, /* B50 */
	{0x51, 0x40}, /* B60 */
	{0x4c, 0x7d}, /* black sun, 2.8V */

	/* lenc */
	{0x80, 0x7f},
	{0x85, 0x10}, /* lenc bias */
	{0x86, 0x00}, /* radius */
	{0x87, 0x00},
	{0x88, 0x00},
	{0x89, 0x35}, /* lenc r gain*/
	{0x8a, 0x30}, /* lenc g gain*/
	{0x8b, 0x30}, /* lenc b gain*/
	/* color matrix*/
	{0xbb, 0x80},
	{0xbc, 0x62},
	{0xbd, 0x1E},
	{0xbe, 0x26},
	{0xbf, 0x7B},
	{0xc0, 0xAC},
	{0xc1, 0x1e},

	{0xb4, 0x33},
	{0xb5, 0x0d},
	{0xb6, 0x02},
	{0xb7, 0x05}, /* offset */
	{0xb8, 0x06}, /* base1 */
	{0xb9, 0x02}, /* base2 */
	{0xba, 0x08}, /* 4x gain limit 16x, dns_th_sel = 1, edge_mt_range = 0*/
	/* UV adjust */
	{0x5A, 0x14},
	{0x5B, 0xa2},
	{0x5C, 0x70},
	{0x5d, 0x20},
	/* AE target */
	{0x24, 0x88}, /* stable high */
	{0x25, 0x78}, /* stable low */
	{0x26, 0xb4}, /* fast zone */

	/* Gamma */
	{0xa3, 0x17},
	{0xa4, 0x20},
	{0xa5, 0x34},
	{0xa6, 0x57},
	{0xa7, 0x68},
	{0xa8, 0x77},
	{0xa9, 0x85},
	{0xaa, 0x91},
	{0xab, 0x9c},
	{0xac, 0xa7},
	{0xad, 0xb9},
	{0xae, 0xc8},
	{0xaf, 0xdd},
	{0xb0, 0xea},
	{0xb1, 0xf1},
	{0xb2, 0x06}, /* slop*/
	/* AWB */
	{0x8c, 0x5d},
	{0x8d, 0x11},
	{0x8e, 0x12},
	{0x8f, 0x11},
	{0x90, 0x50},
	{0x91, 0x22},
	{0x92, 0xd1},
	{0x93, 0xa7},
	{0x94, 0x23},
	{0x24, 0x88},
	{0x25, 0x78},
	{0x26, 0xc4},
	{0x95, 0x3b},
	{0x96, 0xff},
	{0x97, 0x00},
	{0x98, 0x4a},
	{0x99, 0x46},
	{0x9a, 0x3d},
	{0x9b, 0x3a},
	{0x9c, 0xf0},
	{0x9d, 0xf0},
	{0x9e, 0xf0},
	{0x9f, 0xff},
	{0xa0, 0x56},
	{0xa1, 0x55},
	{0xa2, 0x13},
	{0xd2, 0x06}, /* brightness on, saturation on */
	{0x14, 0x33}, /* gain ceiling 16x, manual band 50hz */

	{0x0e, 0x02}, /* wake up */
	{0xff, 0xff},
};

static const struct ov7692_reg yuv422_init_common[] = {

    {0xff, 0xff},  

};

static const struct ov7692_reg jpeg_init_common[] = {
    {0xff, 0xff},  

};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*EFFECT */
static const struct ov7692_reg ov7692_effect_normal_tbl[] = {
    {0xff, 0xff},  

};

static const struct ov7692_reg ov7692_effect_bw_tbl[] = {
    {0xff, 0xff},  
};

static const struct ov7692_reg ov7692_effect_sepia_tbl[] = {
    {0xff, 0xff},  
};

static const struct ov7692_reg ov7692_effect_negative_tbl[] = {
    {0xff, 0xff},  
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*AntiBanding */
static const struct ov7692_reg ov7692_antibanding_auto_tbl[] = {

    {0xff, 0xff},  
};

static const struct ov7692_reg ov7692_antibanding_50z_tbl[] = {
        {0xff, 0xff},  
};

static const struct ov7692_reg ov7692_antibanding_60z_tbl[] = {
        {0xff, 0xff},  
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*Lens_shading*/

static const struct ov7692_reg ov7692_lens_shading_on_tbl[] = {
	/*@@ Lenc On(C) */
    {0xff, 0xff},  

};


static const struct ov7692_reg ov7692_lens_shading_off_tbl[] = {
        {0xff, 0xff},  
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*Contrast */

static const struct ov7692_reg ov7692_contrast_default_lv3_tbl[] = {
    {0xff, 0xff},  
};

static const struct ov7692_reg ov7692_contrast_lv0_tbl[] = {
        {0xff, 0xff},  
};

static const struct ov7692_reg ov7692_contrast_lv1_tbl[] = {
        {0xff, 0xff},  
};

static const struct ov7692_reg ov7692_contrast_lv2_tbl[] = {
        {0xff, 0xff},  
};

static const struct ov7692_reg ov7692_contrast_lv4_tbl[] = {
        {0xff, 0xff},  
};

static const struct ov7692_reg ov7692_contrast_lv5_tbl[] = {
        {0xff, 0xff},  
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*sharpness */

static const struct ov7692_reg ov7692_sharpness_default_lv2_tbl[] = {
    {0xff, 0xff},  
};

static const struct ov7692_reg ov7692_sharpness_lv0_tbl[] = {
        {0xff, 0xff},  
};

static const struct ov7692_reg ov7692_sharpness_lv1_tbl[] = {
        {0xff, 0xff},  
};

static const struct ov7692_reg ov7692_sharpness_lv3_tbl[] = {
        {0xff, 0xff},  
};

static const struct ov7692_reg ov7692_sharpness_lv4_tbl[] = {
        {0xff, 0xff},  
};

static const struct ov7692_reg ov7692_sharpness_lv5_tbl[] = {
        {0xff, 0xff},  
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* saturation */

static const struct ov7692_reg ov7692_saturation_default_lv3_tbl[] = {
    {0xff, 0xff},  
};

static const struct ov7692_reg ov7692_saturation_lv0_tbl[] = {
        {0xff, 0xff},  
};

static const struct ov7692_reg ov7692_saturation_lv1_tbl[] = {
        {0xff, 0xff},  
};

static const struct ov7692_reg ov7692_saturation_lv2_tbl[] = {
        {0xff, 0xff},  
};

static const struct ov7692_reg ov7692_saturation_lv4_tbl[] = {
        {0xff, 0xff},  
};

static const struct ov7692_reg ov7692_saturation_lv5_tbl[] = {
        {0xff, 0xff},  
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* brightness */

static const struct ov7692_reg ov7692_brightness_lv0_tbl[] = {
    {0xff, 0xff},  
};

static const struct ov7692_reg ov7692_brightness_lv1_tbl[] = {
        {0xff, 0xff},  
};

static const struct ov7692_reg ov7692_brightness_lv2_default_tbl[] = {
        {0xff, 0xff},  
};

static const struct ov7692_reg ov7692_brightness_lv3_tbl[] = {
        {0xff, 0xff},  
};

static const struct ov7692_reg ov7692_brightness_lv4_tbl[] = {
        {0xff, 0xff},  
};

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Auto Expourse */

static const struct ov7692_reg ov7692_ae_average_tbl[] = {
    {0xff, 0xff},  
};

static const struct ov7692_reg ov7692_ae_centerweight_tbl[] = {
        {0xff, 0xff},  
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*default awb */
static const struct ov7692_reg ov7692_wb_def[] = {
    {0xff, 0xff},  
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* White Balance */
static const struct ov7692_reg ov7692_wb_fluorescent[] = {
    {0xff, 0xff},  
};

static const struct ov7692_reg ov7692_wb_daylight[] = {
        {0xff, 0xff},  
};

static const struct ov7692_reg ov7692_wb_cloudy[] = {
        {0xff, 0xff},  
};

static const struct ov7692_reg ov7692_wb_tungsten[] = {
        {0xff, 0xff},  
};

/*static const struct ov7692_reg ov7692_fps_5[] = {
        {0xff, 0xff},  
};

static const struct ov7692_reg ov7692_fps_7[] = {
        {0xff, 0xff},  
};
static const struct ov7692_reg ov7692_fps_10[] = {
        {0xff, 0xff},  
};
static const struct ov7692_reg ov7692_fps_15[] = {
        {0xff, 0xff},  
};
static const struct ov7692_reg ov7692_fps_20[] = {
        {0xff, 0xff},  
};
static const struct ov7692_reg ov7692_fps_25[] = {
        {0xff, 0xff},  
};*/

static const struct ov7692_reg ov7692_fps_30[] = {
        {0xff, 0xff},  
};


static const struct ov7692_reg ov7692_afpreinit_tbl[] = {
        {0xff, 0xff},  
};

static const struct ov7692_reg ov7692_afpostinit_tbl[] = {
        {0xff, 0xff},  
};

const u8 ov7692_afinit_data[] = {};

#endif /* __OV7692_H__ */
