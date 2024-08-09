#include <stdio.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <assert.h>

#include "ftstr.h"
#include "ft-inotify.h"

// TODO
// Convert inotify event->names into ftstrings
// Impliment a QUEUE
// Parse TOML config
/* Program move criteria must include extension to work
   because all sorts of programs create tmp files */

uint32_t
dir_from_filetype();

uint32_t
filetype_from_ext();

void
move_file();

int
main(int argc, char* argv[]) {

  if(argc < 2) {
    printf("You need to specify a directory to watch\n");
    exit(1);
  }

  if(argc > 2) {
    printf("Too many arguments I only need a directory to watch\n");
    exit(1);
  }

  printf("What is argv[1] : %s\n", argv[1]);


  struct ftstr newly_created_file = ftstr_create();
  
  do {
    newly_created_file = inotify_watch_dir();
    printf("We got a file named : %s\n", newly_created_file.value);
  }while(1);

  (void)argc;
  return 0;
}
