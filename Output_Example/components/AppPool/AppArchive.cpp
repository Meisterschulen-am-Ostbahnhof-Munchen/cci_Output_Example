#include <stdint.h>
#include <vector>
#include <map>
#include "IsoCommonDef.h"
#if defined(CCI_USE_ARCHIVE)
#include "AppArchive.h"

extern "C"
{
#include "heatshrink/heatshrink_decoder.h"
#include "heatshrink/heatshrink_encoder.h"
}

#if HEATSHRINK_STATIC_INPUT_BUFFER_SIZE != 64
#error "Set define HEATSHRINK_STATIC_INPUT_BUFFER_SIZE to 64."
#endif /* HEATSHRINK_STATIC_INPUT_BUFFER_SIZE != 64 */
#if HEATSHRINK_USE_INDEX != 0
#error "Set define HEATSHRINK_USE_INDEX to 0."
#endif /* HEATSHRINK_USE_INDEX != 0 */

struct HeatshrinkDecoderInfo
{
   HeatshrinkDecoderInfo(std::vector<uint8_t>& archiveIn)
      : archive(&archiveIn)
   {
      heatshrink_decoder_reset(&hd);
   }

   void seekToBegin()
   {
      heatshrink_decoder_reset(&hd);
      sunk = 0;
      fres = HSDR_FINISH_MORE;
   }

   std::vector<uint8_t>* archive = nullptr;
   heatshrink_decoder hd;
   size_t sunk = 0;
   int8_t fres = HSDR_FINISH_MORE;
};

static size_t compress_and_expand_and_check(const uint8_t *input, size_t input_size, uint8_t** data_out, size_t* dataSize_out);
static std::vector<uint8_t> compressPool(const std::vector<uint8_t>& poolData);
/* modified copy from heatshrink static encoder test. */
static std::vector<uint8_t> expandPool(HeatshrinkDecoderInfo& hsd, const uint8_t *comp, size_t compressed_size, size_t decomp_sz);

namespace AppArchive
{
   static std::map<uint8_t, HeatshrinkDecoderInfo*> s_hsd;

   static uint8_t getNextChannel()
   {
      static uint8_t hsdIdx = 1U;
      if (s_hsd.size() >= 128U)  /* We only allow up to 128 open archives. */
      {
         return 0U;
      }

      std::map<uint8_t, HeatshrinkDecoderInfo*>::iterator it = s_hsd.find(hsdIdx);
      while (it != s_hsd.end())
      {
         hsdIdx++; /* start index at 1; '0' is invalid channel */
         if (hsdIdx == 0U)
         {
            hsdIdx = 1U;
         }

         it = s_hsd.find(hsdIdx);
      }

      return hsdIdx;
   }

   std::vector<uint8_t> compress(const std::vector<uint8_t>& poolData)
   {
      return compressPool(poolData);
   }

   std::vector<uint8_t> expand(uint8_t channel, const uint8_t *comp, size_t compressed_size, size_t decomp_sz)
   {
      return std::vector<uint8_t>();
   }

   uint8_t open(std::vector<uint8_t>& archive)
   {
      if (archive.empty())        /* There is nothing to do on an empty archive. */
      {
         return 0U;
      }

      uint8_t hsdIdx = getNextChannel();
      if (hsdIdx == 0)
      {
         return 0U;
      }

      HeatshrinkDecoderInfo* hsd = new HeatshrinkDecoderInfo(archive);
      s_hsd[hsdIdx] = hsd;
      return hsdIdx;
   }

