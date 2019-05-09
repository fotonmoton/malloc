// gcc -O2 -o main main.c -lz

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include <zlib.h>
#include "ft_malloc.h"

struct item {
    void *ptr;
    size_t size;
    size_t hash;
};

int dev_urandom_fd = -1;

static void hash_compute(struct item *item) {
    unsigned long pos = 0;
    do {
        pos += read(dev_urandom_fd, item->ptr, item->size - pos);
        assert(errno == 0);
        // fprintf(stderr, "Read %lu bytes from /dev/urandom\n", pos);
    } while (pos < item->size);

    item->hash = adler32(0, item->ptr, item->size);
}

static int hash_check(struct item *item) {
    if (item->ptr == NULL)
        return 1;

    return (item->hash == adler32(0, item->ptr, item->size));
}

int main(int argc, const char *const argv[]) {
    if (argc < 4) {
        puts("Usage: ... num_passes num_items size_min size_max");
        return 1;
    }

    dev_urandom_fd = open("/dev/urandom", O_RDONLY);
    assert(dev_urandom_fd >= 0);

    size_t num_passes = atoi(argv[1]),
           num_items = atoi(argv[2]),
           size_min = atoi(argv[3]),
           size_max = atoi(argv[4]);
    struct item items[num_items];

    srand(argc + num_items + size_min + size_max + (int)(long)argv[0]);
    srand(rand() ^ time(NULL));
    bzero(items, sizeof(struct item) * num_items);

    for (size_t pass = 0; pass < num_passes; pass++) {
        for (size_t i = 0; i < num_items; i++) {
            if (pass % 3 == 0) {
                if (rand() & 1 && items[i].ptr == NULL) {
                    items[i].size = rand() % (size_max - size_min) + size_min;
                    items[i].ptr = malloc(items[i].size);
                    if (items[i].ptr) {
                        hash_compute(&items[i]);
                        printf("pass %-2lu item %-4lu malloc(%lu) => %p..%p\n",
                               pass, i, items[i].size, items[i].ptr, items[i].ptr + items[i].size);
                    } else {
                        printf("\033[0;31mpass %-2lu item %-4lu returned NULL\033[0m\n", pass, i);
                    }
                }
            } else if (pass % 3 == 1) {
                if (rand() & 1 && items[i].ptr != NULL) {
                   void *old_ptr = items[i].ptr;
                   items[i].size = rand() % (size_max - size_min) + size_min;
                   items[i].ptr = realloc(items[i].ptr, items[i].size);
                   if (items[i].ptr) {
                       hash_compute(&items[i]);
                       printf("pass %-2lu item %-4lu realloc(%p, %lu) => %p\n",
                              pass, i, old_ptr, items[i].size, items[i].ptr);
                   } else {
                       printf("\033[0;31mpass %-2lu item %-4lu realloc failed\033[0m\n", pass, i);
                   }
                }
            } else {
                if (rand() & 1 && items[i].ptr != NULL) {
                    printf("pass %-2lu item %-4lu free(%p)\n",
                           pass, i, items[i].ptr);
                    free(items[i].ptr);
                    items[i].ptr = NULL;
                } else if (pass == num_passes - 1 && items[i].ptr != NULL) {
                    printf("pass %-2lu item %-4lu free(%p)\n",
                           pass, i, items[i].ptr);
                    free(items[i].ptr);
                    items[i].ptr = NULL;
                }
            }

            for (size_t j = 0; j < num_items; j++) {
               if (!hash_check(&items[i])) {
                   printf("\033[0;31mpass %-2lu item %-4lu hash_check failed\033[0m\n", pass, i);
                   items[i].ptr = NULL;
               }
            }
        }

		show_alloc_mem();
    }

    close(dev_urandom_fd);

    return (0);
}
