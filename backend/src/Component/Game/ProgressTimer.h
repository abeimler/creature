#ifndef COMPONENT_GAME_PROGRESSTIMER_H_
#define COMPONENT_GAME_PROGRESSTIMER_H_

#include "Data/Creature.h"

#include "Component/DateTimer.h"

namespace gamecomp {

/**
 * Timer für die Status/Proccesswerte(Wert von 0-100%)
 * Die Wartezeit(von 0% bis 100%) kann bei jeden Level va­ri­ie­ren.
 */
struct ProgressTimer {
    comp::DateTimer timer;     ///< Timer für den Process
    comp::DateTimer fulltimer; ///< Timer für den Proces nach 100% erreicht hat
    bool isfull = false;       ///< true, wenn 100%
    double value = 0.0;        ///< Proccesswerte
    double overlayvalue = 0.0; ///< Proccesswerte der über 100% liegt

    /**
     * Wartezeit die vergangen werden muss damit 100% erreicht wurde
     * Wartezeit abhännig vom Level
     */
    earr::enum_array<data::CreatureLevel, std::chrono::milliseconds> waittime;

    /**
    * Proccesswerte faktor,
    * damit sich der Proccesswerte schneller (> 1.0)
    * oder langsamer (< 1.0) füllt.
    * Bei 0.0 wird der Proccesswerte nicht gefüllt (pausiert)
    */
    double factor = 1.0;
};
} // namespace gamecomp

#endif // COMPONENT_GAME_PROGRESSTIMER_H_
