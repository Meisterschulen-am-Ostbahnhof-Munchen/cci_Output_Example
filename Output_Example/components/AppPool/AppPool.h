/* ************************************************************************ */

/* ************************************************************************ */
#ifndef DEF_APPPOOL_H
#define DEF_APPPOOL_H

#include <stdint.h>
#include <IsoVtcApi.h>
#ifdef __cplusplus
#include <vector>
#endif 

/* ************************************************************************ */

static const uint32_t POOL_GRAPHIC_TYPE_MASK =            0x3U; 
static const uint32_t POOL_GRAPHIC_TYPE_BW =              0x0U;
static const uint32_t POOL_GRAPHIC_TYPE_16 =              0x1U;
static const uint32_t POOL_GRAPHIC_TYPE_256 =             0x2U;
static const uint32_t POOL_ONLY_DRIVER_DETAILS   = 0x80000000U; /* Pool is already on terminal, limit objects to those relevant for the driver. */
static const uint32_t POOL_ONLY_GAUX_OBJECTS     = 0x40000000U; /* Limit objects to those relevant for GAux. */
static const uint32_t POOL_ONLY_LANGUAGE_OBJECTS = 0x20000000U; /* Return only objects required for the new language. */

typedef enum    /* https://de.wikipedia.org/wiki/Liste_der_ISO-639-1-Codes */
{
   Undefined = 0,
   Base = (('x' << 8) + 'x'),  /* initial loader language */
   EN =   (('e' << 8) + 'n'),  /* default pool language */ 
   DE =   (('d' << 8) + 'e'),  /* german */
   SV =   (('s' << 8) + 'v'),  /* swedish */
} PoolLanguageCode;

/* ************************************************************************ */
#ifdef __cplusplus
extern "C" {
#endif
/* ************************************************************************ */
uint8_t  poolLoadByFilename(const char * pcFilename);
uint8_t  poolLoadByByteArray(const uint8_t* data, uint32_t size);
void     poolFree(uint8_t channel);
iso_bool poolIsOpen(uint8_t channel);
iso_bool poolOpen(uint8_t channel, uint32_t mode);
void     poolClose(uint8_t channel);
uint32_t poolReadPos(uint8_t channel, uint8_t* dst, uint32_t u32BlockSizeReq); /* returns 0   when data is not available. requires getSize*/
uint32_t poolReadEOF(uint8_t channel, uint8_t* dst, uint32_t u32BlockSizeReq); /* returns EOF when FP is at EOF, 0 when data is not available. End of pool is determined by EOF. */
uint32_t poolGetPos(uint8_t channel);
uint32_t poolGetSize(uint8_t channel);
const uint8_t* poolGetData(uint8_t channel);
void     poolSeekToBegin(uint8_t channel);
uint16_t poolGetNumObj(uint8_t channel);
uint32_t poolGetMaxObjectSize(uint8_t channel);
/* ************************************************************************ */
#ifdef __cplusplus
} /* end of extern "C" */
#endif
/* ************************************************************************ */

#ifdef __cplusplus

class AppPool
{
public:
// TODO	static const uint32_t MODE_READ = 1U;

   AppPool(const uint8_t* data, uint32_t dataSize);
   AppPool(const char* fileName);
   AppPool(const std::vector<uint8_t>& data);
   ~AppPool();

   const std::vector<uint8_t>& getOriginalPool() const;
   const std::vector<uint8_t>& getOpenPool() const;
   bool open(uint32_t mode);
   void close();
   bool isOpen()const;
   void seekToBegin();
   uint32_t read(uint8_t* dst, uint32_t u32BlockSizeReq);
   uint32_t getPos()const;
   uint32_t getSize()const;
   uint16_t getNumObj()const;
   uint32_t getMaxObjectSize()const;

private:
   enum POOL
   {
      ALL = 0U,
      ROOT,	/* workingset */
      AUX,
      IMG256,
      IMG16,
      IMG2,
      REMAIN,
      SIZE
   };

   uint32_t splitPool();

   struct PoolData
   {
      std::vector<uint8_t> data;		
#if defined(CCI_USE_ARCHIVE)
      std::vector<uint8_t> archive;	/* Assumed to be stored const in ROM for further processing. */
      int8_t channel = 0;				/* HSDR_FINISH_DONE */
#endif /* defined(CCI_USE_ARCHIVE) */
      uint16_t numObj = 0;
   } m_pool[POOL::SIZE];

// TDOD   const uint32_t m_mode;
   std::vector<uint8_t> m_data; /* data to be presented. if !empty() then the pool is considered open*/
   uint16_t m_numObj;
   uint32_t m_pos = 0U;
};

#endif /* __cplusplus */
/* ************************************************************************ */
#endif /* DEF_APPPOOL_H */
/* ************************************************************************ */
