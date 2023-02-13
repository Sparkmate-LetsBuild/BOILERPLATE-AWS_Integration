#pragma once

// -- SNIFFING
// Print NMEA data direct to Serial Monitor as well as Serial

// -- UPLOADING
// Print times and performance for upload tasks
// #define DEBUG_AT_COMMANDS // See all AT commands from the SIMCOM module
// #define DEBUG_HTTP_BODY   // Show HTTP bodies before sending up and HTTP responses
#define DEBUG_HTTP_STATS  // Show HTTP bodies before sending up and HTTP responses

// -- PERFORMANCE
// #define DEBUG_STACK_INFO
// #define DEBUG_BUFFER_STATS  // Show buffer stats
// #define DEBUG_BUFFER_SPEED_INFO
// #define DEBUG_CPU_PERFORMANCE

// -- STATUS LOGGER HANDLER
#define LOG_SIZE 4096
#define LOG_LEVEL_SAVE 2  // 0 is log nothing, 1 is errors, 2 is +reports/stats, 3 is warnings, 4 is everything else (see ../bricks/status_logger.h)
#define LOG_LEVEL_PRINT 3 // 0 is log nothing, 1 is errors, 2 is +reports/stats, 3 is warnings, 4 is everything else (see ../bricks/status_logger.h)

// -- DEBUGGING BYPASSES
// #define UPLOAD_ONLY_REALTIME