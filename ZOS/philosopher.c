
/**
 * Philosopher tries to eat (he must have two forks, otherwise he puts
 * all forks back on table and waits)
 * 
 * @param id Id of philosopher
 */
void eat(int id)
{
    printf("Philosopher %d is trying to eat.\n", id);
}

/**
 * Philosopher thinks for a while before trying to eat again
 * 
 * @param id Id of philosopher
 */
void think(int id)
{
    printf("Philosopher %d is thinking.\n", id);
}