   uint32_t read(uint8_t channel, uint8_t* dst, uint32_t u32BlockSizeReq)
   {
      std::map<uint8_t, HeatshrinkDecoderInfo*>::iterator it = s_hsd.find(channel);
      if (it == s_hsd.end())
      {
         return UINT32_MAX;
      }

      HeatshrinkDecoderInfo* hsdInfo = it->second;
      if (hsdInfo == nullptr)
      {
         s_hsd.erase(it);
         return UINT32_MAX;
      }

      size_t dstIdx = 0U;
      while ((hsdInfo->fres == HSDR_FINISH_MORE) && (dstIdx < u32BlockSizeReq))
      {
         std::vector<uint8_t> poolData = expandPool(*hsdInfo,
            hsdInfo->archive->data(),
            (uint32_t)hsdInfo->archive->size(),
            (u32BlockSizeReq - dstIdx));
         if (!poolData.empty())
         {
            memcpy(&dst[dstIdx], poolData.data(), poolData.size());
            dstIdx += poolData.size();
#if defined(CCI_ARCHIVE_EARLY_ABORT) /* Set abort condition. Only one decompression run. */
            break;
#endif /* defined(CCI_ARCHIVE_EARLY_ABORT) */
         }
         else
         {
            hsdInfo->fres = heatshrink_decoder_finish(&hsdInfo->hd);
            if (hsdInfo->fres != HSDR_FINISH_DONE)
            {
               return UINT32_MAX;	//ASSERT_EQ(HSDR_FINISH_DONE, fres);
            }
         }
      }

      if (hsdInfo->fres != HSDR_FINISH_MORE)
      {
         hsdInfo->fres = HSDR_FINISH_DONE;
         heatshrink_decoder_reset(&hsdInfo->hd);
         hsdInfo->sunk = 0;
      }
      if (dstIdx > u32BlockSizeReq) /* EOF */
      {
         dstIdx = UINT32_MAX;
         hsdInfo->fres = HSDR_FINISH_DONE;
         heatshrink_decoder_reset(&hsdInfo->hd);
         hsdInfo->sunk = 0;
      }

      return (dstIdx == 0U) ? UINT32_MAX : (uint32_t)dstIdx;
   }

   void seekToBegin(uint8_t channel)
   {
      std::map<uint8_t, HeatshrinkDecoderInfo*>::iterator it = s_hsd.find(channel);
      if (it != s_hsd.end())
      {
         it->second->seekToBegin();
      }
   }

   void close(uint8_t channel)
   {

   }

} /* namespace AppArchive */

std::vector<uint8_t> compressPool(const std::vector<uint8_t>& poolData)
{
   uint8_t* data = nullptr;
   size_t dataSize = 0U;
   std::vector<uint8_t> res;

   size_t check = compress_and_expand_and_check(poolData.data(), poolData.size(), &data, &dataSize);

   if ((data != nullptr) && (dataSize > 0) && (check != UINT32_MAX))
   {
      res.resize(dataSize);
      memcpy(res.data(), data, dataSize);
      free(data);
   }

   return res;
}

