#include <stdio.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <unistd.h>

// (1024 * ((sizeof(struct inotify_event)) + 16))
#define EVENT_SIZE (sizeof(struct inotify_event))
#define BUFFER_SIZE (1024 * (EVENT_SIZE + 16))

char*
inotify_watch_dir(char *dir) {
    char buffer[BUFFER_SIZE];

    /* Initializes a new inotify instance and returns a
    file descriptor associated with a new inotify event queue. */
    int fd = inotify_init();

    // This is problem because?
    if (fd < 0) {
      perror("inotify_init");
    }

    /* add a watch to an initialized inotify instance  */
    int wd = inotify_add_watch(fd, dir, IN_CREATE);

    // This is a problem because?
    if(wd < 0) {
        perror("inotify_add_watch");
    }
    int length;
    // Infinite loop to continously watch directory.
    while((length = read(fd, buffer, BUFFER_SIZE))){
        int i = 0;
        while(i < length) {
            struct inotify_event *event = (struct inotify_event *) &buffer[i];
            if (event->mask & IN_CREATE) {
                close(fd);
                return event->name;
            }
            i += EVENT_SIZE + event->len;
        }
    }

    // Close file descriptor
    close(fd);
    return 0;
}
