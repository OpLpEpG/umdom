# Description

   bluepill stm32F103 128MB module, 
   Zephyr OS, 
   module canopennode, 
   shell, 
sensors:
   BME280
   AM2320
   BH1750 
analog:
   ACS712 measure 50Hz current    
can:
   TJA1050 

## Pinout
1. LED  
```
  PC13
```
2. CAN
```
   RD - PA11
   TD - PA12
```
3. I2C
```
   I2C_1 
    SCL - PB8
    SDA - PB9
   I2C_2 
    SCL - PB10
    SDA - PB11
```
4. Serial 1 (debug console)
```
   TX - PA9
   RX - PA10
```
5. Analog inputs 10   
```
   PA0-PA7
   PB0-PB1
```
6. GPIO (3v) 
```
    PA0-PA7 (shared with Analog inputs)

    PB0 (shared with Analog inputs)
    PB1 (shared with Analog inputs)
    PB5

    PC14 (default output)
    PC15 (default output)
```
7. GPIO (5v tolerant) 12 cnt. 
```
    PB3
    PB4
    PB6  
    PB7
    PB12 - PB15 (default input)

    PA8
    PA9  (Serial 1 (console))
    PA10 (Serial 1 (console))
    PA15
```
8. SWD 
```
    PA13 - SWDIO
    PA14 - SWCLK
```
9. RESERV
```
   PB2 - BOOT1
```

## Sensors
```
   BME280 - Zephyr sensor driver
   AM2320
   BH1750 - 4lux resolution L
```   

## ADC 
```
   from ACS712 measure 50Hz amplitude, least squares method
   multichanel scan mode, DMA, timer trigger 50ms - 4 times per period   
```   

## patch Zephyr OS module canopennode CO_TIME.h to use last version EDSEditor

Add  timeOfDay_t TIME_OF_DAY TIME_DIFFERENCE
before "TIME producer and consumer object."

```
.............
  #ifndef timeOfDay_t  
  typedef union {  
   unsigned long long ullValue;  
   struct {  
   unsigned long ms : 28;  
   unsigned reserved : 4;  
   unsigned days : 16;  
   unsigned reserved2 : 16;  
   };  
  } timeOfDay_t;  
  #endif  
     
  typedef timeOfDay_t TIME_OF_DAY;  
  typedef timeOfDay_t TIME_DIFFERENCE;  

/**
 * TIME producer and consumer object.
 */
typedef struct{
    CO_EM_t            *em;             /**< From CO_TIME_init() */
    uint8_t            *operatingState; /**< From CO_TIME_init() */
..........

```
