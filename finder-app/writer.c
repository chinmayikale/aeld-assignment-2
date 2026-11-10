#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <syslog.h>

int main(int argc, char *argv[]) {
    // Open connection to syslog, using LOG_USER facility
    openlog("writer", LOG_PID, LOG_USER);

    // Check if exactly two arguments are provided (file path and string)
    if (argc != 3) {
        syslog(LOG_ERR, "Error: Invalid number of arguments. Expected 2, got %d", argc - 1);
        fprintf(stderr, "Usage: %s <file_path> <string_to_write>\n", argv[0]);
        closelog();
        return 1;
    }

    const char *writefile = argv[1];
    const char *writestr = argv[2];

    // Open the file for writing (create if it doesn't exist, truncate if it does, rw-r--r--)
    int fd = open(writefile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        syslog(LOG_ERR, "Error: Failed to open file %s for writing", writefile);
        perror("open");
        closelog();
        return 1;
    }

    // Write the string to the file
    ssize_t bytes_written = write(fd, writestr, strlen(writestr));
    if (bytes_written == -1) {
        syslog(LOG_ERR, "Error: Failed to write to file %s", writefile);
        perror("writer");
        close(fd);
        closelog();
        return 1;
    }

    // Log the required debug message: "Writing <string> to <file>"
    syslog(LOG_DEBUG, "Writing %s to %s", writestr, writefile);

    // Clean up and close
    if (close(fd) == -1) {
        syslog(LOG_ERR, "Error: Failed to close file %s", writefile);
        perror("close");
        closelog();
        return 1;
    }

    closelog();
    return 0;
}
