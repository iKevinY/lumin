#pragma once

#include <map>
#include <set>
#include "entity.hpp"
#include "common.hpp"

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

	// Registers a light
	void RegisterLight(const LightMesh* light);
	void UnregisterLight(const LightMesh* light);

	// Registers an entity. Should be called on entity init, or to update an entity after it has moved
	void RegisterEntity(const Entity* entity);

	// Unregisters an entity. Should be called on destroy.
	void UnregisterEntity(const Entity* entity);

	// Given a box with param dimensions moving a distance of xDist, yDist
	// Return the result of all collisions that will happen
	const CollisionResult BoxTrace(int width, int height, float xPos, float yPos, float xDist, float yDist, bool unstoppable = false) const;

	// Check whether door and player are colliding
	// Return true if they are
	const bool DoorTrace(vec2 bounding_box, vec2 door_pos, float door_width, float door_height, vec2 player_pos) const;

	// Returns the relevant equations for light calculations for a light source at pos with radius
	const ParametricLines CalculateLightEquations(float xPos, float yPos, float lightRadius) const;

	// Returns a list of all the vertices of light-blocking objects that are found within a light's radius
	const std::vector<vec2> CalculateVertices(float xPos, float yPos, float lightRadius) const;

	bool IsHitByLight(const Entity* entity) const;
	bool IsHitByLight(const vec2 entityPos) const;

	vec2 getClosestVisibleLightSource(const vec2 entityPos) const;

	const void UpdateDynamicLightEquations();

	bool LinesCollide(ParametricLine line1, ParametricLine line2) const;
	bool LinesCollide(ParametricLine line1, ParametricLine line2, vec2& collisionPos) const;

private:
	std::set<const Entity*> registeredEntities;

	// Game entities : Light collision equations
	std::map<const Entity*, const ParametricLines> staticLightCollisionLines;
	std::map<const Entity*, const ParametricLines> dynamicLightCollisionLines;

	// List of box entities that have collision
	std::vector<const Entity*> staticCollisionEntities;
	
	// List of light in the level
	std::set<const LightMesh*> lightSources;

	void CalculateLightEquationForEntry(std::pair<const Entity*, ParametricLines> entry, ParametricLines& outLines, float xPos, float yPos, float lightRadius) const;
	void CalculateVerticesForEntry(const Entity* entity, std::vector<vec2> &outVector, float xPos, float yPos, float lightRadius) const;
};
