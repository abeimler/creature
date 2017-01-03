#ifndef COMPONENT_GAME_PROGRESSTIMER_H_
#define COMPONENT_GAME_PROGRESSTIMER_H_

#include "Data/Creature.h"

#include "Component/DateTimer.h"

#include "Component/Game/Basic.h"

namespace gamecomp {

/**
 * Timer für die Status/Proccesswerte(Wert von 0-100%)
 * Die Wartezeit(von 0% bis 100%) kann bei jeden Level va­ri­ie­ren.
 */
struct ProgressTimer {
    comp::DateTimer timer;     ///< Timer für den Process
    comp::DateTimer fulltimer; ///< Timer für den Proces nach 100% erreicht hat
    bool isfull = false;       ///< true, wenn 100%

    progresstimer_percent_t value = 0.0;        ///< Proccesswerte
    progresstimer_percent_t overlayvalue = 0.0; ///< Proccesswerte der über 100% liegt

    /**
     * Wartezeit die vergangen werden muss damit 100% erreicht wurde
     * Wartezeit abhännig vom Level
     */
    earr::enum_array<data::CreatureLevel, waittime_t> waittime;

    /**
    * Proccesswerte faktor,
    * damit sich der Proccesswerte schneller (> 1.0)
    * oder langsamer (< 1.0) füllt.
    * Bei 0.0 wird der Proccesswerte nicht gefüllt (pausiert)
    */
    progresstimer_factor_t factor = 1.0;
};
} // namespace gamecomp

#endif // COMPONENT_GAME_PROGRESSTIMER_H_
