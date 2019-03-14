#include <stdio.h>
#include <stdlib.h>
/*
YAPILACAKLAR:
1. sutun ve satir
M. sutun ve satir icin karar yapilari düzenlenecek

*/
int gidilenYol[2],yolSecim=0,noWay=0;
int lastDirection = 0,checkingWrong;
const int M=10,N=10;
/*int *ptrA,*ptrB,*ptrC,*ptrD,*ptrE;
BURADAKI POINTERLAR MAINDE BELIRTILDIGI SEKILDE TEMSILIDIR. KODUN HAZIRLANMASINDA ISIMIZI KOLAYLASTIRDILAR. */


// labirent[i][j] == *(ptr1+(i*M)+j)

int pathFind(int *ptr1,int i,int j)
{
    if(*(ptr1 + (i*M)+j + 1) == 1 && j + 1 < N) // saga bakacak
    {
        lastDirection = 0;
        *(ptr1 + (i*M)+j + 1) = 8; // yolu isaretlesin.
        wrongWay(ptr1,i,j+1);
        gidilenYol[yolSecim] += 1;
        return pathFind(ptr1,i,j+1);
    }
    else if(*((ptr1 + ((i+1)*M))+j) == 1 && i + 1 < M) // assagiya bakacak
    {
        lastDirection = 1;
        *((ptr1 + ((i+1)*M))+j) = 8;
        wrongWay(ptr1,i+1,j);
        gidilenYol[yolSecim] += 1;
        return pathFind2(ptr1,i+1,j);
    }
    else if(*(ptr1 + (i*M) + j - 1) == 1 && j - 1 >= 0) // sola bakacak
    {
        lastDirection = 2;
        //*(ptr1 + (i*M)+j) = 5;
        *(ptr1 + (i*M) + j - 1) = 8;
        wrongWay(ptr1,i,j-1);
        gidilenYol[yolSecim] += 1;
        return pathFind(ptr1,i,j-1);
    }
    else if(*(ptr1 + ((i-1)*M) + j ) == 1 && i - 1 >= 0) // üste bakacak ve eger üste gidiyorsa yanlis yola girmistir 5 yapsin.
    {
        lastDirection = 3;
        // *(ptr1 + ((i*M) + j)) = 8;
        *(ptr1 + ((i-1)*M) + j ) = 8;
        wrongWay(ptr1,i-1,j);
        gidilenYol[yolSecim] += 1;
        return pathFind2(ptr1,i-1,j);
    }
    else if(*(ptr1+((M-1)*M)+(N-1)) == 1)
    {
        //wrongWay(ptr1,i,j);
        //gidilenYol[yolSecim] += 1;
        *(ptr1+((M-1)*M)+(N-1)) = 8;
        return 0;
    }
    else
    {
        noWay = 1;
        return 0;
    }
}


