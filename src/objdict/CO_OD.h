// clang-format off
/*******************************************************************************
    CANopen Object Dictionary definition for CANopenNode v1 to v2

    This file was automatically generated with
    libedssharp Object Dictionary Editor v0.8-123-g6c02323-dirty

    https://github.com/CANopenNode/CANopenNode
    https://github.com/robincornelius/libedssharp

    DON'T EDIT THIS FILE MANUALLY !!!!
*******************************************************************************/
#ifndef CO_OD_H_
#define CO_OD_H_

/*******************************************************************************
   CANopen DATA TYPES
*******************************************************************************/
   typedef bool_t       BOOLEAN;
   typedef uint8_t      UNSIGNED8;
   typedef uint16_t     UNSIGNED16;
   typedef uint32_t     UNSIGNED32;
   typedef uint64_t     UNSIGNED64;
   typedef int8_t       INTEGER8;
   typedef int16_t      INTEGER16;
   typedef int32_t      INTEGER32;
   typedef int64_t      INTEGER64;
   typedef float32_t    REAL32;
   typedef float64_t    REAL64;
   typedef char_t       VISIBLE_STRING;
   typedef oChar_t      OCTET_STRING;

   #ifdef DOMAIN
   #undef DOMAIN
   #endif

   typedef domain_t     DOMAIN;


/*******************************************************************************
   FILE INFO:
      FileName:     base4.xdd
      FileVersion:  1
      CreationTime: 2:52
      CreationDate: 09-18-2019
      CreatedBy:    
*******************************************************************************/


/*******************************************************************************
   DEVICE INFO:
      VendorName:     
      VendorNumber:   0
      ProductName:    Zephyr RTOS CANopen umdom
      ProductNumber:  0
*******************************************************************************/


/*******************************************************************************
   FEATURES
*******************************************************************************/
  #define CO_NO_SYNC                     1   //Associated objects: 1005-1007
  #define CO_NO_EMERGENCY                1   //Associated objects: 1014, 1015
  #define CO_NO_TIME                     1   //Associated objects: 1012, 1013
  #define CO_NO_SDO_SERVER               1   //Associated objects: 1200-127F
  #define CO_NO_SDO_CLIENT               0   //Associated objects: 1280-12FF
  #define CO_NO_GFC                      0   //Associated objects: 1300
  #define CO_NO_SRDO                     0   //Associated objects: 1301-1341, 1381-13C0
  #define CO_NO_LSS_SERVER               0   //LSS Slave
  #define CO_NO_LSS_CLIENT               0   //LSS Master
  #define CO_NO_RPDO                     4   //Associated objects: 14xx, 16xx
  #define CO_NO_TPDO                     7   //Associated objects: 18xx, 1Axx
  #define CO_NO_NMT_MASTER               0
  #define CO_NO_TRACE                    0


/*******************************************************************************
   OBJECT DICTIONARY
*******************************************************************************/
   #define CO_OD_NoOfElements             68


/*******************************************************************************
   TYPE DEFINITIONS FOR RECORDS
*******************************************************************************/
/*1018      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               UNSIGNED32     vendorID;
               UNSIGNED32     productCode;
               UNSIGNED32     revisionNumber;
               UNSIGNED32     serialNumber;
               }              OD_identity_t;
/*1026      */ typedef struct {
               UNSIGNED8      highestSubIndexSupported;
               UNSIGNED8      stdIn;
               UNSIGNED64     stdOut;
               }              OD_OSPrompt_t;
/*1200      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               UNSIGNED32     COB_IDClientToServer;
               UNSIGNED32     COB_IDServerToClient;
               }              OD_SDOServerParameter_t;
/*1400      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               UNSIGNED32     COB_IDUsedByRPDO;
               UNSIGNED8      transmissionType;
               }              OD_RPDOCommunicationParameter_t;
/*1600      */ typedef struct {
               UNSIGNED8      numberOfMappedObjects;
               UNSIGNED32     mappedObject1;
               UNSIGNED32     mappedObject2;
               UNSIGNED32     mappedObject3;
               UNSIGNED32     mappedObject4;
               UNSIGNED32     mappedObject5;
               UNSIGNED32     mappedObject6;
               UNSIGNED32     mappedObject7;
               UNSIGNED32     mappedObject8;
               }              OD_RPDOMappingParameter_t;
/*1800      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               UNSIGNED32     COB_IDUsedByTPDO;
               UNSIGNED8      transmissionType;
               UNSIGNED16     inhibitTime;
               UNSIGNED8      compatibilityEntry;
               UNSIGNED16     eventTimer;
               UNSIGNED8      SYNCStartValue;
               }              OD_TPDOCommunicationParameter_t;
/*1A00      */ typedef struct {
               UNSIGNED8      numberOfMappedObjects;
               UNSIGNED32     mappedObject1;
               UNSIGNED32     mappedObject2;
               UNSIGNED32     mappedObject3;
               UNSIGNED32     mappedObject4;
               UNSIGNED32     mappedObject5;
               UNSIGNED32     mappedObject6;
               UNSIGNED32     mappedObject7;
               UNSIGNED32     mappedObject8;
               }              OD_TPDOMappingParameter_t;
/*2001      */ typedef struct {
               UNSIGNED8      numberOfEntries;
               UNSIGNED8      NMT_BootEnable;
               UNSIGNED16     NMT_StartTime;
               }              OD_NMT_BootNetwork_t;
/*2002      */ typedef struct {
               UNSIGNED8      highestSubIndexSupported;
               VISIBLE_STRING port[5];
               UNSIGNED16     outputMask;
               UNSIGNED16     outputStartValue;
               UNSIGNED16     inputMask;
               UNSIGNED16     inputPullUp;
               UNSIGNED16     inputPullDown;
               UNSIGNED16     availableMask;
               }              OD_configPort_t;
/*2005      */ typedef struct {
               UNSIGNED8      highestSubIndexSupported;
               UNSIGNED16     cannelsMask;
               UNSIGNED16     availableMask;
               }              OD_configADC_t;
/*2006      */ typedef struct {
               UNSIGNED8      highestSubIndexSupported;
               UNSIGNED8      I2c;
               UNSIGNED8      addr;
               INTEGER16      lux;
               }              OD_BH1750_t;
/*200A      */ typedef struct {
               UNSIGNED8      highestSubIndexSupported;
               UNSIGNED8      I2c;
               UNSIGNED8      addr;
               INTEGER8       temp;
               INTEGER8       humid;
               }              OD_AM2320_t;
