#include <unistd.h>
#include <string.h>
#include <stdlib.h>

typedef struct s_object t_object;
typedef void    t_ft_ex(t_object *, t_object *);
typedef void    *t_ft(void);

typedef struct s_object {
    t_ft *ft;
    char buf[108];
}   t_object;


void setAnnotation(t_object *obj, char *src) {
    memcpy(obj->buf, src, strlen(src));
    return;
}

int		main(int argc, char *argv[])
{
    t_object *obj_1;
    t_object *obj_2;

	if (argc <= 1)
		exit(1);

    obj_1 = malloc(sizeof(t_object));
    obj_2 = malloc(sizeof(t_object));

	setAnnotation(obj_1, argv[1]);
	
    t_ft_ex *ft_ex = obj_2->ft();
    ft_ex(obj_1, obj_2);
    return (0);
}
