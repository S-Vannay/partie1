/*
 * POOSV 2020-21
 * @author:
 */

#include "Positionable.hpp"

void Positionable::setPosition(const ToricPosition& nouvelle_posi)
{
    position = nouvelle_posi;
}


std::ostream& operator<<(std::ostream& sortie, Positionable& position)
{
    sortie << '[' << position;
    return sortie;
}

std::ostream& display(std::ostream& out, Positionable& posi)
{
    operator<<(out, posi);
}
