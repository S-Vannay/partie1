/*
 * POOSV 2020-21
 * @author:
 */

#pragma once
#include "Utility/Vec2d.hpp"
#include <ostream>
#include <utility>
#include "../Application.hpp"


/*!
 * @brief Handle toric coordinate, distance and other
 * basic math operation in a toric world
 *
 * @note Gets the dimensions of the world from getAppConfig()
 */

class ToricPosition
{

    private :
        Vec2d coordonnees;
        Vec2d dimensions;
        // Accès coordonnées
        double WORLD_WIDTH;
        double WORLD_HEIGHT;

        // Projeter les coordonnées dans le monde torique
        void clamp ();

     public :

        // Constructeurs

        // Constructeur par défaut + C
        ToricPosition (Vec2d const& coor, Vec2d const& dim);
        ToricPosition (Vec2d const& coor);
        ToricPosition (double x, double y);//C
        ToricPosition ();//C
        ToricPosition (ToricPosition const& autre);//C

        // Opérateurs
        ToricPosition& operator=(ToricPosition source); // S
        bool operator==(ToricPosition const& autre);
        void operator+=(ToricPosition const&);// S
        // Lien avec la classe, peut-être à déplacer S
        double operator[](int index) const;

        // Méthodes
        Vec2d const& toVec2d();//C

        double x() const;//C
        double y() const;//C

        Vec2d toricVector (ToricPosition const& that) const;


};

const ToricPosition operator+(ToricPosition const& posi1, ToricPosition const& posi2); //S

std::ostream& operator<<(std::ostream& sortie, ToricPosition& position); //S

double toricDistance (ToricPosition const& from, ToricPosition const& to); //C