/*200C      */ typedef struct {
               UNSIGNED8      highestSubIndexSupported;
               UNSIGNED8      I2c;
               UNSIGNED8      addr;
               INTEGER8       temp;
               INTEGER8       humid;
               INTEGER16      press;
               }              OD_BME280_t;
/*2080      */ typedef struct {
               UNSIGNED8      highestSubIndexSupported;
               UNSIGNED16     inputMask;
               UNSIGNED16     outputMask;
               UNSIGNED16     state;
               UNSIGNED32     setReset;
               }              OD_GPIOPack_t;

/*******************************************************************************
   TYPE DEFINITIONS FOR OBJECT DICTIONARY INDEXES

   some of those are redundant with CO_SDO.h CO_ObjDicId_t <Common CiA301 object
   dictionary entries>
*******************************************************************************/
/*1000 */
        #define OD_1000_deviceType                                  0x1000

/*1001 */
        #define OD_1001_errorRegister                               0x1001

/*1002 */
        #define OD_1002_manufacturerStatusRegister                  0x1002

/*1003 */
        #define OD_1003_preDefinedErrorField                        0x1003

        #define OD_1003_0_preDefinedErrorField_maxSubIndex          0
        #define OD_1003_1_preDefinedErrorField_standardErrorField   1
        #define OD_1003_2_preDefinedErrorField_standardErrorField   2
        #define OD_1003_3_preDefinedErrorField_standardErrorField   3
        #define OD_1003_4_preDefinedErrorField_standardErrorField   4
        #define OD_1003_5_preDefinedErrorField_standardErrorField   5
        #define OD_1003_6_preDefinedErrorField_standardErrorField   6
        #define OD_1003_7_preDefinedErrorField_standardErrorField   7
        #define OD_1003_8_preDefinedErrorField_standardErrorField   8

/*1005 */
        #define OD_1005_COB_ID_SYNCMessage                          0x1005

/*1006 */
        #define OD_1006_communicationCyclePeriod                    0x1006

/*1007 */
        #define OD_1007_synchronousWindowLength                     0x1007

/*1008 */
        #define OD_1008_manufacturerDeviceName                      0x1008

/*1009 */
        #define OD_1009_manufacturerHardwareVersion                 0x1009

/*100A */
        #define OD_100A_manufacturerSoftwareVersion                 0x100A

/*1010 */
        #define OD_1010_storeParameters                             0x1010

        #define OD_1010_0_storeParameters_maxSubIndex               0
        #define OD_1010_1_storeParameters_saveAllParameters         1

/*1011 */
        #define OD_1011_restoreDefaultParameters                    0x1011

        #define OD_1011_0_restoreDefaultParameters_maxSubIndex      0
        #define OD_1011_1_restoreDefaultParameters_restoreAllDefaultParameters 1

/*1012 */
        #define OD_1012_COB_ID_TIME                                 0x1012

/*1014 */
        #define OD_1014_COB_ID_EMCY                                 0x1014

/*1015 */
        #define OD_1015_inhibitTimeEMCY                             0x1015

/*1016 */
        #define OD_1016_consumerHeartbeatTime                       0x1016

        #define OD_1016_0_consumerHeartbeatTime_maxSubIndex         0
        #define OD_1016_1_consumerHeartbeatTime_consumerHeartbeatTime 1
        #define OD_1016_2_consumerHeartbeatTime_consumerHeartbeatTime 2
        #define OD_1016_3_consumerHeartbeatTime_consumerHeartbeatTime 3
        #define OD_1016_4_consumerHeartbeatTime_consumerHeartbeatTime 4

/*1017 */
        #define OD_1017_producerHeartbeatTime                       0x1017

/*1018 */
        #define OD_1018_identity                                    0x1018

        #define OD_1018_0_identity_maxSubIndex                      0
        #define OD_1018_1_identity_vendorID                         1
        #define OD_1018_2_identity_productCode                      2
        #define OD_1018_3_identity_revisionNumber                   3
        #define OD_1018_4_identity_serialNumber                     4

/*1019 */
        #define OD_1019_synchronousCounterOverflowValue             0x1019

/*1026 */
        #define OD_1026_OSPrompt                                    0x1026

        #define OD_1026_0_OSPrompt_maxSubIndex                      0
        #define OD_1026_1_OSPrompt_stdIn                            1
        #define OD_1026_2_OSPrompt_stdOut                           2

/*1029 */
        #define OD_1029_errorBehavior                               0x1029

        #define OD_1029_0_errorBehavior_maxSubIndex                 0
        #define OD_1029_1_errorBehavior_communication               1
        #define OD_1029_2_errorBehavior_communicationOther          2
        #define OD_1029_3_errorBehavior_communicationPassive        3
        #define OD_1029_4_errorBehavior_generic                     4
        #define OD_1029_5_errorBehavior_deviceProfile               5
        #define OD_1029_6_errorBehavior_manufacturerSpecific        6

/*1200 */
        #define OD_1200_SDOServerParameter                          0x1200

        #define OD_1200_0_SDOServerParameter_maxSubIndex            0
        #define OD_1200_1_SDOServerParameter_COB_IDClientToServer   1
        #define OD_1200_2_SDOServerParameter_COB_IDServerToClient   2

/*1400 */
        #define OD_1400_RPDOCommunicationParameter                  0x1400

        #define OD_1400_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1400_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1400_2_RPDOCommunicationParameter_transmissionType 2

/*1401 */
        #define OD_1401_RPDOCommunicationParameter                  0x1401

        #define OD_1401_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1401_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1401_2_RPDOCommunicationParameter_transmissionType 2

/*1402 */
        #define OD_1402_RPDOCommunicationParameter                  0x1402

        #define OD_1402_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1402_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1402_2_RPDOCommunicationParameter_transmissionType 2

/*1403 */
        #define OD_1403_RPDOCommunicationParameter                  0x1403

        #define OD_1403_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1403_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1403_2_RPDOCommunicationParameter_transmissionType 2

