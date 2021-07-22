#pragma once
#include "cpu.h"

// op_code b[31:26] 
#define J			0x2
#define BNE		0x5
#define ADDIU 0x9
#define ORI 	0xD
#define LUI 	0xF
#define COP_0	0x10
#define SW 		0x2B

// op_code b[0:5]
#define SLL 	0x0
#define OR		0x25

// cop0_op
#define MTC0 0x4
