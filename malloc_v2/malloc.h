
#ifndef MALLOC_H_
# define MALLOC_H_

# include <string.h>
# include <unistd.h>
# include <errno.h>
# include <stdio.h>
# include <pthread.h>

typedef struct		s_alloc
{
    struct s_alloc	*next;
    struct s_alloc	*prev;
    size_t		size;
}			t_alloc;

/*
** malloc.c
*/

void			*malloc(size_t);
void			*realloc(void *, size_t );
void			free(void *);
void			show_alloc_mem();
t_alloc			*is_allocated(t_alloc *);

/*
** manage_struct.c
*/

void			rm_free_mmr_avlbl(t_alloc **, t_alloc *);
void			add_free_mmr_avlbl(t_alloc **, t_alloc *);
void			rm_curr_to_content(t_alloc **, t_alloc *);
void			add_curr_to_content(t_alloc **, t_alloc *);
t_alloc			*free_memory_avlbl(t_alloc *, size_t);

#endif  /* MALLOC_H_ */
