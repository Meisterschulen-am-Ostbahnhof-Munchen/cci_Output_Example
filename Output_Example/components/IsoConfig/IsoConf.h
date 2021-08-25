/* ************************************************************************** */
/*!
   \file        IsoConf.h  
               
   \brief       Sample Configuration file for ISO11783 Driver 
                - should be modified by the application programmer 
   
   File for individual configuration settings of ISO Driver - Version for WHEPS Demo
   
   \author      Hammerl Erwin
   \date        Created 29.06.2006 \n
                Updated 16.04.2020

   \copyright   Competence Center ISOBUS e.V.
   
*/
/* ************************************************************************** */
#ifndef DEF_ISO_CONF_H
   #define DEF_ISO_CONF_H

/* ************************************************************************** */
/*! \addtogroup isoconf IsoConf.h Sample
    \ingroup  isoconfig 
    \brief    Sample configuration file
    \details  To define an other file than IsoConf.h as configuration file 
              add the define ISOCONF_APPFILE to your application.
    \code
    #define ISOCONF_APPFILE "MyIsoConf.h"
    \endcode
*/
/*! @{ */
/* ************************************************************************** */

/* ************************************************************************** */
/* Memory type for pointers to huge size variables (for 16-Bit)
   if you define #HUGE_C you must also define #CAST_TO_U8_HUGE_PTR.
*/
#ifdef __C166__                                 /*Keil not tested*/
       #define   HUGE_C        xhuge
       #define   CAST_TO_U8_HUGE_PTR( ptr) ((iso_u8 HUGE_C *)( ptr ))
#else  
    #ifdef _C166                                /*Tasking 16 bit*/ 
       #define   HUGE_C        huge
       #define   CAST_TO_U8_HUGE_PTR( ptr )    ((iso_u8 HUGE_C *)( ptr ))
    #else
      /* do not define HUGE_C if not needed  */       
    #endif
#endif

/* ************************************************************************** */
/*! \name Defines - Enable Clients, protocols, layers, ...
    To disable a functionality and compilation remove the corresponding define.
*/
/*! @{ */

#define _LAY78_   /**< \brief  Enable Part 7: \link apla  Multi CAN Node Application Layer \endlink functionality 
                       \details Since version 8.0 the Base Driver Multi CAN Node API is used as default. \n
                                Removing _LAY78_ from the configuration disables only the application layer module compilation. \n */
#define _LAY6_    /**< \brief Enable Part 6:  \link vtcl   Virtual Terminal Client \endlink functionality */
//#define _LAY10_   /**< \brief Enable Part 10: \link taskc  Task Controller Client \endlink functionality */
//#define _LAY13_   /**< \brief Enable Part 13: \link fsclient  File Server Client \endlink functionality */
//#define _LAY14_   /**< \brief Enable Part 14: \link sequencectrl  Sequence Control Client \endlink functionality (needs _LAY6_) */
//#define _NMEA_    /**< \brief Enable NMEA 2000 extension: fast packet transfer, Module IsoDataM.c is necessary */

#ifdef DOXYGEN  /* add define to documentation */     
    #define _LAY4_   /**< \brief Enable Part 4: \link niuapi Network Interconnection Unit \endlink service functionality 
                          \details Use the defines in the \ref niuconfig "configuration" section to configure the service. */
    #define _LAY23_  /**< \brief Enables interface for TIM Server functionality (not part of ISOBUS driver) */
#endif
/*!@} */

/* ************************************************************************** */
/** \name Defines - Base Driver Multi CAN Node configuration
  @{ */
/*! [CAN Node configuration] */
/*! \def ISO_CAN_NODES 
   \brief Number of physical CAN-busses which shall work with the J1939/ISO11783 protocol ( 1u, 2u, ...) (default 1u) */
#define ISO_CAN_NODES   1u
       
/*! \def ISO_CAN_VT 
   \brief   CAN Node which supports VT, TC, SC, FS functionality (default 0u).
   \details Number of the CAN-bus with full ISO-functionality. \n
            This CAN bus node is used for all clients ( VT-Client, TC-Client, ... ). \n
            All other busses support only basic-functionality. 
            Range: 0u, 1u, ... , (ISO_CAN_NODES-1u) 
*/
#define ISO_CAN_VT      0u  

