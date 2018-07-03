#include		<sys/stat.h>
#include		<sys/types.h>
#include		<unistd.h>
#include		<stdio.h>
#include		<stdlib.h>
#include		<fcntl.h>
#include		<sys/mman.h>

void			my_perror(char *err)
{
  perror(err);
  exit(EXIT_FAILURE);
}

int			main(int argc, char *argv[])
{
  struct stat		st;
  int			file_size;
  int			fd;
  char			*path = "./test";
  void			*mapped_data;
  
  /* Getting "" file size */
  if (!access(path, R_OK))
    stat(path, &st);
  file_size = st.st_size;
  printf("Size of file: %d\n", file_size);

  /* Opening file */
  if ((fd = open(path, O_RDONLY, 0)) == -1)
    my_perror("Open failed");

  /* Populate read_only memory with the file content */
  if ((mapped_data = mmap(NULL, file_size, PROT_READ | PROT_EXEC, MAP_SHARED | MAP_POPULATE, fd, 0)) == (void *)-1)
    my_perror("Mmap failed");
  printf("%p\n", mapped_data);
  return (0);
}
