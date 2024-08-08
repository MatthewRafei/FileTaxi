#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/inotify.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define EVENT_SIZE  (sizeof(struct inotify_event))
#define EVENT_BUF_LEN (1024 * (EVENT_SIZE + 16))

void move_file(const char *src_path, const char *dest_dir, const char *filename);
const char* get_dest_directory(const char *extension);

int main() {
    int length, i = 0;
    int fd;
    int wd;
    char buffer[EVENT_BUF_LEN];

    fd = inotify_init();
    if (fd < 0) {
        perror("inotify_init");
        exit(EXIT_FAILURE);
    }

    wd = inotify_add_watch(fd, getenv("HOME"), IN_CLOSE_WRITE | IN_MOVED_TO);
    if (wd < 0) {
        perror("inotify_add_watch");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("Monitoring directory for new files...\n");

    while (1) {
        length = read(fd, buffer, EVENT_BUF_LEN);
        if (length < 0) {
            perror("read");
            close(fd);
            exit(EXIT_FAILURE);
        }

        while (i < length) {
            struct inotify_event *event = (struct inotify_event *)&buffer[i];
            if (event->len && (event->mask & (IN_CLOSE_WRITE | IN_MOVED_TO))) {
                char src_path[1024];
                snprintf(src_path, sizeof(src_path), "%s/%s", getenv("HOME"), event->name);

                struct stat file_stat;
                if (stat(src_path, &file_stat) == 0 && S_ISREG(file_stat.st_mode)) {
                    char *extension = strrchr(event->name, '.');
                    if (extension) {
                        extension++; // skip the dot
                    } else {
                        extension = "";
                    }

                    const char *dest_dir = get_dest_directory(extension);
                    if (dest_dir) {
                        move_file(src_path, dest_dir, event->name);
                    }
                }
            }
            i += EVENT_SIZE + event->len;
        }
        i = 0;
    }

    close(fd);
    return 0;
}

void move_file(const char *src_path, const char *dest_dir, const char *filename) {
    char dest_path[1024];
    snprintf(dest_path, sizeof(dest_path), "%s/%s", dest_dir, filename);

    if (access(dest_dir, F_OK) != 0) {
        if (mkdir(dest_dir, 0755) != 0) {
            perror("mkdir");
            return;
        }
    }

    if (rename(src_path, dest_path) != 0) {
        perror("rename");
        // Handle file conflicts
        if (errno == EEXIST) {
            char new_path[1024];
            int n = 0;
            while (n <= 99) {
                snprintf(new_path, sizeof(new_path), "%s/%s.%d", dest_dir, filename, n);
                if (access(new_path, F_OK) != 0) {
                    if (rename(src_path, new_path) != 0) {
                        perror("rename");
                    }
                    break;
                }
                n++;
            }
        }
    }
}

const char* get_dest_directory(const char *extension) {
    static const char *documents_dir = "/home/user/Documents";
    static const char *music_dir = "/home/user/Music";
    static const char *pictures_dir = "/home/user/Pictures";
    static const char *videos_dir = "/home/user/Videos";
    static const char *compressed_dir = "/home/user/Documents/Compressed_Files";
    static const char *disk_images_dir = "/home/user/Documents/Disk_Images";
    static const char *data_db_dir = "/home/user/Documents/Data_Database";
    static const char *executables_dir = "/home/user/Documents/Executable_Files";
    static const char *fonts_dir = "/home/user/Documents/Fonts";
    static const char *internet_files_dir = "/home/user/Documents/Internet_Files";
    static const char *presentation_dir = "/home/user/Documents/Presentation";
    static const char *programming_files_dir = "/home/user/Documents/Programming_Files";
    static const char *spreadsheets_dir = "/home/user/Documents/Spreadsheets";

    if (strstr("doc docx odt pdf rtf tex txt wks wps wpd", extension)) {
        return documents_dir;
    } else if (strstr("mp3 wav wma mid midi aif cda mpa ogg wpl", extension)) {
        return music_dir;
    } else if (strstr("jpg jpeg png ai bmp gif ico ps svg tif tiff psd", extension)) {
        return pictures_dir;
    } else if (strstr("avi wmv 3g2 3gp flv h264 m4v mkv mov mp4 mpg mpeg rm swf vob wmv", extension)) {
        return videos_dir;
    } else if (strstr("7z arj deb pkg rar rpm gz z zip", extension)) {
        return compressed_dir;
    } else if (strstr("bin dmg iso toast vcd", extension)) {
        return disk_images_dir;
    } else if (strstr("csv dat db dbf log mdb sav sql tar xml", extension)) {
        return data_db_dir;
    } else if (strstr("apk bat cgi pl com exe gadget jar py wsf", extension)) {
        return executables_dir;
    } else if (strstr("fnt fon otf ttf", extension)) {
        return fonts_dir;
    } else if (strstr("asp cer cfm css htm html js jsp php rss xhtml", extension)) {
        return internet_files_dir;
    } else if (strstr("key odp pps ppt pptx", extension)) {
        return presentation_dir;
    } else if (strstr("c class cpp cs h java sh swift vb", extension)) {
        return programming_files_dir;
    } else if (strstr("ods xlr xls xlsx", extension)) {
        return spreadsheets_dir;
    }

    return NULL;
}
