#include "graphe.h"
#include <cassert>
#include <fstream>
#include <string>

Graphe::Graphe()
{
    P=new Pixel;
    S=new Pixel;
    P->intensite_lumineuse=0;
    P->x=0;
    P->y=0;

    for (int i=0;i<6;i++){
        P->tab_f[i]=0;
        S->tab_f[i]=0;
    }

    L=0;
    C=0;
}

Graphe::Graphe( Graphe *g){
    if(this!=g){
        this->P->intensite_lumineuse=g->P->intensite_lumineuse;
        this->P->x=g->P->x;
        this->P->y=g->P->y;
        for (int i=0;i<6;i++){
            this->P->tab_f[i]=0;
            this->S->tab_f[i]=0;
        }
        this->L=g->L;
        this->C=g->C;

        for (int i=0;i<g->L*g->C;i++){
            Pixel *p=new Pixel;
            p->intensite_lumineuse=g->tab[i]->intensite_lumineuse;
            p->x=g->tab[i]->x;
            p->y=g->tab[i]->y;

            for (int j=0;j<6;j++){
                p->tab_f[j]=0;
                p->tab_f[j]=0;
            }
            this->tab.push_back(p);
        }

    }
}
Graphe::Graphe(std::string nom_fichier){
    P=new Pixel;
    S=new Pixel;

    for (int i=0;i<6;i++){
        P->tab_f[i]=0;
        S->tab_f[i]=0;
    }
    charger_graphe(nom_fichier);
}
void Graphe::donne_cordonne(){
   for(int y=0;y<C;y++){
        for(int x=0;x<L;x++){
            tab[y*L+x]->x=y;
            tab[y*L+x]->y=x;
        }
        
    }
}


void Graphe::charger_graphe(std::string nom_fichier){
    std::ifstream fichier(nom_fichier);
    assert(fichier.is_open());

    std::string format_fichier;
    fichier>> format_fichier;
    assert(format_fichier=="P2");

    std::string ligne;
    fichier.ignore();
    while (fichier.peek() == '#') {
        std::getline(fichier, ligne);
    }
    int intensite_lumineuse;
    fichier >> L >> C >>intensite_lumineuse ;
    P->intensite_lumineuse=intensite_lumineuse;
    S->intensite_lumineuse=intensite_lumineuse;

    assert(P->intensite_lumineuse==intensite_lumineuse);
    assert(S->intensite_lumineuse==intensite_lumineuse);
    
    for (int i = 0; i < L*C; i++) {
        Pixel *p=new Pixel;
        for (int j=0;j<6;j++){
            p->tab_f[j]=0;
        }
        fichier >> p->intensite_lumineuse;
        tab.push_back(p);
    } 
    donne_cordonne();

    fichier.close();
}


 void Graphe::sauvegarde(std::string nom_fichier){
    std::ofstream fichier(nom_fichier);
    assert(fichier.is_open());
    fichier <<"P2\n";
    fichier <<L<<" "<<C<<"\n";

    assert(S!=nullptr);
    fichier <<S->intensite_lumineuse;

    for(int y=0;y<C;y++){
        for(int x=0;x<L;x++){
            fichier<<tab[y*L+x]->intensite_lumineuse<<" ";
        }
        fichier << "\n";;
    }
    fichier.close();
 }
void Graphe::afficher_grille()const{
    for(int y=0;y<C;y++){
        for(int x=0;x<L;x++){
            printf("%d ",tab[y*L+x]->intensite_lumineuse);
        }
        printf("\n");
    }
}
int Graphe::get_indice_globale(int x,int y){
    assert(y*L+x>0 && y*L+x<L*C);
    return y*L+x;
}

int Graphe::get_indice_voisin_nord(int x,int y){
    if(y-1+x>0){
        return (y-1+x);
    }
    
}
int Graphe::get_indice_voisin_sud(int x,int y){
    if(y-1+x<C*L){
        return y+1+x;
    }
}

int Graphe::get_indice_voisin_est(int x,int y){
    if(y+x+1<L){
        return y+x+1;
    }
}
int Graphe::get_indice_voisin_ouest(int x,int y){
    if(y+x-1>L){
        return y+x+1;
    }
}


void Graphe::test_de_regression() const{
    Graphe g;
    Graphe g2("graphe.pgm");
    g2.tab[0]->intensite_lumineuse=1;
    g2.charger_graphe("graphe.pgm");
    Graphe g3(g2);
    assert(g.P!=nullptr);
    assert(g.S!=nullptr);
    printf("affiche de g");
    g.afficher_grille();
    printf("affichage coordonne premier constructeur \n");
    
    for (int i = 0; i < g.L*g.C; i++) {
        printf("cordonne (x,y) de %d: (%d,%d) \n",g.tab[i]->intensite_lumineuse,g.tab[i]->x,g.tab[i]->y);
    } 

    printf("affiche de g2 \n");
    g2.afficher_grille();
    printf("affichage coordonne deuxième constructeur \n");

    for (int i = 0; i < g2.L*g2.C; i++) {
        printf("cordonne (x,y) de %d: (%d,%d) \n",g2.tab[i]->intensite_lumineuse,g2.tab[i]->x,g2.tab[i]->y);
    } 

    printf("affichage coordonne troisième constructeur \n");
    g3.afficher_grille();
    
}

Graphe::~Graphe()
{
    for (int i = 0; i < L*C; i++) {
     delete tab[i];
    }
    
}