/*! [CAN Node configuration] */
/* not used in the driver, only a sample */
#define   ISO_CAN_NODE1     0u          /**< \brief CAN 1 */ 
#define   ISO_CAN_NODE2     1u          /**< \brief CAN 2 .... */ 
#define   ISO_CAN_NODE3     2u          /**< \brief CAN 3 .... */ 
#define   ISO_CAN_NODE4     3u          /**< \brief CAN 4 .... */ 
/*! @} */

/* ************************************************************************** */
/** \name Defines - Base Driver Part 5: Network management configuration
  @{  */
/*! \def ISO_PART5_FE
   \brief   Enable the obsolete behavior of the first edition of Part 5 (not recommended).
   \details For further information see \link drivernodeconfig Part 5 Configuration \endlink
*/
#ifdef DOXYGEN
#define ISO_PART5_FE
#endif

/* The self-configurable address range is between 128 and 247 */
/* Constriction because of conformance test */
#define ISO_FIRST_FREE_SA  200u     /**< \brief First self-configurable address - predefined with 200u */
#define ISO_LAST_FREE_SA   220u     /**< \brief Last  self-configurable address - predefined with 220u */
#define ISO_USER_MAX         64     /**< \brief   Default value for the maximum number of network members for a CAN Node - predefined with 32
                                         \details This value is used as maximum number of entries in the address table for a node,
                                                  if nothing else is specified. To set the maximum number of network members entries
                                                  for a specific CAN node, you can add #ISO_USER_MAX_NODE1, #ISO_USER_MAX_NODE2, ..., #ISO_USER_MAX_NODE6
                                                  to this configuration file. */

#define ISO_NM_LOOPTIME    (5L)    /**< \brief Loop time of the ISO-Task in order to compensate negative effects on
                                                wait-times - predefined with 10 */

#ifdef DOXYGEN   /* add defines to documentation */
    #define ISO_USER_MAX_NODE1      ISO_USER_MAX    /**< \brief Maximum number of network members for CAN Node 1 */
    #define ISO_USER_MAX_NODE2      ISO_USER_MAX    /**< \brief Maximum number of network members for CAN Node 2 */
    #define ISO_USER_MAX_NODE3      ISO_USER_MAX    /**< \brief Maximum number of network members for CAN Node 3 */
    #define ISO_USER_MAX_NODE4      ISO_USER_MAX    /**< \brief Maximum number of network members for CAN Node 4 */
    #define ISO_USER_MAX_NODE5      ISO_USER_MAX    /**< \brief Maximum number of network members for CAN Node 5 */
    #define ISO_USER_MAX_NODE6      ISO_USER_MAX    /**< \brief Maximum number of network members for CAN Node 6 */
#endif

/*! @} */

/* ************************************************************************** */
/** \name Defines - Base Driver Part 3: Transport protocol configuration
  @{  */

/*! \def TP_PARALLEL_MAX
   \brief   Parallel transport channels for all CAN-nodes - predefined with 5
   \details Number of transport protocols which run simultaneously respectively which are saved
            temporarily (same sender and receiver). This parameter defines the transport channels
            for all CAN-nodes ! ( in contrary to version before 6.01 - for every CAN-node ) */
#define TP_PARALLEL_MAX     10  

/* Optional for version >= 6.02 -> Saving RAM, enhancing number of channels per CAN-node  */

/*! \def ISO_TPREDUCED_MAX
   \brief   Optional: Number of transport channels with reduced buffer size - predefined with 0
   \details This parameter defines the number of transport channels with reduced buffer size.
            #TP_PARALLEL_MAX - #ISO_TPREDUCED_MAX are the channels with complete TP size (1785bytes)
            For setting reduced size see #BLOCK_SIZE_J1939 */
#define ISO_TPREDUCED_MAX    5   

/*! \def BLOCK_SIZE_J1939
   \brief   Optional: Reduced data buffer size for TPs - predefined with 1785 Bytes
   \details Defines the data buffer size for the with #ISO_TPREDUCED_MAX defined TP channels.
            Range: 9 to 1785 bytes \n
            E. g. 223 corresponds to the max. NMEA FPT size */
