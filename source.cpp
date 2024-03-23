//Kondziolka Piotr
#include <iostream>
using namespace std; 

long long int potega(long long int p, long long int w)
{
    if(w==0) return 1;
    else return p*potega(p,w-1);
}

bool identical_rows(long long int mat[32][32], int N)
{
    int k=1;
    int counter=0;
    bool flag=false;

    for(int i=0; i<N; i++)
    {
        for(int j=k; j<N; j++)
        {
            counter=0;
            for(int m=0; m<N; m++)
            if(mat[i][m] == mat[j][m]) counter++;

            if(counter==N) flag=true;
        }

        k++;
    }

    return flag;
}


long long int determinant(long long int mat[32][32], int N)
{
    long long int det=0;
    long long int submat[32][32];
   
    if(N==2)
        return (mat[0][0]*mat[1][1]) - (mat[1][0]*mat[0][1]);

    else
    {
        for(int x=0; x<N; x++)
        {   
            if(mat[0][x]!=0) //pominiecie dla 0
            {
                int subi=0;
                for(int i=1; i<N; i++)
                {
                    int subj=0;
                    for(int j=0; j<N; j++)
                    {
                        if(j==x)    continue; //gdy j==x to to element ktory chcemy ominac, wynika to z definicji dopelnienia algebraicznego

                        submat[subi][subj]=mat[i][j];
                        subj++;
                    }
                    subi++;
                }
                det+=(potega(-1, 0+x)*mat[0][x]*determinant(submat,N-1));
            }
        }
    }
   return det;
}


int N, cube[32][32][32];
char operations[100];

