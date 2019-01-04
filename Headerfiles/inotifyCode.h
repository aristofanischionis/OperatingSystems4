#ifndef INOTIFYCODE_HEADER
#define INOTIFYCODE_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <poll.h>
#include <dirent.h>
#include <sys/stat.h>
#include "monitoring.h"
//The fixed size of the event buffer:
#define EVENT_SIZE  ( sizeof (struct inotify_event) )

//The size of the read buffer: estimate 1024 events with 16 bytes per name over and above the fixed size above
#define EVENT_BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )

//helper function prototypes
const char * eventName(struct inotify_event *event);
void fail(const char *message) ;
void recursiveWatch(char *source, int fd);
void handleEvents(int fd, int watched, WDmapping *map);
void rmWD(WDmapping *map, int watched, int fd);

#endif