#define BLOCK_SIZE_J1939   223u   


/*! @} */

/* ************************************************************************** */
/** \name Defines - Base Driver Part 7: Application layer configuration (optional, _LAY78_)
  @{  */
/*! \brief Maximum number of PGN handles - predefined with 10 
\details Number of PGNs which can be initialised in the revised application layer */
#define NUMBERPGN_MAX      40    
/*! \brief Maximum number of SPNs - predefined with 20
\details Number of SPNs which can be initialised in the revised application layer 
  - SPN-Support deactivation: Set NUMBERSPN_MAX to 0  */
#define NUMBERSPN_MAX      60    

#ifdef DOXYGEN   /* add defines to documentation */
    #define NO_SPN_DEFINES       /**< \brief Do not use the SPN defines of the ECU Driver */
#endif
/*! @} */ 

/* END base driver */

/* ************************************************************************** */
/** \name Defines - Part 6 Virtual Terminal Client (optional, _LAY6_)
    See  \link vtclmem Reduce memory footprint options \endlink for
    options to disable or enable specific sub modules or functionalities.
*/
/*! @{ */

/*! \brief Number of possible internal working sets (default 1)
   \details Should be set to the number of internal control functions.
   \par Note:
     - VTC: \n
     default for define ISO_VTC_CONNECTIONS_MAX is (WORKING_SETS * 2) \n
     default for define ISO_AUX_INSTANCES_MAX is (WORKING_SETS) \n
*/
#define   WORKING_SETS          3

/*! \brief All extern Working sets ( auxiliary units, workings sets ) - predefined with 10 */
#define   WS_EXTERN            10

/*! \def ISO_VTC_CONNECTIONS_MAX
   \brief   Maximum number of possible connections between clients and VTs
   \details Is set to #WORKING_SETS * 2 if not defined . \n
      Hint: For every internal working set (control function) at least one VTC mask instance and if mask instance is not on primary VT one auxiliary function instance is needed.
            If a VT client has no auxiliary functions, only one VTC instance is needed for this client. 
*/
#define  ISO_VTC_CONNECTIONS_MAX    ((WORKING_SETS) * 2)

/*! \def ISO_AUX_INSTANCES_MAX
   \brief   Maximum number of possible auxiliary instances/connections
   \details   Is set to #WORKING_SETS if not defined. \n
              This value should be set at least to the sum of all internal control functions
              with a VT-Client that provide a pool with auxiliary functions or inputs.
              (Hint: A control function can have multiple VTC instances, but only one can be an AUX instance.)
*/
# define ISO_AUX_INSTANCES_MAX   (WORKING_SETS)

/*! \def ISO_AUX_ENTRIES_INSTANCE_MAX
    \brief   Maximum number of auxiliary function/inputs entries of the
             client with the largest number of auxiliary functions (or inputs).
    \details Is set to (20) if not defined. 
*/
#define ISO_AUX_ENTRIES_INSTANCE_MAX  (15)

/*! \def ISO_AUX_ENTRIES_MAX
    \brief   Maximum number of possible auxiliary function/inputs entries for all instances
    \details Is set to (#ISO_AUX_ENTRIES_INSTANCE_MAX * #ISO_AUX_INSTANCES_MAX) if not defined. \n
             This value should be set at least to the sum of aux functions/inputs
             provided by the pools of all working sets.
*/
#define  ISO_AUX_ENTRIES_MAX   25

/*! \brief Buffer for sending preferred assignment to the VT - predefined with 112 + (ISO_AUX_ENTRIES_INSTANCE_MAX * 4) = 194 
    \details Internal (stack) buffer for preferred assignment (approx. 15 bytes per allocation is sufficient) 
     - With AuxUnitMax <= WS_EXTERN the buffer can be calculated: 2 + (AuxUnitMax * 11) + (ISO_AUX_ENTRIES_INSTANCE_MAX * 4)    
*/
#define ISO_AUX_BUFF_PREASS   200


/*! \brief Activates client cyclic time limitation see also ISO_TIMECONSUMED_MAX */
#define   ISO_CLIENTS_TIMELIMIT

/*! \brief Maximum time for staying in the cycle loop of the clients - predefined with 10 */
#define   ISO_TIMECONSUMED_MAX  5     

