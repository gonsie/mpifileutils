/* See the file "COPYING" for the full license governing this code. */

#include <stdlib.h>
#include <string.h>

#include "log.h"
#include "checksum.h"

/** Options specified by the user. */
extern DCOPY_options_t DCOPY_user_opts;

/** The loglevel that this instance of dcopy will output. */
extern DCOPY_loglevel  DCOPY_debug_level;

void DCOPY_do_checksum(DCOPY_operation_t* op, CIRCLE_handle* handle)
{
    LOG(DCOPY_LOG_DBG, "Checksum %s chunk %d", op->operand, op->chunk);
    char path[4096];
    sprintf(path, "%s/%s", DCOPY_user_opts.src_path[0], op->operand);
    FILE* old = fopen(path, "rb");

    if(!old) {
        LOG(DCOPY_LOG_ERR, "Unable to open file %s", path);
        return;
    }

    char newfile[4096];
    void* newbuf = (void*) malloc(DCOPY_CHUNK_SIZE);
    void* oldbuf = (void*) malloc(DCOPY_CHUNK_SIZE);
    sprintf(newfile, "%s/%s", DCOPY_user_opts.dest_path, op->operand);
    FILE* new = fopen(newfile, "rb");

    if(!new) {
        LOG(DCOPY_LOG_ERR, "Unable to open file %s", newfile);
        perror("checksum open");
        char* newop = DCOPY_encode_operation(CHECKSUM, op->chunk, op->operand);
        handle->enqueue(newop);
        free(newop);
        return;
    }

    fseek(new, DCOPY_CHUNK_SIZE * op->chunk, SEEK_SET);
    fseek(old, DCOPY_CHUNK_SIZE * op->chunk, SEEK_SET);
    size_t newbytes = fread(newbuf, 1, DCOPY_CHUNK_SIZE, new);
    size_t oldbytes = fread(oldbuf, 1, DCOPY_CHUNK_SIZE, old);

    if(newbytes != oldbytes || memcmp(newbuf, oldbuf, newbytes) != 0) {
        LOG(DCOPY_LOG_ERR, "Incorrect checksum, requeueing file (%s).", op->operand);
        char* newop = DCOPY_encode_operation(STAT, 0, op->operand);
        handle->enqueue(newop);
        free(newop);
    }
    else {
        LOG(DCOPY_LOG_DBG, "File (%s) chunk %d OK.", newfile, op->chunk);
    }

    fclose(new);
    fclose(old);
    free(newbuf);
    free(oldbuf);

    return;
}

/* EOF */