/*1600 */
        #define OD_1600_RPDOMappingParameter                        0x1600

        #define OD_1600_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1600_1_RPDOMappingParameter_mappedObject1        1
        #define OD_1600_2_RPDOMappingParameter_mappedObject2        2
        #define OD_1600_3_RPDOMappingParameter_mappedObject3        3
        #define OD_1600_4_RPDOMappingParameter_mappedObject4        4
        #define OD_1600_5_RPDOMappingParameter_mappedObject5        5
        #define OD_1600_6_RPDOMappingParameter_mappedObject6        6
        #define OD_1600_7_RPDOMappingParameter_mappedObject7        7
        #define OD_1600_8_RPDOMappingParameter_mappedObject8        8

/*1601 */
        #define OD_1601_RPDOMappingParameter                        0x1601

        #define OD_1601_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1601_1_RPDOMappingParameter_mappedObject1        1
        #define OD_1601_2_RPDOMappingParameter_mappedObject2        2
        #define OD_1601_3_RPDOMappingParameter_mappedObject3        3
        #define OD_1601_4_RPDOMappingParameter_mappedObject4        4
        #define OD_1601_5_RPDOMappingParameter_mappedObject5        5
        #define OD_1601_6_RPDOMappingParameter_mappedObject6        6
        #define OD_1601_7_RPDOMappingParameter_mappedObject7        7
        #define OD_1601_8_RPDOMappingParameter_mappedObject8        8

/*1602 */
        #define OD_1602_RPDOMappingParameter                        0x1602

        #define OD_1602_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1602_1_RPDOMappingParameter_mappedObject1        1
        #define OD_1602_2_RPDOMappingParameter_mappedObject2        2
        #define OD_1602_3_RPDOMappingParameter_mappedObject3        3
        #define OD_1602_4_RPDOMappingParameter_mappedObject4        4
        #define OD_1602_5_RPDOMappingParameter_mappedObject5        5
        #define OD_1602_6_RPDOMappingParameter_mappedObject6        6
        #define OD_1602_7_RPDOMappingParameter_mappedObject7        7
        #define OD_1602_8_RPDOMappingParameter_mappedObject8        8

/*1603 */
        #define OD_1603_RPDOMappingParameter                        0x1603

        #define OD_1603_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1603_1_RPDOMappingParameter_mappedObject1        1
        #define OD_1603_2_RPDOMappingParameter_mappedObject2        2
        #define OD_1603_3_RPDOMappingParameter_mappedObject3        3
        #define OD_1603_4_RPDOMappingParameter_mappedObject4        4
        #define OD_1603_5_RPDOMappingParameter_mappedObject5        5
        #define OD_1603_6_RPDOMappingParameter_mappedObject6        6
        #define OD_1603_7_RPDOMappingParameter_mappedObject7        7
        #define OD_1603_8_RPDOMappingParameter_mappedObject8        8

/*1800 */
        #define OD_1800_TPDOCommunicationParameter                  0x1800

        #define OD_1800_0_TPDOCommunicationParameter_maxSubIndex    0
        #define OD_1800_1_TPDOCommunicationParameter_COB_IDUsedByTPDO 1
        #define OD_1800_2_TPDOCommunicationParameter_transmissionType 2
        #define OD_1800_3_TPDOCommunicationParameter_inhibitTime    3
        #define OD_1800_4_TPDOCommunicationParameter_compatibilityEntry 4
        #define OD_1800_5_TPDOCommunicationParameter_eventTimer     5
        #define OD_1800_6_TPDOCommunicationParameter_SYNCStartValue 6

/*1801 */
        #define OD_1801_TPDOCommunicationParameter                  0x1801

        #define OD_1801_0_TPDOCommunicationParameter_maxSubIndex    0
        #define OD_1801_1_TPDOCommunicationParameter_COB_IDUsedByTPDO 1
        #define OD_1801_2_TPDOCommunicationParameter_transmissionType 2
        #define OD_1801_3_TPDOCommunicationParameter_inhibitTime    3
        #define OD_1801_4_TPDOCommunicationParameter_compatibilityEntry 4
        #define OD_1801_5_TPDOCommunicationParameter_eventTimer     5
        #define OD_1801_6_TPDOCommunicationParameter_SYNCStartValue 6

/*1802 */
        #define OD_1802_TPDOCommunicationParameter                  0x1802

        #define OD_1802_0_TPDOCommunicationParameter_maxSubIndex    0
        #define OD_1802_1_TPDOCommunicationParameter_COB_IDUsedByTPDO 1
        #define OD_1802_2_TPDOCommunicationParameter_transmissionType 2
        #define OD_1802_3_TPDOCommunicationParameter_inhibitTime    3
        #define OD_1802_4_TPDOCommunicationParameter_compatibilityEntry 4
        #define OD_1802_5_TPDOCommunicationParameter_eventTimer     5
        #define OD_1802_6_TPDOCommunicationParameter_SYNCStartValue 6

/*1803 */
        #define OD_1803_TPDOCommunicationParameter                  0x1803

        #define OD_1803_0_TPDOCommunicationParameter_maxSubIndex    0
        #define OD_1803_1_TPDOCommunicationParameter_COB_IDUsedByTPDO 1
        #define OD_1803_2_TPDOCommunicationParameter_transmissionType 2
        #define OD_1803_3_TPDOCommunicationParameter_inhibitTime    3
        #define OD_1803_4_TPDOCommunicationParameter_compatibilityEntry 4
        #define OD_1803_5_TPDOCommunicationParameter_eventTimer     5
        #define OD_1803_6_TPDOCommunicationParameter_SYNCStartValue 6

/*1804 */
        #define OD_1804_TPDOCommunicationParameter                  0x1804

        #define OD_1804_0_TPDOCommunicationParameter_maxSubIndex    0
        #define OD_1804_1_TPDOCommunicationParameter_COB_IDUsedByTPDO 1
        #define OD_1804_2_TPDOCommunicationParameter_transmissionType 2
        #define OD_1804_3_TPDOCommunicationParameter_inhibitTime    3
        #define OD_1804_4_TPDOCommunicationParameter_compatibilityEntry 4
        #define OD_1804_5_TPDOCommunicationParameter_eventTimer     5
        #define OD_1804_6_TPDOCommunicationParameter_SYNCStartValue 6

/*1805 */
        #define OD_1805_TPDOCommunicationParameter                  0x1805

        #define OD_1805_0_TPDOCommunicationParameter_maxSubIndex    0
        #define OD_1805_1_TPDOCommunicationParameter_COB_IDUsedByTPDO 1
        #define OD_1805_2_TPDOCommunicationParameter_transmissionType 2
        #define OD_1805_3_TPDOCommunicationParameter_inhibitTime    3
        #define OD_1805_4_TPDOCommunicationParameter_compatibilityEntry 4
        #define OD_1805_5_TPDOCommunicationParameter_eventTimer     5
        #define OD_1805_6_TPDOCommunicationParameter_SYNCStartValue 6

