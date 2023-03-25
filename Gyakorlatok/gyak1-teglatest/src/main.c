#include <stdbool.h>
#include <stdio.h>

struct brick{
  int x;
  int y;
  int z;
};

int calc_volume(struct brick b);
int calc_surface(struct brick b);
struct brick read_brick();
int has_square_side(struct brick b);


int main(int argc, char* argv[])
{

  struct brick b = read_brick();

  printf("A teglatest terfogata: %d\n",calc_volume(b) );
  printf("A teglatest felszine: %d\n",calc_surface(b) );

  if(has_square_side(b)){printf("A teglatestnek van negyzet alaku oldala!");}
  else                  {printf("A teglatestnek nincs negyzet alaku oldala!");}

  return 0;
}





int calc_volume(struct brick b){

return b.x*b.y*b.z;
}

int calc_surface(struct brick b){

return (b.x*b.y+b.y*b.z+b.z*b.x)*2;
}

struct brick read_brick(){
int ok = 1;
struct brick ret;
char ch;

do{
  ok = 1;
  printf("Adja meg a teglatest 1. elet: ");
  
  if (scanf("%d",&ret.x) !=1 || ret.x <=0 ){
    printf("Hibas Input!\n");
    ok = 0;
    
    while(ch=getchar() != '\n');
  }
}while(!ok);

do{
  ok = 1;
  printf("Adja meg a teglatest 2. elet: ");
  
  if (scanf("%d",&ret.y) !=1 || ret.y <=0 ){
    printf("Hibas Input!\n");
    ok = 0;
    
    while(ch=getchar() != '\n');
  }
}while(!ok);

do{
  ok = 1;
  printf("Adja meg a teglatest 3. elet: ");
  
  if (scanf("%d",&ret.z) !=1 || ret.z <=0 ){
    printf("Hibas Input!\n");
    ok = 0;
    
    while(ch=getchar() != '\n');
  }
}while(!ok);

return ret;

}

int has_square_side(struct brick b){

if(b.x == b.y || b.y == b.z || b.z == b.x){return 1;}
else                                      {return 0;}
}