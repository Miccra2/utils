/* made after tsodings Dynamic Array implementation */
#pragma once
#ifndef __DYNAMIC_ARRAY_H__
#define __DYNAMIC_ARRAY_H__

#include <stdint.h> // uint8_t, uint16_t, uint32_t, uint64_t, int8_t, int16_t, int32_t, int64_t
#include <stddef.h> // size_t, ssize_t, NULL
#include <stdlib.h> // malloc, realloc, free

#include "macro.h"
#include "logger.h"

/* General structure of a dynamic array.

typedef struct DynamicArray {
    size_t capacity;
    size_t length;
    void   *items;
} DynamicArray;

where `void` has to be replaced with a type. */

#ifndef AE_DA_MIN_CAP
#define AE_DA_MIN_CAP (512)
#endif // AE_DA_MIN_CAP

#define AE_DA_NEW(da)                      ((da){.capacity=0, .length=0, .items=NULL})
#define AE_DA_FROM_PTR(da, ptr, count)     (UNIMPLEMENTED("DA_FORM_PTR"))
#define AE_DA_FROM_ARRAY(da, array, count) (UNIMPLEMENTED("DA_FROM_ARRAY"))

#define AE_DA_DELETE(da)    \
MACRO                       \
    free((da).items);       \
    (da).items    = NULL;   \
    (da).length   = 0;      \
    (da).capacity = 0;      \
ENDM

#define AE_DA_GET(da, index)
MACRO
    AE_ASSERT();
ENDM
#define AE_DA_ALLOC(da, length)              (UNIMPLEMENTED("DA_ALLOC"))
#define AE_DA_PUSH_FRONT(da, item)           (UNIMPLEMENTED("DA_PUSHF"))
#define AE_DA_POP_FRONT(da)                  (UNIMPLEMENTED("DA_POPF"))
#define AE_DA_APPEND_FRONT(da, items, count) (UNIMPLEMENTED("DA_APPENDF"))
#define AE_DA_PUSH_BACK(da, item)            (UNIMPLEMENTED("DA_PUSHB"))
#define AE_DA_POP_BACK(da)                   (UNIMPLEMENTED("DA_POPB"))
#define AE_DA_APPEND_BACK(da, items, count)  (UNIMPLEMENTED("DA_APPENDB"))

typedef struct AE_U8_DA {
    size_t  capacity;
    size_t  length;
    uint8_t *items;
} AE_U8_DA;

typedef struct AE_U16_DA {
    size_t   capacity;
    size_t   length;
    uint16_t *items;
} AE_U16_DA;

typedef struct AE_U32_DA {
    size_t   capacity;
    size_t   length;
    uint32_t *items;
} AE_U32_DA;

typedef struct AE_U64_DA {
    size_t   capacity;
    size_t   length;
    uint64_t *items;
} AE_U64_DA;

typedef struct AE_USIZE_DA {
    size_t capacity;
    size_t length;
    size_t *items;
} AE_USIZE_DA;

typedef struct AE_I8_DA {
    size_t capacity;
    size_t length;
    int8_t *items;
} AE_I8_DA;

typedef struct AE_I16_DA {
    size_t  capacity;
    size_t  length;
    int16_t *items;
} AE_I16_DA;

typedef struct AE_I32_DA {
    size_t  capacity;
    size_t  length;
    int32_t *items;
} AE_I32_DA;

typedef struct AE_I64_DA {
    size_t  capacity;
    size_t  length;
    int64_t *items;
} AE_I64_DA;

typedef struct AE_ISIZE_DA {
    size_t  capacity;
    size_t  length;
    ssize_t *items;
} AE_ISIZE_DA;

#ifndef NO_STRIP_AE_PREFIX
#define DA_NEW(da)                        AE_DA_NEW(da)
#define DA_FROM_PTR(da, ptr, count)       AE_DA_FROM_PTR(da, ptr, count)
#define DA_FROM_ARRAY(da, array, count)   AE_DA_FROM_ARRAY(da, array, count)
#define DA_DELETE(da)                     AE_DA_DELETE(da)
#define DA_GET(da, index)                 AE_DA_GET(da, index)
#define DA_ALLOC(da, length)              AE_DA_ALLOC(da, length)
#define DA_PUSH_FRONT(da, item)           AE_DA_PUSH_FRONT(da, item)
#define DA_POP_FRONT(da)                  AE_DA_POP_FRONT(da)
#define DA_APPEND_FRONT(da, items, count) AE_DA_APPEND_FRONT(da, items, count)
#define DA_PUSH_BACK(da, item)            AE_DA_PUSH_BACK(da, item)
#define DA_POP_BACK(da)                   AE_DA_POP_BACK(da)
#define DA_APPEND_BACK(da, items, count)  AE_DA_APPEND_BACK(da, items, count)
#define U8_DA           AE_U8_DA
#define U16_DA          AE_U16_DA
#define U32_DA          AE_U32_DA
#define U64_DA          AE_U64_DA
#define USIZE_DA        AE_USIZE_DA
#define I8_DA           AE_I8_DA
#define I16_DA          AE_I16_DA
#define I32_DA          AE_I32_DA
#define I64_DA          AE_I64_DA
#define ISIZE_DA        AE_ISIZE_DA
#endif // NO_STRIP_AE_PREFIX

#endif // __DYNAMIC_ARRAY_H__
