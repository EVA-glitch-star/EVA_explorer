/* Binary explorer : a C CLI tool that opens any file, loads it into memory, and lets you inspect it's raw bytes*/

#include<stdio.h>
#include<stdlib.h>


int main(int argc, char *argv[]){
    if (argc != 2) {
        printf("Usage :%s <file_path>\n",argv[0]);
        return -1 ;
    }

    const char *file_path  = argv[1];
    /* argv[1] is a pointer to second argument
     file_path = argv[1], is just argv[1] pointer copied to file_path pointer */

    FILE *file = fopen(file_path,"rb");
    /*  FILE is a type for file object.
        fopen() -> it takes in 2 parameters : file_path pointer and the mode(in this case it is read binary mode)
        fopen() -> opens file and creates/initializes the FILE object for it
        fopen() -> returns the pointer to the FILE object that the C runtime maintains to manage operations on the opened file by saving state
        fopen() -> returns NULL pointer in case of failure
    */


    if (file == NULL) {
        /* NULL in any case refers to a NULL pointer, it means that the file pointer here does not point to anything */
        perror("failed to open file ");
        return -1 ;
    }

    /* perror() : it is a very useful function, it appends user defined error message with descriptive error message of its own which it derives by referring the errno
        when a system call or a library function fails,  an appropriate error code is produced which then C runtime stores errno(C specific)*/


   if(fseek(file,0,SEEK_END) != 0 ) {
       /* we use fseek() function to change the cursor position maintained by the FILE object - in this case SEEK_END moves cursor to the end of file
       the '0' argument inside fseek() function is called offset and is used to move by that many positions, in this case 0 position so cursor still remains at the end of the file*/
       perror("ftell failed, cursor was not moved to the end of file");
       fclose(file);
       return -1 ;
   }

    size_t file_size;
    if (ftell(file)!=-1){ // if ftell() fails it returns -1
         file_size = (size_t) ftell(file);
        /* ftell() returns the current cursor position, and since we previously moved the cursor to the end of the file, the value returned by ftell in this case logically happens to be the
        file size */
    }
    else {
        perror("ftell failed to return the current cursor position");
        fclose(file);
        return -1 ;
    }
    rewind(file);// moving cursor to the beginning of the file.

    unsigned char* buffer = malloc(file_size);
    /*the syntax here means that buffer pointer points to starting location of the reserved memory block,and the memory block units tend to store unsigned character type elements
     we have chosen unsigned char because we don't want the compiler to interpret the data with a sign, as raw bytes don't have a sign.
     */
    if (buffer == NULL){ // if memory allocation fails malloc() returns a NULL pointer
        perror("memory allocation failed");
        fclose(file);
        return -1 ;
    }

    size_t bytes_read = fread(buffer,1,file_size,file);
    /* function prototype of fread() -> (pointer to where bytes should be copied to, object size, number of objects, pointer to where bytes should be copied from)
        fread() doesn't directly return number of bytes, it in-fact returns number of objects successfully read
        here the object size is 1 as sizeof(char) is 1 .
     */


    /* ---------------------------------------------------------------------------------LOGIC------------------------------------------------------------------------------------------ */


    printf("\nfile name : %s",file_path);
    printf("\nfile size : %zu bytes", file_size);
    printf("\nbytes read : %zu\n\n", bytes_read);

    printf("OFFSET             BYTES                                                                            ASCII\n");
    printf("----------------------------------------------------------------------------------------------------------------\n");

    size_t limit = bytes_read;
    for (size_t i = 0; i < limit; i+=16) {
        printf("\n");
        printf("%08zX        ",i);

        for (size_t j = i; j<i+16;j++) {

                if (j%4==0) {
                    printf("  "); // gap after printing 4 bytes
                }

                if (j<limit) {
                    printf("%02X  ",buffer[j]); //printing bytes in hexadecimal
                }

                if (j>=limit) {
                    printf("     ");// aligning bytes - if bytes read are not perfectly divisible by 16 then to maintain 16 byte structure we append print with spaces
                }

        }

            printf("       "); // gap between bytes zone and ascii zone


        for (size_t j = i; j<i+16 && j<limit;j++) {

            if (buffer[j]>=32 && buffer[j]<=126) { // printable character range
                printf("%c",buffer[j]);
            }

            else {
                printf("."); // replacing unprintable character with '.'
            }
        }
    }

    printf("\n\n");

    printf("file size : %zu\n",file_size);
    printf("bytes read : %zu\n",bytes_read);

    free(buffer);// clearing memory

    if (fclose(file)==EOF) {
        // if fclose() function fails it returns EOF(end of file) value
        perror("Failed to close file");
    }

    return 0 ;

}