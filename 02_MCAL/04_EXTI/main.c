#include





void ahmed (void)
{
	/*Pin A2 High			*/
	MGPIO_voidSetPinValue(GPIOA , PIN2 , HIGH );
	/*Delay for 1 Sec		*/ 
	MSTK_voidSetBusyWait( 1000000 );
	
	/*Pin A2 Low			*/
	MGPIO_voidSetPinValue(GPIOA , PIN2 , LOW );
	/*Delay for 1 Sec		*/ 
	MSTK_voidSetBusyWait( 1000000 );
	
}
void atia (void)
{
	/*Pin A2 High			*/
	MGPIO_voidSetPinValue(GPIOA , PIN3 , HIGH );
	/*Delay for 1 Sec		*/ 
	MSTK_voidSetBusyWait( 1000000 );
	
	/*Pin A2 Low			*/
	MGPIO_voidSetPinValue(GPIOA , PIN3 , LOW );
	/*Delay for 1 Sec		*/ 
	MSTK_voidSetBusyWait( 1000000 );
	
}

int main(void)
{
	/*RCC								*/
	MRCC_voidInitSysClock(void);
	/*RCC AFIO							*/
	MRCC_voidEnablePeripheralClock(APB2 , 0);
	
	MRCC_voidEnablePeripheralClock(APB2 , GPIOA);
	MEXTI_voidSetCallBack(ahmed);
	MEXTI_voidSetCallBack(atia);
	
	/**		GPIO Direction	**/
	/*		A0 = input =====> PULL UP Resistor	*/
	MGPIO_voidSetPinDirection(GPIOA , PIN0 , INPUT_PULLUP_DOWN);
	MGPIO_voidSetPinValue(GPIOA , PIN0 ,HIGH );

	MGPIO_voidSetPinDirection(GPIOA , PIN1 , INPUT_PULLUP_DOWN);
	MGPIO_voidSetPinValue(GPIOA , PIN1 ,HIGH );
	/**	A2 ======> OUTPUT  SPEED 2MHZ PUSH PULL 	*/
	MGPIO_voidSetPinDirection(GPIOA , PIN2 , OUTPUT_SPEED_2MHZ_PP);	
	MGPIO_voidSetPinDirection(GPIOA , PIN3 , OUTPUT_SPEED_2MHZ_PP);	
		
	MEXTI_voidInit();
	MEXTI_voidSetSignalLatch(EXTI_LINE0 , FALLING_EDGE);
	MEXTI_voidSetSignalLatch(EXTI_LINE1 , FALLING_EDGE);
		
	MNVIC_voidSetPriority(6 , 2);
	MNVIC_voidSetPriority(7 , 1);
	MNVIC_voidEnableInterrupt(6);
	MNVIC_voidEnableInterrupt(7);
	//MNVIC_voidSetPendingFlag(6);
	
	while(1);
	
	return 0;
}












