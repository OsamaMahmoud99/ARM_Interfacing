#ifndef LEDMRX_INTERFACE_H
#define LEDMRX_INTERFACE_H



void LEDMRX_voidDispaly(u8 *Copy_u8Data);
void LEDMRX_voidInit(void);
void LEDMRX_voidAnimation(u8 *Copy_u8Data);
void LEDMRX_voidAnimationFrames(u8 Copy_u8Frames[][8] , u8 Copy_u8FramesNum);
void LEDMRX_voidResumeAnimation(void);
void LEDMRX_voidStopAnimation(void);
void LEDMRX_voidSpeedUp(void);
void LEDMRX_voidSpeedDown(void);

#endif
