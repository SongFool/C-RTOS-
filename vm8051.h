#include "stdint.h"
typedef struct{
    uint8_t iram[256];
    uint8_t sfr[128];
    uint8_t xram[65535];
    uint8_t code[65535];
    uint8_t IR[4];
    uint16_t pc;
}vm8051_t;

/*
bit7 CY   进位 / 借位
bit6 AC   半进位（BCD）
bit5 F0   用户标志
bit4 RS1  寄存器组选择
bit3 RS0
bit2 OV   溢出
bit1 -    保留
bit0 P    奇偶校验      A 寄存器的奇偶校验
*/

#define SFR_ADDR(a) ((a) - 0x80)   //0x80固定的
#define ACC     SFR_ADDR(0xE0)     //累加器
#define BREG    SFR_ADDR(0xF0)      //辅助运算寄存器
#define PSW     SFR_ADDR(0xD0)      //标志寄存器
#define SP      SFR_ADDR(0x81)      //堆栈指针
#define DPL     SFR_ADDR(0x82)      //数据指针寄存器低位
#define DPH     SFR_ADDR(0x83)      //数据指针寄存器高位

static inline uint8_t *reg_r(vm8051_t *vm, int n)
{
    uint8_t bank = (vm->sfr[PSW] >> 3) & 0x03;
    return &vm->iram[bank * 8 + n];
}
