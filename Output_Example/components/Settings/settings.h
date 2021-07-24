/* ************************************************************************ */
/*!
   \file
   \brief       Helper functions for reading and writing settings to a file.
*/
/* ************************************************************************ */
#ifndef DEF_SETTINGS_H
#define DEF_SETTINGS_H

#include <stdint.h>
#include <stdlib.h>   // required for 'size_t'

#ifdef __cplusplus
extern "C" {
#endif
/* ************************************************************************ */

    int8_t   getS8(const char section[], const char key[], const int8_t defaultValue);
    int16_t  getS16(const char section[], const char key[], const int16_t defaultValue);
    int32_t  getS32(const char section[], const char key[], const int32_t defaultValue);
    int64_t  getS64(const char section[], const char key[], const int64_t defaultValue);
    uint8_t  getU8(const char section[], const char key[], const uint8_t defaultValue);
    uint16_t getU16(const char section[], const char key[], const uint16_t defaultValue);
    uint32_t getU32(const char section[], const char key[], const uint32_t defaultValue);
    uint64_t getU64(const char section[], const char key[], const uint64_t defaultValue);
    uint64_t getX64(const char section[], const char key[], const uint64_t defaultValue);
    size_t   getString(const char section[], const char key[], const char defaultValue[], char string[], size_t stringSize);

    void setS8(const char section[], const char key[], const int8_t value);
    void setS16(const char section[], const char key[], const int16_t value);
    void setS32(const char section[], const char key[], const int32_t value);
    void setS64(const char section[], const char key[], const int64_t value);
    void setU8(const char section[], const char key[], const uint8_t value);
    void setU16(const char section[], const char key[], const uint16_t value);
    void setU32(const char section[], const char key[], const uint32_t value);
    void setU64(const char section[], const char key[], const uint64_t value);
    void setX64(const char section[], const char key[], const uint64_t value);
    void setString(const char section[], const char key[], const char value[]);
    void eraseString(const char section[], const char key[]);

    void Settings_init(void);

/* ************************************************************************ */
#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* DEF_SETTINGS_H */
/* ************************************************************************ */
