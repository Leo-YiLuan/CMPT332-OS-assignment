/* CMPT 332 GROUP 22 Change, Fall 2022 */
/* Tests threads */

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(void)
{
    thread_create((void*)5, (void*)10, (void*)15);
    exit(0);
}
