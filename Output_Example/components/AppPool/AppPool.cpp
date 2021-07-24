/* ************************************************************************ */


/* ************************************************************************ */
#include <stdint.h> // malloc
#include <string.h>
#include <map>
#include <IsoCommonDef.h>
#include <IsoVtcApi.h>
#include "AppPool.h"
#include "AppCommon/AppUtil.h"
#if defined(CCI_USE_ARCHIVE)
#include "AppArchive.h"
#endif /* defined(CCI_USE_ARCHIVE) */

/* ************************************************************************ */
#if defined(_MSC_VER )
#pragma warning(disable : 4996)
#endif // defined(_MSC_VER )

/* ************************************************************************ */

/* static function declarations */

/* ************************************************************************ */
static uint8_t s_appPoolIdx = 1U;
static std::map<uint8_t, AppPool*>s_appPool;

/* ************************************************************************ */
static uint8_t getNextPoolIdx()
{
    if (s_appPool.size() >= 16U) /* We only allow up to 16 open archives. */
    {
       return 0U;
    }

    std::map<uint8_t, AppPool*>::iterator it = s_appPool.find(s_appPoolIdx);
    while (it != s_appPool.end())
    {
       s_appPoolIdx++; /* start index at 1; '0' is invalid channel */
       if (s_appPoolIdx == 0U)
       {
          s_appPoolIdx = 1U;
       }

       it = s_appPool.find(s_appPoolIdx);
    }

   return s_appPoolIdx;
}

uint8_t poolLoadByFilename(const char * pcFilename)
{
   if (pcFilename == nullptr)
   {
      return 0U;
   }

   uint8_t poolIdx = getNextPoolIdx();
   if (poolIdx == 0)
   {
       return 0U;
   }

   AppPool* appPool = new AppPool(pcFilename);
   s_appPool[poolIdx] = appPool;
   return poolIdx;
}

uint8_t poolLoadByByteArray(const uint8_t* data, uint32_t size)
{
    if ((data == nullptr) || (size == 0))
    {
       return 0U;
    }

    uint8_t poolIdx = getNextPoolIdx();
    if (poolIdx == 0)
    {
        return 0U;
    }

    AppPool* appPool = new AppPool(data, size);
    s_appPool[poolIdx] = appPool;
    return poolIdx;
}

void poolFree(uint8_t channel)
{
   std::map<uint8_t, AppPool*>::iterator it = s_appPool.find(channel);
   if (it != s_appPool.end())
   {
      delete it->second;
      s_appPool.erase(it);
   }
}

static AppPool* getPoolByChannel(uint8_t channel)
{
   std::map<uint8_t, AppPool*>::iterator it = s_appPool.find(channel);
   return (it == s_appPool.end()) ? nullptr : it->second;
}

static void reduceAuxPool(iso_u8 pu8PoolDataIn[], iso_u32* pu32PoolSizeInOut);

extern "C" iso_bool poolIsOpen(uint8_t channel)
{
   AppPool* appPool = getPoolByChannel(channel);
   return ((appPool != nullptr) && (appPool->isOpen())) ? ISO_TRUE : ISO_FALSE;
}

extern "C" iso_bool poolOpen(uint8_t channel, uint32_t mode)
{
   AppPool* appPool = getPoolByChannel(channel);
   return ((appPool != nullptr) && (appPool->open(mode))) ? ISO_TRUE : ISO_FALSE;
}

extern "C" void poolClose(uint8_t channel)
{
   AppPool* appPool = getPoolByChannel(channel);
   if (appPool != nullptr)
   {
      appPool->close();
   }
}

extern "C" uint32_t poolReadPos(uint8_t channel, uint8_t* dst, uint32_t u32BlockSizeReq)
{
   AppPool* appPool = getPoolByChannel(channel);
   if (appPool == nullptr)
   {
      return 0U;
   }

   // Continue reading until EOF or as required data is read.
   uint32_t pos = 0;
   uint32_t count = 0U;
   while ((pos < u32BlockSizeReq) && (count != UINT32_MAX))
   {
      uint32_t req = u32BlockSizeReq - pos;
      count = appPool->read(&dst[pos], req);
      if (count <= req)
      {
         pos += count;
      }
      else
      {
         count = UINT32_MAX;
      }
   }

   return pos;
}

