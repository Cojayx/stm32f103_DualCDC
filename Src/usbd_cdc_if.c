/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : usbd_cdc_if.c
  * @version        : v2.0_Cube
  * @brief          : Usb device for Virtual Com Port.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "usbd_cdc_if.h"

/* USER CODE BEGIN INCLUDE */

/* USER CODE END INCLUDE */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
  * @brief Usb device library.
  * @{
  */

/** @addtogroup USBD_CDC_IF
  * @{
  */

/** @defgroup USBD_CDC_IF_Private_TypesDefinitions USBD_CDC_IF_Private_TypesDefinitions
  * @brief Private types.
  * @{
  */

/* USER CODE BEGIN PRIVATE_TYPES */

/* USER CODE END PRIVATE_TYPES */

/**
  * @}
  */

/** @defgroup USBD_CDC_IF_Private_Defines USBD_CDC_IF_Private_Defines
  * @brief Private defines.
  * @{
  */

/* USER CODE BEGIN PRIVATE_DEFINES */
/* Define size for the receive and transmit buffer over CDC */
/* It's up to user to redefine and/or remove those define */
#define APP_RX_DATA_SIZE  1000
#define APP_TX_DATA_SIZE  1000
/* USER CODE END PRIVATE_DEFINES */

/**
  * @}
  */

/** @defgroup USBD_CDC_IF_Private_Macros USBD_CDC_IF_Private_Macros
  * @brief Private macros.
  * @{
  */

/* USER CODE BEGIN PRIVATE_MACRO */

/* USER CODE END PRIVATE_MACRO */

/**
  * @}
  */

/** @defgroup USBD_CDC_IF_Private_Variables USBD_CDC_IF_Private_Variables
  * @brief Private variables.
  * @{
  */
/* Create buffer for reception and transmission           */
/* It's up to user to redefine and/or remove those define */
/** Received data over USB are stored in this buffer      */
uint8_t UserRxBufferFS[APP_RX_DATA_SIZE];

/** Data to send over USB CDC are stored in this buffer   */
uint8_t UserTxBufferFS[APP_TX_DATA_SIZE];

/* USER CODE BEGIN PRIVATE_VARIABLES */

/* USER CODE END PRIVATE_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_CDC_IF_Exported_Variables USBD_CDC_IF_Exported_Variables
  * @brief Public variables.
  * @{
  */

extern USBD_HandleTypeDef hUsbDeviceFS;

/* USER CODE BEGIN EXPORTED_VARIABLES */
USBD_CDC_LineCodingTypeDef usb_line_coding={
  115200, /* Baud rate        : 115200 */
  0,      /* Stop bits        : 1      */
  0,      /* Parity           : None   */
  8       /* Number Data bits : 8      */
};

#define USB_BUFF_SIZE 1024
struct usb_fifo_t{
  unsigned char buff[USB_BUFF_SIZE];
  volatile unsigned short fi,fo;
};
struct usb_fifo_t usb_fifo;

/* USER CODE END EXPORTED_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_CDC_IF_Private_FunctionPrototypes USBD_CDC_IF_Private_FunctionPrototypes
  * @brief Private functions declaration.
  * @{
  */

static int8_t CDC_Init_FS(void);
static int8_t CDC_DeInit_FS(void);
static int8_t CDC_Control_FS(uint8_t cmd, uint8_t* pbuf, uint16_t length);
static int8_t CDC_Receive_FS(uint8_t* pbuf, uint32_t *Len);

/* USER CODE BEGIN PRIVATE_FUNCTIONS_DECLARATION */

/* USER CODE END PRIVATE_FUNCTIONS_DECLARATION */

/**
  * @}
  */

USBD_CDC_ItfTypeDef USBD_Interface_fops_FS =
{
  CDC_Init_FS,
  CDC_DeInit_FS,
  CDC_Control_FS,
  CDC_Receive_FS
};

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Initializes the CDC media low layer over the FS USB IP
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Init_FS(void)
{
  usb_printk("=>CDC_Init_FS\r\n",15);
  /* USER CODE BEGIN 3 */
  /* Set Application Buffers */
  USBD_CDC_SetTxBuffer(&hUsbDeviceFS, UserTxBufferFS, 0);
  USBD_CDC_SetRxBuffer(&hUsbDeviceFS, UserRxBufferFS);
  usb_fifo.fi = usb_fifo.fo = 0;
  return (USBD_OK);
  /* USER CODE END 3 */
}

/**
  * @brief  DeInitializes the CDC media low layer
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_DeInit_FS(void)
{
  usb_printk("=>CDC_DeInit_FS\r\n",17);
  /* USER CODE BEGIN 4 */
  return (USBD_OK);
  /* USER CODE END 4 */
}

