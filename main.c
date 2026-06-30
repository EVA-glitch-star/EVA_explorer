/*Binary explorer goal : a C CLI tool that opens any file, loads it into memory, and lets you inspect the raw bytes*/
#include<stdio.h>
#include<stdlib.h>
int main(int argc, char *argv[]) { // argc tracks that count of arguments passed , argv is the array of pointers that store the pointers of the arguments passed
    if (argc != 2) {
        printf("Usage :%s <file_path>\n",argv[0]);
        return 1 ;
    }
    const char* file_path  = argv[1]; //file path is a pointer that points to string stored at argv[1]
    FILE *file = fopen(file_path,"rb");
    /*
     FILE is a type.
     fopen() creates and initializes FILE object that contains attributes helpful in reading data like cursor-position.
     fopen() prototype : fopen(pointer of the file path string, mode).
     fopen() returns the address of the FILE object if, it is successfully opened.
     */
    if (file == NULL) { //NULL in any case refers to NULL pointer, meaning that file does not point to anything.
        perror("failed to open file ");
        return 1 ;
    }
    fseek(file,0,SEEK_END); // '0' offset from end (moving cursor to the end) modifies the cursor position and updates it's value in the FILE object.
    size_t file_size;
    if (ftell(file)!=-1) {
         file_size = (size_t) ftell(file); // ftell() returns the current cursor position which logically happens to be the file size by referencing the FILE object.
    }
    else {
        perror("ftell failed to return the current cursor position ");
        fclose(file);
        return -1 ;
    }
    rewind(file);// moving cursor to the start.

    unsigned char* buffer = malloc(file_size);
    /*
     memory has no type
     the pointer gives it meaning ,in this it tells that this memory should be treated as array of raw bytes.
     we use unsigned char to read raw byte.
     */
    if (buffer == NULL) {
        perror("memory allocation failed");
        fclose(file);
        return 1 ;
    }

    size_t bytes_read = fread(buffer,1,file_size,file); // bytes read = object read
    printf("\nFile : %s\n",file_path);
    printf("Size: %zu bytes \n", file_size);
    printf("Bytes read: %zu \n\n", bytes_read); // zu - is format specifier for size_t

    printf("offset\t\t bytes                                                                     ASCII\n");
    printf("------------------------------------------------------------------------------------------------------\n");
    size_t limit = bytes_read;

    for (size_t i = 0; i < limit; i+=16) {
        printf("\n");
        printf("%08zu        ",i);
        for (size_t j = i; j<i+16 && j<limit;j++) {
            printf("%02x  ",buffer[j]);
        }
        printf("       ");
        for (size_t j = i; j<i+16 && j<limit;j++) {
            if (buffer[j]>=32 && buffer[j]<=126) {
                printf("%c",buffer[j]);
            }
            else {
                printf(".");
            }
        }
    }


    printf("\n");
    free(buffer);
    fclose(file);


    return 0 ;

}