/* Define IsoVt.c */

/* new VTC and GAux command buffer defines */
/* This defines replaces VTMSG_BUFSIZE, STRBUFFSIZE and STRLENGTHMAX 
- ISO_VTC_CMD_BUFFER_MAX default 100U (To be safe, the value can be set to VTMSG_BUFSIZE * WORKING_SETS )
- ISO_VTC_CMD_EXDATA_MAX_BLOCKS and ISO_VTC_CMD_STR_BLOCK_SIZE
  To be sure the values can be chosen as follows:
  (ISO_VTC_CMD_EXDATA_MAX_BLOCKS * ISO_VTC_CMD_STR_BLOCK_SIZE) >= (STRBUFFSIZE * STRLENGTHMAX * WORKING_SETS) 
*/

/*! \brief VTC command buffer: Max number of entries for all instances
   \details The command buffer is used of all VT clients. When opening a data mask, usually a command is sent for each object.
   The buffer size must be larger than the number of these objects for all possible VT clients.
   This define replaces VTMSG_BUFSIZE. */
#define ISO_VTC_CMD_BUFFER_MAX         100U

/*! \brief VTC command buffer: Max number of entries which can be used from one instance
   \details This define limits the available number of command buffer entries for one VT connection (instance).
   Per default every VT connection can use the complete buffer. */
#define ISO_VTC_CMD_INSTANCE_MAX       (ISO_VTC_CMD_BUFFER_MAX)

/*! \brief VTC command buffer: Extended data storage block size in bytes
   \details There is an extension buffer for commands sending data with more than 9 bytes (e. g. change string value). 
   This extension buffer is partitioned into blocks. This define sets the size of a single block. 
   Normally it is not necessary to adapt this define because e. g. a string with 25 bytes works with 2 blocks. 
   In the case that you want to set a lot of strings with 20 bytes changing the define could be useful. */
#define ISO_VTC_CMD_STR_BLOCK_SIZE     16U

/*! \brief VTC command buffer: Max number of data blocks for managing the extended command data
   \details The size of the extension buffer is #ISO_VTC_CMD_EXDATA_MAX_BLOCKS * #ISO_VTC_CMD_STR_BLOCK_SIZE ). \n
    Determination of the define: Calculate the number of strings sent of the data page with the most number of strings 
    of all VT connections and add these together. If the strings can be longer than #ISO_VTC_CMD_STR_BLOCK_SIZE than the string length divided through
    #ISO_VTC_CMD_STR_BLOCK_SIZE minus 1 must be added.
 */
#define ISO_VTC_CMD_EXDATA_MAX_BLOCKS  64U

/*! \brief VTC command buffer:  Max length of a single string
   \details This define is used to limit the maximum length of string for the the change string value command.

This buffer must be larger than the longest string present (in bytes) which is sent via the bus.
This define replaces STRLENGTHMAX. */
#define ISO_VTC_CMD_STR_MAX_LENGTH     256U

/**/

/*! \brief Waittime in seconds for preferred VT - predefined with 7
\details Length of time in seconds, equals waiting period for the preferred virtual terminal, 
pre-defined with 7 seconds. During runtime this value can be changed with IsoVTDataSet() */
#define   ISO_WAITVT_SEC        (5u)

/*! \brief Maximum number of version strings stored after (extended) get versions - predef. with 5
\details This parameter defines the number of pool versions which are stored in the VTClient
when receiving the (extended) get versions response */  
#define   ISO_VTC_MAX_POOLVERSIONS   (10u)

/*! \brief Size of buffer for the working set object - predefined with 30
\details: The working set object is cached of the VT client. This buffer must be larger than the working set object */
#define   ISO_VTC_WS_POOL_BUFFER    (50uL)

/* Define IsoPool.c */
/*! \brief Size of the VTC pool buffer 
\details Size of memory in bytes for objects which are being sent with a single ETP. 
In case there is sufficient RAM, the buffer should correlate to the pool size 
as some terminals display a charge indicator which applies to the whole pool 
and the whole pool is being downloaded in an ETP. In any case this buffer 
must be bigger than the biggest object in the pool (256 colour-images!).
This define replaces RAMSIZEPOOL */
#define ISO_VTC_POOLBUFFERSIZE     (25000uL)      /* Poolbuffer size */

