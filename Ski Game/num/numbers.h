/*

  Numbers.h --- this is with the 8x8 font for the numbers!
				and the head of the character (for lives at the bottom of the screen)


*/

#define  n_WIDTH   8
#define  n_HEIGHT  8

#define  head_WIDTH   8
#define  head_HEIGHT  8


const u16 headData[] = {
                    0x6200, 0x6362, 0x6363, 0x0000, 0x6362, 0x6363, 0x6262, 0x0063, 0x2A00, 0x1C2A,
                    0x1C1C, 0x0000, 0x5D32, 0x0B0B, 0x0B5D, 0x0032, 0x0B31, 0x1C0B, 0x0B0B, 0x0031,
                    0x2A31, 0x172A, 0x1C1C, 0x0031, 0x2631, 0x232A, 0x1C1C, 0x0031, 0x3131, 0x2A26,
                    0x311C, 0x0031,};

const u16 n0Data[] = {
                    0x8E00, 0x3B3B, 0x8E3B, 0x0000, 0x3B8E, 0x8E3B, 0x3B3B, 0x008E, 0x3B8E, 0x8E3B,
                    0x3B3B, 0x008E, 0x3B8E, 0x8E3B, 0x3B3B, 0x008E, 0x3B8E, 0x8E3B, 0x3B3B, 0x008E,
                    0x3B8E, 0x8E3B, 0x3B3B, 0x008E, 0x3B8E, 0x8E3B, 0x3B3B, 0x008E, 0x8E00, 0x3B3B,
                    0x8E3B, 0x0000,};
const u16 n9Data[] = {
                    0x8E00, 0x3B3B, 0x8E3B, 0x0000, 0x3B8E, 0x8E3B, 0x3B3B, 0x008E, 0x3B8E, 0x8E3B,
                    0x3B3B, 0x008E, 0x3B8E, 0x8E3B, 0x3B3B, 0x008E, 0x8E00, 0x3B3B, 0x3B3B, 0x008E,
                    0x0000, 0x8E8E, 0x3B3B, 0x008E, 0x3B8E, 0x8E3B, 0x3B3B, 0x008E, 0x8E00, 0x3B3B,
                    0x8E3B, 0x0000,};
const u16 n8Data[] = {
                    0x8E00, 0x3B3B, 0x8E3B, 0x0000, 0x3B8E, 0x8E3B, 0x3B3B, 0x008E, 0x3B8E, 0x8E3B,
                    0x3B3B, 0x008E, 0x8E00, 0x3B3B, 0x8E3B, 0x0000, 0x3B8E, 0x8E3B, 0x3B3B, 0x008E,
                    0x3B8E, 0x8E3B, 0x3B3B, 0x008E, 0x3B8E, 0x8E3B, 0x3B3B, 0x008E, 0x8E00, 0x3B3B,
                    0x8E3B, 0x0000,};

const u16 n7Data[] = {
                    0x3B8E, 0x3B3B, 0x3B3B, 0x008E, 0x8E00, 0x8E8E, 0x3B3B, 0x008E, 0x0000, 0x3B8E,
                    0x8E3B, 0x0000, 0x0000, 0x3B8E, 0x8E3B, 0x0000, 0x8E00, 0x3B3B, 0x008E, 0x0000,
                    0x8E00, 0x3B3B, 0x008E, 0x0000, 0x8E00, 0x3B3B, 0x008E, 0x0000, 0x8E00, 0x3B3B,
                    0x008E, 0x0000,};

const u16 n6Data[] = {
                    0x8E00, 0x3B3B, 0x8E3B, 0x0000, 0x3B8E, 0x8E3B, 0x3B3B, 0x008E, 0x3B8E, 0x8E3B,
                    0x008E, 0x0000, 0x3B8E, 0x3B3B, 0x8E3B, 0x0000, 0x3B8E, 0x8E3B, 0x3B3B, 0x008E,
                    0x3B8E, 0x8E3B, 0x3B3B, 0x008E, 0x3B8E, 0x8E3B, 0x3B3B, 0x008E, 0x8E00, 0x3B3B,
                    0x8E3B, 0x0000,};

const u16 n5Data[] = {
                    0x8E00, 0x3B3B, 0x3B3B, 0x008E, 0x8E00, 0x3B3B, 0x8E8E, 0x0000, 0x3B8E, 0x8E3B,
                    0x0000, 0x0000, 0x3B8E, 0x3B3B, 0x8E3B, 0x0000, 0x3B8E, 0x8E8E, 0x3B3B, 0x008E,
                    0x8E00, 0x8E8E, 0x3B3B, 0x008E, 0x3B8E, 0x8E3B, 0x3B3B, 0x008E, 0x8E00, 0x3B3B,
                    0x8E3B, 0x0000,};

const u16 n4Data[] = {
                    0x0000, 0x8E00, 0x3B3B, 0x008E, 0x0000, 0x3B8E, 0x3B3B, 0x008E, 0x8E00, 0x8E3B,
                    0x3B3B, 0x008E, 0x8E00, 0x8E3B, 0x3B3B, 0x008E, 0x3B8E, 0x8E8E, 0x3B3B, 0x008E,
                    0x3B8E, 0x3B3B, 0x3B3B, 0x8E3B, 0x8E00, 0x8E8E, 0x3B3B, 0x008E, 0x0000, 0x8E00,
                    0x3B3B, 0x008E,};

const u16 n3Data[] = {
                    0x8E00, 0x3B3B, 0x8E3B, 0x0000, 0x3B8E, 0x8E3B, 0x3B3B, 0x008E, 0x8E00, 0x8E8E,
                    0x3B3B, 0x008E, 0x0000, 0x3B8E, 0x8E3B, 0x0000, 0x0000, 0x8E00, 0x3B3B, 0x008E,
                    0x8E00, 0x8E8E, 0x3B3B, 0x008E, 0x3B8E, 0x8E3B, 0x3B3B, 0x008E, 0x0000, 0x3B3B,
                    0x8E3B, 0x0000,};

const u16 n2Data[] = {
                    0x8E00, 0x3B3B, 0x8E3B, 0x0000, 0x3B8E, 0x8E3B, 0x3B3B, 0x008E, 0x8E00, 0x8E8E,
                    0x3B3B, 0x008E, 0x0000, 0x8E00, 0x3B3B, 0x008E, 0x0000, 0x3B8E, 0x8E3B, 0x0000,
                    0x8E00, 0x3B3B, 0x008E, 0x0000, 0x3B8E, 0x8E3B, 0x8E8E, 0x0000, 0x3B8E, 0x3B3B,
                    0x3B3B, 0x008E,};

const u16 n1Data[] = {
                    0x0000, 0x3B8E, 0x3B3B, 0x008E, 0x8E00, 0x3B3B, 0x3B3B, 0x008E, 0x3B8E, 0x8E3B,
                    0x3B3B, 0x008E, 0x8E8E, 0x8E8E, 0x3B3B, 0x008E, 0x0000, 0x8E00, 0x3B3B, 0x008E,
                    0x0000, 0x8E00, 0x3B3B, 0x008E, 0x0000, 0x8E00, 0x3B3B, 0x008E, 0x0000, 0x8E00,
                    0x3B3B, 0x008E,};