/*1806 */
        #define OD_1806_TPDOCommunicationParameter                  0x1806

        #define OD_1806_0_TPDOCommunicationParameter_maxSubIndex    0
        #define OD_1806_1_TPDOCommunicationParameter_COB_IDUsedByTPDO 1
        #define OD_1806_2_TPDOCommunicationParameter_transmissionType 2
        #define OD_1806_3_TPDOCommunicationParameter_inhibitTime    3
        #define OD_1806_4_TPDOCommunicationParameter_compatibilityEntry 4
        #define OD_1806_5_TPDOCommunicationParameter_eventTimer     5
        #define OD_1806_6_TPDOCommunicationParameter_SYNCStartValue 6

/*1A00 */
        #define OD_1A00_TPDOMappingParameter                        0x1A00

        #define OD_1A00_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A00_1_TPDOMappingParameter_mappedObject1        1
        #define OD_1A00_2_TPDOMappingParameter_mappedObject2        2
        #define OD_1A00_3_TPDOMappingParameter_mappedObject3        3
        #define OD_1A00_4_TPDOMappingParameter_mappedObject4        4
        #define OD_1A00_5_TPDOMappingParameter_mappedObject5        5
        #define OD_1A00_6_TPDOMappingParameter_mappedObject6        6
        #define OD_1A00_7_TPDOMappingParameter_mappedObject7        7
        #define OD_1A00_8_TPDOMappingParameter_mappedObject8        8

/*1A01 */
        #define OD_1A01_TPDOMappingParameter                        0x1A01

        #define OD_1A01_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A01_1_TPDOMappingParameter_mappedObject1        1
        #define OD_1A01_2_TPDOMappingParameter_mappedObject2        2
        #define OD_1A01_3_TPDOMappingParameter_mappedObject3        3
        #define OD_1A01_4_TPDOMappingParameter_mappedObject4        4
        #define OD_1A01_5_TPDOMappingParameter_mappedObject5        5
        #define OD_1A01_6_TPDOMappingParameter_mappedObject6        6
        #define OD_1A01_7_TPDOMappingParameter_mappedObject7        7
        #define OD_1A01_8_TPDOMappingParameter_mappedObject8        8

/*1A02 */
        #define OD_1A02_TPDOMappingParameter                        0x1A02

        #define OD_1A02_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A02_1_TPDOMappingParameter_mappedObject1        1
        #define OD_1A02_2_TPDOMappingParameter_mappedObject2        2
        #define OD_1A02_3_TPDOMappingParameter_mappedObject3        3
        #define OD_1A02_4_TPDOMappingParameter_mappedObject4        4
        #define OD_1A02_5_TPDOMappingParameter_mappedObject5        5
        #define OD_1A02_6_TPDOMappingParameter_mappedObject6        6
        #define OD_1A02_7_TPDOMappingParameter_mappedObject7        7
        #define OD_1A02_8_TPDOMappingParameter_mappedObject8        8

/*1A03 */
        #define OD_1A03_TPDOMappingParameter                        0x1A03

        #define OD_1A03_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A03_1_TPDOMappingParameter_mappedObject1        1
        #define OD_1A03_2_TPDOMappingParameter_mappedObject2        2
        #define OD_1A03_3_TPDOMappingParameter_mappedObject3        3
        #define OD_1A03_4_TPDOMappingParameter_mappedObject4        4
        #define OD_1A03_5_TPDOMappingParameter_mappedObject5        5
        #define OD_1A03_6_TPDOMappingParameter_mappedObject6        6
        #define OD_1A03_7_TPDOMappingParameter_mappedObject7        7
        #define OD_1A03_8_TPDOMappingParameter_mappedObject8        8

/*1A04 */
        #define OD_1A04_TPDOMappingParameter                        0x1A04

        #define OD_1A04_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A04_1_TPDOMappingParameter_mappedObject1        1
        #define OD_1A04_2_TPDOMappingParameter_mappedObject2        2
        #define OD_1A04_3_TPDOMappingParameter_mappedObject3        3
        #define OD_1A04_4_TPDOMappingParameter_mappedObject4        4
        #define OD_1A04_5_TPDOMappingParameter_mappedObject5        5
        #define OD_1A04_6_TPDOMappingParameter_mappedObject6        6
        #define OD_1A04_7_TPDOMappingParameter_mappedObject7        7
        #define OD_1A04_8_TPDOMappingParameter_mappedObject8        8

/*1A05 */
        #define OD_1A05_TPDOMappingParameter                        0x1A05

        #define OD_1A05_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A05_1_TPDOMappingParameter_mappedObject1        1
        #define OD_1A05_2_TPDOMappingParameter_mappedObject2        2
        #define OD_1A05_3_TPDOMappingParameter_mappedObject3        3
        #define OD_1A05_4_TPDOMappingParameter_mappedObject4        4
        #define OD_1A05_5_TPDOMappingParameter_mappedObject5        5
        #define OD_1A05_6_TPDOMappingParameter_mappedObject6        6
        #define OD_1A05_7_TPDOMappingParameter_mappedObject7        7
        #define OD_1A05_8_TPDOMappingParameter_mappedObject8        8

/*1A06 */
        #define OD_1A06_TPDOMappingParameter                        0x1A06

        #define OD_1A06_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A06_1_TPDOMappingParameter_mappedObject1        1
        #define OD_1A06_2_TPDOMappingParameter_mappedObject2        2
        #define OD_1A06_3_TPDOMappingParameter_mappedObject3        3
        #define OD_1A06_4_TPDOMappingParameter_mappedObject4        4
        #define OD_1A06_5_TPDOMappingParameter_mappedObject5        5
        #define OD_1A06_6_TPDOMappingParameter_mappedObject6        6
        #define OD_1A06_7_TPDOMappingParameter_mappedObject7        7
        #define OD_1A06_8_TPDOMappingParameter_mappedObject8        8

/*1F50 */
        #define OD_1F50_programData                                 0x1F50

        #define OD_1F50_0_programData_maxSubIndex                   0
        #define OD_1F50_1_programData_                              1

