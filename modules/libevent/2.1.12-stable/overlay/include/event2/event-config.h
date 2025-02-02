#ifndef EVENT2_EVENT_CONFIG_H_INCLUDED_
#define EVENT2_EVENT_CONFIG_H_INCLUDED_

#if defined(__linux__)
#include <event2/event-config_linux.h>
#elif defined(__APPLE__)
#include <event2/event-config_apple.h>
#endif

#endif  // EVENT2_EVENT_CONFIG_H_INCLUDED_
