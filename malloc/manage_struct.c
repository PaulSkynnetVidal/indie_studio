
#include "malloc.h"

t_alloc		*free_memory_avlbl(t_alloc *freecontent, size_t size)
{
  t_alloc	*tmp;

  tmp = freecontent;
  while (tmp && tmp->size < size)
    tmp = tmp->next;
  return (tmp);
}

void		rm_free_mmr_avlbl(t_alloc **freecontent, t_alloc *current)
{
  t_alloc	*tmp;

  tmp = *freecontent;
  while (tmp && tmp->size != current->size)
    tmp = tmp->next;
  if (tmp)
    {
      if (tmp->prev)
	tmp->prev->next = tmp->next;
      if (tmp->next)
	tmp->next->prev = tmp->prev;
    }
}

void		add_free_mmr_avlbl(t_alloc **freecontent, t_alloc *current)
{
  t_alloc	*tmp;

  tmp = *freecontent;
  while (tmp && tmp->size <= current->size)
    tmp = tmp->next;
  current->next = ((void*)0);
  current->prev = ((void*)0);
  if (tmp)
    {
      if (tmp->next)
	tmp->next->prev = current;
      current->next = tmp->next;
      tmp->next = current;
      current->prev = tmp;
    }
  else
    tmp = current;
}

void		rm_curr_to_content(t_alloc **content, t_alloc *current)
{
  t_alloc	*tmp;

  tmp = *content;
  while (tmp && tmp != current)
    tmp = tmp->next;
  if (tmp)
    {
      if (current->next)
	current->next->prev = tmp;
      tmp->next = current->next;
    }

}

void		add_curr_to_content(t_alloc **content, t_alloc *current)
{
  t_alloc	*tmp;

  tmp = *content;
  while (tmp && tmp->next)
    tmp = tmp->next;
  if (tmp)
    {
      tmp->next = current;
      current->prev = tmp;
      current->next = ((void*)0);
    }
  else
    tmp = current;
}
