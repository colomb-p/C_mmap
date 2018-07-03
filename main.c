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
  int			fd2;
  char			*path = "./test";
  void			*mapped_data;
  void			*mapped_data2;
  
  /* Getting "" file size */
  if (!access(path, R_OK))
    stat(path, &st);
  file_size = st.st_size;
  printf("Size of file: %d\n", file_size);

  /* Opening file */
  if ((fd = open(path, O_RDONLY, 0)) == -1)
    my_perror("Open failed");

  if ((fd2 = open(path, O_RDONLY, 0)) == -1)
    my_perror("Open failed");

  /* Populate read_only memory with the file content */
  if ((mapped_data = mmap(NULL, file_size, PROT_READ | PROT_EXEC, MAP_SHARED | MAP_POPULATE, fd, 0)) == (void *)-1)
    my_perror("Mmap failed");

  if ((mapped_data2 = mmap(NULL, file_size, PROT_READ | PROT_EXEC, MAP_SHARED | MAP_POPULATE, fd2, 0)) == (void *)-1)
    my_perror("Mmap failed");
  printf("%p, %p\n", mapped_data, mapped_data2);
  return (0);
}
