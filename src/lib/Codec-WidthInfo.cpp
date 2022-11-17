﻿//==============================================================================
// Codec-WidthInfo
//==============================================================================
#include "stdafx.h"

namespace Gurax {

const Codec::WidthInfo Codec::_widthInfoTbl[] = {
	{ 0x000020, WidthProp::N  },
	{ 0x00007f, WidthProp::Na },
	{ 0x0000a1, WidthProp::N  },
	{ 0x0000a2, WidthProp::A  },
	{ 0x0000a4, WidthProp::Na },
	{ 0x0000a5, WidthProp::A  },
	{ 0x0000a7, WidthProp::Na },
	{ 0x0000a9, WidthProp::A  },
	{ 0x0000aa, WidthProp::N  },
	{ 0x0000ab, WidthProp::A  },
	{ 0x0000ac, WidthProp::N  },
	{ 0x0000ad, WidthProp::Na },
	{ 0x0000af, WidthProp::A  },
	{ 0x0000b0, WidthProp::Na },
	{ 0x0000b5, WidthProp::A  },
	{ 0x0000b6, WidthProp::N  },
	{ 0x0000bb, WidthProp::A  },
	{ 0x0000bc, WidthProp::N  },
	{ 0x0000c0, WidthProp::A  },
	{ 0x0000c6, WidthProp::N  },
	{ 0x0000c7, WidthProp::A  },
	{ 0x0000d0, WidthProp::N  },
	{ 0x0000d1, WidthProp::A  },
	{ 0x0000d7, WidthProp::N  },
	{ 0x0000d9, WidthProp::A  },
	{ 0x0000de, WidthProp::N  },
	{ 0x0000e2, WidthProp::A  },
	{ 0x0000e6, WidthProp::N  },
	{ 0x0000e7, WidthProp::A  },
	{ 0x0000e8, WidthProp::N  },
	{ 0x0000eb, WidthProp::A  },
	{ 0x0000ec, WidthProp::N  },
	{ 0x0000ee, WidthProp::A  },
	{ 0x0000f0, WidthProp::N  },
	{ 0x0000f1, WidthProp::A  },
	{ 0x0000f2, WidthProp::N  },
	{ 0x0000f4, WidthProp::A  },
	{ 0x0000f7, WidthProp::N  },
	{ 0x0000fb, WidthProp::A  },
	{ 0x0000fc, WidthProp::N  },
	{ 0x0000fd, WidthProp::A  },
	{ 0x0000fe, WidthProp::N  },
	{ 0x0000ff, WidthProp::A  },
	{ 0x000101, WidthProp::N  },
	{ 0x000102, WidthProp::A  },
	{ 0x000111, WidthProp::N  },
	{ 0x000112, WidthProp::A  },
	{ 0x000113, WidthProp::N  },
	{ 0x000114, WidthProp::A  },
	{ 0x00011b, WidthProp::N  },
	{ 0x00011c, WidthProp::A  },
	{ 0x000126, WidthProp::N  },
	{ 0x000128, WidthProp::A  },
	{ 0x00012b, WidthProp::N  },
	{ 0x00012c, WidthProp::A  },
	{ 0x000131, WidthProp::N  },
	{ 0x000134, WidthProp::A  },
	{ 0x000138, WidthProp::N  },
	{ 0x000139, WidthProp::A  },
	{ 0x00013f, WidthProp::N  },
	{ 0x000143, WidthProp::A  },
	{ 0x000144, WidthProp::N  },
	{ 0x000145, WidthProp::A  },
	{ 0x000148, WidthProp::N  },
	{ 0x00014c, WidthProp::A  },
	{ 0x00014d, WidthProp::N  },
	{ 0x00014e, WidthProp::A  },
	{ 0x000152, WidthProp::N  },
	{ 0x000154, WidthProp::A  },
	{ 0x000166, WidthProp::N  },
	{ 0x000168, WidthProp::A  },
	{ 0x00016b, WidthProp::N  },
	{ 0x00016c, WidthProp::A  },
	{ 0x0001ce, WidthProp::N  },
	{ 0x0001cf, WidthProp::A  },
	{ 0x0001d0, WidthProp::N  },
	{ 0x0001d1, WidthProp::A  },
	{ 0x0001d2, WidthProp::N  },
	{ 0x0001d3, WidthProp::A  },
	{ 0x0001d4, WidthProp::N  },
	{ 0x0001d5, WidthProp::A  },
	{ 0x0001d6, WidthProp::N  },
	{ 0x0001d7, WidthProp::A  },
	{ 0x0001d8, WidthProp::N  },
	{ 0x0001d9, WidthProp::A  },
	{ 0x0001da, WidthProp::N  },
	{ 0x0001db, WidthProp::A  },
	{ 0x0001dc, WidthProp::N  },
	{ 0x0001dd, WidthProp::A  },
	{ 0x000251, WidthProp::N  },
	{ 0x000252, WidthProp::A  },
	{ 0x000261, WidthProp::N  },
	{ 0x000262, WidthProp::A  },
	{ 0x0002c4, WidthProp::N  },
	{ 0x0002c5, WidthProp::A  },
	{ 0x0002c7, WidthProp::N  },
	{ 0x0002c8, WidthProp::A  },
	{ 0x0002c9, WidthProp::N  },
	{ 0x0002cc, WidthProp::A  },
	{ 0x0002cd, WidthProp::N  },
	{ 0x0002ce, WidthProp::A  },
	{ 0x0002d0, WidthProp::N  },
	{ 0x0002d1, WidthProp::A  },
	{ 0x0002d8, WidthProp::N  },
	{ 0x0002dc, WidthProp::A  },
	{ 0x0002dd, WidthProp::N  },
	{ 0x0002de, WidthProp::A  },
	{ 0x0002df, WidthProp::N  },
	{ 0x0002e0, WidthProp::A  },
	{ 0x000300, WidthProp::N  },
	{ 0x000370, WidthProp::A  },
	{ 0x000391, WidthProp::N  },
	{ 0x0003aa, WidthProp::A  },
	{ 0x0003b1, WidthProp::N  },
	{ 0x0003c2, WidthProp::A  },
	{ 0x0003c3, WidthProp::N  },
	{ 0x0003ca, WidthProp::A  },
	{ 0x000401, WidthProp::N  },
	{ 0x000402, WidthProp::A  },
	{ 0x000410, WidthProp::N  },
	{ 0x000450, WidthProp::A  },
	{ 0x000451, WidthProp::N  },
	{ 0x000452, WidthProp::A  },
	{ 0x001100, WidthProp::N  },
	{ 0x001160, WidthProp::W  },
	{ 0x002010, WidthProp::N  },
	{ 0x002011, WidthProp::A  },
	{ 0x002013, WidthProp::N  },
	{ 0x002017, WidthProp::A  },
	{ 0x002018, WidthProp::N  },
	{ 0x00201a, WidthProp::A  },
	{ 0x00201c, WidthProp::N  },
	{ 0x00201e, WidthProp::A  },
	{ 0x002020, WidthProp::N  },
	{ 0x002023, WidthProp::A  },
	{ 0x002024, WidthProp::N  },
	{ 0x002028, WidthProp::A  },
	{ 0x002030, WidthProp::N  },
	{ 0x002031, WidthProp::A  },
	{ 0x002032, WidthProp::N  },
	{ 0x002034, WidthProp::A  },
	{ 0x002035, WidthProp::N  },
	{ 0x002036, WidthProp::A  },
	{ 0x00203b, WidthProp::N  },
	{ 0x00203c, WidthProp::A  },
	{ 0x00203e, WidthProp::N  },
	{ 0x00203f, WidthProp::A  },
	{ 0x002074, WidthProp::N  },
	{ 0x002075, WidthProp::A  },
	{ 0x00207f, WidthProp::N  },
	{ 0x002080, WidthProp::A  },
	{ 0x002081, WidthProp::N  },
	{ 0x002085, WidthProp::A  },
	{ 0x0020a9, WidthProp::N  },
	{ 0x0020aa, WidthProp::H  },
	{ 0x0020ac, WidthProp::N  },
	{ 0x0020ad, WidthProp::A  },
	{ 0x002103, WidthProp::N  },
	{ 0x002104, WidthProp::A  },
	{ 0x002105, WidthProp::N  },
	{ 0x002106, WidthProp::A  },
	{ 0x002109, WidthProp::N  },
	{ 0x00210a, WidthProp::A  },
	{ 0x002113, WidthProp::N  },
	{ 0x002114, WidthProp::A  },
	{ 0x002116, WidthProp::N  },
	{ 0x002117, WidthProp::A  },
	{ 0x002121, WidthProp::N  },
	{ 0x002123, WidthProp::A  },
	{ 0x002126, WidthProp::N  },
	{ 0x002127, WidthProp::A  },
	{ 0x00212b, WidthProp::N  },
	{ 0x00212c, WidthProp::A  },
	{ 0x002153, WidthProp::N  },
	{ 0x002155, WidthProp::A  },
	{ 0x00215b, WidthProp::N  },
	{ 0x00215f, WidthProp::A  },
	{ 0x002160, WidthProp::N  },
	{ 0x00216c, WidthProp::A  },
	{ 0x002170, WidthProp::N  },
	{ 0x00217a, WidthProp::A  },
	{ 0x002189, WidthProp::N  },
	{ 0x00219a, WidthProp::A  },
	{ 0x0021b8, WidthProp::N  },
	{ 0x0021ba, WidthProp::A  },
	{ 0x0021d2, WidthProp::N  },
	{ 0x0021d3, WidthProp::A  },
	{ 0x0021d4, WidthProp::N  },
	{ 0x0021d5, WidthProp::A  },
	{ 0x0021e7, WidthProp::N  },
	{ 0x0021e8, WidthProp::A  },
	{ 0x002200, WidthProp::N  },
	{ 0x002201, WidthProp::A  },
	{ 0x002202, WidthProp::N  },
	{ 0x002204, WidthProp::A  },
	{ 0x002207, WidthProp::N  },
	{ 0x002209, WidthProp::A  },
	{ 0x00220b, WidthProp::N  },
	{ 0x00220c, WidthProp::A  },
	{ 0x00220f, WidthProp::N  },
	{ 0x002210, WidthProp::A  },
	{ 0x002211, WidthProp::N  },
	{ 0x002212, WidthProp::A  },
	{ 0x002215, WidthProp::N  },
	{ 0x002216, WidthProp::A  },
	{ 0x00221a, WidthProp::N  },
	{ 0x00221b, WidthProp::A  },
	{ 0x00221d, WidthProp::N  },
	{ 0x002221, WidthProp::A  },
	{ 0x002223, WidthProp::N  },
	{ 0x002224, WidthProp::A  },
	{ 0x002225, WidthProp::N  },
	{ 0x002226, WidthProp::A  },
	{ 0x002227, WidthProp::N  },
	{ 0x00222d, WidthProp::A  },
	{ 0x00222e, WidthProp::N  },
	{ 0x00222f, WidthProp::A  },
	{ 0x002234, WidthProp::N  },
	{ 0x002238, WidthProp::A  },
	{ 0x00223c, WidthProp::N  },
	{ 0x00223e, WidthProp::A  },
	{ 0x002248, WidthProp::N  },
	{ 0x002249, WidthProp::A  },
	{ 0x00224c, WidthProp::N  },
	{ 0x00224d, WidthProp::A  },
	{ 0x002252, WidthProp::N  },
	{ 0x002253, WidthProp::A  },
	{ 0x002260, WidthProp::N  },
	{ 0x002262, WidthProp::A  },
	{ 0x002264, WidthProp::N  },
	{ 0x002268, WidthProp::A  },
	{ 0x00226a, WidthProp::N  },
	{ 0x00226c, WidthProp::A  },
	{ 0x00226e, WidthProp::N  },
	{ 0x002270, WidthProp::A  },
	{ 0x002282, WidthProp::N  },
	{ 0x002284, WidthProp::A  },
	{ 0x002286, WidthProp::N  },
	{ 0x002288, WidthProp::A  },
	{ 0x002295, WidthProp::N  },
	{ 0x002296, WidthProp::A  },
	{ 0x002299, WidthProp::N  },
	{ 0x00229a, WidthProp::A  },
	{ 0x0022a5, WidthProp::N  },
	{ 0x0022a6, WidthProp::A  },
	{ 0x0022bf, WidthProp::N  },
	{ 0x0022c0, WidthProp::A  },
	{ 0x002312, WidthProp::N  },
	{ 0x002313, WidthProp::A  },
	{ 0x002329, WidthProp::N  },
	{ 0x00232b, WidthProp::W  },
	{ 0x002460, WidthProp::N  },
	{ 0x0024ea, WidthProp::A  },
	{ 0x0024eb, WidthProp::N  },
	{ 0x00254c, WidthProp::A  },
	{ 0x002550, WidthProp::N  },
	{ 0x002574, WidthProp::A  },
	{ 0x002580, WidthProp::N  },
	{ 0x002590, WidthProp::A  },
	{ 0x002592, WidthProp::N  },
	{ 0x002596, WidthProp::A  },
	{ 0x0025a0, WidthProp::N  },
	{ 0x0025a2, WidthProp::A  },
	{ 0x0025a3, WidthProp::N  },
	{ 0x0025aa, WidthProp::A  },
	{ 0x0025b2, WidthProp::N  },
	{ 0x0025b4, WidthProp::A  },
	{ 0x0025b6, WidthProp::N  },
	{ 0x0025b8, WidthProp::A  },
	{ 0x0025bc, WidthProp::N  },
	{ 0x0025be, WidthProp::A  },
	{ 0x0025c0, WidthProp::N  },
	{ 0x0025c2, WidthProp::A  },
	{ 0x0025c6, WidthProp::N  },
	{ 0x0025c9, WidthProp::A  },
	{ 0x0025cb, WidthProp::N  },
	{ 0x0025cc, WidthProp::A  },
	{ 0x0025ce, WidthProp::N  },
	{ 0x0025d2, WidthProp::A  },
	{ 0x0025e2, WidthProp::N  },
	{ 0x0025e6, WidthProp::A  },
	{ 0x0025ef, WidthProp::N  },
	{ 0x0025f0, WidthProp::A  },
	{ 0x002605, WidthProp::N  },
	{ 0x002607, WidthProp::A  },
	{ 0x002609, WidthProp::N  },
	{ 0x00260a, WidthProp::A  },
	{ 0x00260e, WidthProp::N  },
	{ 0x002610, WidthProp::A  },
	{ 0x002614, WidthProp::N  },
	{ 0x002616, WidthProp::A  },
	{ 0x00261c, WidthProp::N  },
	{ 0x00261d, WidthProp::A  },
	{ 0x00261e, WidthProp::N  },
	{ 0x00261f, WidthProp::A  },
	{ 0x002640, WidthProp::N  },
	{ 0x002641, WidthProp::A  },
	{ 0x002642, WidthProp::N  },
	{ 0x002643, WidthProp::A  },
	{ 0x002660, WidthProp::N  },
	{ 0x002662, WidthProp::A  },
	{ 0x002663, WidthProp::N  },
	{ 0x002666, WidthProp::A  },
	{ 0x002667, WidthProp::N  },
	{ 0x00266b, WidthProp::A  },
	{ 0x00266c, WidthProp::N  },
	{ 0x00266e, WidthProp::A  },
	{ 0x00266f, WidthProp::N  },
	{ 0x002670, WidthProp::A  },
	{ 0x00269e, WidthProp::N  },
	{ 0x0026a0, WidthProp::A  },
	{ 0x0026be, WidthProp::N  },
	{ 0x0026c0, WidthProp::A  },
	{ 0x0026c4, WidthProp::N  },
	{ 0x0026ce, WidthProp::A  },
	{ 0x0026cf, WidthProp::N  },
	{ 0x0026e2, WidthProp::A  },
	{ 0x0026e3, WidthProp::N  },
	{ 0x0026e4, WidthProp::A  },
	{ 0x0026e8, WidthProp::N  },
	{ 0x002700, WidthProp::A  },
	{ 0x00273d, WidthProp::N  },
	{ 0x00273e, WidthProp::A  },
	{ 0x002757, WidthProp::N  },
	{ 0x002758, WidthProp::A  },
	{ 0x002776, WidthProp::N  },
	{ 0x002780, WidthProp::A  },
	{ 0x0027e6, WidthProp::N  },
	{ 0x0027ee, WidthProp::Na },
	{ 0x002985, WidthProp::N  },
	{ 0x002987, WidthProp::Na },
	{ 0x002b55, WidthProp::N  },
	{ 0x002b5a, WidthProp::A  },
	{ 0x002e80, WidthProp::N  },
	{ 0x003000, WidthProp::W  },
	{ 0x003001, WidthProp::F  },
	{ 0x00303f, WidthProp::W  },
	{ 0x003041, WidthProp::N  },
	{ 0x003248, WidthProp::W  },
	{ 0x003250, WidthProp::A  },
	{ 0x004dc0, WidthProp::W  },
	{ 0x004e00, WidthProp::N  },
	{ 0x00a4d0, WidthProp::W  },
	{ 0x00a960, WidthProp::N  },
	{ 0x00a980, WidthProp::W  },
	{ 0x00ac00, WidthProp::N  },
	{ 0x00d7b0, WidthProp::W  },
	{ 0x00e000, WidthProp::N  },
	{ 0x00f900, WidthProp::A  },
	{ 0x00fb00, WidthProp::W  },
	{ 0x00fe00, WidthProp::N  },
	{ 0x00fe10, WidthProp::A  },
	{ 0x00fe20, WidthProp::W  },
	{ 0x00fe30, WidthProp::N  },
	{ 0x00fe70, WidthProp::W  },
	{ 0x00ff01, WidthProp::N  },
	{ 0x00ff61, WidthProp::F  },
	{ 0x00ffe0, WidthProp::H  },
	{ 0x00ffe8, WidthProp::F  },
	{ 0x00fff9, WidthProp::H  },
	{ 0x00fffd, WidthProp::N  },
	{ 0x010000, WidthProp::A  },
	{ 0x01b000, WidthProp::N  },
	{ 0x01bc00, WidthProp::W  },
	{ 0x01f100, WidthProp::N  },
	{ 0x01f10b, WidthProp::A  },
	{ 0x01f110, WidthProp::N  },
	{ 0x01f12e, WidthProp::A  },
	{ 0x01f130, WidthProp::N  },
	{ 0x01f16a, WidthProp::A  },
	{ 0x01f170, WidthProp::N  },
	{ 0x01f1e6, WidthProp::A  },
	{ 0x01f200, WidthProp::N  },
	{ 0x01f300, WidthProp::W  },
	{ 0x020000, WidthProp::N  },
	{ 0x0e0001, WidthProp::W  },
	{ 0x0e0100, WidthProp::N  },
	{ 0x10fffe, WidthProp::A  },
	{ 0x000000, WidthProp::N  },
	{ 0x000020, WidthProp::N  },
	{ 0x00007f, WidthProp::Na },
	{ 0x0000a1, WidthProp::N  },
	{ 0x0000a2, WidthProp::A  },
	{ 0x0000a4, WidthProp::Na },
	{ 0x0000a5, WidthProp::A  },
	{ 0x0000a7, WidthProp::Na },
	{ 0x0000a9, WidthProp::A  },
	{ 0x0000aa, WidthProp::N  },
	{ 0x0000ab, WidthProp::A  },
	{ 0x0000ac, WidthProp::N  },
	{ 0x0000ad, WidthProp::Na },
	{ 0x0000af, WidthProp::A  },
	{ 0x0000b0, WidthProp::Na },
	{ 0x0000b5, WidthProp::A  },
	{ 0x0000b6, WidthProp::N  },
	{ 0x0000bb, WidthProp::A  },
	{ 0x0000bc, WidthProp::N  },
	{ 0x0000c0, WidthProp::A  },
	{ 0x0000c6, WidthProp::N  },
	{ 0x0000c7, WidthProp::A  },
	{ 0x0000d0, WidthProp::N  },
	{ 0x0000d1, WidthProp::A  },
	{ 0x0000d7, WidthProp::N  },
	{ 0x0000d9, WidthProp::A  },
	{ 0x0000de, WidthProp::N  },
	{ 0x0000e2, WidthProp::A  },
	{ 0x0000e6, WidthProp::N  },
	{ 0x0000e7, WidthProp::A  },
	{ 0x0000e8, WidthProp::N  },
	{ 0x0000eb, WidthProp::A  },
	{ 0x0000ec, WidthProp::N  },
	{ 0x0000ee, WidthProp::A  },
	{ 0x0000f0, WidthProp::N  },
	{ 0x0000f1, WidthProp::A  },
	{ 0x0000f2, WidthProp::N  },
	{ 0x0000f4, WidthProp::A  },
	{ 0x0000f7, WidthProp::N  },
	{ 0x0000fb, WidthProp::A  },
	{ 0x0000fc, WidthProp::N  },
	{ 0x0000fd, WidthProp::A  },
	{ 0x0000fe, WidthProp::N  },
	{ 0x0000ff, WidthProp::A  },
	{ 0x000101, WidthProp::N  },
	{ 0x000102, WidthProp::A  },
	{ 0x000111, WidthProp::N  },
	{ 0x000112, WidthProp::A  },
	{ 0x000113, WidthProp::N  },
	{ 0x000114, WidthProp::A  },
	{ 0x00011b, WidthProp::N  },
	{ 0x00011c, WidthProp::A  },
	{ 0x000126, WidthProp::N  },
	{ 0x000128, WidthProp::A  },
	{ 0x00012b, WidthProp::N  },
	{ 0x00012c, WidthProp::A  },
	{ 0x000131, WidthProp::N  },
	{ 0x000134, WidthProp::A  },
	{ 0x000138, WidthProp::N  },
	{ 0x000139, WidthProp::A  },
	{ 0x00013f, WidthProp::N  },
	{ 0x000143, WidthProp::A  },
	{ 0x000144, WidthProp::N  },
	{ 0x000145, WidthProp::A  },
	{ 0x000148, WidthProp::N  },
	{ 0x00014c, WidthProp::A  },
	{ 0x00014d, WidthProp::N  },
	{ 0x00014e, WidthProp::A  },
	{ 0x000152, WidthProp::N  },
	{ 0x000154, WidthProp::A  },
	{ 0x000166, WidthProp::N  },
	{ 0x000168, WidthProp::A  },
	{ 0x00016b, WidthProp::N  },
	{ 0x00016c, WidthProp::A  },
	{ 0x0001ce, WidthProp::N  },
	{ 0x0001cf, WidthProp::A  },
	{ 0x0001d0, WidthProp::N  },
	{ 0x0001d1, WidthProp::A  },
	{ 0x0001d2, WidthProp::N  },
	{ 0x0001d3, WidthProp::A  },
	{ 0x0001d4, WidthProp::N  },
	{ 0x0001d5, WidthProp::A  },
	{ 0x0001d6, WidthProp::N  },
	{ 0x0001d7, WidthProp::A  },
	{ 0x0001d8, WidthProp::N  },
	{ 0x0001d9, WidthProp::A  },
	{ 0x0001da, WidthProp::N  },
	{ 0x0001db, WidthProp::A  },
	{ 0x0001dc, WidthProp::N  },
	{ 0x0001dd, WidthProp::A  },
	{ 0x000251, WidthProp::N  },
	{ 0x000252, WidthProp::A  },
	{ 0x000261, WidthProp::N  },
	{ 0x000262, WidthProp::A  },
	{ 0x0002c4, WidthProp::N  },
	{ 0x0002c5, WidthProp::A  },
	{ 0x0002c7, WidthProp::N  },
	{ 0x0002c8, WidthProp::A  },
	{ 0x0002c9, WidthProp::N  },
	{ 0x0002cc, WidthProp::A  },
	{ 0x0002cd, WidthProp::N  },
	{ 0x0002ce, WidthProp::A  },
	{ 0x0002d0, WidthProp::N  },
	{ 0x0002d1, WidthProp::A  },
	{ 0x0002d8, WidthProp::N  },
	{ 0x0002dc, WidthProp::A  },
	{ 0x0002dd, WidthProp::N  },
	{ 0x0002de, WidthProp::A  },
	{ 0x0002df, WidthProp::N  },
	{ 0x0002e0, WidthProp::A  },
	{ 0x000300, WidthProp::N  },
	{ 0x000370, WidthProp::A  },
	{ 0x000391, WidthProp::N  },
	{ 0x0003aa, WidthProp::A  },
	{ 0x0003b1, WidthProp::N  },
	{ 0x0003c2, WidthProp::A  },
	{ 0x0003c3, WidthProp::N  },
	{ 0x0003ca, WidthProp::A  },
	{ 0x000401, WidthProp::N  },
	{ 0x000402, WidthProp::A  },
	{ 0x000410, WidthProp::N  },
	{ 0x000450, WidthProp::A  },
	{ 0x000451, WidthProp::N  },
	{ 0x000452, WidthProp::A  },
	{ 0x001100, WidthProp::N  },
	{ 0x001160, WidthProp::W  },
	{ 0x002010, WidthProp::N  },
	{ 0x002011, WidthProp::A  },
	{ 0x002013, WidthProp::N  },
	{ 0x002017, WidthProp::A  },
	{ 0x002018, WidthProp::N  },
	{ 0x00201a, WidthProp::A  },
	{ 0x00201c, WidthProp::N  },
	{ 0x00201e, WidthProp::A  },
	{ 0x002020, WidthProp::N  },
	{ 0x002023, WidthProp::A  },
	{ 0x002024, WidthProp::N  },
	{ 0x002028, WidthProp::A  },
	{ 0x002030, WidthProp::N  },
	{ 0x002031, WidthProp::A  },
	{ 0x002032, WidthProp::N  },
	{ 0x002034, WidthProp::A  },
	{ 0x002035, WidthProp::N  },
	{ 0x002036, WidthProp::A  },
	{ 0x00203b, WidthProp::N  },
	{ 0x00203c, WidthProp::A  },
	{ 0x00203e, WidthProp::N  },
	{ 0x00203f, WidthProp::A  },
	{ 0x002074, WidthProp::N  },
	{ 0x002075, WidthProp::A  },
	{ 0x00207f, WidthProp::N  },
	{ 0x002080, WidthProp::A  },
	{ 0x002081, WidthProp::N  },
	{ 0x002085, WidthProp::A  },
	{ 0x0020a9, WidthProp::N  },
	{ 0x0020aa, WidthProp::H  },
	{ 0x0020ac, WidthProp::N  },
	{ 0x0020ad, WidthProp::A  },
	{ 0x002103, WidthProp::N  },
	{ 0x002104, WidthProp::A  },
	{ 0x002105, WidthProp::N  },
	{ 0x002106, WidthProp::A  },
	{ 0x002109, WidthProp::N  },
	{ 0x00210a, WidthProp::A  },
	{ 0x002113, WidthProp::N  },
	{ 0x002114, WidthProp::A  },
	{ 0x002116, WidthProp::N  },
	{ 0x002117, WidthProp::A  },
	{ 0x002121, WidthProp::N  },
	{ 0x002123, WidthProp::A  },
	{ 0x002126, WidthProp::N  },
	{ 0x002127, WidthProp::A  },
	{ 0x00212b, WidthProp::N  },
	{ 0x00212c, WidthProp::A  },
	{ 0x002153, WidthProp::N  },
	{ 0x002155, WidthProp::A  },
	{ 0x00215b, WidthProp::N  },
	{ 0x00215f, WidthProp::A  },
	{ 0x002160, WidthProp::N  },
	{ 0x00216c, WidthProp::A  },
	{ 0x002170, WidthProp::N  },
	{ 0x00217a, WidthProp::A  },
	{ 0x002189, WidthProp::N  },
	{ 0x00219a, WidthProp::A  },
	{ 0x0021b8, WidthProp::N  },
	{ 0x0021ba, WidthProp::A  },
	{ 0x0021d2, WidthProp::N  },
	{ 0x0021d3, WidthProp::A  },
	{ 0x0021d4, WidthProp::N  },
	{ 0x0021d5, WidthProp::A  },
	{ 0x0021e7, WidthProp::N  },
	{ 0x0021e8, WidthProp::A  },
	{ 0x002200, WidthProp::N  },
	{ 0x002201, WidthProp::A  },
	{ 0x002202, WidthProp::N  },
	{ 0x002204, WidthProp::A  },
	{ 0x002207, WidthProp::N  },
	{ 0x002209, WidthProp::A  },
	{ 0x00220b, WidthProp::N  },
	{ 0x00220c, WidthProp::A  },
	{ 0x00220f, WidthProp::N  },
	{ 0x002210, WidthProp::A  },
	{ 0x002211, WidthProp::N  },
	{ 0x002212, WidthProp::A  },
	{ 0x002215, WidthProp::N  },
	{ 0x002216, WidthProp::A  },
	{ 0x00221a, WidthProp::N  },
	{ 0x00221b, WidthProp::A  },
	{ 0x00221d, WidthProp::N  },
	{ 0x002221, WidthProp::A  },
	{ 0x002223, WidthProp::N  },
	{ 0x002224, WidthProp::A  },
	{ 0x002225, WidthProp::N  },
	{ 0x002226, WidthProp::A  },
	{ 0x002227, WidthProp::N  },
	{ 0x00222d, WidthProp::A  },
	{ 0x00222e, WidthProp::N  },
	{ 0x00222f, WidthProp::A  },
	{ 0x002234, WidthProp::N  },
	{ 0x002238, WidthProp::A  },
	{ 0x00223c, WidthProp::N  },
	{ 0x00223e, WidthProp::A  },
	{ 0x002248, WidthProp::N  },
	{ 0x002249, WidthProp::A  },
	{ 0x00224c, WidthProp::N  },
	{ 0x00224d, WidthProp::A  },
	{ 0x002252, WidthProp::N  },
	{ 0x002253, WidthProp::A  },
	{ 0x002260, WidthProp::N  },
	{ 0x002262, WidthProp::A  },
	{ 0x002264, WidthProp::N  },
	{ 0x002268, WidthProp::A  },
	{ 0x00226a, WidthProp::N  },
	{ 0x00226c, WidthProp::A  },
	{ 0x00226e, WidthProp::N  },
	{ 0x002270, WidthProp::A  },
	{ 0x002282, WidthProp::N  },
	{ 0x002284, WidthProp::A  },
	{ 0x002286, WidthProp::N  },
	{ 0x002288, WidthProp::A  },
	{ 0x002295, WidthProp::N  },
	{ 0x002296, WidthProp::A  },
	{ 0x002299, WidthProp::N  },
	{ 0x00229a, WidthProp::A  },
	{ 0x0022a5, WidthProp::N  },
	{ 0x0022a6, WidthProp::A  },
	{ 0x0022bf, WidthProp::N  },
	{ 0x0022c0, WidthProp::A  },
	{ 0x002312, WidthProp::N  },
	{ 0x002313, WidthProp::A  },
	{ 0x002329, WidthProp::N  },
	{ 0x00232b, WidthProp::W  },
	{ 0x002460, WidthProp::N  },
	{ 0x0024ea, WidthProp::A  },
	{ 0x0024eb, WidthProp::N  },
	{ 0x00254c, WidthProp::A  },
	{ 0x002550, WidthProp::N  },
	{ 0x002574, WidthProp::A  },
	{ 0x002580, WidthProp::N  },
	{ 0x002590, WidthProp::A  },
	{ 0x002592, WidthProp::N  },
	{ 0x002596, WidthProp::A  },
	{ 0x0025a0, WidthProp::N  },
	{ 0x0025a2, WidthProp::A  },
	{ 0x0025a3, WidthProp::N  },
	{ 0x0025aa, WidthProp::A  },
	{ 0x0025b2, WidthProp::N  },
	{ 0x0025b4, WidthProp::A  },
	{ 0x0025b6, WidthProp::N  },
	{ 0x0025b8, WidthProp::A  },
	{ 0x0025bc, WidthProp::N  },
	{ 0x0025be, WidthProp::A  },
	{ 0x0025c0, WidthProp::N  },
	{ 0x0025c2, WidthProp::A  },
	{ 0x0025c6, WidthProp::N  },
	{ 0x0025c9, WidthProp::A  },
	{ 0x0025cb, WidthProp::N  },
	{ 0x0025cc, WidthProp::A  },
	{ 0x0025ce, WidthProp::N  },
	{ 0x0025d2, WidthProp::A  },
	{ 0x0025e2, WidthProp::N  },
	{ 0x0025e6, WidthProp::A  },
	{ 0x0025ef, WidthProp::N  },
	{ 0x0025f0, WidthProp::A  },
	{ 0x002605, WidthProp::N  },
	{ 0x002607, WidthProp::A  },
	{ 0x002609, WidthProp::N  },
	{ 0x00260a, WidthProp::A  },
	{ 0x00260e, WidthProp::N  },
	{ 0x002610, WidthProp::A  },
	{ 0x002614, WidthProp::N  },
	{ 0x002616, WidthProp::A  },
	{ 0x00261c, WidthProp::N  },
	{ 0x00261d, WidthProp::A  },
	{ 0x00261e, WidthProp::N  },
	{ 0x00261f, WidthProp::A  },
	{ 0x002640, WidthProp::N  },
	{ 0x002641, WidthProp::A  },
	{ 0x002642, WidthProp::N  },
	{ 0x002643, WidthProp::A  },
	{ 0x002660, WidthProp::N  },
	{ 0x002662, WidthProp::A  },
	{ 0x002663, WidthProp::N  },
	{ 0x002666, WidthProp::A  },
	{ 0x002667, WidthProp::N  },
	{ 0x00266b, WidthProp::A  },
	{ 0x00266c, WidthProp::N  },
	{ 0x00266e, WidthProp::A  },
	{ 0x00266f, WidthProp::N  },
	{ 0x002670, WidthProp::A  },
	{ 0x00269e, WidthProp::N  },
	{ 0x0026a0, WidthProp::A  },
	{ 0x0026be, WidthProp::N  },
	{ 0x0026c0, WidthProp::A  },
	{ 0x0026c4, WidthProp::N  },
	{ 0x0026ce, WidthProp::A  },
	{ 0x0026cf, WidthProp::N  },
	{ 0x0026e2, WidthProp::A  },
	{ 0x0026e3, WidthProp::N  },
	{ 0x0026e4, WidthProp::A  },
	{ 0x0026e8, WidthProp::N  },
	{ 0x002700, WidthProp::A  },
	{ 0x00273d, WidthProp::N  },
	{ 0x00273e, WidthProp::A  },
	{ 0x002757, WidthProp::N  },
	{ 0x002758, WidthProp::A  },
	{ 0x002776, WidthProp::N  },
	{ 0x002780, WidthProp::A  },
	{ 0x0027e6, WidthProp::N  },
	{ 0x0027ee, WidthProp::Na },
	{ 0x002985, WidthProp::N  },
	{ 0x002987, WidthProp::Na },
	{ 0x002b55, WidthProp::N  },
	{ 0x002b5a, WidthProp::A  },
	{ 0x002e80, WidthProp::N  },
	{ 0x003000, WidthProp::W  },
	{ 0x003001, WidthProp::F  },
	{ 0x00303f, WidthProp::W  },
	{ 0x003041, WidthProp::N  },
	{ 0x003248, WidthProp::W  },
	{ 0x003250, WidthProp::A  },
	{ 0x004dc0, WidthProp::W  },
	{ 0x004e00, WidthProp::N  },
	{ 0x00a4d0, WidthProp::W  },
	{ 0x00a960, WidthProp::N  },
	{ 0x00a980, WidthProp::W  },
	{ 0x00ac00, WidthProp::N  },
	{ 0x00d7b0, WidthProp::W  },
	{ 0x00e000, WidthProp::N  },
	{ 0x00f900, WidthProp::A  },
	{ 0x00fb00, WidthProp::W  },
	{ 0x00fe00, WidthProp::N  },
	{ 0x00fe10, WidthProp::A  },
	{ 0x00fe20, WidthProp::W  },
	{ 0x00fe30, WidthProp::N  },
	{ 0x00fe70, WidthProp::W  },
	{ 0x00ff01, WidthProp::N  },
	{ 0x00ff61, WidthProp::F  },
	{ 0x00ffe0, WidthProp::H  },
	{ 0x00ffe8, WidthProp::F  },
	{ 0x00fff9, WidthProp::H  },
	{ 0x00fffd, WidthProp::N  },
	{ 0x010000, WidthProp::A  },
	{ 0x01b000, WidthProp::N  },
	{ 0x01bc00, WidthProp::W  },
	{ 0x01f100, WidthProp::N  },
	{ 0x01f10b, WidthProp::A  },
	{ 0x01f110, WidthProp::N  },
	{ 0x01f12e, WidthProp::A  },
	{ 0x01f130, WidthProp::N  },
	{ 0x01f16a, WidthProp::A  },
	{ 0x01f170, WidthProp::N  },
	{ 0x01f1e6, WidthProp::A  },
	{ 0x01f200, WidthProp::N  },
	{ 0x01f300, WidthProp::W  },
	{ 0x020000, WidthProp::N  },
	{ 0x0e0001, WidthProp::W  },
	{ 0x0e0100, WidthProp::N  },
	{ 0x10fffe, WidthProp::A  },
	{ 0x000000, WidthProp::N  },
};

}
