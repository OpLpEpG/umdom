// clang-format off
/*******************************************************************************
    CANopen Object Dictionary definition for CANopenNode v1 to v2

    This file was automatically generated with
    libedssharp Object Dictionary Editor v0.8-123-g6c02323-dirty

    https://github.com/CANopenNode/CANopenNode
    https://github.com/robincornelius/libedssharp

    DON'T EDIT THIS FILE MANUALLY !!!!
*******************************************************************************/
// For CANopenNode V2 users, C macro `CO_VERSION_MAJOR=2` has to be added to project options
#ifndef CO_VERSION_MAJOR
 #include "CO_driver.h"
 #include "CO_OD.h"
 #include "CO_SDO.h"
#elif CO_VERSION_MAJOR < 4
 #include "301/CO_driver.h"
 #include "CO_OD.h"
 #include "301/CO_SDOserver.h"
#else
 #error This Object dictionary is not compatible with CANopenNode v4.0 and up!
#endif

/*******************************************************************************
   DEFINITION AND INITIALIZATION OF OBJECT DICTIONARY VARIABLES
*******************************************************************************/


/***** Definition for RAM variables *******************************************/
struct sCO_OD_RAM CO_OD_RAM = {
           CO_OD_FIRST_LAST_WORD,

/*1000*/ 0x0000L,
/*1001*/ 0x0L,
/*1002*/ 0x0000L,
/*1003*/ {0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1005*/ 0x0080L,
/*1006*/ 0x0000L,
/*1007*/ 0x0000L,
/*1008*/ {'Z', 'e', 'p', 'h', 'y', 'r', ' ', 'R', 'T', 'O', 'S', '/', 'C', 'A', 'N', 'o', 'p', 'e', 'n', 'N', 'o', 'd', 'e'},
/*1009*/ {'3', '.', '0', '0'},
/*100A*/ {'3', '.', '0', '0'},
/*1010*/ {0x0003L},
/*1011*/ {0x0001L},
/*1012*/ 0x80000100L,
/*1014*/ 0x0080L,
/*1015*/ 0x64,
/*1016*/ {0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1017*/ 0x3E8,
/*1018*/ {0x4L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1019*/ 0x0L,
/*1026*/ {0x2L, 0x0L, 0x0L},
/*1029*/ {0x0L, 0x0L, 0x1L, 0x0L, 0x0L, 0x0L},
/*1200*/ {{0x2L, 0x0600L, 0x0580L}},
/*1400*/ {{0x6L, 0x0200L, 0xFEL},
/*1401*/ {0x6L, 0x0300L, 0xFEL},
/*1402*/ {0x6L, 0x0400L, 0xFEL},
/*1403*/ {0x6L, 0x0500L, 0xFEL}},
/*1600*/ {{0x2L, 0x20800410L, 0x20800510L, 0x63000310L, 0x63000410L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1601*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1602*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1603*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L}},
/*1800*/ {{0x6L, 0x0180L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
/*1801*/ {0x6L, 0x0280L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
/*1802*/ {0x6L, 0x0380L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
/*1803*/ {0x6L, 0x0480L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
/*1804*/ {0x6L, 0x01C0L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
/*1805*/ {0x6L, 0x02C0L, 0xFEL, 0xBB8, 0x0L, 0x00, 0x0L},
/*1806*/ {0x6L, 0x03C0L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L}},
/*1A00*/ {{0x1L, 0x20800310L, 0x61000210L, 0x61000310L, 0x61000410L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1A01*/ {0x4L, 0x64010110L, 0x64010210L, 0x64010310L, 0x64010410L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1A02*/ {0x4L, 0x64010510L, 0x64010610L, 0x64010710L, 0x64010810L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1A03*/ {0x0L, 0x64010910L, 0x64010A10L, 0x64010B10L, 0x64010C10L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1A04*/ {0x0L, 0x64000108L, 0x64000208L, 0x64000308L, 0x64000408L, 0x64000508L, 0x64000608L, 0x64000708L, 0x64000808L},
/*1A05*/ {0x6L, 0x20060310L, 0x200A0408L, 0x200A0308L, 0x200C0510L, 0x200C0308L, 0x200C0408L, 0x0000L, 0x0000L},
/*1A06*/ {0x1L, 0x10260208L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L}},
/*1F50*/ {0},
/*1F51*/ {0x0L},
/*1F56*/ {0x0000L},
/*1F57*/ {0x0000L},
/*1F80*/ 0x0000L,
/*2000*/ 0x0L,
/*2001*/ {0x2L, 0x0L, 0x1F4},
/*2002*/ {{0x7L, {'G', 'P', 'I', 'O', 'A'}, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8100},
/*2003*/ {0x7L, {'G', 'P', 'I', 'O', 'B'}, 0x00, 0x00, 0xF000, 0xF000, 0x00, 0xF0F8},
/*2004*/ {0x7L, {'G', 'P', 'I', 'O', 'C'}, 0xC000, 0xC000, 0x00, 0x00, 0x00, 0xC000}},
/*2005*/ {0x2L, 0xFF, 0x3FF},
/*2006*/ {{0x3L, 0x1L, 0x23L, 0x8000},
/*2009*/ {0x3L, 0x2L, 0x5CL, 0x8000}},
/*200A*/ {0x4L, 0x1L, 0x5CL, 0x80, 0x80},
/*200C*/ {{0x5L, 0x1L, 0x76L, 0x80, 0x80, 0x8000},
/*200F*/ {0x5L, 0x2L, 0x77L, 0x80, 0x80, 0x8000}},
/*2080*/ {0x5L, 0x00, 0x00, 0x00, 0x00, 0x00},
/*2100*/ {0x0L},
/*2101*/ 0x0000L,
/*6100*/ {0x00, 0x00, 0x00, 0x00},
/*6300*/ {0x00, 0x00, 0x00, 0x00},
/*6400*/ {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
/*6401*/ {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
/*67FE*/ {0x0L},

           CO_OD_FIRST_LAST_WORD,
};


/***** Definition for ROM variables *******************************************/
struct sCO_OD_ROM CO_OD_ROM = {
           CO_OD_FIRST_LAST_WORD,


           CO_OD_FIRST_LAST_WORD,
};


/***** Definition for EEPROM variables *******************************************/
struct sCO_OD_EEPROM CO_OD_EEPROM = {
           CO_OD_FIRST_LAST_WORD,


           CO_OD_FIRST_LAST_WORD,
};




/*******************************************************************************
   STRUCTURES FOR RECORD TYPE OBJECTS
*******************************************************************************/


/*0x1018*/ const CO_OD_entryRecord_t OD_record1018[5] = {
           {(void*)&CO_OD_RAM.identity.maxSubIndex, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.identity.vendorID, 0x86, 0x4 },
           {(void*)&CO_OD_RAM.identity.productCode, 0x86, 0x4 },
           {(void*)&CO_OD_RAM.identity.revisionNumber, 0x86, 0x4 },
           {(void*)&CO_OD_RAM.identity.serialNumber, 0x86, 0x4 },
};

/*0x1026*/ const CO_OD_entryRecord_t OD_record1026[3] = {
           {(void*)&CO_OD_RAM.OSPrompt.highestSubIndexSupported, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.OSPrompt.stdIn, 0x3A, 0x1 },
           {(void*)&CO_OD_RAM.OSPrompt.stdOut, 0x26, 0x1 },
};

/*0x1200*/ const CO_OD_entryRecord_t OD_record1200[3] = {
           {(void*)&CO_OD_RAM.SDOServerParameter[0].maxSubIndex, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.SDOServerParameter[0].COB_IDClientToServer, 0x86, 0x4 },
           {(void*)&CO_OD_RAM.SDOServerParameter[0].COB_IDServerToClient, 0x86, 0x4 },
};

/*0x1400*/ const CO_OD_entryRecord_t OD_record1400[3] = {
           {(void*)&CO_OD_RAM.RPDOCommunicationParameter[0].maxSubIndex, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.RPDOCommunicationParameter[0].COB_IDUsedByRPDO, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.RPDOCommunicationParameter[0].transmissionType, 0x0E, 0x1 },
};

/*0x1401*/ const CO_OD_entryRecord_t OD_record1401[3] = {
           {(void*)&CO_OD_RAM.RPDOCommunicationParameter[1].maxSubIndex, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.RPDOCommunicationParameter[1].COB_IDUsedByRPDO, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.RPDOCommunicationParameter[1].transmissionType, 0x0E, 0x1 },
};

/*0x1402*/ const CO_OD_entryRecord_t OD_record1402[3] = {
           {(void*)&CO_OD_RAM.RPDOCommunicationParameter[2].maxSubIndex, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.RPDOCommunicationParameter[2].COB_IDUsedByRPDO, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.RPDOCommunicationParameter[2].transmissionType, 0x0E, 0x1 },
};

/*0x1403*/ const CO_OD_entryRecord_t OD_record1403[3] = {
           {(void*)&CO_OD_RAM.RPDOCommunicationParameter[3].maxSubIndex, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.RPDOCommunicationParameter[3].COB_IDUsedByRPDO, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.RPDOCommunicationParameter[3].transmissionType, 0x0E, 0x1 },
};

/*0x1600*/ const CO_OD_entryRecord_t OD_record1600[9] = {
           {(void*)&CO_OD_RAM.RPDOMappingParameter[0].numberOfMappedObjects, 0x0E, 0x1 },
           {(void*)&CO_OD_RAM.RPDOMappingParameter[0].mappedObject1, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.RPDOMappingParameter[0].mappedObject2, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.RPDOMappingParameter[0].mappedObject3, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.RPDOMappingParameter[0].mappedObject4, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.RPDOMappingParameter[0].mappedObject5, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.RPDOMappingParameter[0].mappedObject6, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.RPDOMappingParameter[0].mappedObject7, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.RPDOMappingParameter[0].mappedObject8, 0x8E, 0x4 },
};

/*0x1601*/ const CO_OD_entryRecord_t OD_record1601[9] = {
           {(void*)&CO_OD_RAM.RPDOMappingParameter[1].numberOfMappedObjects, 0x0E, 0x1 },
           {(void*)&CO_OD_RAM.RPDOMappingParameter[1].mappedObject1, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.RPDOMappingParameter[1].mappedObject2, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.RPDOMappingParameter[1].mappedObject3, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.RPDOMappingParameter[1].mappedObject4, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.RPDOMappingParameter[1].mappedObject5, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.RPDOMappingParameter[1].mappedObject6, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.RPDOMappingParameter[1].mappedObject7, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.RPDOMappingParameter[1].mappedObject8, 0x8E, 0x4 },
};

/*0x1602*/ const CO_OD_entryRecord_t OD_record1602[9] = {
           {(void*)&CO_OD_RAM.RPDOMappingParameter[2].numberOfMappedObjects, 0x0E, 0x1 },
           {(void*)&CO_OD_RAM.RPDOMappingParameter[2].mappedObject1, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.RPDOMappingParameter[2].mappedObject2, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.RPDOMappingParameter[2].mappedObject3, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.RPDOMappingParameter[2].mappedObject4, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.RPDOMappingParameter[2].mappedObject5, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.RPDOMappingParameter[2].mappedObject6, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.RPDOMappingParameter[2].mappedObject7, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.RPDOMappingParameter[2].mappedObject8, 0x8E, 0x4 },
};

/*0x1603*/ const CO_OD_entryRecord_t OD_record1603[9] = {
           {(void*)&CO_OD_RAM.RPDOMappingParameter[3].numberOfMappedObjects, 0x0E, 0x1 },
           {(void*)&CO_OD_RAM.RPDOMappingParameter[3].mappedObject1, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.RPDOMappingParameter[3].mappedObject2, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.RPDOMappingParameter[3].mappedObject3, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.RPDOMappingParameter[3].mappedObject4, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.RPDOMappingParameter[3].mappedObject5, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.RPDOMappingParameter[3].mappedObject6, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.RPDOMappingParameter[3].mappedObject7, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.RPDOMappingParameter[3].mappedObject8, 0x8E, 0x4 },
};

/*0x1800*/ const CO_OD_entryRecord_t OD_record1800[7] = {
           {(void*)&CO_OD_RAM.TPDOCommunicationParameter[0].maxSubIndex, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.TPDOCommunicationParameter[0].COB_IDUsedByTPDO, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOCommunicationParameter[0].transmissionType, 0x0E, 0x1 },
           {(void*)&CO_OD_RAM.TPDOCommunicationParameter[0].inhibitTime, 0x8E, 0x2 },
           {(void*)&CO_OD_RAM.TPDOCommunicationParameter[0].compatibilityEntry, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.TPDOCommunicationParameter[0].eventTimer, 0x8E, 0x2 },
           {(void*)&CO_OD_RAM.TPDOCommunicationParameter[0].SYNCStartValue, 0x0E, 0x1 },
};

/*0x1801*/ const CO_OD_entryRecord_t OD_record1801[7] = {
           {(void*)&CO_OD_RAM.TPDOCommunicationParameter[1].maxSubIndex, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.TPDOCommunicationParameter[1].COB_IDUsedByTPDO, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOCommunicationParameter[1].transmissionType, 0x0E, 0x1 },
           {(void*)&CO_OD_RAM.TPDOCommunicationParameter[1].inhibitTime, 0x8E, 0x2 },
           {(void*)&CO_OD_RAM.TPDOCommunicationParameter[1].compatibilityEntry, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.TPDOCommunicationParameter[1].eventTimer, 0x8E, 0x2 },
           {(void*)&CO_OD_RAM.TPDOCommunicationParameter[1].SYNCStartValue, 0x0E, 0x1 },
};

/*0x1802*/ const CO_OD_entryRecord_t OD_record1802[7] = {
           {(void*)&CO_OD_RAM.TPDOCommunicationParameter[2].maxSubIndex, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.TPDOCommunicationParameter[2].COB_IDUsedByTPDO, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOCommunicationParameter[2].transmissionType, 0x0E, 0x1 },
           {(void*)&CO_OD_RAM.TPDOCommunicationParameter[2].inhibitTime, 0x8E, 0x2 },
           {(void*)&CO_OD_RAM.TPDOCommunicationParameter[2].compatibilityEntry, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.TPDOCommunicationParameter[2].eventTimer, 0x8E, 0x2 },
           {(void*)&CO_OD_RAM.TPDOCommunicationParameter[2].SYNCStartValue, 0x0E, 0x1 },
};

/*0x1803*/ const CO_OD_entryRecord_t OD_record1803[7] = {
           {(void*)&CO_OD_RAM.TPDOCommunicationParameter[3].maxSubIndex, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.TPDOCommunicationParameter[3].COB_IDUsedByTPDO, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOCommunicationParameter[3].transmissionType, 0x0E, 0x1 },
           {(void*)&CO_OD_RAM.TPDOCommunicationParameter[3].inhibitTime, 0x8E, 0x2 },
           {(void*)&CO_OD_RAM.TPDOCommunicationParameter[3].compatibilityEntry, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.TPDOCommunicationParameter[3].eventTimer, 0x8E, 0x2 },
           {(void*)&CO_OD_RAM.TPDOCommunicationParameter[3].SYNCStartValue, 0x0E, 0x1 },
};

/*0x1804*/ const CO_OD_entryRecord_t OD_record1804[7] = {
           {(void*)&CO_OD_RAM.TPDOCommunicationParameter[4].maxSubIndex, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.TPDOCommunicationParameter[4].COB_IDUsedByTPDO, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOCommunicationParameter[4].transmissionType, 0x0E, 0x1 },
           {(void*)&CO_OD_RAM.TPDOCommunicationParameter[4].inhibitTime, 0x8E, 0x2 },
           {(void*)&CO_OD_RAM.TPDOCommunicationParameter[4].compatibilityEntry, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.TPDOCommunicationParameter[4].eventTimer, 0x8E, 0x2 },
           {(void*)&CO_OD_RAM.TPDOCommunicationParameter[4].SYNCStartValue, 0x0E, 0x1 },
};

/*0x1805*/ const CO_OD_entryRecord_t OD_record1805[7] = {
           {(void*)&CO_OD_RAM.TPDOCommunicationParameter[5].maxSubIndex, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.TPDOCommunicationParameter[5].COB_IDUsedByTPDO, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOCommunicationParameter[5].transmissionType, 0x0E, 0x1 },
           {(void*)&CO_OD_RAM.TPDOCommunicationParameter[5].inhibitTime, 0x8E, 0x2 },
           {(void*)&CO_OD_RAM.TPDOCommunicationParameter[5].compatibilityEntry, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.TPDOCommunicationParameter[5].eventTimer, 0x8E, 0x2 },
           {(void*)&CO_OD_RAM.TPDOCommunicationParameter[5].SYNCStartValue, 0x0E, 0x1 },
};

/*0x1806*/ const CO_OD_entryRecord_t OD_record1806[7] = {
           {(void*)&CO_OD_RAM.TPDOCommunicationParameter[6].maxSubIndex, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.TPDOCommunicationParameter[6].COB_IDUsedByTPDO, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOCommunicationParameter[6].transmissionType, 0x0E, 0x1 },
           {(void*)&CO_OD_RAM.TPDOCommunicationParameter[6].inhibitTime, 0x8E, 0x2 },
           {(void*)&CO_OD_RAM.TPDOCommunicationParameter[6].compatibilityEntry, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.TPDOCommunicationParameter[6].eventTimer, 0x8E, 0x2 },
           {(void*)&CO_OD_RAM.TPDOCommunicationParameter[6].SYNCStartValue, 0x0E, 0x1 },
};

/*0x1A00*/ const CO_OD_entryRecord_t OD_record1A00[9] = {
           {(void*)&CO_OD_RAM.TPDOMappingParameter[0].numberOfMappedObjects, 0x0E, 0x1 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[0].mappedObject1, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[0].mappedObject2, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[0].mappedObject3, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[0].mappedObject4, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[0].mappedObject5, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[0].mappedObject6, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[0].mappedObject7, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[0].mappedObject8, 0x8E, 0x4 },
};

/*0x1A01*/ const CO_OD_entryRecord_t OD_record1A01[9] = {
           {(void*)&CO_OD_RAM.TPDOMappingParameter[1].numberOfMappedObjects, 0x0E, 0x1 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[1].mappedObject1, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[1].mappedObject2, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[1].mappedObject3, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[1].mappedObject4, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[1].mappedObject5, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[1].mappedObject6, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[1].mappedObject7, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[1].mappedObject8, 0x8E, 0x4 },
};

/*0x1A02*/ const CO_OD_entryRecord_t OD_record1A02[9] = {
           {(void*)&CO_OD_RAM.TPDOMappingParameter[2].numberOfMappedObjects, 0x0E, 0x1 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[2].mappedObject1, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[2].mappedObject2, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[2].mappedObject3, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[2].mappedObject4, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[2].mappedObject5, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[2].mappedObject6, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[2].mappedObject7, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[2].mappedObject8, 0x8E, 0x4 },
};

/*0x1A03*/ const CO_OD_entryRecord_t OD_record1A03[9] = {
           {(void*)&CO_OD_RAM.TPDOMappingParameter[3].numberOfMappedObjects, 0x0E, 0x1 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[3].mappedObject1, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[3].mappedObject2, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[3].mappedObject3, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[3].mappedObject4, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[3].mappedObject5, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[3].mappedObject6, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[3].mappedObject7, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[3].mappedObject8, 0x8E, 0x4 },
};

/*0x1A04*/ const CO_OD_entryRecord_t OD_record1A04[9] = {
           {(void*)&CO_OD_RAM.TPDOMappingParameter[4].numberOfMappedObjects, 0x0E, 0x1 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[4].mappedObject1, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[4].mappedObject2, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[4].mappedObject3, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[4].mappedObject4, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[4].mappedObject5, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[4].mappedObject6, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[4].mappedObject7, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[4].mappedObject8, 0x8E, 0x4 },
};

/*0x1A05*/ const CO_OD_entryRecord_t OD_record1A05[9] = {
           {(void*)&CO_OD_RAM.TPDOMappingParameter[5].numberOfMappedObjects, 0x0E, 0x1 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[5].mappedObject1, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[5].mappedObject2, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[5].mappedObject3, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[5].mappedObject4, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[5].mappedObject5, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[5].mappedObject6, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[5].mappedObject7, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[5].mappedObject8, 0x8E, 0x4 },
};

/*0x1A06*/ const CO_OD_entryRecord_t OD_record1A06[9] = {
           {(void*)&CO_OD_RAM.TPDOMappingParameter[6].numberOfMappedObjects, 0x0E, 0x1 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[6].mappedObject1, 0x86, 0x4 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[6].mappedObject2, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[6].mappedObject3, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[6].mappedObject4, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[6].mappedObject5, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[6].mappedObject6, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[6].mappedObject7, 0x8E, 0x4 },
           {(void*)&CO_OD_RAM.TPDOMappingParameter[6].mappedObject8, 0x8E, 0x4 },
};

/*0x2001*/ const CO_OD_entryRecord_t OD_record2001[3] = {
           {(void*)&CO_OD_RAM.NMT_BootNetwork.numberOfEntries, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.NMT_BootNetwork.NMT_BootEnable, 0x0E, 0x1 },
           {(void*)&CO_OD_RAM.NMT_BootNetwork.NMT_StartTime, 0x8E, 0x2 },
};

/*0x2002*/ const CO_OD_entryRecord_t OD_record2002[8] = {
           {(void*)&CO_OD_RAM.configPort[0].highestSubIndexSupported, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.configPort[0].port, 0x06, 0x5 },
           {(void*)&CO_OD_RAM.configPort[0].outputMask, 0x8E, 0x2 },
           {(void*)&CO_OD_RAM.configPort[0].outputStartValue, 0x8E, 0x2 },
           {(void*)&CO_OD_RAM.configPort[0].inputMask, 0x8E, 0x2 },
           {(void*)&CO_OD_RAM.configPort[0].inputPullUp, 0x8E, 0x2 },
           {(void*)&CO_OD_RAM.configPort[0].inputPullDown, 0x8E, 0x2 },
           {(void*)&CO_OD_RAM.configPort[0].availableMask, 0x86, 0x2 },
};

/*0x2003*/ const CO_OD_entryRecord_t OD_record2003[8] = {
           {(void*)&CO_OD_RAM.configPort[1].highestSubIndexSupported, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.configPort[1].port, 0x06, 0x5 },
           {(void*)&CO_OD_RAM.configPort[1].outputMask, 0x8E, 0x2 },
           {(void*)&CO_OD_RAM.configPort[1].outputStartValue, 0x8E, 0x2 },
           {(void*)&CO_OD_RAM.configPort[1].inputMask, 0x8E, 0x2 },
           {(void*)&CO_OD_RAM.configPort[1].inputPullUp, 0x8E, 0x2 },
           {(void*)&CO_OD_RAM.configPort[1].inputPullDown, 0x8E, 0x2 },
           {(void*)&CO_OD_RAM.configPort[1].availableMask, 0x86, 0x2 },
};

/*0x2004*/ const CO_OD_entryRecord_t OD_record2004[8] = {
           {(void*)&CO_OD_RAM.configPort[2].highestSubIndexSupported, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.configPort[2].port, 0x06, 0x5 },
           {(void*)&CO_OD_RAM.configPort[2].outputMask, 0x8E, 0x2 },
           {(void*)&CO_OD_RAM.configPort[2].outputStartValue, 0x8E, 0x2 },
           {(void*)&CO_OD_RAM.configPort[2].inputMask, 0x8E, 0x2 },
           {(void*)&CO_OD_RAM.configPort[2].inputPullUp, 0x8E, 0x2 },
           {(void*)&CO_OD_RAM.configPort[2].inputPullDown, 0x8E, 0x2 },
           {(void*)&CO_OD_RAM.configPort[2].availableMask, 0x86, 0x2 },
};

/*0x2005*/ const CO_OD_entryRecord_t OD_record2005[3] = {
           {(void*)&CO_OD_RAM.configADC.highestSubIndexSupported, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.configADC.cannelsMask, 0x8E, 0x2 },
           {(void*)&CO_OD_RAM.configADC.availableMask, 0x86, 0x2 },
};

/*0x2006*/ const CO_OD_entryRecord_t OD_record2006[4] = {
           {(void*)&CO_OD_RAM.BH1750[0].highestSubIndexSupported, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.BH1750[0].I2c, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.BH1750[0].addr, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.BH1750[0].lux, 0xE6, 0x2 },
};

/*0x2009*/ const CO_OD_entryRecord_t OD_record2009[4] = {
           {(void*)&CO_OD_RAM.BH1750[1].highestSubIndexSupported, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.BH1750[1].I2c, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.BH1750[1].addr, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.BH1750[1].lux, 0xE6, 0x2 },
};

/*0x200A*/ const CO_OD_entryRecord_t OD_record200A[5] = {
           {(void*)&CO_OD_RAM.AM2320.highestSubIndexSupported, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.AM2320.I2c, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.AM2320.addr, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.AM2320.temp, 0x66, 0x1 },
           {(void*)&CO_OD_RAM.AM2320.humid, 0x66, 0x1 },
};

/*0x200C*/ const CO_OD_entryRecord_t OD_record200C[6] = {
           {(void*)&CO_OD_RAM.BME280[0].highestSubIndexSupported, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.BME280[0].I2c, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.BME280[0].addr, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.BME280[0].temp, 0x66, 0x1 },
           {(void*)&CO_OD_RAM.BME280[0].humid, 0x66, 0x1 },
           {(void*)&CO_OD_RAM.BME280[0].press, 0xE6, 0x2 },
};

/*0x200F*/ const CO_OD_entryRecord_t OD_record200F[6] = {
           {(void*)&CO_OD_RAM.BME280[1].highestSubIndexSupported, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.BME280[1].I2c, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.BME280[1].addr, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.BME280[1].temp, 0x66, 0x1 },
           {(void*)&CO_OD_RAM.BME280[1].humid, 0x66, 0x1 },
           {(void*)&CO_OD_RAM.BME280[1].press, 0xE6, 0x2 },
};

/*0x2080*/ const CO_OD_entryRecord_t OD_record2080[6] = {
           {(void*)&CO_OD_RAM.GPIOPack.highestSubIndexSupported, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.GPIOPack.inputMask, 0x86, 0x2 },
           {(void*)&CO_OD_RAM.GPIOPack.outputMask, 0x86, 0x2 },
           {(void*)&CO_OD_RAM.GPIOPack.state, 0xE6, 0x2 },
           {(void*)&CO_OD_RAM.GPIOPack.set, 0x9A, 0x2 },
           {(void*)&CO_OD_RAM.GPIOPack.reset, 0x9A, 0x2 },
};

/*******************************************************************************
   OBJECT DICTIONARY
*******************************************************************************/
const CO_OD_entry_t CO_OD[CO_OD_NoOfElements] = {
{0x1000, 0x00, 0x86,  4, (void*)&CO_OD_RAM.deviceType},
{0x1001, 0x00, 0x36,  1, (void*)&CO_OD_RAM.errorRegister},
{0x1002, 0x00, 0xB6,  4, (void*)&CO_OD_RAM.manufacturerStatusRegister},
{0x1003, 0x08, 0x8E,  4, (void*)&CO_OD_RAM.preDefinedErrorField[0]},
{0x1005, 0x00, 0x8E,  4, (void*)&CO_OD_RAM.COB_ID_SYNCMessage},
{0x1006, 0x00, 0x8E,  4, (void*)&CO_OD_RAM.communicationCyclePeriod},
{0x1007, 0x00, 0x8E,  4, (void*)&CO_OD_RAM.synchronousWindowLength},
{0x1008, 0x00, 0x06, 23, (void*)&CO_OD_RAM.manufacturerDeviceName},
{0x1009, 0x00, 0x06,  4, (void*)&CO_OD_RAM.manufacturerHardwareVersion},
{0x100A, 0x00, 0x06,  4, (void*)&CO_OD_RAM.manufacturerSoftwareVersion},
{0x1010, 0x01, 0x8E,  4, (void*)&CO_OD_RAM.storeParameters[0]},
{0x1011, 0x01, 0x8E,  4, (void*)&CO_OD_RAM.restoreDefaultParameters[0]},
{0x1012, 0x00, 0x86,  4, (void*)&CO_OD_RAM.COB_ID_TIME},
{0x1014, 0x00, 0x86,  4, (void*)&CO_OD_RAM.COB_ID_EMCY},
{0x1015, 0x00, 0x8E,  2, (void*)&CO_OD_RAM.inhibitTimeEMCY},
{0x1016, 0x04, 0x8E,  4, (void*)&CO_OD_RAM.consumerHeartbeatTime[0]},
{0x1017, 0x00, 0x8E,  2, (void*)&CO_OD_RAM.producerHeartbeatTime},
{0x1018, 0x04, 0x00,  0, (void*)&OD_record1018},
{0x1019, 0x00, 0x0E,  1, (void*)&CO_OD_RAM.synchronousCounterOverflowValue},
{0x1026, 0x02, 0x00,  0, (void*)&OD_record1026},
{0x1029, 0x06, 0x0E,  1, (void*)&CO_OD_RAM.errorBehavior[0]},
{0x1200, 0x02, 0x00,  0, (void*)&OD_record1200},
{0x1400, 0x02, 0x00,  0, (void*)&OD_record1400},
{0x1401, 0x02, 0x00,  0, (void*)&OD_record1401},
{0x1402, 0x02, 0x00,  0, (void*)&OD_record1402},
{0x1403, 0x02, 0x00,  0, (void*)&OD_record1403},
{0x1600, 0x08, 0x00,  0, (void*)&OD_record1600},
{0x1601, 0x08, 0x00,  0, (void*)&OD_record1601},
{0x1602, 0x08, 0x00,  0, (void*)&OD_record1602},
{0x1603, 0x08, 0x00,  0, (void*)&OD_record1603},
{0x1800, 0x06, 0x00,  0, (void*)&OD_record1800},
{0x1801, 0x06, 0x00,  0, (void*)&OD_record1801},
{0x1802, 0x06, 0x00,  0, (void*)&OD_record1802},
{0x1803, 0x06, 0x00,  0, (void*)&OD_record1803},
{0x1804, 0x06, 0x00,  0, (void*)&OD_record1804},
{0x1805, 0x06, 0x00,  0, (void*)&OD_record1805},
{0x1806, 0x06, 0x00,  0, (void*)&OD_record1806},
{0x1A00, 0x08, 0x00,  0, (void*)&OD_record1A00},
{0x1A01, 0x08, 0x00,  0, (void*)&OD_record1A01},
{0x1A02, 0x08, 0x00,  0, (void*)&OD_record1A02},
{0x1A03, 0x08, 0x00,  0, (void*)&OD_record1A03},
{0x1A04, 0x08, 0x00,  0, (void*)&OD_record1A04},
{0x1A05, 0x08, 0x00,  0, (void*)&OD_record1A05},
{0x1A06, 0x08, 0x00,  0, (void*)&OD_record1A06},
{0x1F50, 0x01, 0x0A,  0, (void*)0},
{0x1F51, 0x01, 0x0E,  1, (void*)&CO_OD_RAM.programControl[0]},
{0x1F56, 0x01, 0x86,  4, (void*)&CO_OD_RAM.programSoftwareIdentification[0]},
{0x1F57, 0x01, 0x86,  4, (void*)&CO_OD_RAM.flashStatusIdentification[0]},
{0x1F80, 0x00, 0x8E,  4, (void*)&CO_OD_RAM.NMTStartup},
{0x2000, 0x00, 0x0E,  1, (void*)&CO_OD_RAM.IO_Configuration},
{0x2001, 0x02, 0x00,  0, (void*)&OD_record2001},
{0x2002, 0x07, 0x00,  0, (void*)&OD_record2002},
{0x2003, 0x07, 0x00,  0, (void*)&OD_record2003},
{0x2004, 0x07, 0x00,  0, (void*)&OD_record2004},
{0x2005, 0x02, 0x00,  0, (void*)&OD_record2005},
{0x2006, 0x03, 0x00,  0, (void*)&OD_record2006},
{0x2009, 0x03, 0x00,  0, (void*)&OD_record2009},
{0x200A, 0x04, 0x00,  0, (void*)&OD_record200A},
{0x200C, 0x05, 0x00,  0, (void*)&OD_record200C},
{0x200F, 0x05, 0x00,  0, (void*)&OD_record200F},
{0x2080, 0x05, 0x00,  0, (void*)&OD_record2080},
{0x2100, 0x00, 0x36, 10, (void*)&CO_OD_RAM.errorStatusBits},
{0x2101, 0x00, 0xB6,  4, (void*)&CO_OD_RAM.powerOnCounter},
{0x6100, 0x04, 0xFE,  2, (void*)&CO_OD_RAM.readInput16Bit[0]},
{0x6300, 0x04, 0xBE,  2, (void*)&CO_OD_RAM.writeOutput16Bit[0]},
{0x6400, 0x10, 0x76,  1, (void*)&CO_OD_RAM.readAnalogueInput8Bit[0]},
{0x6401, 0x10, 0xF6,  2, (void*)&CO_OD_RAM.readAnalogueInput16Bit[0]},
{0x67FE, 0x01, 0x0E,  1, (void*)&CO_OD_RAM.errorBehaviour[0]},
};
// clang-format on
