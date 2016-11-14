#include "System/Game/CreatureProgressTimerSystem.h"

namespace gamesystem {

double CreatureProgressTimerSystem::updateCallbackTimer(
    EventBus& events, Entity entity,
    gamecomp::ProgressTimerCallback& timer, data::CreatureLevel level,
    gamecomp::CreatureProgressTimerCallback type) {
    double ret = updateTimer(timer.base, level);

    if (timer.base.timer.isstart && !timer.base.timer.ispause) {
        if (!util::iszero(timer.base.value - timer.oldvalue)) {
            if (timer.base.isfull) {
                emit_event<gameevent::ProgressTimerCallbackEvent>(events, 
                    entity, type, level);

                timer.oldvalue = 0;
            } else {
                timer.oldvalue = timer.base.value;
            }
        }

        if (timer.base.isfull && timer.isendless) {
            progresstimer_util_.restart(timer.base);
            timer.oldvalue = timer.base.value;
        }
    }

    return ret;
}

double CreatureProgressTimerSystem::updateIncrementTimer(
    EventBus& events, Entity entity,
    gamecomp::ProgressTimerIncrement& timer, data::CreatureLevel level,
    gamecomp::CreatureProgressTimerIncrement type) {
    double ret = updateTimer(timer.base, level);

    if (timer.base.timer.isstart && !timer.base.timer.ispause) {
        double addvalue = ret;
        addvalue *= timer.addvalue_per_percent;

        if (!util::iszero(addvalue)) {
            emit_event<gameevent::ProgressTimerIncrementEvent>(events, entity, type, level,
                                                     addvalue);
        }

        if (timer.base.isfull && timer.isendless) {
            progresstimer_util_.restart(timer.base);
        }
    }

    return ret;
}

double CreatureProgressTimerSystem::updateStarvationPhaseTimer(
    EventBus& events, Entity entity,
    gamecomp::ProgressTimerCallback& timer, data::CreatureLevel level,
    gamecomp::StarvationPhase type) {
    double ret = updateTimer(timer.base, level);

    if (timer.base.timer.isstart && !timer.base.timer.ispause) {
        if (!util::iszero(timer.base.value - timer.oldvalue)) {
            if (timer.base.isfull) {
                emit_event<gameevent::ProgressTimerStarvationPhaseEvent>(events, 
                    entity, type, level);

                timer.oldvalue = 0;
            } else {
                timer.oldvalue = timer.base.value;
            }
        }
    }

    return ret;
}

double CreatureProgressTimerSystem::updateShortTermMemoryTimer(
    EventBus& events, Entity entity,
    gamecomp::ProgressTimerCallback& timer, data::CreatureLevel level,
    gamecomp::CreatureActivity activity) {
    double ret = updateTimer(timer.base, level);

    if (timer.base.timer.isstart && !timer.base.timer.ispause) {
        if (!util::iszero(timer.base.value - timer.oldvalue)) {
            if (timer.base.isfull) {
                emit_event<gameevent::ProgressTimerShortTermMemoryEvent>(events, 
                    entity, activity, level);

                timer.oldvalue = 0;
            } else {
                timer.oldvalue = timer.base.value;
            }
        }
    }

    return ret;
}

double CreatureProgressTimerSystem::updateMediumTermMemoryTimer(
    EventBus& events, Entity entity,
    gamecomp::ProgressTimerCallback& timer, data::CreatureLevel level,
    gamecomp::CreatureActivity activity) {
    double ret = updateTimer(timer.base, level);

    if (timer.base.timer.isstart && !timer.base.timer.ispause) {
        if (!util::iszero(timer.base.value - timer.oldvalue)) {
            if (timer.base.isfull) {
                emit_event<gameevent::ProgressTimerMediumTermMemoryEvent>(events, 
                    entity, activity, level);

                timer.oldvalue = 0;
            } else {
                timer.oldvalue = timer.base.value;
            }
        }
    }

    return ret;
}


double
CreatureProgressTimerSystem::updateTimer(gamecomp::ProgressTimer& timer,
                                         data::CreatureLevel level) {
    datetimer_util_.update(timer.timer, this->ignortimer_);
    datetimer_util_.update(timer.fulltimer, this->ignortimer_);

    if (!timer.timer.isstart && !timer.timer.ispause) {
        return 0.0;
}

    double addValue = 0.0;
    auto waitTime_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        earr::enum_array_at(timer.waittime, level));
    auto timer_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        datetimer_util_.getTime(timer.timer));

    /// t/100 => damit min. jedes 1% überprüft wird
    std::chrono::milliseconds min_waitTime_ms = waitTime_ms / 100;

    if (waitTime_ms > std::chrono::milliseconds::zero() &&
        timer_ms >= min_waitTime_ms) {
        // storage nanosec vs. millisec in float vs. double
        // double cant storage 64 bit integer
        // nanosec chrono: A signed integral type of at least 64 bits
        // millisec chrono: A signed integral type of at least 45 bits
        double addValue_percent =
            (static_cast<double>(timer_ms.count()) * 100.0) /
            static_cast<double>(waitTime_ms.count());
        addValue = addValue_percent * timer.factor;

        timer.value += addValue;

        if (timer.value > 100.0) {
            if (!timer.isfull) {
                datetimer_util_.start(timer.fulltimer);

                double ticks_ms_f =
                    static_cast<double>(waitTime_ms.count()) *
                    ((timer.value - 100.0) / 100.0);
                std::chrono::milliseconds addTm_ms(
                    static_cast<int64_t>(ticks_ms_f));

                datetimer_util_.addTime(timer.fulltimer, addTm_ms);
            }
            timer.isfull = true;
        } else if (timer.value >= 100.0 && timer.value <= 100.0) {
            if (!timer.isfull) {
                datetimer_util_.start(timer.fulltimer);
            }
            timer.isfull = true;
        } else if (timer.value < 100.0) {
            if (timer.isfull) {
                datetimer_util_.stop(timer.fulltimer);
                timer.isfull = false;
                timer.overlayvalue = 0.0;
            }
        }
        timer.value = std::min<double>(100.0, timer.value);
        timer.value = std::max<double>(0.0, timer.value);

        if (timer.isfull) {
            auto fulltimer_ms =
                std::chrono::duration_cast<std::chrono::milliseconds>(
                    datetimer_util_.getTime(timer.fulltimer));

            double fullValue_percent =
                (static_cast<double>(fulltimer_ms.count()) * 100.0) /
                static_cast<double>(waitTime_ms.count());
            timer.overlayvalue += fullValue_percent * timer.factor;
        }

        // double not zero
        if (!util::iszero(addValue)) {
            datetimer_util_.restart(timer.timer);
        }
    }

    return addValue;
}