extern "C" uint32_t poolReadEOF(uint8_t channel, uint8_t* dst, uint32_t u32BlockSizeReq)
{
   AppPool* appPool = getPoolByChannel(channel);
   return (appPool != nullptr) ? appPool->read(dst, u32BlockSizeReq) : UINT32_MAX;
}

extern "C" uint32_t poolGetPos(uint8_t channel)
{
   AppPool* appPool = getPoolByChannel(channel);
   return (appPool != nullptr) ? appPool->getPos() : 0U;
}

extern "C" uint32_t poolGetSize(uint8_t channel)
{
   AppPool* appPool = getPoolByChannel(channel);
   return (appPool != nullptr) ? appPool->getSize() : 0U;
}

const uint8_t* poolGetData(uint8_t channel)
{
   AppPool* appPool = getPoolByChannel(channel);
   return (appPool != nullptr) ? appPool->getOpenPool().data() : 0U;
}

extern "C" void poolSeekToBegin(uint8_t channel)
{
   AppPool* appPool = getPoolByChannel(channel);
   if (appPool != nullptr)
   {
      appPool->seekToBegin();
   }
}

extern "C" uint16_t poolGetNumObj(uint8_t channel)
{
   AppPool* appPool = getPoolByChannel(channel);
   return (appPool != nullptr) ? appPool->getNumObj() : 0U;
}

uint32_t poolGetMaxObjectSize(uint8_t channel)
{
   AppPool* appPool = getPoolByChannel(channel);
   return (appPool != nullptr) ? appPool->getMaxObjectSize() : 0U;
}

static std::vector<uint8_t> getDataFromFile(const char* fileName)
{
   std::vector<uint8_t> data;

   if (fileName != nullptr)
   {
      FILE *pFile = fopen(fileName, "rb");
      if (pFile)
      {
         fseek(pFile, 0L, SEEK_END);
         iso_u32 poolSize = static_cast<iso_u32>(ftell(pFile));
         data.resize(poolSize);
         fseek(pFile, 0L, SEEK_SET);
         (void)fread(data.data(), sizeof(iso_u8), poolSize, pFile);
         fclose(pFile);
         pFile = nullptr;
      }
   }

   return data;
}

static std::vector<uint8_t> getDataFromMemory(const uint8_t* poolData, uint32_t poolSize)
{
   std::vector<uint8_t> data;

   if ((poolData != nullptr) && (poolSize > 0))
   {
      data.resize(poolSize);
      memcpy(data.data(), poolData, poolSize);
   }

   return data;
}

AppPool::AppPool(const uint8_t* data, uint32_t dataSize)
   : AppPool(getDataFromMemory(data, dataSize))
{
}

AppPool::AppPool(const char* fileName)
   : AppPool(getDataFromFile(fileName))
{
}

AppPool::AppPool(const std::vector<uint8_t>& data) 
   : m_pool()
   // TODO m_mode(0U),
{
   if (data.empty())
   {
      return;
   }

   PoolData &pool = m_pool[POOL::ALL];
   pool.numObj = IsoVtcGetNumofPoolObjs(data.data(), (iso_s32)data.size());

   if (pool.numObj == 0U)
   {
      return;
   }
   
   pool.data = data;
   splitPool();	/* all other objects */

#if defined(CCI_USE_ARCHIVE)
   for (uint8_t idx = POOL::ALL; idx < POOL::SIZE; idx++)
   {
      PoolData &pool = m_pool[idx];
      if (pool.numObj > 0)
      {
         pool.archive = AppArchive::compress(pool.data);
      }
   }
#endif /* defined(CCI_USE_ARCHIVE) */

   if (m_pool[POOL::ALL].numObj != (m_pool[POOL::ROOT].numObj + 
                            m_pool[POOL::AUX].numObj +
                            m_pool[POOL::IMG256].numObj +
                            m_pool[POOL::REMAIN].numObj))
   {
      for (uint8_t idx = POOL::ALL; idx < POOL::SIZE; idx++)
      {
         m_pool[idx] = PoolData();
      }
   }
}

AppPool::~AppPool()
{
}