int pathFind2(int *ptr1,int i,int j)
{
    if(*((ptr1 + ((i+1)*M))+j) == 1 && i + 1 < M) // assagiya bakacak
    {
        lastDirection = 1;
        *((ptr1 + ((i+1)*M))+j) = 8;
        wrongWay(ptr1,i+1,j);
        gidilenYol[yolSecim] += 1;
        return pathFind(ptr1,i+1,j);
    }
    else if(*(ptr1 + (i*M)+j + 1) == 1 && j + 1 < N) // saga bakacak
    {
        lastDirection = 0;
        *(ptr1 + (i*M)+j + 1) = 8; // yolu isaretlesin.
        wrongWay(ptr1,i,j+1);
        gidilenYol[yolSecim] += 1;
        return pathFind2(ptr1,i,j+1);
    }
    else if(*(ptr1 + (i*M) + j - 1) == 1 && j - 1 >= 0) // sola bakacak
    {
        lastDirection = 2;
        *(ptr1 + (i*M) + j - 1) = 8;
        wrongWay(ptr1,i,j-1);
        gidilenYol[yolSecim] += 1;
        return pathFind2(ptr1,i,j-1);
    }
    else if(*(ptr1 + ((i-1)*M) + j ) == 1 && i - 1 >= 0) // üste bakacak ve eger üste gidiyorsa yanlis yola girmistir 5 yapsin.
    {
        lastDirection = 3;
        *(ptr1 + ((i-1)*M) + j ) = 8;
        wrongWay(ptr1,i-1,j);
        gidilenYol[yolSecim] += 1;
        return pathFind2(ptr1,i-1,j);
    }
    else if(*(ptr1+((M-1)*M)+(N-1)) == 1)
    {
        //wrongWay(ptr1,i,j);
        gidilenYol[yolSecim] += 1;
        *(ptr1+((M-1)*M)+(N-1)) = 8;
        return 0;
    }
    else
    {
        noWay = 1;
        return 0;
    }
}

	/*"
    ptrA = (ptr1 + (i*M)+j + 1);       // SAGA
    ptrB = ((ptr1 + ((i+1)*M))+j);    // ASSAGIYA
    ptrC = (ptr1 + (i*M) + j - 1);   // SOLA
    ptrD = (ptr1 + ((i-1)*M) + j ); // USTE
    ptrE = (ptr1 + (9*M)+9);       // yolun sonu
	*/