/*1F51 */
        #define OD_1F51_programControl                              0x1F51

        #define OD_1F51_0_programControl_maxSubIndex                0
        #define OD_1F51_1_programControl_                           1

/*1F56 */
        #define OD_1F56_programSoftwareIdentification               0x1F56

        #define OD_1F56_0_programSoftwareIdentification_maxSubIndex 0
        #define OD_1F56_1_programSoftwareIdentification_            1

/*1F57 */
        #define OD_1F57_flashStatusIdentification                   0x1F57

        #define OD_1F57_0_flashStatusIdentification_maxSubIndex     0
        #define OD_1F57_1_flashStatusIdentification_                1

/*1F80 */
        #define OD_1F80_NMTStartup                                  0x1F80

/*2000 */
        #define OD_2000_IO_Configuration                            0x2000

/*2001 */
        #define OD_2001_NMT_BootNetwork                             0x2001

        #define OD_2001_0_NMT_BootNetwork_maxSubIndex               0
        #define OD_2001_1_NMT_BootNetwork_NMT_BootEnable            1
        #define OD_2001_2_NMT_BootNetwork_NMT_StartTime             2

/*2002 */
        #define OD_2002_configPort                                  0x2002

        #define OD_2002_0_configPort_maxSubIndex                    0
        #define OD_2002_1_configPort_port                           1
        #define OD_2002_2_configPort_outputMask                     2
        #define OD_2002_3_configPort_outputStartValue               3
        #define OD_2002_4_configPort_inputMask                      4
        #define OD_2002_5_configPort_inputPullUp                    5
        #define OD_2002_6_configPort_inputPullDown                  6
        #define OD_2002_7_configPort_availableMask                  7

/*2003 */
        #define OD_2003_configPort                                  0x2003

        #define OD_2003_0_configPort_maxSubIndex                    0
        #define OD_2003_1_configPort_port                           1
        #define OD_2003_2_configPort_outputMask                     2
        #define OD_2003_3_configPort_outputStartValue               3
        #define OD_2003_4_configPort_inputMask                      4
        #define OD_2003_5_configPort_inputPullUp                    5
        #define OD_2003_6_configPort_inputPullDown                  6
        #define OD_2003_7_configPort_availableMask                  7

/*2004 */
        #define OD_2004_configPort                                  0x2004

        #define OD_2004_0_configPort_maxSubIndex                    0
        #define OD_2004_1_configPort_port                           1
        #define OD_2004_2_configPort_outputMask                     2
        #define OD_2004_3_configPort_outputStartValue               3
        #define OD_2004_4_configPort_inputMask                      4
        #define OD_2004_5_configPort_inputPullUp                    5
        #define OD_2004_6_configPort_inputPullDown                  6
        #define OD_2004_7_configPort_availableMask                  7

/*2005 */
        #define OD_2005_configADC                                   0x2005

        #define OD_2005_0_configADC_maxSubIndex                     0
        #define OD_2005_1_configADC_cannelsMask                     1
        #define OD_2005_2_configADC_availableMask                   2

/*2006 */
        #define OD_2006_BH1750                                      0x2006

        #define OD_2006_0_BH1750_maxSubIndex                        0
        #define OD_2006_1_BH1750_I2c                                1
        #define OD_2006_2_BH1750_addr                               2
        #define OD_2006_3_BH1750_lux                                3

/*2009 */
        #define OD_2009_BH1750                                      0x2009

        #define OD_2009_0_BH1750_maxSubIndex                        0
        #define OD_2009_1_BH1750_I2c                                1
        #define OD_2009_2_BH1750_addr                               2
        #define OD_2009_3_BH1750_lux                                3

/*200A */
        #define OD_200A_AM2320                                      0x200A

        #define OD_200A_0_AM2320_maxSubIndex                        0
        #define OD_200A_1_AM2320_I2c                                1
        #define OD_200A_2_AM2320_addr                               2
        #define OD_200A_3_AM2320_temp                               3
        #define OD_200A_4_AM2320_humid                              4

/*200C */
        #define OD_200C_BME280                                      0x200C

        #define OD_200C_0_BME280_maxSubIndex                        0
        #define OD_200C_1_BME280_I2c                                1
        #define OD_200C_2_BME280_addr                               2
        #define OD_200C_3_BME280_temp                               3
        #define OD_200C_4_BME280_humid                              4
        #define OD_200C_5_BME280_press                              5

/*200F */
        #define OD_200F_BME280                                      0x200F

        #define OD_200F_0_BME280_maxSubIndex                        0
        #define OD_200F_1_BME280_I2c                                1
        #define OD_200F_2_BME280_addr                               2
        #define OD_200F_3_BME280_temp                               3
        #define OD_200F_4_BME280_humid                              4
        #define OD_200F_5_BME280_press                              5

/*2080 */
        #define OD_2080_GPIOPack                                    0x2080

        #define OD_2080_0_GPIOPack_maxSubIndex                      0
        #define OD_2080_1_GPIOPack_inputMask                        1
        #define OD_2080_2_GPIOPack_outputMask                       2
        #define OD_2080_3_GPIOPack_state                            3
        #define OD_2080_4_GPIOPack_setReset                         4

/*2100 */
        #define OD_2100_errorStatusBits                             0x2100

/*2101 */
        #define OD_2101_RTR                                         0x2101

/*6100 */
        #define OD_6100_readInput16Bit                              0x6100

        #define OD_6100_0_readInput16Bit_maxSubIndex                0
        #define OD_6100_1_readInput16Bit_readInput1hTo10h           1
        #define OD_6100_2_readInput16Bit_readInput11hTo20h          2
        #define OD_6100_3_readInput16Bit_readInput21hTo30h          3
        #define OD_6100_4_readInput16Bit_readInput31hTo40h          4

/*6300 */
        #define OD_6300_writeOutput16Bit                            0x6300

        #define OD_6300_0_writeOutput16Bit_maxSubIndex              0
        #define OD_6300_1_writeOutput16Bit_writeOutput1hTo10h       1
        #define OD_6300_2_writeOutput16Bit_writeOutput11hTo20h      2
        #define OD_6300_3_writeOutput16Bit_writeOutput21hTo30h      3
        #define OD_6300_4_writeOutput16Bit_writeOutput31hTo40h      4

