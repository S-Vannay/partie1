/*
 * POOSV 2020-21
 * @author: Chloé Voirol et Sara Vannay
 */


 /* isEqual + gestion d'erreur*/

#include "ToricPosition.hpp"
#include "Utility/Utility.hpp"
#include <cmath>



/*!

  @brief Opérateur = de (re)copie selon sa définition par défaut
  @param Un élément pour déterminer son égalité (comparaison)
  @return Un pointeur sur la valeur acutelle du this

  */
ToricPosition& ToricPosition::operator=(ToricPosition source)
 {
     std::swap (*this, source);
     return *this;
 }


/*!

  @brief Deux getteurs
  @param Les coordonnées prises individuellement : une fois x et une fois y
  @return Les coordonnées de x et y

  */
double ToricPosition::x () const  {return coordonnees[0];}
double ToricPosition::y () const {return coordonnees[1];}


/*!

  @brief Opérateur = de comparaison des coordonnées (x et y) de deux ToricPosition
  @param Un nouveau ToricPosition
  @return Une booléen pour déterminer si les deux coordonnées sont égales ou non

  */
bool ToricPosition::operator==(ToricPosition const& autre)
{
    if (isEqual((autre.x(), x()) and isEqual(autre.y(), y()))){
        return true;
    }else {
        return false;
    }
}


/*!

  @brief Opérateur += qui ajoute une position à une autre
  @param Un nouveau ToricPosition
  @return Les nouvelles coordonées projetées dans le monde torique par la fonction de clamping

  */

void ToricPosition::operator+=(ToricPosition const& pos)
{
    coordonnees += pos.coordonnees;
    clamp();
}

/*!

  @brief Opérateur d'indexation [] qui permet d'accéder à un élément de Vec2d
  @param Un index, c'est-à-dire le ième élément du tableau (0 ou 1 ici)
  @return Le contenu de l'élément du Vec2d à la ième position (0 ou 1 ici)

  */

double ToricPosition::operator[](int index) const
{
    /* if !(index == 0 or index == 1 ){
        throw std::string("Erreur: seul 0 et 1 sont valables !")*/
        switch (index) {
            case 0 : return coordonnees[0]; break;
            case 1 : return coordonnees[1]; break;
        }

}


/*!

  @brief Opérateur d'indexation + qui ajoute une position à une autre
  @param Une position 1 et une position 2
  @return La nouvelle valeur de la position 1 après l'addition

  */

const ToricPosition operator+(ToricPosition& posi1, ToricPosition const& posi2)
{
    posi1 += posi2;
    return posi1;

}

/*!

  @brief Opérateur d'affichage << qui affiche les positions
  @param Une sortie (où afficher) et une position
  @return La sortie sur laquelle sont affichées les positions

  */

std::ostream& operator<<(std::ostream& sortie, ToricPosition& position)
{
    sortie << '[' << position.x() << ',' << position.y() << ']';
    return sortie;
}

void ToricPosition::clamp ()

 /*!

   @brief projette 'coordonnes' en coordonées du monde torique
   @param 'coordonnes', pas besoin de les spécifier dans les paramètres de la fonction car on est dans la classe
   @return void, les coordonnées ont été modifiées dans le corp de la fonction

   */

 {
    double x (coordonnees[0]);
    double y (coordonnees[1]);
    Vec2d v (x,y);

      x = fmod(x, WORLD_WIDTH);

      if (x < 0) {x += WORLD_WIDTH;}



      y = fmod(y, WORLD_HEIGHT);

      if (y < 0) {y += WORLD_HEIGHT;}

      coordonnees = v;

 }



 ToricPosition :: ToricPosition (Vec2d const& coor, Vec2d const& dim)

 /*!
   @brief constructeur initialisant les dimensions du monde torique et garanti que les coordonnées sont dedans
   @param dim, dimensions du monde torique
   @param coor, coordonnées du point
 */

  : coordonnees(coor), dimensions (dim)

 {
     // Gestion d'erreur dimensions doivent être plus grandes que 0
     WORLD_HEIGHT = dimensions[0];
     WORLD_WIDTH = dimensions[1];
     clamp();

 }

 ToricPosition::ToricPosition (Vec2d const& coor)
/*
 @brief contructeur initialisant les coordonnées à un vecteur et les dimension du monde torique à des données par défaut
 @param coor, le vecteur contenant les coordonnées x et y
 */
{
    Vec2d w (getAppConfig().simulation_size,getAppConfig().simulation_size);
    ToricPosition (coor,w);
}

 ToricPosition :: ToricPosition (double x, double y)

 /*!
   @brief constructeur initialisant les coordonnées à (x,y) et les dimensions du monde torique à des données par défaut
   @param x
   @param y
 */

 {
     ToricPosition(Vec2d(x,y));
 }


 ToricPosition :: ToricPosition ()

 /*!
   @brief constructeur initialisant les coordonnées à (0,0) et les dimensions du monde torique à des données par défaut
 */

 {

    ToricPosition (0,0);

 }



 ToricPosition :: ToricPosition (ToricPosition const& autre)

 /*!
   @brief constructeur de copie ???codé selon sa définition par défaut???
   @param autre, le ToricPosition copié
 */

     :coordonnees(autre.coordonnees), dimensions(autre.dimensions), WORLD_WIDTH (autre.WORLD_WIDTH), WORLD_HEIGHT (autre.WORLD_HEIGHT)

{}



 Vec2d const& ToricPosition :: toVec2d()

 /*!
   @brief renvoie les coordonnees de notre objet
   */

 {

    return coordonnees;

 }


Vec2d ToricPosition::toricVector (ToricPosition const& that) const
{
    double x (that.x());
    double y (that.y());

    Vec2d a (x, y);

    for (int i(-1) ; i <= 1 ; i+=2) {
        if (abs(coordonnees[0]-x) > abs(coordonnees[0]-x + i * WORLD_WIDTH)){
            x += i * WORLD_WIDTH;
        }
    }
    for (int j(-1) ; j <= 1 ; j+=2) {
        if (abs(coordonnees[1]-y) > abs(coordonnees[1]-y + j * WORLD_HEIGHT)){
                y += j * WORLD_HEIGHT;
        }
    }
    return a;
}

double toricDistance (ToricPosition const& from, ToricPosition const& to)
/*!
 @brief Fonction servant à calculer la distance torique entre deux positions
 @param from, point de départ
 @param to, point d'arrivée
 @return la distance entre les deux points
 */
{
    Vec2d distance;
   distance = from.ToricPosition::toricVector(to);
   return distance.length();
}

