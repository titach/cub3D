#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// int main()
// {
//     int i = 0;
//     char *av = "map.cub";

//     while (*av)
//     {
//         if (strncmp(av, ".cub", 5) == 0)
//         {
//             printf("%s\n", av);
//             while (i-- > 0)
//             {
//                 av--;
//             }
//             break;
//         }
//         i++;
//         av++;
//     }
//     printf("%s\n", av);
// }

int main()
{
    char *str = "NO ./path_to_the_north_texture";

    char *new;

    new = strdup(str + 3);
    printf("%s\n", new);
    free(new);
}