/*6400 */
        #define OD_6400_readAnalogueInput8Bit                       0x6400

        #define OD_6400_0_readAnalogueInput8Bit_maxSubIndex         0
        #define OD_6400_1_readAnalogueInput8Bit_analogueInput01h    1
        #define OD_6400_2_readAnalogueInput8Bit_analogueInput02h    2
        #define OD_6400_3_readAnalogueInput8Bit_analogueInput03h    3
        #define OD_6400_4_readAnalogueInput8Bit_analogueInput04h    4
        #define OD_6400_5_readAnalogueInput8Bit_analogueInput05h    5
        #define OD_6400_6_readAnalogueInput8Bit_analogueInput06h    6
        #define OD_6400_7_readAnalogueInput8Bit_analogueInput07h    7
        #define OD_6400_8_readAnalogueInput8Bit_analogueInput08h    8
        #define OD_6400_9_readAnalogueInput8Bit_analogueInput09h    9
        #define OD_6400_10_readAnalogueInput8Bit_analogueInput0Ah   10
        #define OD_6400_11_readAnalogueInput8Bit_analogueInput0Bh   11
        #define OD_6400_12_readAnalogueInput8Bit_analogueInput0Ch   12
        #define OD_6400_13_readAnalogueInput8Bit_analogueInput0Dh   13
        #define OD_6400_14_readAnalogueInput8Bit_analogueInput0Eh   14
        #define OD_6400_15_readAnalogueInput8Bit_analogueInput0Fh   15
        #define OD_6400_16_readAnalogueInput8Bit_analogueInput10h   16

/*6401 */
        #define OD_6401_readAnalogueInput16Bit                      0x6401

        #define OD_6401_0_readAnalogueInput16Bit_maxSubIndex        0
        #define OD_6401_1_readAnalogueInput16Bit_analogInput01h     1
        #define OD_6401_2_readAnalogueInput16Bit_analogInput02h     2
        #define OD_6401_3_readAnalogueInput16Bit_analogInput03h     3
        #define OD_6401_4_readAnalogueInput16Bit_analogInput04h     4
        #define OD_6401_5_readAnalogueInput16Bit_analogInput05h     5
        #define OD_6401_6_readAnalogueInput16Bit_analogInput06h     6
        #define OD_6401_7_readAnalogueInput16Bit_analogInput07h     7
        #define OD_6401_8_readAnalogueInput16Bit_analogInput08h     8
        #define OD_6401_9_readAnalogueInput16Bit_analogInput09h     9
        #define OD_6401_10_readAnalogueInput16Bit_analogInput0Ah    10
        #define OD_6401_11_readAnalogueInput16Bit_analogInput0Bh    11
        #define OD_6401_12_readAnalogueInput16Bit_analogInput0Ch    12
        #define OD_6401_13_readAnalogueInput16Bit_analogInput0Dh    13
        #define OD_6401_14_readAnalogueInput16Bit_analogInput0Eh    14
        #define OD_6401_15_readAnalogueInput16Bit_analogInput0Fh    15
        #define OD_6401_16_readAnalogueInput16Bit_analogInput10h    16

/*67FE */
        #define OD_67FE_errorBehaviour                              0x67FE

        #define OD_67FE_0_errorBehaviour_maxSubIndex                0
        #define OD_67FE_1_errorBehaviour_communicationError         1

/*******************************************************************************
   STRUCTURES FOR VARIABLES IN DIFFERENT MEMORY LOCATIONS
*******************************************************************************/
#define  CO_OD_FIRST_LAST_WORD     0x55 //Any value from 0x01 to 0xFE. If changed, EEPROM will be reinitialized.

/***** Structure for RAM variables ********************************************/
struct sCO_OD_RAM{
               UNSIGNED32     FirstWord;

/*1000      */ UNSIGNED32     deviceType;
/*1001      */ UNSIGNED8      errorRegister;
/*1002      */ UNSIGNED32     manufacturerStatusRegister;
/*1003      */ UNSIGNED32      preDefinedErrorField[8];
/*1005      */ UNSIGNED32     COB_ID_SYNCMessage;
/*1006      */ UNSIGNED32     communicationCyclePeriod;
/*1007      */ UNSIGNED32     synchronousWindowLength;
/*1008      */ VISIBLE_STRING manufacturerDeviceName[23];
/*1009      */ VISIBLE_STRING manufacturerHardwareVersion[4];
/*100A      */ VISIBLE_STRING manufacturerSoftwareVersion[4];
/*1010      */ UNSIGNED32      storeParameters[1];
/*1011      */ UNSIGNED32      restoreDefaultParameters[1];
/*1012      */ UNSIGNED32     COB_ID_TIME;
/*1014      */ UNSIGNED32     COB_ID_EMCY;
/*1015      */ UNSIGNED16     inhibitTimeEMCY;
/*1016      */ UNSIGNED32      consumerHeartbeatTime[4];
/*1017      */ UNSIGNED16     producerHeartbeatTime;
/*1018      */ OD_identity_t   identity;
/*1019      */ UNSIGNED8      synchronousCounterOverflowValue;
/*1026      */ OD_OSPrompt_t   OSPrompt;
/*1029      */ UNSIGNED8       errorBehavior[6];
/*1200      */ OD_SDOServerParameter_t SDOServerParameter[1];
/*1400      */ OD_RPDOCommunicationParameter_t RPDOCommunicationParameter[4];
/*1600      */ OD_RPDOMappingParameter_t RPDOMappingParameter[4];
/*1800      */ OD_TPDOCommunicationParameter_t TPDOCommunicationParameter[7];
/*1A00      */ OD_TPDOMappingParameter_t TPDOMappingParameter[7];
/*1F50      */ DOMAIN          programData[1];
/*1F51      */ UNSIGNED8       programControl[1];
/*1F56      */ UNSIGNED32      programSoftwareIdentification[1];
/*1F57      */ UNSIGNED32      flashStatusIdentification[1];
/*1F80      */ UNSIGNED32     NMTStartup;
/*2000      */ UNSIGNED8      IO_Configuration;
/*2001      */ OD_NMT_BootNetwork_t NMT_BootNetwork;
/*2002      */ OD_configPort_t configPort[3];
/*2005      */ OD_configADC_t  configADC;
/*2006      */ OD_BH1750_t     BH1750[2];
/*200A      */ OD_AM2320_t     AM2320;
/*200C      */ OD_BME280_t     BME280[2];
/*2080      */ OD_GPIOPack_t   GPIOPack;
/*2100      */ OCTET_STRING   errorStatusBits[10];
/*2101      */ UNSIGNED8      RTR;
/*6100      */ UNSIGNED16      readInput16Bit[4];
/*6300      */ UNSIGNED16      writeOutput16Bit[4];
/*6400      */ INTEGER8        readAnalogueInput8Bit[16];
/*6401      */ INTEGER16       readAnalogueInput16Bit[16];
/*67FE      */ UNSIGNED8       errorBehaviour[1];