uint32_t AppPool::splitPool()	/* all other objects */
{
   uint32_t maxObjSize = 0U; /* max object size not counting images */
   uint32_t poolSize = static_cast<uint32_t>(m_pool[POOL::ALL].data.size());
   const uint8_t* poolDataIn = m_pool[POOL::ALL].data.data();

   for (uint8_t idx = POOL::ROOT; idx < POOL::SIZE; idx++)
   {
      m_pool[idx].data.clear();
   }

   if (poolSize > 0U)
   {
      uint32_t poolIdx[POOL::SIZE];
      for (uint8_t idx = POOL::ALL; idx < POOL::SIZE; idx++)
      {
         poolIdx[idx] = 0U;
      }

      for (uint8_t idx = POOL::ROOT; idx < POOL::SIZE; idx++)
      {
         m_pool[idx].data.resize(poolSize, 0U);
      }

      while (poolIdx[POOL::ALL] < poolSize)
      {
         const iso_u8* poolData = &poolDataIn[poolIdx[POOL::ALL]];
         iso_u32 objectSize = IsoVtcPoolObjSize(poolData);
         if (objectSize > 0)
         {
            OBJTYP_e eObjTyp = (OBJTYP_e)poolData[2];
            switch (eObjTyp)
            {
            case WorkingSet:  /* Top level object describes an implement (working set). */
               memmove(&m_pool[POOL::ROOT].data[poolIdx[POOL::ROOT]], poolData, objectSize);
               poolIdx[POOL::ROOT] += objectSize;
               if (maxObjSize < objectSize) maxObjSize = objectSize;
               break;

               /* Picture graphic object */
            case PictureGraphic: /* Used to output a picture graphic (bitmap). */
            {
               ISOGRAPH_TYPE_e type = (ISOGRAPH_TYPE_e)poolData[9];
               if (type <= colour_256)
               {
                  memmove(&m_pool[POOL::IMG256].data[poolIdx[POOL::IMG256]], poolData, objectSize);
                  poolIdx[POOL::IMG256] += objectSize;

                  if (type <= colour_16)
                  {
                     memmove(&m_pool[POOL::IMG16].data[poolIdx[POOL::IMG16]], poolData, objectSize);
                     poolIdx[POOL::IMG16] += objectSize;
                  }
                  else
                  {
                     iso_u32 u32ObjSize = 0UL; // objectSize;
/*                     if (IsoVtc_PoolObjPictureConvert(poolData,
                        (uint32_t)m_pool[POOL::IMG16].data.size(),
                        (uint32_t)poolIdx[POOL::IMG16],
                        &m_pool[POOL::IMG16].data[poolIdx[POOL::IMG16]],
                        &u32ObjSize, colour_16) == E_NO_ERR) */
                     if (IsoVtcPoolConvertPictureObject(poolData,
                        &m_pool[POOL::IMG16].data[poolIdx[POOL::IMG16]],
                        ((uint32_t)m_pool[POOL::IMG16].data.size() - (uint32_t)poolIdx[POOL::IMG16]),
                        colour_16, &u32ObjSize) == E_NO_ERR)
                     {
                        poolIdx[POOL::IMG16] += u32ObjSize;
                     }
                  }

                  if (type == monochrome)
                  {
                     memmove(&m_pool[POOL::IMG2].data[poolIdx[POOL::IMG2]], poolData, objectSize);
                     poolIdx[POOL::IMG2] += objectSize;
                  }
                  else
                  {
                     iso_u32 u32ObjSize = 0UL; // objectSize;
                     /* if (IsoVtc_PoolObjPictureConvert(poolData,
                        (uint32_t)m_pool[POOL::IMG2].data.size(),
                        (uint32_t)poolIdx[POOL::IMG2],
                        &m_pool[POOL::IMG2].data[poolIdx[POOL::IMG2]],
                        &u32ObjSize, monochrome) == E_NO_ERR) */
                     if (IsoVtcPoolConvertPictureObject(poolData,
                        &m_pool[POOL::IMG2].data[poolIdx[POOL::IMG2]],
                        ((uint32_t)m_pool[POOL::IMG2].data.size() - (uint32_t)poolIdx[POOL::IMG2]),
                        monochrome, &u32ObjSize) == E_NO_ERR)
                     {
                        poolIdx[POOL::IMG2] += u32ObjSize;
                     }
                  }
               }
               break;
            }

               /* Auxiliary control */
            case AuxiliaryFunction2: /* Defines the designator and function type 2. OK*/
               memmove(&m_pool[POOL::AUX].data[poolIdx[POOL::AUX]], poolData, objectSize);
               poolIdx[POOL::AUX] += objectSize;
               if (maxObjSize < objectSize) maxObjSize = objectSize;
               break;

            default:
               memmove(&m_pool[POOL::REMAIN].data[poolIdx[POOL::REMAIN]], poolData, objectSize);
               poolIdx[POOL::REMAIN] += objectSize;
               if (maxObjSize < objectSize) maxObjSize = objectSize;
               break;
            }

            poolIdx[POOL::ALL] += objectSize;
         }
         else
         { /* invalid pool */
            poolIdx[POOL::ALL] = poolSize;	/* abort loop */
            m_pool[POOL::ROOT].data.clear();
            m_pool[POOL::AUX].data.clear();
            m_pool[POOL::IMG256].data.clear();
            m_pool[POOL::REMAIN].data.clear();
            break;
         }
      }

      /* produce output */
      for (uint8_t idx = POOL::ROOT; idx < POOL::SIZE; idx++)
      {
         std::vector<uint8_t>& data = m_pool[idx].data;
         int32_t newPoolSize = (int32_t)poolIdx[idx];
         data.resize(newPoolSize);
         m_pool[idx].numObj = IsoVtcGetNumofPoolObjs(data.data(), newPoolSize);
      }
   }

   return maxObjSize;
}

