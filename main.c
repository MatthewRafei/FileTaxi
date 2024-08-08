#include <stdio.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <assert.h>

#include "ftstr.h"
//#include "utils.h"

#include "ft-inotify.h"

// TODO
// Impliment a QUEUE
// Convert inotify event->names into ftstrings
// Parse TOML config
/* Program move criteria must include extension to work
because all sorts of programs create tmp files */

//#define DIR "~/Downloads"

// Do not allow infinite looping logic, folders should not be connected in circle or loop into each other
/*
enum Dir {
  DIR_DOCUMENTS = 0,
  DIR_MUSIC = 1,
  DIR_PICTURES = 2,
  DIR_VIDEOS = 3,
  DIR_COMPRESSED = 4,
  DIR_DISKIMG = 5,
  DIR_DB = 6,
  DIR_EXE = 7,
  DIR_FONTS = 8,
  DIR_INTERNET = 9,
  DIR_PRESENTATIONS = 10,
  DIR_PROGRAMMING_FILES = 11,
  DIR_SPREADSHEETS = 12,
  DIR_NONE = 13,
};
*/

// inotifywait -m -e close_write -e moved_to --format "%f" "$TARGET" | while read FILENAME; do
//

// static const char *const arr[] = {
//     "/Documents/Word_Processor_And_Text_files",
//     "/Music",
//     "/Pictures",
//     "/Videos",
//     "/Documents/Compressed_Files",
//     "/Documents/Disk_Images",
//     "/Documents/Data_Database"S,
//     "/Documents/Executable_File",
//     "/Documents/Fonts",
//     "/Documents/Internet_files",
//     "~/Documents/Presentation",
//     "$HOME/Documents/Programming_Files",
//     "$HOME/Documents/Spreadsheets",
// }

uint32_t
dir_from_filetype();
uint32_t
filetype_from_ext();

// Returns 1 if the computer is on.
// Else value is undefined.
uint32_t
is_computer_on() {
  return 1;
}

void
move_file();
/*
void
test_strs() {
   // Create ftstr string
   struct ftstr test_ftstr = ftstr_create();
   // Test the size of .value should be the same as char
   assert(sizeof(*(test_ftstr.value)) == sizeof(char));
   // Test capacity should be 1
   assert(test_ftstr.cap == 1);
   // Test length should be 0 as 0 indexed
   assert(test_ftstr.len == 0);
   // Test wether the character was set to null terminator or not
   assert(test_ftstr.value[0] == '\0');

   // Create new c str and set it equal to "Hello, world!"
   char *cstr = "Hello, world!";
   // Turn newly created c str to ftstr
   struct ftstr cstr_to_ftstr = ftstr_from_cstr(cstr);
   // Set the value of ftstr to the c str value.
   test_ftstr = ftstr_from_cstr(cstr);

   // Test if contents of value for both ftstr structs are the same
   assert(*(test_ftstr.value) == *(cstr_to_ftstr.value));

   // test_ftstr2 is equal to test_ftstr
   struct ftstr test_ftstr2 = ftstr_from_ftstr(&test_ftstr);

   // These should have the same value
   assert(*(test_ftstr2.value) == *(test_ftstr.value));
}
*/

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

    printf("size = %zu\n", sizeof(struct ftstr));

    struct ftstr str = ftstr_from_cstr("foo bar baz");

    size_t len = 0;
    struct ftstr *lst = ftstr_from_split_on_delim(&str, ' ', &len);

    for (size_t i = 0; i < len; ++i) {
        ftstr_dump(&lst[i]);
        putchar('\n');
    }

    // If we create ftstr from ftstr_from_cstr than all we need to do is free.
    free(str.value);
    //free(lst->value);
    //free(lst);

    //test_strs();

    printf("What is argv[1] : %s\n", argv[1]);

    //int ch;
    do {
        char* newly_created_file = inotify_watch_dir(argv[1]);
        printf("The newly created file is %s\n", newly_created_file);
    }while(1);

    //printf("What is the size of char in int %d\n", (int)sizeof(char));

    (void)argc;
    return 0;
}
