#include <stdio.h>
#include <string.h>
int is_at_end(const char *p1, const char *p2)
{
    size_t len_p2 = strlen(p2) - 1;
    size_t len_p1 = strlen(p1) - 1;
    do{
        if (*(p1 + len_p1) != *(p2 + len_p2))
            return 0;
    } while (len_p1--, len_p2--);
    return 1;


}

int main(void)
{
    printf("%d", !!is_at_end("necati ergin", "ergin"));
    printf("%d", !!is_at_end("kahramanmaras", "maras"));
    printf("%d", !!is_at_end("kaanaslan", "uslan"));
    printf("%d", !!is_at_end("baskent Ankara", "kara"));
    printf("%d", !!is_at_end("ergin", "necati ergin"));
}