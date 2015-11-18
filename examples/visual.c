/**
 * Copyright (C) ARM Limited 2014-2015. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include "streamline_annotate.h"

static const unsigned char arm_logo_limited_use[] = {
  0x47, 0x49, 0x46, 0x38, 0x39, 0x61, 0x2c, 0x01, 0x7c, 0x00, 0xd5, 0x00,
  0x00, 0xc4, 0xe2, 0xe9, 0x4d, 0xa7, 0xbf, 0xbf, 0xbf, 0xbf, 0x40, 0x40,
  0x40, 0x7f, 0x7f, 0x7f, 0x88, 0xc4, 0xd4, 0xf0, 0xf8, 0xfa, 0x10, 0x10,
  0x10, 0xef, 0xef, 0xef, 0x21, 0x91, 0xae, 0xcf, 0xcf, 0xcf, 0x9f, 0x9f,
  0x9f, 0x6b, 0xb6, 0xc9, 0xa6, 0xd3, 0xdf, 0x60, 0x60, 0x60, 0x30, 0x99,
  0xb4, 0x30, 0x30, 0x30, 0x8f, 0x8f, 0x8f, 0x3f, 0xa0, 0xb9, 0x20, 0x20,
  0x20, 0xdf, 0xdf, 0xdf, 0xaf, 0xaf, 0xaf, 0xe1, 0xf0, 0xf4, 0xd2, 0xe9,
  0xef, 0x50, 0x50, 0x50, 0x70, 0x70, 0x70, 0x97, 0xcc, 0xd9, 0x5c, 0xaf,
  0xc4, 0xb5, 0xda, 0xe4, 0x7a, 0xbd, 0xcf, 0x00, 0x00, 0x00, 0x12, 0x8a,
  0xa9, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x2c, 0x00, 0x00, 0x00, 0x00, 0x2c, 0x01, 0x7c, 0x00, 0x00, 0x06,
  0xff, 0x40, 0x90, 0x70, 0x48, 0x2c, 0x1a, 0x8f, 0xc8, 0xa4, 0x72, 0xc9,
  0x6c, 0x3a, 0x9f, 0xd0, 0xa8, 0x74, 0x4a, 0xad, 0x5a, 0xaf, 0xd8, 0xac,
  0x76, 0xcb, 0xed, 0x7a, 0xbf, 0xe0, 0xb0, 0x78, 0x4c, 0x2e, 0x9b, 0xcf,
  0xe8, 0xb4, 0x7a, 0xcd, 0x6e, 0xbb, 0xdf, 0xf0, 0xb8, 0x7c, 0x4e, 0xaf,
  0xdb, 0xef, 0xf8, 0xbc, 0x7e, 0xcf, 0xef, 0xfb, 0xff, 0x80, 0x81, 0x82,
  0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e,
  0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a,
  0x9b, 0x9c, 0x9d, 0x9e, 0x9f, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6,
  0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2,
  0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0x5e, 0x06, 0x09, 0x1f,
  0xbf, 0xc0, 0xc1, 0xc2, 0xc3, 0xc0, 0x0d, 0x69, 0x05, 0xc4, 0xc9, 0xca,
  0xcb, 0xc9, 0x12, 0x01, 0x05, 0x1c, 0x16, 0x61, 0x01, 0xcc, 0xc4, 0x05,
  0x74, 0x17, 0xbe, 0xd5, 0xc2, 0x00, 0x4a, 0x16, 0x1d, 0x0f, 0xc1, 0x1b,
  0xdd, 0x66, 0x0d, 0xdb, 0xd5, 0x0f, 0xc7, 0xe7, 0xeb, 0xec, 0xbf, 0x12,
  0x1d, 0x17, 0x5e, 0xd4, 0xed, 0x1f, 0xc6, 0x71, 0x06, 0xe1, 0xf4, 0xe4,
  0x47, 0x1a, 0xc0, 0x01, 0x1d, 0x01, 0xf2, 0x05, 0x30, 0x50, 0x26, 0x1f,
  0xbd, 0x61, 0xfb, 0xca, 0x20, 0x3b, 0xc8, 0x70, 0x99, 0x04, 0x7b, 0x5a,
  0xe6, 0xe9, 0x83, 0x63, 0x40, 0x02, 0xc3, 0x84, 0x44, 0x18, 0x7c, 0x48,
  0xa0, 0x81, 0xe0, 0x10, 0x00, 0x16, 0x25, 0x78, 0x0c, 0x03, 0xa0, 0xe1,
  0xb0, 0x00, 0x68, 0x16, 0x9a, 0x5c, 0x29, 0xec, 0x01, 0xc4, 0x2b, 0x12,
  0xdb, 0x25, 0x88, 0xe7, 0x66, 0x43, 0x43, 0x8c, 0x42, 0xfa, 0x3d, 0xb8,
  0x00, 0x30, 0x80, 0xcf, 0xff, 0x02, 0xd2, 0x34, 0xa2, 0x14, 0xa3, 0x91,
  0x25, 0x30, 0x69, 0x66, 0x54, 0x1a, 0x5d, 0x1a, 0x00, 0xa9, 0x95, 0x98,
  0xed, 0x1e, 0x8c, 0x54, 0x53, 0xf4, 0xa2, 0x91, 0x5e, 0x33, 0x41, 0x40,
  0x4d, 0x40, 0x90, 0xda, 0xcb, 0x2e, 0x06, 0x96, 0x02, 0x63, 0x70, 0x46,
  0xa9, 0x58, 0x96, 0x09, 0xbe, 0x4a, 0x81, 0xda, 0x4e, 0xe4, 0x9a, 0x7e,
  0x26, 0x71, 0xf6, 0xbb, 0xa6, 0xf5, 0x83, 0x10, 0x0b, 0xe1, 0x8c, 0x5d,
  0xf8, 0x20, 0x21, 0x0c, 0xdc, 0xb3, 0x53, 0xc5, 0x98, 0x3d, 0xcb, 0x92,
  0x6c, 0x15, 0xb6, 0xed, 0x36, 0xa8, 0x31, 0xb7, 0x12, 0x27, 0x35, 0xa4,
  0xd4, 0x86, 0x84, 0xd3, 0x20, 0xc4, 0x62, 0xe0, 0x2d, 0x06, 0xc5, 0xd2,
  0x25, 0x33, 0x98, 0xf0, 0x4a, 0xc3, 0x53, 0x10, 0xb7, 0x03, 0x5d, 0x26,
  0x1b, 0x4b, 0x9c, 0x09, 0xd2, 0x09, 0xa1, 0xe6, 0x33, 0x5c, 0x02, 0xa4,
  0xc8, 0x70, 0x66, 0x29, 0xe9, 0x39, 0x41, 0x52, 0xcf, 0x84, 0x49, 0x43,
  0x11, 0xdd, 0x8e, 0x72, 0x69, 0x6d, 0x8d, 0x8d, 0x7c, 0x18, 0x5a, 0x37,
  0x18, 0x87, 0x21, 0xb1, 0xbf, 0x54, 0x25, 0xac, 0xf6, 0x4b, 0x67, 0xdc,
  0x26, 0x3b, 0x84, 0x5e, 0xda, 0x1c, 0xac, 0x45, 0xa3, 0xa8, 0x55, 0xd7,
  0x05, 0x00, 0x40, 0xa3, 0x6d, 0x21, 0x1d, 0x3e, 0xc8, 0xbe, 0x12, 0x16,
  0xba, 0x76, 0xc1, 0xd0, 0x09, 0x1f, 0x8f, 0xc2, 0x5b, 0x26, 0x4d, 0x30,
  0x15, 0xc5, 0x3a, 0xfe, 0x00, 0xd9, 0x2e, 0x88, 0xf2, 0x1e, 0x2d, 0x7b,
  0xf9, 0x8b, 0x7b, 0x3d, 0xfa, 0xf4, 0x62, 0x71, 0xc5, 0x5e, 0x80, 0xef,
  0x79, 0xb1, 0xdc, 0x69, 0x46, 0xcc, 0xb5, 0x9a, 0x7d, 0x20, 0xf8, 0xd2,
  0x4d, 0x49, 0xc4, 0x71, 0x91, 0x99, 0x67, 0x11, 0x82, 0xf1, 0x1c, 0x80,
  0x0c, 0xe9, 0xc6, 0x44, 0x7b, 0xf4, 0xb8, 0xe5, 0xff, 0x45, 0x78, 0x67,
  0xe1, 0xd4, 0xcb, 0x07, 0xf1, 0x44, 0xb6, 0x20, 0x65, 0x16, 0xf9, 0xb7,
  0x05, 0x07, 0x18, 0x92, 0x38, 0xc6, 0x85, 0x2d, 0xd2, 0x53, 0xe0, 0x86,
  0x84, 0x79, 0xb8, 0x05, 0x63, 0x21, 0x1e, 0x61, 0xce, 0x4c, 0x0d, 0x6c,
  0x06, 0x40, 0x01, 0x1a, 0x08, 0xf5, 0x85, 0x4d, 0x18, 0x6a, 0xd8, 0x05,
  0x8c, 0x31, 0xb2, 0xa3, 0xd8, 0x13, 0x1c, 0x1e, 0x64, 0x64, 0x15, 0x2c,
  0x7a, 0x36, 0x9e, 0x77, 0x05, 0x4c, 0xc5, 0x41, 0x38, 0x36, 0x6e, 0x61,
  0x41, 0x92, 0x4e, 0x39, 0xd7, 0x90, 0x4f, 0x60, 0x86, 0x19, 0xe6, 0x75,
  0x62, 0x75, 0xb9, 0x44, 0x93, 0x07, 0x49, 0x97, 0x85, 0x69, 0x52, 0x26,
  0xd1, 0x80, 0x36, 0x60, 0x6a, 0xb3, 0xc1, 0x65, 0x59, 0x20, 0xa9, 0xd9,
  0x7f, 0x07, 0x3d, 0x71, 0x81, 0x06, 0x13, 0x32, 0xb4, 0x19, 0x8d, 0xb8,
  0x55, 0x07, 0x85, 0x05, 0xc0, 0x11, 0x36, 0x9e, 0x10, 0x06, 0x14, 0x40,
  0x66, 0x02, 0x0c, 0x1c, 0x8a, 0x45, 0x9f, 0xd0, 0x09, 0x68, 0x61, 0x43,
  0x52, 0x5c, 0xb9, 0xd2, 0x79, 0x67, 0xa6, 0xa7, 0xa2, 0x14, 0xf1, 0x41,
  0xe7, 0x68, 0x1a, 0x51, 0x26, 0x29, 0x28, 0x16, 0x76, 0x2a, 0x33, 0x45,
  0xa7, 0x0d, 0x99, 0x99, 0x04, 0x9a, 0x0c, 0x65, 0x45, 0x05, 0xab, 0x56,
  0xc9, 0x41, 0x64, 0x92, 0x98, 0x72, 0x51, 0x6a, 0x32, 0x54, 0xe0, 0x63,
  0xd2, 0xa8, 0x44, 0xc0, 0x7a, 0xd0, 0x6b, 0x53, 0x1c, 0xd8, 0x66, 0x1c,
  0x5b, 0x26, 0x09, 0xcc, 0xa6, 0x5b, 0xdc, 0x4a, 0x4c, 0x15, 0x38, 0x1e,
  0xf4, 0xa7, 0x12, 0xbe, 0x1e, 0x94, 0x65, 0x13, 0xca, 0xde, 0x24, 0x47,
  0xb5, 0xe2, 0xcc, 0xda, 0x4e, 0x85, 0xc9, 0x52, 0x5a, 0x05, 0xa4, 0xe7,
  0x70, 0x8b, 0x44, 0xb4, 0x07, 0x89, 0xeb, 0x66, 0x8c, 0x9f, 0x9e, 0x51,
  0xff, 0x28, 0x3b, 0x1c, 0xd0, 0x76, 0xd0, 0x8c, 0x5a, 0x60, 0x1b, 0x8c,
  0x15, 0x20, 0x96, 0xeb, 0x04, 0xb9, 0x4e, 0x3a, 0xe1, 0x2e, 0x86, 0xe9,
  0x96, 0xd1, 0x2c, 0x3b, 0xdf, 0x81, 0x5b, 0xcd, 0x93, 0x57, 0xc8, 0x0b,
  0x8c, 0x15, 0xff, 0xb2, 0x63, 0xae, 0x11, 0xf8, 0x3a, 0xcb, 0x04, 0x9b,
  0x2d, 0xf6, 0x4b, 0x46, 0xc3, 0x6a, 0xf2, 0xd7, 0x8e, 0xaa, 0xa4, 0x7a,
  0x4b, 0xc5, 0xbe, 0xdb, 0xde, 0x6b, 0xec, 0xa8, 0xba, 0x26, 0x29, 0xb1,
  0x18, 0xc5, 0xbe, 0x8b, 0xe8, 0xba, 0xeb, 0x3c, 0x5b, 0xa7, 0xc6, 0x53,
  0x70, 0xac, 0xb0, 0xc7, 0xc6, 0x8e, 0x87, 0x2a, 0xba, 0x70, 0xd4, 0xdb,
  0x56, 0x46, 0xad, 0xd2, 0x69, 0x85, 0xc1, 0xbf, 0x58, 0x11, 0x2a, 0x3d,
  0x0b, 0x17, 0xd1, 0x70, 0xab, 0xf0, 0x82, 0xa0, 0x2d, 0xcd, 0x6f, 0xa0,
  0x7c, 0xce, 0x4b, 0x7b, 0x31, 0xe4, 0x5b, 0xb7, 0x0c, 0xed, 0xdc, 0xd0,
  0x92, 0x80, 0x1a, 0x2b, 0x55, 0x11, 0xc2, 0x46, 0xfc, 0x46, 0xc2, 0xeb,
  0x04, 0xd6, 0x70, 0xad, 0x05, 0xb3, 0x2c, 0x05, 0x99, 0xf4, 0xa8, 0x3c,
  0xae, 0xb1, 0xc0, 0xd8, 0x68, 0xb1, 0xc8, 0x6f, 0x34, 0xac, 0x21, 0xd7,
  0x4b, 0xdb, 0x2a, 0x36, 0x14, 0x2e, 0xb3, 0x0b, 0x33, 0xda, 0x1f, 0x2c,
  0x09, 0xb7, 0xd6, 0x6d, 0x94, 0x4c, 0x0f, 0xb2, 0x0d, 0x32, 0x14, 0xb4,
  0x14, 0x3c, 0x33, 0x38, 0xb6, 0x49, 0x3a, 0x33, 0x8c, 0xf7, 0x58, 0x10,
  0xe3, 0x3d, 0xf2, 0x17, 0x36, 0xb3, 0x03, 0x36, 0x08, 0x85, 0x3f, 0xbe,
  0x44, 0xe1, 0x54, 0x64, 0xbd, 0x4e, 0x5f, 0x77, 0x2f, 0xae, 0x34, 0xdb,
  0x6c, 0x8c, 0x98, 0x26, 0x12, 0x7e, 0x8f, 0x06, 0x75, 0x9e, 0x51, 0x18,
  0x70, 0x34, 0x3d, 0x4f, 0x57, 0x1d, 0xd5, 0xe7, 0xc6, 0xae, 0xbe, 0x8e,
  0xe5, 0x5c, 0xec, 0x5d, 0xff, 0x0d, 0xc6, 0x42, 0xc8, 0x7e, 0x0e, 0xee,
  0x84, 0xcf, 0xed, 0x4d, 0x01, 0xb0, 0x9f, 0x23, 0x69, 0x13, 0x0d, 0x07,
  0xd0, 0xf4, 0xe2, 0xbf, 0x34, 0x6a, 0x2d, 0x1b, 0x64, 0xbf, 0x9c, 0x44,
  0xdd, 0xe7, 0xa8, 0x99, 0xf1, 0x45, 0xdc, 0x55, 0x6f, 0x7d, 0xf5, 0x05,
  0x74, 0xd0, 0x7c, 0x43, 0x66, 0xaf, 0x2a, 0x38, 0x08, 0xb6, 0x03, 0x88,
  0x12, 0xf4, 0xdb, 0xd0, 0xae, 0xc5, 0xf1, 0xf4, 0xf0, 0x2a, 0x30, 0x33,
  0xc3, 0x4b, 0x8d, 0x3c, 0x3d, 0xed, 0xbb, 0xee, 0x7c, 0xe1, 0x0d, 0xb9,
  0x45, 0x7e, 0x35, 0xe6, 0x67, 0xa1, 0x79, 0x35, 0xf1, 0x27, 0xd8, 0x50,
  0xeb, 0x55, 0xa0, 0x1f, 0xda, 0x00, 0x07, 0xad, 0xef, 0x09, 0x61, 0x7f,
  0xb8, 0x01, 0x16, 0x08, 0xee, 0xc7, 0x8c, 0xfc, 0x91, 0x27, 0x78, 0xcb,
  0x20, 0xd8, 0x10, 0x44, 0x47, 0x8f, 0xc9, 0x45, 0x41, 0x80, 0x49, 0x92,
  0xe0, 0xd9, 0xec, 0x35, 0x84, 0xed, 0x45, 0xea, 0x3d, 0x0c, 0x5c, 0x86,
  0x03, 0x11, 0xb6, 0xbc, 0x25, 0x20, 0x90, 0x19, 0xbc, 0xa2, 0xd6, 0xfb,
  0xd8, 0xc1, 0xb9, 0x01, 0x71, 0x10, 0x51, 0x1e, 0xf4, 0x8c, 0x8a, 0x42,
  0xa8, 0x8c, 0x11, 0x56, 0x21, 0x86, 0xe8, 0x70, 0x02, 0xfa, 0x3a, 0x16,
  0xb6, 0x15, 0x6e, 0x63, 0x5a, 0x9d, 0x73, 0xde, 0x10, 0x08, 0x85, 0xa1,
  0xaf, 0xd0, 0x30, 0x19, 0x36, 0x9c, 0xc2, 0x0e, 0xd9, 0xd1, 0xbd, 0x23,
  0x0c, 0xcd, 0x86, 0x18, 0x14, 0x5f, 0xe2, 0x32, 0xf5, 0xc2, 0x21, 0x34,
  0x2e, 0x37, 0x46, 0x38, 0x22, 0x31, 0x92, 0x28, 0x85, 0x13, 0x2e, 0x83,
  0x77, 0x46, 0x08, 0xdf, 0x32, 0xa8, 0x46, 0x85, 0x28, 0x42, 0x47, 0x7a,
  0xd3, 0xa9, 0xe2, 0x10, 0xc4, 0xc8, 0x10, 0x32, 0x7e, 0xa4, 0x84, 0x66,
  0xa0, 0x60, 0x62, 0xa2, 0xb0, 0x3e, 0x66, 0x80, 0xff, 0x91, 0x09, 0x66,
  0x24, 0x4c, 0x02, 0x08, 0xc8, 0x24, 0x03, 0xfa, 0xaf, 0x46, 0x74, 0xd2,
  0x22, 0x42, 0xd2, 0xb0, 0xb6, 0x75, 0xa4, 0xb0, 0x08, 0x85, 0xd3, 0xe0,
  0xe5, 0x7c, 0x98, 0x8c, 0x0e, 0x4c, 0x31, 0x88, 0xeb, 0x58, 0x98, 0x17,
  0x25, 0xa7, 0x33, 0x41, 0x72, 0x23, 0x0d, 0x75, 0x54, 0xc6, 0x77, 0x06,
  0xd5, 0x90, 0xfe, 0x3d, 0x21, 0x8f, 0x46, 0x61, 0xc0, 0x1d, 0xfb, 0xa8,
  0xc6, 0x22, 0xe8, 0x0e, 0x7e, 0x45, 0x13, 0x82, 0x25, 0x83, 0xc1, 0xc5,
  0x27, 0xac, 0x72, 0x2c, 0xc1, 0xe2, 0x5e, 0x00, 0x19, 0x19, 0x8c, 0x07,
  0xb4, 0xb2, 0x38, 0x40, 0x53, 0xc2, 0xcc, 0xe0, 0x98, 0x45, 0x5e, 0x8e,
  0x61, 0x92, 0xc9, 0x48, 0xe5, 0x12, 0x5e, 0xf9, 0x0b, 0x0b, 0xe2, 0x91,
  0x96, 0xc2, 0x70, 0x64, 0x16, 0x8a, 0xb7, 0x04, 0x39, 0x1e, 0x84, 0x57,
  0xc4, 0x14, 0xcf, 0x19, 0xca, 0x73, 0x10, 0x63, 0x2e, 0x21, 0x93, 0xca,
  0x38, 0xe4, 0x11, 0x40, 0xb9, 0x14, 0x20, 0xae, 0xc5, 0x8f, 0x49, 0xb8,
  0x22, 0x3b, 0xd0, 0x88, 0x84, 0x68, 0xde, 0x92, 0x09, 0x85, 0x3c, 0x07,
  0x00, 0xa1, 0xc0, 0xc6, 0x66, 0x94, 0x11, 0x99, 0xc3, 0xf0, 0xe6, 0x6e,
  0xc0, 0x99, 0x84, 0x9f, 0xb1, 0x43, 0x91, 0x0b, 0xf4, 0x65, 0x18, 0xb0,
  0x99, 0x8c, 0x51, 0x26, 0xc1, 0x99, 0xec, 0x30, 0x1f, 0x37, 0xc5, 0x22,
  0x4f, 0x48, 0x86, 0xcb, 0x09, 0xed, 0x0c, 0x46, 0x0b, 0x87, 0xa9, 0xcf,
  0x2f, 0x44, 0xd3, 0x8d, 0x5d, 0x9c, 0xda, 0x14, 0x0a, 0x57, 0x80, 0x8a,
  0x5a, 0x34, 0x7b, 0x38, 0xa4, 0x07, 0x3e, 0xbd, 0x57, 0xca, 0x24, 0x44,
  0x8e, 0x19, 0x05, 0x2d, 0x82, 0x39, 0xcd, 0x00, 0x4c, 0x62, 0xf0, 0xd1,
  0x09, 0xa5, 0xbb, 0x58, 0xef, 0xa2, 0x86, 0x84, 0x44, 0x41, 0xf0, 0x1c,
  0xff, 0x27, 0xa5, 0x62, 0x2e, 0x9f, 0x00, 0x4c, 0x57, 0x35, 0x61, 0xa4,
  0x64, 0x48, 0xe9, 0x3a, 0x36, 0xf9, 0x94, 0x86, 0x6c, 0x94, 0x08, 0x98,
  0xd3, 0xe5, 0x29, 0x77, 0xfa, 0x48, 0x8e, 0xce, 0xd4, 0x09, 0xbb, 0x0c,
  0x26, 0xdd, 0x1a, 0x7a, 0x24, 0x78, 0xfe, 0xaa, 0xa8, 0x88, 0xf4, 0x9d,
  0x11, 0x30, 0xf8, 0x53, 0xa1, 0xd1, 0x93, 0x09, 0x21, 0xcb, 0x66, 0x14,
  0x70, 0x3a, 0x06, 0x7e, 0x3a, 0x55, 0x18, 0x4d, 0x44, 0x42, 0x50, 0x8f,
  0x19, 0x9c, 0x6f, 0x76, 0x74, 0x09, 0xe2, 0x04, 0xc6, 0x3a, 0x99, 0xc0,
  0xd5, 0x30, 0xd8, 0xf3, 0xab, 0xe7, 0xb0, 0xe6, 0x54, 0xa5, 0x7a, 0x84,
  0x92, 0x26, 0x63, 0x70, 0x1b, 0x3c, 0x2a, 0x14, 0x96, 0x98, 0xbc, 0x96,
  0x31, 0x75, 0x0b, 0x43, 0x85, 0xab, 0x56, 0x3f, 0x49, 0xd7, 0xab, 0x64,
  0x74, 0x1b, 0xda, 0xec, 0xd5, 0x55, 0x11, 0x7a, 0x92, 0x8d, 0xfd, 0x35,
  0x0b, 0x3a, 0x15, 0x6c, 0x0e, 0x09, 0xcb, 0x52, 0x1d, 0x5e, 0xca, 0xac,
  0x7a, 0xbd, 0xa0, 0x42, 0xa1, 0x7a, 0x84, 0xb6, 0x7a, 0x49, 0xb2, 0x13,
  0x71, 0xc2, 0x58, 0x45, 0xbb, 0x92, 0xc4, 0x2e, 0xe8, 0xac, 0x4e, 0xd0,
  0x80, 0x45, 0xfd, 0x59, 0xce, 0xc7, 0x3e, 0x0a, 0xb4, 0x99, 0x55, 0xc2,
  0x68, 0x9b, 0x90, 0xd5, 0x6a, 0xba, 0x30, 0xb6, 0x6a, 0xf0, 0x6c, 0x17,
  0xde, 0x0a, 0xdb, 0x6d, 0xb0, 0x76, 0xb6, 0x4d, 0x48, 0x68, 0x32, 0x4c,
  0xcb, 0xcc, 0x37, 0xe8, 0x96, 0x0b, 0x81, 0xed, 0x2d, 0x31, 0x36, 0x0a,
  0xdc, 0x26, 0x1c, 0x96, 0x19, 0x72, 0x55, 0x2c, 0x6a, 0xcf, 0x70, 0x5c,
  0x2d, 0x44, 0x56, 0xb9, 0xcc, 0x80, 0x6a, 0x73, 0xd9, 0x5a, 0x56, 0xe2,
  0x2d, 0x36, 0x0d, 0xd5, 0xcd, 0xc2, 0x47, 0xb1, 0x5b, 0x8d, 0xb0, 0x22,
  0xa7, 0xb0, 0x4a, 0x78, 0xff, 0xee, 0x32, 0xf0, 0x3a, 0x84, 0xe2, 0xba,
  0x21, 0xbc, 0x58, 0x78, 0x29, 0x79, 0x85, 0xc1, 0xd3, 0x24, 0x6c, 0x97,
  0x09, 0xc2, 0xdd, 0xa2, 0x41, 0xb7, 0xc1, 0xde, 0x31, 0xc0, 0x97, 0x84,
  0xf3, 0x6d, 0x47, 0x0a, 0xef, 0xcb, 0x04, 0xaf, 0x12, 0x03, 0xa2, 0x79,
  0xe5, 0xe1, 0x7b, 0x5d, 0xfb, 0xaa, 0x00, 0x47, 0x85, 0xac, 0xa8, 0x9b,
  0x42, 0x7e, 0x87, 0xe1, 0x4f, 0xf7, 0xb6, 0xe1, 0xbf, 0x54, 0xb8, 0xae,
  0x83, 0x6b, 0xb8, 0xc8, 0xca, 0x4e, 0x41, 0xbe, 0xca, 0xc0, 0xa7, 0x85,
  0xd9, 0x80, 0xe1, 0x29, 0x8c, 0x37, 0xae, 0xd7, 0x4b, 0xb1, 0x8a, 0x57,
  0xcc, 0xe2, 0xea, 0x81, 0x98, 0x18, 0x83, 0x23, 0x30, 0x84, 0x19, 0x52,
  0xd4, 0x11, 0xaf, 0xa1, 0xc4, 0x52, 0x78, 0xf1, 0x30, 0xcc, 0xbb, 0x05,
  0xbb, 0x52, 0x58, 0xb6, 0xe8, 0x6d, 0xe6, 0x4a, 0x78, 0x6c, 0xe3, 0xdc,
  0x32, 0x38, 0x0a, 0x13, 0x0e, 0x06, 0x6b, 0xb1, 0xc0, 0xd7, 0x75, 0x48,
  0x50, 0xc6, 0x4c, 0xf0, 0x31, 0x7d, 0x1f, 0x59, 0x64, 0xf0, 0x1e, 0x79,
  0x9e, 0x6d, 0x44, 0xc3, 0xd0, 0x3e, 0x90, 0x38, 0x28, 0xa3, 0xb5, 0xb4,
  0x32, 0x55, 0xf0, 0x85, 0xaf, 0x6c, 0xd9, 0x86, 0x98, 0x16, 0x0b, 0x49,
  0x06, 0x46, 0x13, 0xbd, 0x1c, 0xe6, 0x0a, 0xb6, 0x39, 0x92, 0x70, 0xc0,
  0x31, 0x4d, 0x3b, 0xa9, 0x06, 0x1d, 0x4f, 0x59, 0xac, 0x41, 0x66, 0x02,
  0x6f, 0xd9, 0x31, 0xaa, 0x2a, 0xa3, 0x41, 0xce, 0xb4, 0xb5, 0x73, 0x30,
  0xaa, 0x1a, 0xaf, 0x5d, 0xe1, 0xd9, 0xc3, 0xdf, 0x32, 0x49, 0xd0, 0xfc,
  0x4c, 0x5d, 0x32, 0xe3, 0xd7, 0x24, 0xc2, 0x0c, 0x83, 0x86, 0x27, 0x3b,
  0x57, 0x44, 0x53, 0x21, 0x9d, 0xb3, 0x33, 0xaa, 0x98, 0x49, 0xec, 0xe8,
  0x25, 0xa8, 0x37, 0x19, 0xd1, 0x1d, 0x92, 0x49, 0xdb, 0x00, 0xc7, 0xe6,
  0x66, 0x0a, 0x3a, 0x18, 0x0b, 0x63, 0xb4, 0x19, 0x00, 0xfd, 0xe5, 0xff,
  0x71, 0xfa, 0x4b, 0xdb, 0xcc, 0x73, 0x13, 0x4e, 0xbc, 0x0e, 0xdc, 0xa9,
  0xba, 0x0c, 0xac, 0x56, 0x82, 0x94, 0x83, 0xc1, 0xd9, 0x2f, 0x18, 0x78,
  0x18, 0xf0, 0x2a, 0xf5, 0x12, 0x26, 0x3d, 0xb0, 0x04, 0x0b, 0x71, 0xcc,
  0xb1, 0xc2, 0x02, 0x40, 0xd7, 0x81, 0xe0, 0x33, 0x60, 0x7a, 0x1b, 0x1a,
  0x12, 0xb6, 0x09, 0x57, 0x82, 0xb1, 0x5b, 0x93, 0x21, 0xd7, 0x48, 0x48,
  0xf3, 0x2f, 0x62, 0x3a, 0x86, 0x65, 0xd7, 0x3a, 0xaa, 0x96, 0xae, 0x02,
  0xb1, 0x99, 0x61, 0x24, 0x6b, 0xfb, 0xb7, 0xd3, 0x48, 0xf8, 0x34, 0x31,
  0xea, 0xbb, 0x86, 0x5d, 0xab, 0x19, 0xdc, 0x11, 0x5e, 0xe6, 0x4a, 0x2e,
  0x63, 0x6e, 0x31, 0x60, 0xbb, 0x97, 0x0d, 0x21, 0xe7, 0x1a, 0x9a, 0x2c,
  0xbc, 0xa9, 0x48, 0x9b, 0xa1, 0x26, 0x51, 0x59, 0xbd, 0x49, 0x82, 0x6e,
  0x23, 0xb8, 0xfb, 0x17, 0x4b, 0x16, 0xc3, 0x96, 0x5f, 0xf2, 0xef, 0x37,
  0x03, 0xcc, 0x6b, 0xdf, 0xfd, 0x73, 0xc1, 0x8b, 0x60, 0x92, 0x85, 0xba,
  0x41, 0xdb, 0x1f, 0x38, 0x4f, 0xc3, 0x95, 0x10, 0xcd, 0x5f, 0x00, 0x70,
  0xe0, 0x60, 0xb8, 0xf7, 0x2e, 0x46, 0x4e, 0xf2, 0x92, 0x9b, 0xfc, 0xe4,
  0x28, 0x4f, 0xb9, 0xca, 0x57, 0xce, 0xf2, 0x96, 0xbb, 0xfc, 0xe5, 0x30,
  0x8f, 0xb9, 0xcc, 0x67, 0x4e, 0xf3, 0x9a, 0xdb, 0xfc, 0xe6, 0x38, 0xcf,
  0xb9, 0xce, 0x77, 0xce, 0xf3, 0x9e, 0xfb, 0xfc, 0xe7, 0x90, 0x08, 0x02,
  0x00, 0x3b, 0x00
};

int main(void)
{
	ANNOTATE_SETUP;

	ANNOTATE_VISUAL(arm_logo_limited_use, sizeof(arm_logo_limited_use), "ARM");

	return 0;
}