/*! \brief Block request during segmented pool transfer
\details Number of bytes requested of driver of "flash" - depends on the operating system */
#define SEGPOOLBLOCK                (1024u)

/*! \brief Maximal number of manipulation ranges
\details Maximum number of ranges given for pool manipulation
( Number of calling #IsoVtcPoolSetIDRangeMode() ) */
#define ISO_NO_SCALING_ELEMENTS_MAX   (30u)

/*! \brief Maximum number of objects loaded, manipulated .. to RAM during one loop
\details Number of manipulated objects during one machine loop - default is 4 */
#define ISO_MANIPULATE_MAX_LOOPS       10

/*! \brief Maximum time in ms which driver can load objects before next loop 
\details Maximum time in ms for manipulating objects till driver leave this loop - default is 20 ms */
#define ISO_MANIPULATE_MAX_TIME_MS    (20L)

/*! \brief Maximum number of multiple copied objects including original */
#define ISO_POOLNUMANICOPY              4

/*! @} */ /* END Part 6 */

/* ************************************************************************** */
/** \name Defines - Part 10 Task Controller Client (optional, _LAY10_)*/
/** @{ */
/*! \brief Defines the number of possible TC-Clients (predefined with 1)*/
#define   TC_NUMB_TCCLIENTS               3      

/*! \brief Maximum number of process data ( predefined is 20)
\details Note: Must be higher than the real number of PDs).*/
#define   PROCESSDATA_MAX                130

/*! \brief Size of buffer for device description pool (predefined is 1000) 
\details
- RAM-buffer for the DeviceDescription (number DD-objects * 50 should be sufficient)
- Minimum is real size + 50   */
#define   DEVICEDESCRIPTION_SIZE        4000

/*! \brief Number of nested Device elements (predefined with 10)*/
#define   TC_NUMNESTED_DE                10

/*! \brief Minimum timecycle for PD list (reducing prozessor load)*/
#define   TC_TIMECYCLEMIN_PDS           (50L)

/** @} */ /* END Part 10 */

/* ************************************************************************** */
/** \name Defines - Part 13 File Server Client (optional, _LAY13_)
     see \link fscconfig FS-Client Configuration \endlink for a list of all defines \n
     Configuration Sample: 
*/
/*! @{ */
#define FSC_MAX_CONNECTIONS     2      /**< \brief Maximum of simultaneous connections ( predefined is 2)  */
#define FSC_MAX_IO_HANDLES      6      /**< \brief Maximum of simultaneous io channels ( predefined is FSC_MAX_CONNECTIONS * 3)  */
/*! @} */ /* END Part 13 */

/* ************************************************************************** */
/** \name Defines - Part 14 Sequence Control Client (optional, _LAY14_)*/
/*! @{ */
#define SCD_SIZE             1000     /**< \brief  Predefined size of SCD buffer is 1000 */
#define SCFUNCTION_MAX         10     /**< \brief  Predefined number of functions is 20
                                           \details Maximum number of SCD function objects (more than in SCD) */
#define SCSTATES_MAX           15     /**< \brief   Predefined number of functions is 20
                                           \details Maximum number of SCD state objects (more than in SCD) */
#define  SCPOOBBUFFEXT         20     /**< \brief  Size of buffer for ExtDefObjDef object - predefined with 30 */
/*!@} */ /* END Part 14 */


/* ************************************************************************** */
/*!@}*/ /* END doxygen group isoconf */
/* ************************************************************************** */


/* ****************  Debugging  *********************************** */

#define ISO_DEBUG_ENABLED              // activate output
#define ISO_DEBUG_USE_EXTERN_FUNCTIONS // intern states to output window else in to cout

#define ISO_DIAG_EXTERNAL
#define ISO_VTC_GRAPHIC_AUX
#define CCI_CUSTOM_GAUX_VT_STATUS
#define ISO_NM_MSG_MONITOR
#define DISABLE_CMDLINE_PARSING

#define ISO_REMOVE_DEPRECATED /* Make sure, that samples are not using deprecated functions. */

#endif   /* DEF_ISO_CONF_H */
