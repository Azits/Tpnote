#ifndef _GRAPHE
#define _GRAPHE
#include <vector>
#include <string>
/**
 * @brief structure qui represente un pixel dans notre programe
 *  x,y: des entier (cordonnées)
 * intensite lumineuse:  entier 
 * 
 */
struct Pixel
{
    int x,y;
    int intensite_lumineuse;
};

/**
 * @class  Graphe
 * @brief Une classe qui represente un graphe
 * Le graphe est structuré de la manière suivante:
 * P pointeur vers le pixel puit du graphe
 * S pointeur vers le pixel Source du graphe
 * tab un tbleau de pointeur vers tout les pixel du graphe
 */
class Graphe
{
private:
    int L;
    int C;
   std::vector<Pixel*> tab;

public:
    /// @brief Constructeur par defaut 
    Graphe();

    /**
     * @brief Constructeur qui charge un graphe sauvegardé dans un fichier
     * @param une chainne de caractère 
     */
    Graphe(std::string nom_fichier);

    Graphe(Graphe *g);

    /// @brief destructeur  par defaut 
    ~Graphe();


    /**
     * @brief lis un fichier pgm puis complète les iformtion de notre garphe
     * il ajoute les pixel de l'image dans tab et donne les valeur de L et C
     */
    void charger_graphe(std::string fichier);


    void sauvegarde(std::string fichier);

    /// @brief de regression 
    void test_de_regression() const;

    /// @brief affichage  la grille 
    void afficher_grille()const;
    
    /// @brief donne les cordonne (x,y) par l'indice du pixel dans tab
    void donne_cordonne();

    /**
     * @brief renvoi l’indice global d’un nœud positionné sur la ligne x et la colonne y
     * @param x,y: entiers
     * @return return un entier 
     */
    int get_indice_globale(int x,int y);

    int get_indice_voisin_nord(int x,int y);
    int get_indice_voisin_sud(int x,int y);
    int get_indice_voisin_est(int x,int y);
    int get_indice_voisin_ouest(int x,int y);

};



#endif