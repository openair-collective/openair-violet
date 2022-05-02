/*
 * Global variables with default values
 * and global functions will go here
 */

// waste time without blocking using a for-loop
void my_delay(volatile long delay_time)
{
    delay_time = delay_time * 1e+6L;
    for (volatile long count = delay_time; count > 0L; count--)
        ;
}