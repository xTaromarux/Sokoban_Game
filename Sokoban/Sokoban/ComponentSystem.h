#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

//* Tworzenie klas bez definicji
class Component;
class Entity;
class Manager;

//* ID obiketu
using ComponentID = std::size_t;
using Group = std::size_t;

//* Wstawianie ID obiektu w wybrane miejsce
inline ComponentID getNewComponentTypeID() {
	static ComponentID lastID = 0u;
	return lastID++;
}

//* Szablon do pobierania ID obiektu
template <typename T> inline ComponentID getComponentTypeID() noexcept {
	static_assert (std::is_base_of<Component, T>::value, "");
	static ComponentID typeID = getNewComponentTypeID();
	return typeID;
}

//* Maxymalna liczba przetrzymywania Kompoentow oraz Grup
constexpr std::size_t maxComponents = 64;
constexpr std::size_t maxGroups = 64;

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitset = std::bitset<maxGroups>;

using ComponentArray = std::array<Component*, maxComponents>;

//* Definicja klasy wirtualnej do tworzenia komponentow - polimorfizm
class Component {
public:
	Entity* entity;

	virtual void init() {}
	virtual void update() {}
	virtual void update(Entity& Start)  {}
	virtual void draw() {}
	virtual ~Component() {}
};

//* Definicja klasy
class Entity {
private:
	Manager& manager;
	//* okreslanie stanu
	bool active = true;
	//*wektor komponentow z dynamicza wielkoscia 
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitset;
	GroupBitset groupBitset;

public:
	Entity(Manager& mManager) : manager(mManager) {}

	//* funkcja odswierzajaca 
	void update() {
		for (auto& c : components) c->update();
	}

	//* funkcja renderujaca
	void draw() {
		for (auto& c : components) c->draw();
	}

	//* funkcja sprawdzajaca aktywnosc 
	bool isActive() const { return active; }

	//* funkcja niszczaca/wylaczajaca obiekt
	void destroy() { active = false; }

	//* funkcja sprawdzajaca grupe obiketu
	bool hasGroup(Group mGroup) {
		return groupBitset[mGroup];
	}

	//* funkcja dodajaca obiekt do grupy
	void addGroup(Group mGroup);

	//* funkcja usuwajaca obiekt z grupy
	void delGroup(Group mGroup) {
		groupBitset[mGroup] = false;
	}

	//* szablon do sprawdzania czy dany obiekt posiada dany komponent
	template <typename T> bool hasComponent() const {
		return componentBitset[getComponentTypeID<T>()];
	}

	//* szablon dodawnia do obiekt dany komponent
	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs) {
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component>uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;
		componentBitset[getComponentTypeID<T>()] = true;

		c->init();
		return *c;
	}

	//* szablon pobierajacy z obiektu dany komponent
	template<typename T> T& getComponent() const {
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}


};

//* Definicja klasy
class Manager {
private:
	std::vector<std::unique_ptr<Entity>> entities;
	std::array<std::vector<Entity*>, maxGroups> groupedEntities;
public:

	//* funkcja odswierzjaca
	void update() {
		for (auto& e : entities) e->update();
	}

	//* funkcja renderujaca
	void draw() {
		for (auto& e : entities) e->draw();
	}

	//* funkcja odswierzajaca
	void refresh() {
		for (auto i(0u); i < maxGroups; i++)
		{
			auto& v(groupedEntities[i]);
			v.erase(
				std::remove_if(std::begin(v), std::end(v),
					[i](Entity* mEntity)
					{
						return !mEntity->isActive() || !mEntity->hasGroup(i);
					}),
				std::end(v));
		}

		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity>& mEntity)
			{
				return !mEntity->isActive();
			}),
			std::end(entities));
	}

	//* funkcja dodawania do grupy
	void AddToGroup(Entity* mEntity, Group mGroup) {
		groupedEntities[mGroup].emplace_back(mEntity);
	}

	std::vector<Entity*>& getGroup(Group mGroup) {
		return groupedEntities[mGroup];
	}

	Entity& addEntity() {
		Entity* e = new Entity(*this);
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return *e;
	}
};
