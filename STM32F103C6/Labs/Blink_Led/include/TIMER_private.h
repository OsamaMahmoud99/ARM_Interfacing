/************************************************************************/
/*  Author  : OsamaMahmoud                                              */
/*  Date    : 4/10/2020                                                 */
/************************************************************************/
#ifndef TIMER_PRIVATE_H
#define TIMER_PRIVATE_H

/* Array of pointer to address of each timer */
volatile u32 *TIM[TIMER_NUMBER]=
{
	(volatile u32*)0x40012C00,
	(volatile u32*)(0x40000000),
	(volatile u32*)(0x40000400),
	(volatile u32*)(0x40000800)
};

/* offset of each register */
#define    CR1    0
#define    CR2    1
#define    SMCR   2
#define    DIER   3
#define    SR     4
#define    EGR    5
#define    CCMR1  6
#define    CCMR2  7
#define    CCER   8
#define    CNT    9
#define    PSC    10
#define    ARR    11
#define    RCR    12
#define    CCR1   13
#define    CCR2   14
#define    CCR3   15
#define    CCR4   16
#define    BDTR   17
#define    DCR    18
#define    DMAR   19


#endif
