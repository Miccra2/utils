#pragma once
#ifndef __POSITION_H__
#define __POSITION_H__

#include <stddef.h> // size_t

typedef struct Position {
    char   *begin;
    char   *end;
    char   *offset;
    size_t line;
} Position;

Position new_position(char *begin, char *end, char *offset, size_t line) {
    return (Position){.begin=begin, .end=end, .offset=offset, .line=line};
}

#endif // __POSITION_H__