bool AppPool::open(uint32_t mode)
{
   //m_poolOnlyDriverDetails = (mode & POOL_ONLY_DRIVER_DETAILS) != 0U;
   //m_graphicType = static_cast<ISOGRAPH_TYPE_e>(mode & 0x03);
   // language
//	uint32_t exception = 0;

   m_data = m_pool[POOL::ROOT].data;
   m_data.insert(m_data.end(), m_pool[POOL::AUX].data.begin(), m_pool[POOL::AUX].data.end());

   if ((mode & POOL_ONLY_DRIVER_DETAILS) == 0U)
   {
      m_data.insert(m_data.end(), m_pool[POOL::IMG256].data.begin(), m_pool[POOL::IMG256].data.end());
      m_data.insert(m_data.end(), m_pool[POOL::REMAIN].data.begin(), m_pool[POOL::REMAIN].data.end());
   }

   if ((mode & POOL_ONLY_GAUX_OBJECTS) != 0U)
   {
      uint32_t poolSize = (uint32_t)(m_data.size());
      reduceAuxPool(m_data.data(), &poolSize);  // implementation is a copy from GAux.c
      m_data.resize(poolSize);
   }

   m_numObj = IsoVtcGetNumofPoolObjs(m_data.data(), (iso_s32)m_data.size());
   m_pos = 0U;

#if defined(CCI_USE_ARCHIVE)
   m_pool[POOL::ROOT  ].channel = AppArchive::open(m_pool[POOL::ROOT  ].archive);
   m_pool[POOL::AUX   ].channel = AppArchive::open(m_pool[POOL::AUX   ].archive);
// m_pool[POOL::IMG2  ].channel = AppArchive::open(m_pool[POOL::IMG2  ].archive);
// m_pool[POOL::IMG16 ].channel = AppArchive::open(m_pool[POOL::IMG16 ].archive);
   m_pool[POOL::IMG256].channel = AppArchive::open(m_pool[POOL::IMG256].archive);
   m_pool[POOL::REMAIN].channel = AppArchive::open(m_pool[POOL::REMAIN].archive);
#endif /* defined(CCI_USE_ARCHIVE) */

   return m_data.size() > 0;
}

uint32_t AppPool::read(uint8_t* dst, uint32_t u32BlockSizeReq)
{
#if !defined(CCI_USE_ARCHIVE)
   if ((m_data.empty()) || (dst==nullptr))
   {
      return UINT32_MAX;
   }

   if (m_pos >= m_data.size())
   {
      return UINT32_MAX;
   }

   if ((m_pos + u32BlockSizeReq) > m_data.size())
   {
      u32BlockSizeReq = static_cast<uint32_t>(m_data.size() - m_pos);
   }

   memcpy(dst, &m_data[m_pos], u32BlockSizeReq);
   m_pos += u32BlockSizeReq;
   return u32BlockSizeReq;

#else // !defined(CCI_USE_ARCHIVE)
   uint32_t ret = 0U;
   uint8_t idx = 1U;
   for (idx = POOL::ROOT; idx < POOL::SIZE; idx++)
   {
      PoolData &poolData = m_pool[idx];
      if (poolData.channel == 0)
      {
         continue;
      }

      ret = AppArchive::read(poolData.channel, dst, u32BlockSizeReq);
      if (ret <= u32BlockSizeReq)
      {
         m_pos += ret;
         iso_DebugPrint("%d/%d: %d %d\n", idx, poolData.channel, ret, m_pos);
         break;
      }
   }

   if (idx == POOL::SIZE)
   {
      ret = UINT32_MAX;
   }

   return ret;
#endif /* !defined(CCI_USE_ARCHIVE) */
}

