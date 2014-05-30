/*
 * HealthSystem.hpp
 *
 *  Created on: 29 May 2014
 *      Author: Marco
 */

#ifndef HEALTHSYSTEM_HPP_
#define HEALTHSYSTEM_HPP_o

#include <vector>
#include "Entity.hpp"
#include "Health.hpp"
#include "Game.hpp"

typedef enum
{
	HEALTH_DEATH,
	HEALTH_HIT,
	HEALTH_HEAL
} HealthEventType;

typedef struct
{
	HealthEventType type;
	Entity entity;
} HealthEvent;
class HealthSystem {
public:
	HealthSystem();
	virtual ~HealthSystem();

	std::vector<HealthEvent> runHealthSystem(const Game &game, const GameDelta delta)
	{
		std::vector<HealthEvent> healthEvents;

		for (auto &healthUpdate : delta.getHealthDelta())
		{
			Entity affected_entity = healthUpdate.first;
			Health total = game.getCurrentGameState().getHealth(affected_entity);

			Health sum = total + healthUpdate.second;
			if (sum.getHealth() <= 0) {
				healthEvents.push_back(HealthEvent{HEALTH_DEATH, healthUpdate.first});
			} else if (healthUpdate.second.getHealth() > 0){
				healthEvents.push_back(HealthEvent{HEALTH_HEAL, healthUpdate.first});
			} else {
				healthEvents.push_back(HealthEvent{HEALTH_HIT, healthUpdate.first});
			}
		}

		return healthEvents;
	}
};

#endif /* HEALTHSYSTEM_HPP_ */
