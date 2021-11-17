#include "projectile.hpp"
#include "mapsquare.hpp"
#include <cmath>
MapSquare* Projectile::GetLocation() { return location_; }

void Projectile::ChangeLocation(MapSquare* square) {
    location_ = square;
}

void Projectile::SetRemovalTrue() { to_be_removed_ = true; }

Enemy* Projectile::GetTarget() { return target_; }

unsigned int Projectile::GetStrength() { return strength_; }

bool Projectile::ToBeRemoved() { return to_be_removed_; }

