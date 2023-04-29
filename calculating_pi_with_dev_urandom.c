#include <stdio.h>
#include <math.h>
#define POINTS 100000

double calculate_points_inside_the_circle(long long pts)
{
    unsigned int a;
    unsigned int b;
    unsigned int c;
    unsigned int d;
    FILE *f1 = fopen("/dev/urandom", "r");
    FILE *f2 = fopen("/dev/urandom", "r");
    FILE *f3 = fopen("/dev/urandom", "r");
    FILE *f4 = fopen("/dev/urandom", "r");
    long long cnt=0;
    for (long long i = 0;i < pts;i++){
        fread(&a, sizeof(a), 1, f1);
        fread(&b, sizeof(b), 1, f2);
        fread(&c, sizeof(c), 1, f3);
        fread(&d, sizeof(d), 1, f4);
 
        if (sqrt(fmod(((double)a / b), 1.) * fmod(((double)a / b), 1.) + fmod(((double)c / d), 1.) * fmod(((double)c / d), 1.)) <= 1.){
            cnt++;
        }


    }
    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);

    return (double)cnt / pts;

}

int main(void)
{
    printf("%lf\n", calculate_points_inside_the_circle(POINTS)*4.);
}