const std::vector<uint8_t>& AppPool::getOriginalPool() const
{
   return m_pool[POOL::ALL].data;
}

const std::vector<uint8_t>& AppPool::getOpenPool() const
{
   return m_data;
}

void AppPool::close()
{
   m_data.clear();
}

bool AppPool::isOpen()const
{
   return m_data.size() > 0;
}

uint32_t AppPool::getPos()const
{
   return (m_data.size() > 0) ? m_pos : UINT32_MAX;
}

uint32_t AppPool::getSize()const
{
   return (m_data.size() > 0) ? static_cast<uint32_t>(m_pool[POOL::ALL].data.size()) : 0U;
}

void AppPool::seekToBegin()
{
#if defined(CCI_USE_ARCHIVE)
   for (uint8_t idx = POOL::ALL; idx < POOL::SIZE; idx++)
   {
      PoolData &poolData = m_pool[idx];
      AppArchive::seekToBegin(poolData.channel);
   }
#endif /* defined(CCI_USE_ARCHIVE) */
   
   m_pos = 0;
}

uint16_t AppPool::getNumObj()const
{
   return m_numObj;
}

uint32_t AppPool::getMaxObjectSize()const
{
   return (uint32_t)m_pool[POOL::ALL].data.size();
}

static void reduceAuxPool(iso_u8 pu8PoolDataInOut[], iso_u32* pu32PoolSizeInOut)
{
   if ((pu8PoolDataInOut != NULL) && (pu32PoolSizeInOut != NULL))
   {
      iso_u32 u32PoolSrcIdx = 0;
      iso_u32 u32PoolCopyIdx = 0;
      iso_u32 u32PoolSize = *pu32PoolSizeInOut;
      while (u32PoolSrcIdx < u32PoolSize)
      {
         iso_bool copyObject = ISO_FALSE;
         iso_u8* poolData = &pu8PoolDataInOut[u32PoolSrcIdx];
         iso_u32 objectSize = IsoVtcPoolObjSize(poolData);
         iso_u32 newObjectSize = objectSize;
         //          iso_u16 objectID = getU16(poolData);
         OBJTYP_e eObjTyp = (OBJTYP_e)poolData[2];
         switch (eObjTyp)
         {
         case WorkingSet:  /* Top level object describes an implement (working set). */
            copyObject = ISO_TRUE;
            break;

            /* Picture graphic object */
         case PictureGraphic: /* Used to output a picture graphic (bitmap). */
         {
            iso_u16 width = bufferGetU16(&poolData[5]);
            iso_u16 hight = bufferGetU16(&poolData[7]);
            if ((width <= 64U) && (hight <= 64U))
            {
               copyObject = ISO_TRUE;
            }
            else if ((width <= 128U) && (hight <= 128U))
            {	// e.g. crop all pictures smaller then 128 pix.
               if (IsoPoolCropCenterOfPictureObject(poolData, 64, 64, &newObjectSize) == E_NO_ERR)
               {
                  copyObject = ISO_TRUE;
               }
            }
            else { /* skip picture object */ }
            break;
         }

         /* Auxiliary control */
         case AuxiliaryFunction2: /* Defines the designator and function type 2. OK*/
         {
            iso_u8 auxFunctionType = poolData[4] & 0x0FU;
            if (auxFunctionType == 2)   // non latching boolean
            {
               copyObject = ISO_TRUE; // in use for a break point.
            }

            break;
         }
#if 1    /* object pointer object - CCI A3 feature BugID 11522 */
         case ObjectPointer:
            copyObject = ISO_TRUE;
            break;
#endif 
         default:
            break;
         }

         if ((copyObject != ISO_FALSE) && (newObjectSize > 0))
         {
            memmove(&pu8PoolDataInOut[u32PoolCopyIdx], poolData, newObjectSize);
            u32PoolCopyIdx += newObjectSize;
         }

         u32PoolSrcIdx += objectSize;
      }

      *pu32PoolSizeInOut = u32PoolCopyIdx;
   }
   else
   {
      if (pu32PoolSizeInOut != NULL)
      {
         *pu32PoolSizeInOut = 0;
      }
   }
}

/* ************************************************************************ */
