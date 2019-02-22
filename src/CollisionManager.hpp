#pragma once

#include <map>
#include "entity.hpp"
#include "common.hpp"
#include "door.hpp"

// Manages collisions
class CollisionManager
{

public:

struct EntityResult
{
	const Entity* entity;
	float xPos;
	float yPos;
};

// CollisionResult is the result of moving one box a set distance.
// Collisions are resolved one by one
struct CollisionResult
{
	std::vector<EntityResult> entitiesHit;	// List of entities the box hit
	float resultXPos = 0.f;					// Final position the box would be
	float resultYPos = 0.f;					// Final position the box would be
	bool hitGround = false;					// If there was a grounding collision
	bool hitCeiling = false;				// If there was a ceiling collision
};

public:
	CollisionManager() {}

	// Singleton
	static CollisionManager& GetInstance()
	{
		static CollisionManager instance;
		return instance;
	}

	// Make sure these functions never get called (or else we may end up with more than 1 CollisionManager)
	CollisionManager(CollisionManager const &) = delete;
	void operator=(CollisionManager const &) = delete;

	// Registers an entity. Should be called on entity init, or to update an entity after it has moved
	void RegisterEntity(Entity* entity);

	// Unregisters an entity. Should be called on destroy.
	void UnregisterEntity(Entity* entity);

	// Given a box with param dimensions moving a distance of xDist, yDist
	// Return the result of all collisions that will happen
	const CollisionResult BoxTrace(int width, int height, float xPos, float yPos, float xDist, float yDist, bool unstoppable = false) const;

	// Check whether door and player are colliding
	// Return true if they are
	const bool DoorTrace(vec2 bounding_box, vec2 door_pos, float door_width, float door_height, vec2 player_pos) const;

	// Returns the relevant equations for light calculations for a light source at pos with radius
	const ParametricLines CalculateLightEquations(float xPos, float yPos, float lightRadius) const;

private:
	// Game entities : Light collision equations
	std::map<Entity*, const ParametricLines> staticLightCollisionLines;

	// List of box entities that have collision
	std::vector<const Entity*> staticCollisionEntities;
};