void CreatureProgressTimerSystem::update(EntityManager& entities,
                                         EventBus& events,
                                         TimeDelta dt) {
    gameentity::Component<gamecomp::CreatureProgressTimersComponent> creatureprogresstimers;

    for (auto entity :
         entities.entities_with_components(creatureprogresstimers)) {
        data::CreatureLevel level =
            creatureprogresstimers->creaturelevel;

        datetimer_util_.update(creatureprogresstimers->lifetimer);

        for (auto& timer : creatureprogresstimers->timer) {
            updateTimer(timer, level);
        }

        for (auto type : earr::Enum<gamecomp::CreatureProgressTimerCallback>()) {
            auto& timer = earr::enum_array_at(creatureprogresstimers->callback, type);

            updateCallbackTimer(events, entity, timer, level, type);
        }

        for (auto type : earr::Enum<gamecomp::CreatureProgressTimerIncrement>()) {
            auto& timer = earr::enum_array_at(creatureprogresstimers->increment, type);

            updateIncrementTimer(events, entity, timer, level, type);
        }

        for (auto type : earr::Enum<gamecomp::StarvationPhase>()) {
            auto& timer = earr::enum_array_at(creatureprogresstimers->starvation, type);

            updateStarvationPhaseTimer(events, entity, timer, level, type);
        }

        for (auto activity : earr::Enum<gamecomp::CreatureActivity>()) {
            auto& shortterm_timer = earr::enum_array_at(creatureprogresstimers->memory, activity).shortterm;

            updateShortTermMemoryTimer(events, entity, shortterm_timer, level,
                                       activity);


            auto& mediumterm_timer = earr::enum_array_at(creatureprogresstimers->memory, activity).mediumterm;

            updateMediumTermMemoryTimer(events, entity, mediumterm_timer, level,
                                        activity);
        }
    }
}
} // namespace gamesystem
