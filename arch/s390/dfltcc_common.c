/* dfltcc_deflate.c - IBM Z DEFLATE CONVERSION CALL support. */

#include "dfltcc_common.h"

#include <errno.h>
#include <stddef.h>
#include <stdlib.h>

int env_dfltcc_disabled;
int env_dfltcc_source_date_epoch;
unsigned long env_dfltcc_level_mask;
unsigned long env_dfltcc_block_size;
unsigned long env_dfltcc_block_threshold;
unsigned long env_dfltcc_dht_threshold;
unsigned long env_dfltcc_ribm;

static unsigned long xstrtoul(const char *s, unsigned long _default)
{
    char *endptr;
    unsigned long result;

    if (!(s && *s))
        return _default;
    errno = 0;
    result = strtoul(s, &endptr, 0);
    return (errno || *endptr) ? _default : result;
}

__attribute__((constructor)) static void init_globals(void)
{
    const char *env;

    env = getenv("DFLTCC");
    env_dfltcc_disabled = env && !strcmp(env, "0");

    env = getenv("SOURCE_DATE_EPOCH");
    env_dfltcc_source_date_epoch = !!env;

#ifndef DFLTCC_LEVEL_MASK
#define DFLTCC_LEVEL_MASK 0x2
#endif
    env_dfltcc_level_mask = xstrtoul(getenv("DFLTCC_LEVEL_MASK"),
                              DFLTCC_LEVEL_MASK);

#ifndef DFLTCC_BLOCK_SIZE
#define DFLTCC_BLOCK_SIZE 1048576
#endif
    env_dfltcc_block_size = xstrtoul(getenv("DFLTCC_BLOCK_SIZE"),
                              DFLTCC_BLOCK_SIZE);

#ifndef DFLTCC_FIRST_FHT_BLOCK_SIZE
#define DFLTCC_FIRST_FHT_BLOCK_SIZE 4096
#endif
    env_dfltcc_block_threshold = xstrtoul(getenv("DFLTCC_FIRST_FHT_BLOCK_SIZE"),
                                   DFLTCC_FIRST_FHT_BLOCK_SIZE);

#ifndef DFLTCC_DHT_MIN_SAMPLE_SIZE
#define DFLTCC_DHT_MIN_SAMPLE_SIZE 4096
#endif
    env_dfltcc_dht_threshold = xstrtoul(getenv("DFLTCC_DHT_MIN_SAMPLE_SIZE"),
                                 DFLTCC_DHT_MIN_SAMPLE_SIZE);

#ifndef DFLTCC_RIBM
#define DFLTCC_RIBM 0
#endif
    env_dfltcc_ribm = xstrtoul(getenv("DFLTCC_RIBM"), DFLTCC_RIBM);

}