/**
  * @brief  Manage the CDC class requests
  * @param  cmd: Command code
  * @param  pbuf: Buffer containing command data (request parameters)
  * @param  length: Number of data to be sent (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Control_FS(uint8_t cmd, uint8_t* pbuf, uint16_t length)
{
  /* USER CODE BEGIN 5 */
  USBD_CDC_LineCodingTypeDef *line_coding;
  usb_printk("=>CDC_Control_FS[cmd=",21);
  usb_printf("%x]\r\n", cmd);
  switch(cmd)
  {
    case CDC_SEND_ENCAPSULATED_COMMAND:
    usb_printk("->CDC_SEND_ENCAPSULATED_COMMAND\r\n",33);

    break;

    case CDC_GET_ENCAPSULATED_RESPONSE:
    usb_printk("->CDC_GET_ENCAPSULATED_RESPONSE\r\n",33);

    break;

    case CDC_SET_COMM_FEATURE:
    usb_printk("->CDC_SET_COMM_FEATURE\r\n",24);

    break;

    case CDC_GET_COMM_FEATURE:
    usb_printk("->CDC_GET_COMM_FEATURE\r\n",24);

    break;

    case CDC_CLEAR_COMM_FEATURE:
    usb_printk("->CDC_CLEAR_COMM_FEATURE\r\n",26);

    break;

  /*******************************************************************************/
  /* Line Coding Structure                                                       */
  /*-----------------------------------------------------------------------------*/
  /* Offset | Field       | Size | Value  | Description                          */
  /* 0      | dwDTERate   |   4  | Number |Data terminal rate, in bits per second*/
  /* 4      | bCharFormat |   1  | Number | Stop bits                            */
  /*                                        0 - 1 Stop bit                       */
  /*                                        1 - 1.5 Stop bits                    */
  /*                                        2 - 2 Stop bits                      */
  /* 5      | bParityType |  1   | Number | Parity                               */
  /*                                        0 - None                             */
  /*                                        1 - Odd                              */
  /*                                        2 - Even                             */
  /*                                        3 - Mark                             */
  /*                                        4 - Space                            */
  /* 6      | bDataBits  |   1   | Number Data bits (5, 6, 7, 8 or 16).          */
  /*******************************************************************************/
    case CDC_SET_LINE_CODING:
    usb_printk("->CDC_SET_LINE_CODING\r\n",23);
    line_coding = (USBD_CDC_LineCodingTypeDef *)pbuf;

    usb_line_coding.bitrate    = line_coding->bitrate;
    usb_line_coding.format     = line_coding->format;
    usb_line_coding.paritytype = line_coding->paritytype;
    usb_line_coding.datatype   = line_coding->datatype;
    break;

    case CDC_GET_LINE_CODING:
    usb_printk("->CDC_GET_LINE_CODING\r\n",23);
    line_coding = &usb_line_coding;
    pbuf[0] = (uint8_t)(line_coding->bitrate);
    pbuf[1] = (uint8_t)(line_coding->bitrate >> 8);
    pbuf[2] = (uint8_t)(line_coding->bitrate >> 16);
    pbuf[3] = (uint8_t)(line_coding->bitrate >> 24);
    pbuf[4] = line_coding->format;
    pbuf[5] = line_coding->paritytype;
    pbuf[6] = line_coding->datatype;

    break;

    case CDC_SET_CONTROL_LINE_STATE:
    usb_printk("->CDC_SET_CONTROL_LINE_STATE\r\n",30);
//    usb_printf("%x %x %x %x %x %x %x\r\n", pbuf[0], pbuf[1], pbuf[2], pbuf[3]
//                                         , pbuf[4], pbuf[5], pbuf[6]);

    break;

    case CDC_SEND_BREAK:
    usb_printk("->CDC_SEND_BREAK\r\n",18);

    break;

  default:
    break;
  }

  return (USBD_OK);
  /* USER CODE END 5 */
}

