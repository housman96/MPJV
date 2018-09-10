#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <vector>
#include "Particle.h"

/**
 * La classe qui affiche tous les objets qu'on lui donne
 */
class Affichage
{
private:
  static std::vector<Particle> list;

public:
  Affichage(int argc, char **argv, Particle part);
  static void Display();
  static void redim(int width, int height);
};

#endif