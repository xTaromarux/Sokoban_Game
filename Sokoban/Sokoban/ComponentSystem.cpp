#include "ComponentSystem.h"

//* definicja dodawania obiektu do grupy
void Entity::addGroup(Group mGroup) {
	groupBitset[mGroup] = true;
	manager.AddToGroup(this, mGroup);
}