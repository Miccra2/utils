/* made after tsodings Dynamic Array implementation */
#pragma once
#ifndef __DYNAMIC_ARRAY_H__
#define __DYNAMIC_ARRAY_H__

#include <stdint.h> // uint8_t, uint16_t, uint32_t, uint64_t, int8_t, int16_t, int32_t, int64_t
#include <stddef.h> // size_t, ssize_t, NULL
#include <stdlib.h> // malloc, realloc, free
#include <assert.h> // assert

#include "macro.h"
#include "logger.h"

/* General structure of a dynamic array.

typedef struct DynamicArray {
    size_t capacity;
    size_t length;
    void   *items;
} DynamicArray;

where `void` has to be replaced with a type. */

#ifndef DA_MIN_CAP
#define DA_MIN_CAP (512)
#endif // DA_MIN_CAP

#define DA_NEW(da)                      ((da){.capacity=0, .length=0, .items=NULL})
#define DA_FROM_PTR(da, ptr, count)     (UNIMPLEMENTED("DA_FORM_PTR"))
#define DA_FROM_ARRAY(da, array, count) (UNIMPLEMENTED("DA_FROM_ARRAY"))

#define DA_DELETE(da) ({    \
    free((da).items);       \
    (da).items    = NULL;   \
    (da).length   = 0;      \
    (da).capacity = 0;      \
})

#define DA_GET(da, index)            (UNIMPLEMENTED("DA_GET"))
#define DA_ALLOC(da, length)         (UNIMPLEMENTED("DA_ALLOC"))
#define DA_PUSHF(da, item)           (UNIMPLEMENTED("DA_PUSHF"))
#define DA_POPF(da)                  (UNIMPLEMENTED("DA_POPF"))
#define DA_APPENDF(da, items, count) (UNIMPLEMENTED("DA_APPENDF"))
#define DA_PUSHB(da, item)           (UNIMPLEMENTED("DA_PUSHB"))
#define DA_POPB(da)                  (UNIMPLEMENTED("DA_POPB"))
#define DA_APPENDB(da, items, count) (UNIMPLEMENTED("DA_APPENDB"))

typedef struct U8_DA {
    size_t  capacity;
    size_t  length;
    uint8_t *items;
} U8_DA;

typedef struct U16_DA {
    size_t   capacity;
    size_t   length;
    uint16_t *items;
} U16_DA;

typedef struct U32_DA {
    size_t   capacity;
    size_t   length;
    uint32_ t *items;
} U32_DA;

typedef struct U64_DA {
    size_t   capacity;
    size_t   length;
    uint64_t *items;
} U64_DA;

typedef struct USIZE_DA {
    size_t capacity;
    size_t length;
    size_t *items;
} USIZE_DA;

typedef struct I8_DA {
    size_t capacity;
    size_t length;
    int8_t *items;
} I8_DA;

typedef struct I16_DA {
    size_t  capacity;
    size_t  length;
    int16_t *items;
} I16_DA;

typedef struct I32_DA {
    size_t  capacity;
    size_t  length;
    int32_t *items;
} I32_DA;

typedef struct I64_DA {
    size_t  capacity;
    size_t  length;
    int64_t *items;
} I64_DA;

typedef struct ISIZE_DA {
    size_t  capacity;
    size_t  length;
    ssize_t *items;
} ISIZE_DA;

#endif // __DYNAMIC_ARRAY_H__