/**
  * @brief  Data received over USB OUT endpoint are sent over CDC interface
  *         through this function.
  *
  *         @note
  *         This function will block any OUT packet reception on USB endpoint
  *         untill exiting this function. If you exit this function before transfer
  *         is complete on CDC interface (ie. using DMA controller) it will result
  *         in receiving more data while previous ones are still not sent.
  *
  * @param  Buf: Buffer of data to be received
  * @param  Len: Number of data received (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Receive_FS(uint8_t* Buf, uint32_t *Len)
{
  usb_printk("=>CDC_Receive_FS\r\n",18);
  /* USER CODE BEGIN 6 */

  if(usb_fifo.fi + *Len <= USB_BUFF_SIZE){
    memcpy(&usb_fifo.buff[usb_fifo.fi], Buf, *Len);
  } else{
    unsigned short l = USB_BUFF_SIZE-usb_fifo.fi;
    memcpy(&usb_fifo.buff[usb_fifo.fi], Buf, l);
    memcpy(&usb_fifo.buff[0], &Buf[l], *Len-l);
  }
  usb_fifo.fi = (usb_fifo.fi+*Len) % USB_BUFF_SIZE;

  USBD_CDC_SetRxBuffer(&hUsbDeviceFS, &Buf[0]);
  USBD_CDC_ReceivePacket(&hUsbDeviceFS);
  return (USBD_OK);
  /* USER CODE END 6 */
}

/**
  * @brief  CDC_Transmit_FS
  *         Data to send over USB IN endpoint are sent over CDC interface
  *         through this function.
  *         @note
  *
  *
  * @param  Buf: Buffer of data to be sent
  * @param  Len: Number of data to be sent (in bytes)
  * @retval USBD_OK if all operations are OK else USBD_FAIL or USBD_BUSY
  */
uint8_t CDC_Transmit_FS(uint8_t* Buf, uint16_t Len)
{
  uint8_t result = USBD_OK;
  usb_printk("=>CDC_Transmit_FS\r\n",19);
  /* USER CODE BEGIN 7 */
  USBD_CDC_HandleTypeDef *hcdc = (USBD_CDC_HandleTypeDef*)hUsbDeviceFS.pClassData;
  if (hcdc->TxState != 0){
    return USBD_BUSY;
  }
  USBD_CDC_SetTxBuffer(&hUsbDeviceFS, Buf, Len);
  result = USBD_CDC_TransmitPacket(&hUsbDeviceFS);
  /* USER CODE END 7 */
  return result;
}

/* USER CODE BEGIN PRIVATE_FUNCTIONS_IMPLEMENTATION */
int UsbDevRecvAvailableDataLen(void)
{
  int len = (usb_fifo.fi + USB_BUFF_SIZE - usb_fifo.fo) % USB_BUFF_SIZE;
  return len;
}

int UsbDevRecvs(unsigned char *buf, unsigned short want_len)
{
  int len;
  int fifo_len;

  fifo_len = (usb_fifo.fi + USB_BUFF_SIZE - usb_fifo.fo) % USB_BUFF_SIZE;
  len = (fifo_len>=want_len) ? want_len : fifo_len;
  if(len<=0)
    return 0;

  if(len>0){
    if(usb_fifo.fo+len <= USB_BUFF_SIZE){
      memcpy(buf, &usb_fifo.buff[usb_fifo.fo], len);
    } else{
      unsigned short l = USB_BUFF_SIZE-usb_fifo.fo;
      memcpy(buf, &usb_fifo.buff[usb_fifo.fo], l);
      memcpy(&buf[l], &usb_fifo.buff[0], l);
    }
    usb_fifo.fo = (usb_fifo.fo+len) % USB_BUFF_SIZE;
  }
  return len;
}

int UsbDevSends(unsigned char *buf, int len)
{
  return CDC_Transmit_FS(buf,len);
}

/* USER CODE END PRIVATE_FUNCTIONS_IMPLEMENTATION */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
