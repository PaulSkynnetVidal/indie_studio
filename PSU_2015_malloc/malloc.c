
#include "malloc.h"

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

static t_alloc	*content = (void*)0;
static t_alloc  *freecontent = (void*)0;

void            *malloc(size_t size)
{
  t_alloc	*current;
  int		paddi;

  pthread_mutex_lock(&mutex);
  current = (void*)0;
  paddi = (size + sizeof(t_alloc));
  if ((current = free_memory_avlbl(freecontent, size)))
    rm_free_mmr_avlbl(&freecontent, current);
  else
    {
      if ((current = sbrk(paddi + (paddi % 8))) == ((void*)-1))
	{
	  write(2, strerror(errno), strlen(strerror(errno)));
	  return ((void*)0);
	}
    }
  current->size = (paddi + (paddi %8));
  add_curr_to_content(&content, current);
  pthread_mutex_unlock(&mutex);
  return ((void*)current);
}

void		free(void *ptr)
{
  t_alloc	*current;

  if (ptr && (current = is_allocated(ptr - sizeof(t_alloc))))
    {
      add_free_mmr_avlbl(&freecontent, current);
      rm_curr_to_content(&content, current);
      ptr = ((void*)0);
    }
}

void            *realloc(void *current, size_t size)
{
  void		*new_content;

  if (current && size == 0)
    {
      free(current);
      return ((void*)0);
    }
  if (current)
    {
      if (((t_alloc*)current)->size >= size)
	return (current);
      if (!(new_content = malloc(size)))
	return ((void*)0);
      new_content = memmove(new_content, current, size);
      free(current);
      return (new_content);
    }
  return (malloc(size));
}

t_alloc		*is_allocated(t_alloc *current)
{
  t_alloc	*tmp;

  tmp = content;
  while (tmp && tmp != current)
    tmp = tmp->next;
  return tmp;
}

void		show_alloc_mem()
{
  t_alloc	*tmp;

  tmp = content;
  printf("break : %p\n", sbrk(0));
  while (tmp)
    {
      printf("%p - %p : %zu octets\n", tmp, tmp + tmp->size, tmp->size);
      tmp = tmp->next;
    }
}
