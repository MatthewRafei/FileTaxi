#include <stdio.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <assert.h>

#include "ftstr.h"
#include "utils.h"

#define DIR "~/Downloads"

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

uint32_t dir_from_filetype();
uint32_t filetype_from_ext();

void move_file();

/* void test_strs() { */
/*   struct ftstr test_ftstr = ftstr_create(); */
/*   assert(test_ftstr.value == sizeof(char)); */
/*   assert(test_ftstr.cap == 1); */
/*   assert(test_ftstr.len == 0); */
/*   assert(test_ftstr.value[0] == '\0'); */

/*   char *cstr = "Hello, world!"; */
/*   struct ftstr cstr_to_ftstr = ftstr_from_cstr(cstr); */
/*   test_ftstr.value = ftstr_append_cstr(test_ftstr, cstr); */
/*   assert(if(test_ftstr.value == cstr_to_ftstr.value)); */
  
/* } */

int main(void) {
    printf("size = %zu\n", sizeof(struct ftstr));

    struct ftstr str = ftstr_from_cstr("foo bar baz");

    size_t len = 0;
    struct ftstr *lst = ftstr_from_split_on_delim(&str, ' ', &len);

    for (size_t i = 0; i < len; ++i) {
        ftstr_dump(&lst[i]);
        putchar('\n');
    }
    
    //test_strs();

    printf("What is the size of char in int %d\n", (int)sizeof(char));


    return 0;
}