               UNSIGNED32     LastWord;
};

/***** Structure for ROM variables ********************************************/
struct sCO_OD_ROM{
               UNSIGNED32     FirstWord;


               UNSIGNED32     LastWord;
};

/***** Structure for EEPROM variables ********************************************/
struct sCO_OD_EEPROM{
               UNSIGNED32     FirstWord;


               UNSIGNED32     LastWord;
};

/***** Declaration of Object Dictionary variables *****************************/
extern struct sCO_OD_RAM CO_OD_RAM;

extern struct sCO_OD_ROM CO_OD_ROM;

extern struct sCO_OD_EEPROM CO_OD_EEPROM;

/*******************************************************************************
   ALIASES FOR OBJECT DICTIONARY VARIABLES
*******************************************************************************/
/*1000, Data Type: UNSIGNED32 */
        #define OD_deviceType                                       CO_OD_RAM.deviceType

/*1001, Data Type: UNSIGNED8 */
        #define OD_errorRegister                                    CO_OD_RAM.errorRegister

/*1002, Data Type: UNSIGNED32 */
        #define OD_manufacturerStatusRegister                       CO_OD_RAM.manufacturerStatusRegister

/*1003, Data Type: UNSIGNED32, Array[8] */
        #define OD_preDefinedErrorField                             CO_OD_RAM.preDefinedErrorField
        #define ODL_preDefinedErrorField_arrayLength                8
        #define ODA_preDefinedErrorField_standardErrorField         0

/*1005, Data Type: UNSIGNED32 */
        #define OD_COB_ID_SYNCMessage                               CO_OD_RAM.COB_ID_SYNCMessage

/*1006, Data Type: UNSIGNED32 */
        #define OD_communicationCyclePeriod                         CO_OD_RAM.communicationCyclePeriod

/*1007, Data Type: UNSIGNED32 */
        #define OD_synchronousWindowLength                          CO_OD_RAM.synchronousWindowLength

/*1008, Data Type: VISIBLE_STRING */
        #define OD_manufacturerDeviceName                           CO_OD_RAM.manufacturerDeviceName
        #define ODL_manufacturerDeviceName_stringLength             23

/*1009, Data Type: VISIBLE_STRING */
        #define OD_manufacturerHardwareVersion                      CO_OD_RAM.manufacturerHardwareVersion
        #define ODL_manufacturerHardwareVersion_stringLength        4

/*100A, Data Type: VISIBLE_STRING */
        #define OD_manufacturerSoftwareVersion                      CO_OD_RAM.manufacturerSoftwareVersion
        #define ODL_manufacturerSoftwareVersion_stringLength        4

/*1010, Data Type: UNSIGNED32, Array[1] */
        #define OD_storeParameters                                  CO_OD_RAM.storeParameters
        #define ODL_storeParameters_arrayLength                     1
        #define ODA_storeParameters_saveAllParameters               0

/*1011, Data Type: UNSIGNED32, Array[1] */
        #define OD_restoreDefaultParameters                         CO_OD_RAM.restoreDefaultParameters
        #define ODL_restoreDefaultParameters_arrayLength            1
        #define ODA_restoreDefaultParameters_restoreAllDefaultParameters 0

/*1012, Data Type: UNSIGNED32 */
        #define OD_COB_ID_TIME                                      CO_OD_RAM.COB_ID_TIME

/*1014, Data Type: UNSIGNED32 */
        #define OD_COB_ID_EMCY                                      CO_OD_RAM.COB_ID_EMCY

/*1015, Data Type: UNSIGNED16 */
        #define OD_inhibitTimeEMCY                                  CO_OD_RAM.inhibitTimeEMCY

/*1016, Data Type: UNSIGNED32, Array[4] */
        #define OD_consumerHeartbeatTime                            CO_OD_RAM.consumerHeartbeatTime
        #define ODL_consumerHeartbeatTime_arrayLength               4
        #define ODA_consumerHeartbeatTime_consumerHeartbeatTime     0

/*1017, Data Type: UNSIGNED16 */
        #define OD_producerHeartbeatTime                            CO_OD_RAM.producerHeartbeatTime

/*1018, Data Type: identity_t */
        #define OD_identity                                         CO_OD_RAM.identity

/*1019, Data Type: UNSIGNED8 */
        #define OD_synchronousCounterOverflowValue                  CO_OD_RAM.synchronousCounterOverflowValue

/*1026, Data Type: OSPrompt_t */
        #define OD_OSPrompt                                         CO_OD_RAM.OSPrompt

/*1029, Data Type: UNSIGNED8, Array[6] */
        #define OD_errorBehavior                                    CO_OD_RAM.errorBehavior
        #define ODL_errorBehavior_arrayLength                       6
        #define ODA_errorBehavior_communication                     0
        #define ODA_errorBehavior_communicationOther                1
        #define ODA_errorBehavior_communicationPassive              2
        #define ODA_errorBehavior_generic                           3
        #define ODA_errorBehavior_deviceProfile                     4
        #define ODA_errorBehavior_manufacturerSpecific              5

/*1200, Data Type: SDOServerParameter_t */
        #define OD_SDOServerParameter                               CO_OD_RAM.SDOServerParameter

/*1400, Data Type: RPDOCommunicationParameter_t */
        #define OD_RPDOCommunicationParameter                       CO_OD_RAM.RPDOCommunicationParameter

/*1600, Data Type: RPDOMappingParameter_t */
        #define OD_RPDOMappingParameter                             CO_OD_RAM.RPDOMappingParameter

/*1800, Data Type: TPDOCommunicationParameter_t */
        #define OD_TPDOCommunicationParameter                       CO_OD_RAM.TPDOCommunicationParameter

/*1A00, Data Type: TPDOMappingParameter_t */
        #define OD_TPDOMappingParameter                             CO_OD_RAM.TPDOMappingParameter

/*1F50, Data Type: DOMAIN, Array[1] */
        #define OD_programData                                      CO_OD_RAM.programData
        #define ODL_programData_arrayLength                         1
        #define ODA_programData_                                    0