int wrongWay(int *ptr1,int i,int j)
{
    if(lastDirection == 0) // YANLIS YOL SOLDAN GELDIYSE
    {
        if(*(ptr1 + ((i+1)*M)+j) == 0 && *(ptr1 + (i*M) + j + 1) == 0 && *(ptr1 + ((i-1)*M) + j ) == 0 && *(ptr1 + (i*M)+ j - 1) == 8) // YANLIS YOL SOLDAN GELDIYSE
        {
            *(ptr1 + (i*M) + j) = 5; // cikmaz yol olarak isaretlerim
            gidilenYol[yolSecim] -= 1;
            return pathFind(ptr1,i,j-1);
        }
        else if(i == 0 && *(ptr1 + (i*M)+j + 1) == 0 && *((ptr1 + ((i+1)*M))+j) == 0 && *(ptr1 + (i*M) + j - 1) == 8)
        {
        	*(ptr1 + (i*M) + j) = 5; // cikmaz yol olarak isaretlerim
        	gidilenYol[yolSecim] -= 1;
        	return pathFind(ptr1,i,j-1);
		}
		else if(i == M-1 && *(ptr1 + (i*M)+j + 1) == 0 && *(ptr1 + ((i-1)*M) + j ) == 0 && *(ptr1 + (i*M) + j - 1) == 8)
		{
			*(ptr1 + (i*M) + j) = 5;
			gidilenYol[yolSecim] -= 1;
			return pathFind(ptr1,i,j-1);
		}
    }
    else if(lastDirection == 1) // YANLIS YOL ÜSTTEN GELDIYSE
    {
        if(*(ptr1 + (i*M)+j - 1) == 0 && *(ptr1 + ((i+1)*M) + j ) == 0 && *(ptr1 + (i*M)+j + 1) == 0 && *(ptr1 + ((i-1)*M) + j ) == 8)
        {
            *(ptr1 + (i*M) + j) = 5;
        	gidilenYol[yolSecim] -= 1;
            return pathFind2(ptr1,i-1,j);
        }
        else if(j == 0 && *(ptr1 + (i*M)+j + 1) == 0 && *((ptr1 + ((i+1)*M))+j) == 0 && *(ptr1 + ((i-1)*M) + j ) == 8)
        {
        	*(ptr1+ (i*M)+ j) = 5;
        	gidilenYol[yolSecim] -= 1;
        	return pathFind(ptr1,i-1,j);
		}
		else if(j == N-1 && *((ptr1 + ((i+1)*M))+j) == 0 && *(ptr1 + (i*M) + j - 1) == 0 && *(ptr1 + ((i-1)*M) + j ) == 8)
		{
			*(ptr1+ (i*M)+ j) = 5;
			gidilenYol[yolSecim] -= 1;
			return pathFind(ptr1,i-1,j);
		}
    }
    else if(lastDirection == 2) // // YANLIS YOL SAGDAN GELDIYSE
    {
        if(*((ptr1 + ((i+1)*M))+j) == 0 && *(ptr1 + (i*M)+j - 1) == 0 && *(ptr1 + ((i-1)*M) + j) == 0 && *(ptr1 + (i*M) + j + 1) == 8)
        {
        	gidilenYol[yolSecim] -= 1;
            *(ptr1 + (i*M) + j) = 5;
            return pathFind(ptr1,i,j+1);
        }
        else if(i == 0 && *(ptr1 + (i*M) + j - 1) == 0 && *((ptr1 + ((i+1)*M))+j) == 0 && *(ptr1 + (i*M)+j + 1) == 8)
        {
         	gidilenYol[yolSecim] -= 1;
            *(ptr1 + (i*M) + j) = 5;
            return pathFind(ptr1,i,j+1);
		}
		else if(i == M-1 && *(ptr1 + (i*M) + j - 1) == 0 && *(ptr1 + ((i-1)*M) + j ) == 0 && *(ptr1 + (i*M)+j + 1) == 8)
		{
        	gidilenYol[yolSecim] -= 1;
            *(ptr1 + (i*M) + j) = 5;
            return pathFind(ptr1,i,j+1);			
		}
    }
    else if(lastDirection == 3) // // YANLIS YOL ASAGIDAN GELDIYSE
    {
        if(*((ptr1 + ((i-1)*M))+j) == 0 && *(ptr1 + (i*M) + j - 1) == 0 && *(ptr1 + (i*M)+j + 1) == 0 && *(ptr1 + ((i+1)*M) + j ) == 8)
        {
        	gidilenYol[yolSecim] -= 1;
            *(ptr1 + (i*M) + j) = 5;
            return pathFind2(ptr1,i+1,j);
        }
        else if(j == 0 && *(ptr1 + (i*M)+j + 1) == 0 && *(ptr1 + ((i-1)*M) + j ) == 0 && *(ptr1 + ((i+1)*M) + j ) == 8)
        {
        	gidilenYol[yolSecim] -= 1;
            *(ptr1 + (i*M) + j) = 5;
            return pathFind2(ptr1,i+1,j);        	
		}
		else if(j == N-1 && *(ptr1 + (i*M) + j - 1) == 0 && *(ptr1 + ((i-1)*M) + j ) == 0 && *(ptr1 + ((i+1)*M) + j ) == 8)
		{
        	gidilenYol[yolSecim] -= 1;
            *(ptr1 + (i*M) + j) = 5;
            return pathFind2(ptr1,i+1,j);			
		}
    }
    else if(lastDirection == 0 || lastDirection == 2)
    {
        return pathFind2(ptr1,i,j);
    }
    else if(lastDirection == 1 || lastDirection == 3)
    {
        return pathFind(ptr1,i,j);
    }
    else
    {
    	*(ptr1 + (i*M) + j) = 5;
    	return pathFind(ptr1,i,j);
	}
}


