


int  main(int ac, char **av)
{
  int	i;
  int	socket;

  for (i = 0; i < 2000; i++)
  {
    socket = connect_to(av[1], av[2]);
    if (socket != -1)
    {
      printf("reussi %d\n", i);
    }
  }
  pause();
  return (0);
}