/*1F51, Data Type: UNSIGNED8, Array[1] */
        #define OD_programControl                                   CO_OD_RAM.programControl
        #define ODL_programControl_arrayLength                      1
        #define ODA_programControl_                                 0

/*1F56, Data Type: UNSIGNED32, Array[1] */
        #define OD_programSoftwareIdentification                    CO_OD_RAM.programSoftwareIdentification
        #define ODL_programSoftwareIdentification_arrayLength       1
        #define ODA_programSoftwareIdentification_                  0

/*1F57, Data Type: UNSIGNED32, Array[1] */
        #define OD_flashStatusIdentification                        CO_OD_RAM.flashStatusIdentification
        #define ODL_flashStatusIdentification_arrayLength           1
        #define ODA_flashStatusIdentification_                      0

/*1F80, Data Type: UNSIGNED32 */
        #define OD_NMTStartup                                       CO_OD_RAM.NMTStartup

/*2000, Data Type: UNSIGNED8 */
        #define OD_IO_Configuration                                 CO_OD_RAM.IO_Configuration

/*2001, Data Type: NMT_BootNetwork_t */
        #define OD_NMT_BootNetwork                                  CO_OD_RAM.NMT_BootNetwork

/*2002, Data Type: configPort_t */
        #define OD_configPort                                       CO_OD_RAM.configPort

/*2005, Data Type: configADC_t */
        #define OD_configADC                                        CO_OD_RAM.configADC

/*2006, Data Type: BH1750_t */
        #define OD_BH1750                                           CO_OD_RAM.BH1750

/*200A, Data Type: AM2320_t */
        #define OD_AM2320                                           CO_OD_RAM.AM2320

/*200C, Data Type: BME280_t */
        #define OD_BME280                                           CO_OD_RAM.BME280

/*2080, Data Type: GPIOPack_t */
        #define OD_GPIOPack                                         CO_OD_RAM.GPIOPack

/*2100, Data Type: OCTET_STRING */
        #define OD_errorStatusBits                                  CO_OD_RAM.errorStatusBits
        #define ODL_errorStatusBits_stringLength                    10

/*2101, Data Type: UNSIGNED8 */
        #define OD_RTR                                              CO_OD_RAM.RTR

/*6100, Data Type: UNSIGNED16, Array[4] */
        #define OD_readInput16Bit                                   CO_OD_RAM.readInput16Bit
        #define ODL_readInput16Bit_arrayLength                      4
        #define ODA_readInput16Bit_readInput1hTo10h                 0
        #define ODA_readInput16Bit_readInput11hTo20h                1
        #define ODA_readInput16Bit_readInput21hTo30h                2
        #define ODA_readInput16Bit_readInput31hTo40h                3

/*6300, Data Type: UNSIGNED16, Array[4] */
        #define OD_writeOutput16Bit                                 CO_OD_RAM.writeOutput16Bit
        #define ODL_writeOutput16Bit_arrayLength                    4
        #define ODA_writeOutput16Bit_writeOutput1hTo10h             0
        #define ODA_writeOutput16Bit_writeOutput11hTo20h            1
        #define ODA_writeOutput16Bit_writeOutput21hTo30h            2
        #define ODA_writeOutput16Bit_writeOutput31hTo40h            3

/*6400, Data Type: INTEGER8, Array[16] */
        #define OD_readAnalogueInput8Bit                            CO_OD_RAM.readAnalogueInput8Bit
        #define ODL_readAnalogueInput8Bit_arrayLength               16
        #define ODA_readAnalogueInput8Bit_analogueInput01h          0
        #define ODA_readAnalogueInput8Bit_analogueInput02h          1
        #define ODA_readAnalogueInput8Bit_analogueInput03h          2
        #define ODA_readAnalogueInput8Bit_analogueInput04h          3
        #define ODA_readAnalogueInput8Bit_analogueInput05h          4
        #define ODA_readAnalogueInput8Bit_analogueInput06h          5
        #define ODA_readAnalogueInput8Bit_analogueInput07h          6
        #define ODA_readAnalogueInput8Bit_analogueInput08h          7
        #define ODA_readAnalogueInput8Bit_analogueInput09h          8
        #define ODA_readAnalogueInput8Bit_analogueInput0Ah          9
        #define ODA_readAnalogueInput8Bit_analogueInput0Bh          10
        #define ODA_readAnalogueInput8Bit_analogueInput0Ch          11
        #define ODA_readAnalogueInput8Bit_analogueInput0Dh          12
        #define ODA_readAnalogueInput8Bit_analogueInput0Eh          13
        #define ODA_readAnalogueInput8Bit_analogueInput0Fh          14
        #define ODA_readAnalogueInput8Bit_analogueInput10h          15

/*6401, Data Type: INTEGER16, Array[16] */
        #define OD_readAnalogueInput16Bit                           CO_OD_RAM.readAnalogueInput16Bit
        #define ODL_readAnalogueInput16Bit_arrayLength              16
        #define ODA_readAnalogueInput16Bit_analogInput01h           0
        #define ODA_readAnalogueInput16Bit_analogInput02h           1
        #define ODA_readAnalogueInput16Bit_analogInput03h           2
        #define ODA_readAnalogueInput16Bit_analogInput04h           3
        #define ODA_readAnalogueInput16Bit_analogInput05h           4
        #define ODA_readAnalogueInput16Bit_analogInput06h           5
        #define ODA_readAnalogueInput16Bit_analogInput07h           6
        #define ODA_readAnalogueInput16Bit_analogInput08h           7
        #define ODA_readAnalogueInput16Bit_analogInput09h           8
        #define ODA_readAnalogueInput16Bit_analogInput0Ah           9
        #define ODA_readAnalogueInput16Bit_analogInput0Bh           10
        #define ODA_readAnalogueInput16Bit_analogInput0Ch           11
        #define ODA_readAnalogueInput16Bit_analogInput0Dh           12
        #define ODA_readAnalogueInput16Bit_analogInput0Eh           13
        #define ODA_readAnalogueInput16Bit_analogInput0Fh           14
        #define ODA_readAnalogueInput16Bit_analogInput10h           15

/*67FE, Data Type: UNSIGNED8, Array[1] */
        #define OD_errorBehaviour                                   CO_OD_RAM.errorBehaviour
        #define ODL_errorBehaviour_arrayLength                      1
        #define ODA_errorBehaviour_communicationError               0

#endif
// clang-format on