int main()
{   
    cin>>N; 

    // wypelniam caly szescian zerami zeby dla przypadkow w ktorym dlugosc jakiejs bryly wychodzi poza rozmiar szescianu, wtedy sumuje 0
    for(int d=0; d<N; d++)  //glebokosc
    for(int h=0; h<N; h++)  //wysokosc
    for(int w=0; w<N; w++)  //szerokosc
    cube[h][w][d]=0;


    // wypelnienie szescianu
    for(int d=0; d<N; d++)  //glebokosc
    for(int h=0; h<N; h++)  //wysokosc
    for(int w=0; w<N; w++)  //szerokosc
        cin>>cube[h][w][d];

    while(operations[0]!='E')
    {
        cin>>operations[0];

        if(operations[0]=='D') //wyznacznik
        {   
            int indeks;
            cin>>operations[1]>>indeks;
            

            if(operations[1]=='l') 
            {
                long long int arr[32][32];

                for(int d=0; d<N; d++)  //glebokosc
                for(int w=0; w<N; w++)  //szerokosc
                arr[d][w]=cube[indeks][w][d];   //przepisanie 'plastru' danych do tablicy 2D 
            
                if(identical_rows(arr,N)==true) cout<<0<<endl;
                else
                    cout<<determinant(arr,N)<<endl;
            }

            if(operations[1]=='v') 
            {
                long long int arr[32][32];

                for(int h=0; h<N; h++)  //wysokosc
                for(int d=0; d<N; d++)  //glebokosc
                arr[h][d]=cube[h][indeks][d];   //przepisanie 'plastru' danych do tablicy 2D 
            
                
                if(identical_rows(arr,N)==true) cout<<0<<endl;
                else
                    cout<<determinant(arr,N)<<endl;
            }

            if(operations[1]=='p') 
            {
                long long int arr[32][32];

                for(int h=0; h<N; h++)  //wysokosc
                for(int w=0; w<N; w++)  //szerokosc
                arr[h][w]=cube[h][w][indeks];   //przepisanie 'plastru' danych do tablicy 2D 
            
                
                if(identical_rows(arr,N)==true) cout<<0<<endl;
                else
                    cout<<determinant(arr,N)<<endl;
            }
        }

        if(operations[0]=='C')  //prostopadloscian
        {   
            long long int L,v,p,h,w,d,suma=0;
            int Zp=1, Zv=1, ZL=1;   //za pomoca tych zmiennych operuje na znaku odpowiednio depth width height
    
            cin>>L>>v>>p>>h>>w>>d;
            //jesli ktoras z zadanych wspolrzednych wykracza lub jest rowna polowie dlugosci szescianu to wtedy chcemy obrocic os w przeciwna strone zeby zmierzala do centrum szescianu
            if(p>=N/2) Zp*=-1;  
            if(v>=N/2) Zv*=-1;
            if(L>=N/2) ZL*=-1;

            for(int depth=0; depth<=d; depth++)  
            for(int height=0; height<=h; height++)  
            for(int width=0; width<=w; width++) 
            {   
                if(!((L+ZL*height) < 0 || (v+Zv*width) < 0 || (p+Zp*depth) < 0 )) // jesli jakakolwiek wspolrzednia jest ujemna to ignorujemy caly klocek
                    suma+=cube[L+ZL*height][v+Zv*width][p+Zp*depth];
                
            }cout<<suma<<endl;
        }

        if(operations[0]=='T')  //czworoscian
        {
            long long int L,v,p,e,suma=0;
            cin>>L>>v>>p>>e;

            int Zp=1, Zv=1, ZL=1;

            //analogiczne postepowanie ze znakiem
            if(p>=N/2) Zp*=-1;
            if(v>=N/2) Zv*=-1;
            if(L>=N/2) ZL*=-1;

            int k=e,pom=e;

            //te petle realizuja sumowanie schodkowe, dziele czworoscian na pojedyncze 'plastry' i sumuje je wierszami, po kazdej sumie zmniejszajac dlugosc wiersza. Kiedy przechodze do kolejnego plastru robie dokladnie to samo ALE musze miec dlugosc poczatkowa wiersza mniejsza o 1 niz z poprzedniej sumy
            for(int depth=0; depth<=e; depth++)
            {    
                for(int height=0; height<=e; height++)  
                {   
                    for(int width=k; width>=0; width--)
                    {   
                        if(!((L+ZL*height) < 0 || (v+Zv*width) < 0 || (p+Zp*depth) < 0 ))   //analogicznie jak w prostopadloscianie, ignorujemy
                            suma+=cube[L+ZL*height][v+Zv*width][p+Zp*depth];
                    }
                    k--;    //dla kazdej sumy krotszy wiersz 
                }k=--pom;   //po sumie jednego 'plastra' zmniejszam poczatkowa dlugsoc wiersza, dla tej dlugosci bedzie kolejna suma
                
            }cout<<suma<<endl;
        }

        if(operations[0]=='O')
        {
            long long int L,v,p,r,suma=0;
            cin>>L>>v>>p>>r;

            int Zp=1, Zv=1, ZL=1;
    
            //analogiczne postepowanie ze znakiem
            if(p>=N/2) Zp*=-1;
            if(v>=N/2) Zv*=-1;
            if(L>=N/2) ZL*=-1;

            //w petlach przemieszczam sie tak jak po szescianie o krawedzi r, na pewno w tym szescianie zawiera sie oktal
            for(int depth=0; depth<=r; depth++)  
            for(int height=0; height<=r; height++)  
            for(int width=0; width<=r; width++) 
            {   
                //analogicznie jak w prostopadloscianie, ignorujemy
                //drugi warunek - rownanie sfery: (x-x0)^2 + (y-y0)^2 + (z-z0)^2 = r^2 , skoro ja poruszam sie tak jak po szescianie o krawedzi r to wystarczy sprawdzic czy (x-x0)^2 + (y-y0)^2 + (z-z0)^2 <= r^2, wtedy wiemy czy dany 'klocek' nalezy do sfery a w naszym przypadku, czy nalezy do oktalu bo on zawiera sie w szescianie po ktorym sie poruszam
                if(!((L+ZL*height) < 0 || (v+Zv*width) < 0 || (p+Zp*depth) < 0 ) && potega(L+ZL*height - L,2)+potega(v+Zv*width - v,2)+potega(p+Zp*depth - p,2) <= potega(r,2))           
                    suma+=cube[L+ZL*height][v+Zv*width][p+Zp*depth];
            }cout<<suma<<endl;
        }
    }

    return 0;
}