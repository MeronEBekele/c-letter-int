#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    char character;
    int integerValue = 0;

    // Open the file in read-only mode using open system call
    fd = open("letter.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // Loop to read the file every three seconds
    while (1) {
        ssize_t bytes_read = read(fd, &character, 1);

        // Check for read errors or end-of-file
        if (bytes_read == -1) {
            perror("Error reading from file");
            close(fd);
            return 1;
        } else if (bytes_read == 0) {
            // End of file reached, reset file pointer to beginning
            lseek(fd, 0, SEEK_SET);
        } else {
            // Convert uppercase letters to their ASCII values
            if (character >= 'A' && character <= 'Z') {
                integerValue = integerValue * 100 + (character - 'A' + 1); // Adding 1 to differentiate between letters
            }
            // Convert lowercase letters to their ASCII values
            else if (character >= 'a' && character <= 'z') {
                integerValue = integerValue * 100 + (character - 'a' + 1); // Adding 1 to differentiate between letters
              }
        }

        // Output the integer value
        printf("The integer value read from the file is: %d\n", integerValue);

        // Reset integerValue for next read
        integerValue = 0;

        // Sleep for three seconds
        sleep(3);
    }

    // Close the file (unreachable code in this loop)
    close(fd);

    return 0;
}

