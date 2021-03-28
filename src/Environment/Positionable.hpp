/*
 * POOSV 2020-21
 * @author: 
 */

#pragma once
#include "ToricPosition.hpp"


/*!
 * @brief Manage a position in a toric world
 *
 * 
 */
class Positionable
{
   public :
        // Constructeurs
        Positionable (); // C
        Positionable (ToricPosition& toricp); //C

        // Méthodes
        Positionable getPosition(); // C
        void setPosition (const ToricPosition& nouvelle_posi); // S
        // Opérateurs

    private :
        ToricPosition position;
};

std::ostream& operator<<(std::ostream& sortie, Positionable& position); //S
std::ostream& display(std::ostream& out, Positionable& posi); // S


