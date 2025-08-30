
#include "debug.h"
/* Define LED pin */
#define LED_PORT    GPIOB
#define LED_PIN     GPIO_Pin_1
#define LED_CLOCK   RCC_APB2Periph_GPIOB

/* UART Configuration */
#define UART_PORT       USART1
#define UART_TX_PIN     GPIO_Pin_9
#define UART_RX_PIN     GPIO_Pin_10
#define UART_GPIO_PORT  GPIOA
#define UART_CLOCK      RCC_APB2Periph_USART1
#define UART_GPIO_CLOCK RCC_APB2Periph_GPIOA

/* Command definitions */
#define CMD_LED_ON      0xAA    // Command to turn LED ON
#define CMD_LED_OFF     0xBB    // Command to turn LED OFF

/**
 * Initialize GPIO for LED control
 */
void GPIO_LED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(LED_CLOCK, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = LED_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED_PORT, &GPIO_InitStructure);
    
    // Ensure LED starts in OFF state (active-low LED)
    GPIO_SetBits(LED_PORT, LED_PIN);
}

/**
 * Initialize UART for serial communication
 */
void UART_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    
    RCC_APB2PeriphClockCmd(UART_CLOCK | UART_GPIO_CLOCK, ENABLE);
    
    // Configure TX pin
    GPIO_InitStructure.GPIO_Pin = UART_TX_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(UART_GPIO_PORT, &GPIO_InitStructure);
    
    // Configure RX pin
    GPIO_InitStructure.GPIO_Pin = UART_RX_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(UART_GPIO_PORT, &GPIO_InitStructure);
    
    // Configure UART parameters
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(UART_PORT, &USART_InitStructure);
    
    // Enable UART
    USART_Cmd(UART_PORT, ENABLE);
}

/**
 * Receive a byte from UART
 * @return Received byte
 */
uint8_t UART_ReceiveByte(void)
{
    while(USART_GetFlagStatus(UART_PORT, USART_FLAG_RXNE) == RESET);
    return USART_ReceiveData(UART_PORT);
}

/**
 * Send a string through UART
 * @param str String to send
 */
void UART_SendString(char *str)
{
    while(*str)
    {
        USART_SendData(UART_PORT, *str++);
        while(USART_GetFlagStatus(UART_PORT, USART_FLAG_TXE) == RESET);
    }
}

/**
 * Main program entry
 */
int main(void)
{
    uint8_t receivedByte;
    
    // Initialize the system
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    SystemCoreClockUpdate();
    
    // Initialize peripherals
    GPIO_LED_Init();  // Initialize LED (OFF state)
    UART_Init();      // Initialize UART communication
    
    // Send welcome message
    UART_SendString("LED Control: Send 0xAA (170) to turn ON, 0xBB (187) to turn OFF\r\n");
    UART_SendString("LED is currently OFF\r\n");
    
    // Main loop
    while(1)
    {
        // Wait for and receive a byte
        receivedByte = UART_ReceiveByte();
        
        // Display received byte for debugging
        UART_SendString("Received byte: ");
        char buffer[10];
        sprintf(buffer, "%d", receivedByte);
        UART_SendString(buffer);
        UART_SendString("\r\n");
        
        // Process received command
        if(receivedByte == CMD_LED_ON)
        {
            // Turn LED ON (active-low LED)
            GPIO_ResetBits(LED_PORT, LED_PIN);
            UART_SendString("LED turned ON\r\n");
        }
        else if(receivedByte == CMD_LED_OFF)
        {
            // Turn LED OFF (active-low LED)
            GPIO_SetBits(LED_PORT, LED_PIN);
            UART_SendString("LED turned OFF\r\n");
        }
    }
}