#include <stdio.h>

typedef void (*FPTR)(void);

void foo(void){
    printf("foo is called\n");
}

void bar(void){
    printf("bar is called\n");
}

FPTR set_func(FPTR fptr)
{
    static FPTR func_call_back = foo;
    FPTR ret = func_call_back;
    if (fptr)
        func_call_back = fptr;
    return ret;
}


void func(void)
{
   set_func(NULL)();
}


int main(void)
{
    func();
    set_func(bar);
    func();
    func();
}