size_t compress_and_expand_and_check(const uint8_t *input, size_t input_size, uint8_t** data_out, size_t* dataSize_out)
{
   static heatshrink_encoder hse;
   static heatshrink_decoder hsd;

   heatshrink_encoder_reset(&hse);
   heatshrink_decoder_reset(&hsd);
   size_t comp_sz = input_size + (input_size / 2) + 4;
   size_t decomp_sz = input_size + (input_size / 2) + 4;
   uint8_t *comp = (uint8_t*)malloc(comp_sz);
   uint8_t *decomp = (uint8_t*)malloc(decomp_sz);
   if (comp == NULL) return UINT32_MAX;
   if (decomp == NULL) return UINT32_MAX;
   memset(comp, 0, comp_sz);
   memset(decomp, 0, decomp_sz);

   size_t count = 0;
   size_t sunk = 0;
   size_t polled = 0;
   while (sunk < input_size)
   {
      HSE_sink_res sres = heatshrink_encoder_sink(&hse, (uint8_t*)&input[sunk], input_size - sunk, &count);
      if (sres < 0) return UINT32_MAX;
      sunk += count;
      if (sunk == input_size)
      {
         HSE_finish_res fres = heatshrink_encoder_finish(&hse);
         if (fres != HSER_FINISH_MORE) return UINT32_MAX;
      }

      HSE_poll_res pres;
      do {                    /* "turn the crank" */
         pres = heatshrink_encoder_poll(&hse, &comp[polled], comp_sz - polled, &count);
         if (pres < 0) return UINT32_MAX;
         polled += count;
      } while (pres == HSER_POLL_MORE);
      if (pres != HSER_POLL_EMPTY) return UINT32_MAX;
      if (polled >= comp_sz) return UINT32_MAX;
      if (sunk == input_size)
      {
         HSE_finish_res fres = heatshrink_encoder_finish(&hse);
         if (fres != HSER_FINISH_DONE) return UINT32_MAX;
      }
   }
   size_t compressed_size = polled;
   sunk = 0;
   polled = 0;

   while (sunk < compressed_size)
   {
      HSD_sink_res sres = heatshrink_decoder_sink(&hsd, &comp[sunk], compressed_size - sunk, &count);
      if (sres < 0) return UINT32_MAX;
      sunk += count;
      if (sunk == compressed_size)
      {
         HSD_finish_res fres = heatshrink_decoder_finish(&hsd);
         if (fres != HSDR_FINISH_MORE) return UINT32_MAX;
      }

      HSD_poll_res pres;
      do {
         pres = heatshrink_decoder_poll(&hsd, &decomp[polled],
            30/*decomp_sz - polled*/, &count);
         if (pres < 0) return UINT32_MAX;
         polled += count;
      } while (pres == HSDR_POLL_MORE);
      if (pres != HSDR_POLL_EMPTY) return UINT32_MAX;
      if (sunk == compressed_size) {
         HSD_finish_res fres = heatshrink_decoder_finish(&hsd);
         if (fres != HSDR_FINISH_DONE) return UINT32_MAX;
      }

      if (polled > input_size) return UINT32_MAX;
   }

   if (polled != input_size) return UINT32_MAX;

   for (size_t i = 0; i < input_size; i++)
   {
      if (input[i] != decomp[i])
         return UINT32_MAX;
   }

   if ((data_out != 0) & (dataSize_out != 0))
   {
      *data_out = comp;
      *dataSize_out = sunk;
   }
   else
   {
      free(comp);
   }

   free(decomp);
   return 0;
}

std::vector<uint8_t> expandPool(HeatshrinkDecoderInfo& hsd, const uint8_t *comp, size_t compressed_size, size_t decomp_sz)
{
   size_t polled = 0;
   std::vector<uint8_t> decomp(decomp_sz);
   memset(decomp.data(), 0, decomp_sz);

   /* read previously decompressed data */
   HSD_poll_res pres = HSDR_POLL_MORE;
   while ((pres == HSDR_POLL_MORE) && (decomp_sz > polled))
   {
      size_t count = 0;
      pres = heatshrink_decoder_poll(&hsd.hd, &decomp[0], decomp_sz, &count);
      polled += count;
   }

   /* decompress until all data is parsed or limit is reached */
   HSD_sink_res sres = HSDR_SINK_OK;
   while ((hsd.sunk < compressed_size) && (decomp_sz > polled))
   {
      size_t count = 0;
      sres = heatshrink_decoder_sink(&hsd.hd, (uint8_t*)&comp[hsd.sunk], compressed_size - hsd.sunk, &count);
      hsd.sunk += count;
      if (hsd.sunk == compressed_size)
      {
         HSD_finish_res fres = heatshrink_decoder_finish(&hsd.hd);
         if (fres != HSDR_FINISH_MORE)
         {
            return std::vector<uint8_t>();	//ASSERT_EQ(HSDR_FINISH_MORE, heatshrink_decoder_finish(&hsd));
         }
      }

      pres = HSDR_POLL_MORE;
      while ((pres == HSDR_POLL_MORE) && (decomp_sz > polled))
      {
         pres = heatshrink_decoder_poll(&hsd.hd, &decomp[polled], decomp_sz - polled, &count);
         polled += count;
#if defined(CCI_ARCHIVE_EARLY_ABORT) /* Set abort condition. Only one decompression run. */
         decomp_sz = polled;
         decomp.resize(polled);
#endif defined(CCI_ARCHIVE_EARLY_ABORT)
      }
   }

   if (decomp_sz > polled)
   {
      decomp.resize(polled);
   }

   return decomp;
}

#endif /* defined(CCI_USE_ARCHIVE) */
