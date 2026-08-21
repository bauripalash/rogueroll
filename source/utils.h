#ifndef PBGBA_UTILS_H
#define PBGBA_UTILS_H
#include <stdbool.h>

typedef struct Vec2 {
    int x;
    int y;
} Vec2;

#define NewVec2(x, y) ((Vec2){x, y})

#ifndef NDEBUG
#include "external/mgba.h"
#define LOG_INIT() mgba_open()
#define LOG_DEBUG(fmt, ...)                                                    \
    mgba_printf(MGBA_LOG_DEBUG, "[DEBUG]" fmt "\n", ##__VA_ARGS__)
#define LOG_INFO(fmt, ...)                                                     \
    mgba_printf(MGBA_LOG_INFO, "[INFO] " fmt "\n", ##__VA_ARGS__)
#define LOG_WARN(fmt, ...)                                                     \
    mgba_printf(MGBA_LOG_WARN, "[WARN] " fmt "\n", ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...)                                                    \
    mgba_printf(MGBA_LOG_ERROR, "[ERROR] " fmt "\n", ##__VA_ARGS__)
#define LOG_FATAL(fmt, ...)                                                    \
    mgba_printf(MGBA_LOG_FATAL, "[FATAL] " fmt "\n", ##__VA_ARGS__)

#else

// Zero-overhead production stubs
#define LOG_INIT()          ((void)0)
#define LOG_DEBUG(fmt, ...) ((void)0)
#define LOG_INFO(fmt, ...)  ((void)0)
#define LOG_WARN(fmt, ...)  ((void)0)
#define LOG_ERROR(fmt, ...) ((void)0)
#define LOG_FATAL(fmt, ...) ((void)0)

#endif

#endif