int main()
{
    int i=0,j=0,k;
    int *ptr1;





	int labirent[10][10]={
    {1,1,1,1,0,1,0,1,1,0},
    {0,1,0,1,0,1,1,0,0,1},
    {0,1,0,1,0,1,0,1,0,1},
    {1,1,1,1,1,0,1,0,0,1},
    {0,0,1,1,0,1,0,0,1,0},
    {1,1,0,1,1,1,1,0,1,0},
    {1,1,0,1,0,1,0,1,0,1},
    {0,1,0,0,0,1,0,1,0,1},
    {0,0,0,1,0,1,1,0,1,0},
    {1,1,0,0,1,0,1,1,1,1},
    };
 	int labirent2[10][10]={
    {1,1,1,1,0,1,0,1,1,0},
    {0,1,0,1,0,1,1,0,0,1},
    {0,1,0,1,0,1,0,1,0,1},
    {1,1,1,1,1,0,1,0,0,1},
    {0,0,1,1,0,1,0,0,1,0},
    {1,1,0,1,1,1,1,0,1,0},
    {1,1,0,1,0,1,0,1,0,1},
    {0,1,0,0,0,1,0,1,0,1},
    {0,0,0,1,0,1,1,0,1,0},
    {1,1,0,0,1,0,1,1,1,1},
    };
	ptr1 = (int *) malloc(sizeof(int)*(M*N));

    ptr1 = labirent;
    gidilenYol[yolSecim] += 1;
    pathFind(ptr1,i,j); // yatay oncelikli
    *(ptr1+(i*M)+j) = 8;
    printf("<====================ILK YOL====================>\n\n\n");
    for(i=0;i<M;i++) // i => satir icin j => sutun icin
    {
        for(j=0;j<N;j++)
        {
            printf("%3d",*(ptr1+(i*M)+j));
        }
        printf("\n");
    }
    //printf("\n\n\n<========================================>\n");
    yolSecim++; // diger yolu saydirmaya basladigi yer
    i=0,j=0;
    gidilenYol[yolSecim] += 1;
    ptr1 = labirent2;
    *(ptr1+(i*M)+j) = 8;
    pathFind2(ptr1,i,j); // dikey oncelikli
    printf("<====================IKINCI YOL====================>\n\n\n");
    for(i=0;i<M;i++) // i => satir icin j => sutun icin
    {
        for(j=0;j<N;j++)
        {
            printf("%3d",*(ptr1+(i*M)+j));
        }
        printf("\n");
    }
    printf("\n\n\n<========================================>\n");

    if(gidilenYol[0] < (M+N-1)) // Ilk yolda yolu bulamadiysa
    {
        printf("1. yol cikmaz yol:%d br(Mumkun olan en kisa yoldan kucuk(%d)).\n",gidilenYol[0],M+N-1);
        printf("2. yol en kisa yol:%d br.",gidilenYol[1]);
        return 0;
    }
    else if(gidilenYol[1] < (M+N-1)) // Ikinci yolda yolu bulamadiysa
    {
        printf("1. yol en kisa yol:%d br.\n",gidilenYol[0]);
        printf("2. yol cikmaz yol:%d br(Mumkun olan en kisa yoldan kucuk(%d)).\n",gidilenYol[1],M+N-1);
        return 0;
    }
    else if(gidilenYol[0] > gidilenYol[1]) // yani yatay oncelikliyken daha uzunsa
    {
        printf("1. yol uzun yol:%d br.\n",gidilenYol[0]);
        printf("2. yol en kisa yol:%d br.",gidilenYol[1]);
        return 0;
    }
    else if(gidilenYol[1] > gidilenYol[0]) // yani dikey oncelikliyken daha kisaysa
    {
        printf("1. yol en kisa yol:%d br.\n",gidilenYol[0]);
        printf("2. yol uzun yol:%d br.",gidilenYol[1]);
        return 0;
    }    
    else if(gidilenYol[1] == gidilenYol[0]) // iki yol da esitse
    {
        printf("3-Iki yolun da uzunlugu birbiriyle ayni: %d br.",gidilenYol[0]);
    }
    else if(noWay == 1)
    {
        printf("Yol bulunamadi!");
        return 0;
    }
}




//  Reddit:  https://www.reddit.com/r/mercymekofficial

//  Github:  https://www.github.com/mercymekofficial

//  Patreon: https://www.patreon.com/mercymekofficial

//  Gmail: mercymekofficial@gmail.com / sipsipsubidibao@gmail.com

// 
