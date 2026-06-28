/*Binary explorer goal : build a C CLI tool that opens any file, loads it into memory, and lets you inspect the raw bytes*/
#include <stdio.h>
#include<stdlib.h>
int main(int argc, char *argv[]) {
    if (argc <2) {
        printf("Usage :%s<file_path>\n",argv[0]);
        return 1 ;
    }
    const char* file_path  = argv[1];
    FILE *file = fopen(file_path,"rb");
    if (file == NULL) {
        perror("failed to open file ");
        return 1 ;
    }
    fseek(file,0,SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    unsigned char* buffer = malloc(file_size);
    if (buffer ==NULL) {
        perror("memory allocation failed");
        fclose(file);
        return 1 ;
    }

    size_t bytes_read = fread(buffer,1,file_size,file);
    printf("File : %s\n",file_path);
    printf("Size: %ld bytes \n", file_size);
    printf("Bytes read: %zu \n\n", bytes_read);

    printf("first 64 bytes : \n");
    long limit = (file_size<64)? file_size:64;
    for (long i = 0 ; i < limit ; i++) {
        printf("%02x ", buffer[i]);
    }

    printf("\n");
    free(buffer);
    fclose(file);


    return 0 ;


    return 0;
}
