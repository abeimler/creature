#include "Entity/Game/CreatureEntityCreator.h"

namespace gameentity {

double CreatureEntityCreator::getBMI(const gamecomp::CreatureGeneComponent& gene,
                              double minweight, double maxweight, double weight,
                              double bodysize) {
    /*
    s    : Größe
    g    : Gewicht
    gmin : minimal Gewicht
    bmin : minimal bmi
    bmix : maximal bmi
    m    : Masse

    BMI errechnen:
    bmi = sqrt(s*g + gmin) + (gmin * (bmin/2/bmax)) * m

    Größe errechnen:
    s = ((bmi -(gmin * (bmin/2/bmax)) * m)^2 - gmin)/g

    Masse errechnen:
    m = (sqrt(s*g + gmin) - bmi) / (-(gmin * (bmin/2/bmax)))


    bmi	= sqrt(s*g + gmin) + (gmin*(bmin/2/bmax)) * m
    bmi -(gmin * (bmin/2/bmax)) * m 		        = sqrt(s*g + gmin)
    (bmi -(gmin * (bmin/2/bmax)) * m)^2 		    = s*g + gmin
    (bmi -(gmin * (bmin/2/bmax)) * m)^2 - gmin 	    = s*g

    s = ((bmi -(gmin * (bmin/2/bmax)) * m)^2 - gmin)/g



    bmi	= sqrt(s*g + gmin) + (gmin*(bmin/2/bmax)) * m
    bmi - (gmin * (bmin/2/bmax)) * m 		    = sqrt(s*g + gmin)
    bmi - (gmin * (bmin/2/bmax)) * m 		    = sqrt(s*g + gmin)
    - (gmin * (bmin/2/bmax)) * m 			    = sqrt(s*g + gmin) -
    bmi

    m = (sqrt(s*g + gmin) - bmi) / (- (gmin * (bmin/2/bmax)))
    */

    double s = bodysize;
    double g = weight;
    double gmin = minweight;
    double gmax = maxweight;
    double bmin = gene.min_bmi;
    double bmax = gene.max_bmi;
    double m = gene.bodymass;

    return (bmin > 0.0 && gmin > 0.0 && bmax > 0.0 && gmin <= gmax)?
                std::sqrt(s * g + gmin) + (gmin * (bmin / 2.0 / bmax)) * m
            : 0.0;
}

double CreatureEntityCreator::getBodyMass(double s, double g, double mg, double ibmi,
                                   double minbmi, double maxbmi) {
    /*
    s    : Größe
    g    : Gewicht
    gmin   : minimal Gewicht
    bmin : minimal bmi
    bmix : maximal bmi
    ibmi : ideal bmi
    m    : Masse

    Ideal Masse errechnen:
    m = (sqrt(s*g + gmin) - ibmi) / (-(gmin * (bmin/2/bmax)))

    es dürfen keine nevativen Werte rauskommen
    bei mass < 0 : mass = 1 / abs(mass)

    see CreatureEntityCreator::getBMI()
    */

    double mass =
        (std::sqrt(s * g + mg) - ibmi) / (-(mg * (minbmi / 2.0 / maxbmi)));
    
    return (mass < 0.0)? 1.0 / std::abs(mass) : mass;
}

double CreatureEntityCreator::getBodySize(double minbmi, double maxbmi, double bmi,
                                   double mass, double minweight, double maxweight,
                                   double weight) {
    /*
    s    : Größe
    g    : Gewicht
    gmin : minimal Gewicht
    bmin : minimal bmi
    bmix : maximal bmi
    m    : Masse

    Körpergröße errechnen:
    s = ((bmi -(gmin * (bmin/2/bmax)) * m)^2 - gmin)/g
    */

    double g = weight;
    double gmin = minweight;
    double gmax = maxweight;
    double bmin = minbmi;
    double bmax = maxbmi;
    double m = mass;

    return (bmin > 0.0 && gmin > 0.0 && bmax > 0.0 && gmin <= gmax && !util::iszero(g))?
                (std::pow(bmi - (gmin * (bmin / 2.0 / bmax)) * m, 2.0) - gmin) / g
           : 0.0;
}



double CreatureEntityCreator::getBMI(const data::Creature& creature,
                              const gamecomp::CreatureGeneComponent& gene,
                              double weight) {
    double bodysize = creature.getBodySize();
    double minweight = creature.getMinWeight();
    double maxweight = creature.getMaxWeight();

    return getBMI(gene, minweight, maxweight, weight, bodysize);
}


double CreatureEntityCreator::getBodyMass(const data::Creature& creature,
                                    const gamecomp::CreatureGeneComponent& gene) {
    double s = creature.getBodySize();
    double g =
        creature.getMinWeight() *
        ((!util::iszero(gene.max_bmi)) ? (1.0 + (gene.ideal_bmi / gene.max_bmi))
                                 : 1.0);
    double mg = creature.getMinWeight();

    return getBodyMass(gene, s, g, mg);
}

double CreatureEntityCreator::getBodyMass(const gamecomp::CreatureGeneComponent& gene, 
                                    double s, double g, double mg) {
    double ibmi = gene.ideal_bmi;
    double maxbmi = gene.max_bmi;
    double minbmi = gene.min_bmi;
    return getBodyMass(s, g, mg, ibmi, minbmi, maxbmi);
}



gamecomp::CreatureGeneWaitTime::waittime_t<gamecomp::CreatureProgressTimer>
CreatureEntityCreator::createTimerWaitTime(data::CreatureLevel creature_level) {
    gamecomp::CreatureGeneWaitTime::waittime_t<gamecomp::CreatureProgressTimer> ret;

    switch(creature_level){
        case data::CreatureLevel::Egg:
        case data::CreatureLevel::Baby:
            setCreatureGeneWaitTime(ret, +gamecomp::CreatureProgressTimer::Hungry,
                                    std::chrono::hours(3));
            setCreatureGeneWaitTime(ret, +gamecomp::CreatureProgressTimer::Thirsty,
                                    std::chrono::hours(3));
            setCreatureGeneWaitTime(ret, +gamecomp::CreatureProgressTimer::Tired,
                                    std::chrono::hours(6));
        break;
        case data::CreatureLevel::Baby2:
            setCreatureGeneWaitTime(ret, +gamecomp::CreatureProgressTimer::Hungry,
                                    std::chrono::hours(4));
            setCreatureGeneWaitTime(ret, +gamecomp::CreatureProgressTimer::Thirsty,
                                    std::chrono::hours(4));
            setCreatureGeneWaitTime(ret, +gamecomp::CreatureProgressTimer::Tired,
                                    std::chrono::hours(9));
        break;
        case data::CreatureLevel::Child:
            setCreatureGeneWaitTime(ret, +gamecomp::CreatureProgressTimer::Hungry,
                                    std::chrono::hours(6));
            setCreatureGeneWaitTime(ret, +gamecomp::CreatureProgressTimer::Thirsty,
                                    std::chrono::hours(5));
            setCreatureGeneWaitTime(ret, +gamecomp::CreatureProgressTimer::Tired,
                                    std::chrono::hours(12));
        break;
        case data::CreatureLevel::Adult:
        case data::CreatureLevel::Perfect:
        case data::CreatureLevel::Ultimate:
            setCreatureGeneWaitTime(ret, +gamecomp::CreatureProgressTimer::Hungry,
                                    std::chrono::hours(8));
            setCreatureGeneWaitTime(ret, +gamecomp::CreatureProgressTimer::Thirsty,
                                    std::chrono::hours(7));
            setCreatureGeneWaitTime(ret, +gamecomp::CreatureProgressTimer::Tired,
                                    std::chrono::hours(18));
        break;
        case data::CreatureLevel::END:
        break;
    }

    switch(creature_level){
        case data::CreatureLevel::Egg:
            setCreatureGeneWaitTime(ret, +gamecomp::CreatureProgressTimer::Evolution,
                                    std::chrono::minutes(1));
        break;
        case data::CreatureLevel::Baby:
            setCreatureGeneWaitTime(ret, +gamecomp::CreatureProgressTimer::Evolution,
                                    std::chrono::hours(9));
        break;
        case data::CreatureLevel::Baby2:
            setCreatureGeneWaitTime(ret, +gamecomp::CreatureProgressTimer::Evolution,
                                    std::chrono::hours(20));
        break;
        case data::CreatureLevel::Child:
            setCreatureGeneWaitTime(ret, +gamecomp::CreatureProgressTimer::Evolution,
                                    std::chrono::hours(24 * 5));
        break;
        case data::CreatureLevel::Adult:
            setCreatureGeneWaitTime(ret, +gamecomp::CreatureProgressTimer::Evolution,
                                    std::chrono::hours(24 * 30 * 1));
        break;
        case data::CreatureLevel::Perfect:
            setCreatureGeneWaitTime(ret, +gamecomp::CreatureProgressTimer::Evolution,
                                    std::chrono::hours(24 * 30 * 2));
        break;
        case data::CreatureLevel::Ultimate:
            setCreatureGeneWaitTime(ret, +gamecomp::CreatureProgressTimer::Evolution,
                                    std::chrono::hours(24 * 30 * 6));
        break;
        case data::CreatureLevel::END:
        break;
    }

    clearCreatureGeneWaitTime(ret, +gamecomp::CreatureProgressTimer::Training);

    clearCreatureGeneWaitTime(ret, +gamecomp::CreatureProgressTimer::RunAway);

    return ret;
}


gamecomp::CreatureGeneWaitTime::waittime_t<gamecomp::CreatureProgressTimerCallback>
CreatureEntityCreator::createCallbackWaitTime(data::CreatureLevel creature_level) {
    gamecomp::CreatureGeneWaitTime::waittime_t<gamecomp::CreatureProgressTimerCallback> ret;

    switch(creature_level){
        case data::CreatureLevel::Egg:
        case data::CreatureLevel::Baby:
            setCreatureGeneWaitTime(ret,
                            +gamecomp::CreatureProgressTimerCallback::Digestion,
                            std::chrono::hours(5));
            setCreatureGeneWaitTime(ret, 
                            +gamecomp::CreatureProgressTimerCallback::PauseDigestionHungry,
                            std::chrono::hours(8));
            setCreatureGeneWaitTime(ret,
                            +gamecomp::CreatureProgressTimerCallback::FullDigestionHeap,
                            std::chrono::hours(24 * 3));
            setCreatureGeneWaitTime(ret, 
                            +gamecomp::CreatureProgressTimerCallback::IllbyOverweight,
                            std::chrono::hours(24 * 30 * 6));
            setCreatureGeneWaitTime(ret,
                            +gamecomp::CreatureProgressTimerCallback::GoSleep,
                            std::chrono::minutes(5));
            setCreatureGeneWaitTime(ret,
                            +gamecomp::CreatureProgressTimerCallback::Inhospital,
                            std::chrono::minutes(10));
            setCreatureGeneWaitTime(ret, 
                            +gamecomp::CreatureProgressTimerCallback::HurtToDead,
                            std::chrono::hours(24 * 10));
            setCreatureGeneWaitTime(ret, 
                            +gamecomp::CreatureProgressTimerCallback::IllToDead,
                            std::chrono::hours(24 * 20));
            setCreatureGeneWaitTime(ret, 
                            +gamecomp::CreatureProgressTimerCallback::Unhappy,
                            std::chrono::hours(24 * 35));
            setCreatureGeneWaitTime(ret, 
                            +gamecomp::CreatureProgressTimerCallback::RunAwayUnhappy,
                            std::chrono::minutes(40));
            setCreatureGeneWaitTime(ret, 
                            +gamecomp::CreatureProgressTimerCallback::Bored,
                            std::chrono::minutes(45));
        break;
        case data::CreatureLevel::Baby2:
            setCreatureGeneWaitTime(ret,
                            +gamecomp::CreatureProgressTimerCallback::Digestion,
                            std::chrono::hours(7));
            setCreatureGeneWaitTime(ret, 
                            +gamecomp::CreatureProgressTimerCallback::PauseDigestionHungry,
                            std::chrono::hours(12));
            setCreatureGeneWaitTime(ret,
                            +gamecomp::CreatureProgressTimerCallback::FullDigestionHeap,
                            std::chrono::hours(24 * 5));
            setCreatureGeneWaitTime(ret, 
                            +gamecomp::CreatureProgressTimerCallback::IllbyOverweight,
                            std::chrono::hours(24 * 30 * 5));
            setCreatureGeneWaitTime(ret,
                            +gamecomp::CreatureProgressTimerCallback::GoSleep,
                            std::chrono::minutes(10));
            setCreatureGeneWaitTime(ret,
                            +gamecomp::CreatureProgressTimerCallback::Inhospital,
                            std::chrono::minutes(10));
            setCreatureGeneWaitTime(ret, 
                            +gamecomp::CreatureProgressTimerCallback::HurtToDead,
                            std::chrono::hours(24 * 20));
            setCreatureGeneWaitTime(ret, 
                            +gamecomp::CreatureProgressTimerCallback::IllToDead,
                            std::chrono::hours(24 * 30));
            setCreatureGeneWaitTime(ret, 
                            +gamecomp::CreatureProgressTimerCallback::Unhappy,
                            std::chrono::hours(24 * 60));
            setCreatureGeneWaitTime(ret, 
                            +gamecomp::CreatureProgressTimerCallback::RunAwayUnhappy,
                            std::chrono::hours(1));
            setCreatureGeneWaitTime(ret, 
                            +gamecomp::CreatureProgressTimerCallback::Bored,
                            std::chrono::hours(1));
        break;
        case data::CreatureLevel::Child:
            setCreatureGeneWaitTime(ret,
                            +gamecomp::CreatureProgressTimerCallback::Digestion,
                            std::chrono::hours(8));
            setCreatureGeneWaitTime(ret, 
                            +gamecomp::CreatureProgressTimerCallback::PauseDigestionHungry,
                            std::chrono::hours(20));
            setCreatureGeneWaitTime(ret,
                            +gamecomp::CreatureProgressTimerCallback::FullDigestionHeap,
                            std::chrono::hours(24 * 15));
            setCreatureGeneWaitTime(ret, 
                            +gamecomp::CreatureProgressTimerCallback::IllbyOverweight,
                            std::chrono::hours(24 * 30 * 5));
            setCreatureGeneWaitTime(ret,
                            +gamecomp::CreatureProgressTimerCallback::GoSleep,
                            std::chrono::minutes(20));
            setCreatureGeneWaitTime(ret,
                            +gamecomp::CreatureProgressTimerCallback::Inhospital,
                            std::chrono::minutes(15));
            setCreatureGeneWaitTime(ret, 
                            +gamecomp::CreatureProgressTimerCallback::HurtToDead,
                            std::chrono::hours(24 * 30));
            setCreatureGeneWaitTime(ret, 
                            +gamecomp::CreatureProgressTimerCallback::IllToDead,
                            std::chrono::hours(24 * 40));
            setCreatureGeneWaitTime(ret, 
                            +gamecomp::CreatureProgressTimerCallback::Unhappy,
                            std::chrono::hours(24 * 60));
            setCreatureGeneWaitTime(ret, 
                            +gamecomp::CreatureProgressTimerCallback::RunAwayUnhappy,
                            std::chrono::hours(24));
            setCreatureGeneWaitTime(ret, 
                            +gamecomp::CreatureProgressTimerCallback::Bored,
                            std::chrono::hours(3));
                            
        break;
        case data::CreatureLevel::Adult:
        case data::CreatureLevel::Perfect:
        case data::CreatureLevel::Ultimate:
            setCreatureGeneWaitTime(ret,
                            +gamecomp::CreatureProgressTimerCallback::Digestion,
                            std::chrono::hours(10));
            setCreatureGeneWaitTime(ret, 
                            +gamecomp::CreatureProgressTimerCallback::PauseDigestionHungry,
                            std::chrono::hours(28));
            setCreatureGeneWaitTime(ret,
                            +gamecomp::CreatureProgressTimerCallback::FullDigestionHeap,
                            std::chrono::hours(24 * 20));
            setCreatureGeneWaitTime(ret, 
                            +gamecomp::CreatureProgressTimerCallback::IllbyOverweight,
                            std::chrono::hours(24 * 30 * 4));
            setCreatureGeneWaitTime(ret,
                            +gamecomp::CreatureProgressTimerCallback::GoSleep,
                            std::chrono::minutes(30));
            setCreatureGeneWaitTime(ret,
                            +gamecomp::CreatureProgressTimerCallback::Inhospital,
                            std::chrono::minutes(15));
            setCreatureGeneWaitTime(ret, 
                            +gamecomp::CreatureProgressTimerCallback::HurtToDead,
                            std::chrono::hours(24 * 40));
            setCreatureGeneWaitTime(ret, 
                            +gamecomp::CreatureProgressTimerCallback::IllToDead,
                            std::chrono::hours(24 * 50));
            setCreatureGeneWaitTime(ret, 
                            +gamecomp::CreatureProgressTimerCallback::Unhappy,
                            std::chrono::hours(24 * 90));
            setCreatureGeneWaitTime(ret, 
                            +gamecomp::CreatureProgressTimerCallback::RunAwayUnhappy,
                            std::chrono::hours(24 * 2));
            setCreatureGeneWaitTime(ret, 
                            +gamecomp::CreatureProgressTimerCallback::Bored,
                            std::chrono::hours(2));
        break;
        case data::CreatureLevel::END:
        break;
    }

    return ret;
}


gamecomp::CreatureGeneWaitTime::waittime_t<gamecomp::CreatureProgressTimerIncrement>
CreatureEntityCreator::createIncrementWaitTime(data::CreatureLevel creature_level) {
    gamecomp::CreatureGeneWaitTime::waittime_t<gamecomp::CreatureProgressTimerIncrement> ret;


    switch(creature_level){
        case data::CreatureLevel::Egg:
        case data::CreatureLevel::Baby:
            setCreatureGeneWaitTime(ret, 
                                +gamecomp::CreatureProgressTimerIncrement::LostWeightTimerHungry,
                                std::chrono::hours(24 * 5));
            setCreatureGeneWaitTime(ret, 
                                +gamecomp::CreatureProgressTimerIncrement::LostWeightTimerThirsty,
                                std::chrono::hours(24 * 5));
            setCreatureGeneWaitTime(ret, 
                                +gamecomp::CreatureProgressTimerIncrement::LostCalories,
                                std::chrono::hours(24));
            setCreatureGeneWaitTime(ret, 
                                +gamecomp::CreatureProgressTimerIncrement::GainWeightCalories,
                                std::chrono::hours(24));
            setCreatureGeneWaitTime(ret,
                                +gamecomp::CreatureProgressTimerIncrement::GoodSleep,
                                std::chrono::hours(12));
            setCreatureGeneWaitTime(ret,
                                +gamecomp::CreatureProgressTimerIncrement::BadSleep,
                                std::chrono::hours(13));
            setCreatureGeneWaitTime(ret, 
                                +gamecomp::CreatureProgressTimerIncrement::RestHospital,
                                std::chrono::hours(3));
            setCreatureGeneWaitTime(ret, 
                                +gamecomp::CreatureProgressTimerIncrement::HurtLostHP,
                                std::chrono::hours(9 * 24));
        break;
        case data::CreatureLevel::Baby2:
            setCreatureGeneWaitTime(ret, 
                                    +gamecomp::CreatureProgressTimerIncrement::LostWeightTimerHungry,
                                    std::chrono::hours(24 * 5));
            setCreatureGeneWaitTime(ret, 
                                    +gamecomp::CreatureProgressTimerIncrement::LostWeightTimerThirsty,
                                    std::chrono::hours(24 * 5));
            setCreatureGeneWaitTime(ret, 
                                    +gamecomp::CreatureProgressTimerIncrement::LostCalories,
                                    std::chrono::hours(24));
            setCreatureGeneWaitTime(ret, 
                                    +gamecomp::CreatureProgressTimerIncrement::GainWeightCalories,
                                    std::chrono::hours(24));
            setCreatureGeneWaitTime(ret,
                                    +gamecomp::CreatureProgressTimerIncrement::GoodSleep,
                                    std::chrono::hours(10));
            setCreatureGeneWaitTime(ret,
                                    +gamecomp::CreatureProgressTimerIncrement::BadSleep,
                                    std::chrono::hours(11));
            setCreatureGeneWaitTime(ret, 
                                    +gamecomp::CreatureProgressTimerIncrement::RestHospital,
                                    std::chrono::hours(2));
            setCreatureGeneWaitTime(ret, 
                                    +gamecomp::CreatureProgressTimerIncrement::HurtLostHP,
                                    std::chrono::hours(14 * 24));
        break;
        case data::CreatureLevel::Child:
            setCreatureGeneWaitTime(ret, 
                                +gamecomp::CreatureProgressTimerIncrement::LostWeightTimerHungry,
                                std::chrono::hours(24 * 6));
            setCreatureGeneWaitTime(ret, 
                                +gamecomp::CreatureProgressTimerIncrement::LostWeightTimerThirsty,
                                std::chrono::hours(24 * 6));
            setCreatureGeneWaitTime(ret, 
                                +gamecomp::CreatureProgressTimerIncrement::LostCalories,
                                std::chrono::hours(24));
            setCreatureGeneWaitTime(ret, 
                                +gamecomp::CreatureProgressTimerIncrement::GainWeightCalories,
                                std::chrono::hours(24));
            setCreatureGeneWaitTime(ret,
                                +gamecomp::CreatureProgressTimerIncrement::GoodSleep,
                                std::chrono::hours(8));
            setCreatureGeneWaitTime(ret,
                                +gamecomp::CreatureProgressTimerIncrement::BadSleep,
                                std::chrono::hours(10));
            setCreatureGeneWaitTime(ret, 
                                +gamecomp::CreatureProgressTimerIncrement::RestHospital,
                                std::chrono::hours(1));
            setCreatureGeneWaitTime(ret, 
                                +gamecomp::CreatureProgressTimerIncrement::HurtLostHP,
                                std::chrono::hours(24 * 24));
        break;
        case data::CreatureLevel::Adult:
        case data::CreatureLevel::Perfect:
        case data::CreatureLevel::Ultimate:
            setCreatureGeneWaitTime(ret, 
                                +gamecomp::CreatureProgressTimerIncrement::LostWeightTimerHungry,
                                std::chrono::hours(24 * 7));
            setCreatureGeneWaitTime(ret, 
                                +gamecomp::CreatureProgressTimerIncrement::LostWeightTimerThirsty,
                                std::chrono::hours(24 * 7));
            setCreatureGeneWaitTime(ret, 
                                +gamecomp::CreatureProgressTimerIncrement::LostCalories,
                                std::chrono::hours(24));
            setCreatureGeneWaitTime(ret, 
                                +gamecomp::CreatureProgressTimerIncrement::GainWeightCalories,
                                std::chrono::hours(24));
            setCreatureGeneWaitTime(ret,
                                +gamecomp::CreatureProgressTimerIncrement::GoodSleep,
                                std::chrono::hours(7));
            setCreatureGeneWaitTime(ret,
                                +gamecomp::CreatureProgressTimerIncrement::BadSleep,
                                std::chrono::hours(9));
            setCreatureGeneWaitTime(ret, 
                                +gamecomp::CreatureProgressTimerIncrement::RestHospital,
                                std::chrono::hours(2));
            setCreatureGeneWaitTime(ret, 
                                +gamecomp::CreatureProgressTimerIncrement::HurtLostHP,
                                std::chrono::hours(35 * 24));
        break;
        case data::CreatureLevel::END:
        break;
    }

    switch(creature_level){
        case data::CreatureLevel::Egg:
            setCreatureGeneWaitTime(ret, 
                                +gamecomp::CreatureProgressTimerIncrement::Growing,
                                std::chrono::minutes(1));
        break;
        case data::CreatureLevel::Baby:
            setCreatureGeneWaitTime(ret, 
                                +gamecomp::CreatureProgressTimerIncrement::Growing,
                                std::chrono::hours(8));
        break;
        case data::CreatureLevel::Baby2:
            setCreatureGeneWaitTime(ret, 
                                +gamecomp::CreatureProgressTimerIncrement::Growing,
                                std::chrono::hours(19));
        break;
        case data::CreatureLevel::Child:
            setCreatureGeneWaitTime(ret, 
                                +gamecomp::CreatureProgressTimerIncrement::Growing,
                                std::chrono::hours(24 * 4));
        break;
        case data::CreatureLevel::Adult:
            setCreatureGeneWaitTime(ret, 
                                +gamecomp::CreatureProgressTimerIncrement::Growing,
                                std::chrono::hours(24 * 20));
        break;
        case data::CreatureLevel::Perfect:
            setCreatureGeneWaitTime(ret, 
                                +gamecomp::CreatureProgressTimerIncrement::Growing,
                                std::chrono::hours(24 * 30 * 1));
        break;
        case data::CreatureLevel::Ultimate:
            setCreatureGeneWaitTime(ret, 
                                +gamecomp::CreatureProgressTimerIncrement::Growing,
                                std::chrono::hours(24 * 30 * 5));
        break;
        case data::CreatureLevel::END:
        break;
    }

    clearCreatureGeneWaitTime(ret,
                              +gamecomp::CreatureProgressTimerIncrement::Rest);


    return ret;
}


gamecomp::CreatureGeneWaitTime::waittime_t<gamecomp::StarvationPhase>
CreatureEntityCreator::createStarvationWaitTime(data::CreatureLevel creature_level) {
    gamecomp::CreatureGeneWaitTime::waittime_t<gamecomp::StarvationPhase> ret;

    switch(creature_level){
        case data::CreatureLevel::Egg:
        case data::CreatureLevel::Baby:
            setCreatureGeneWaitTime(ret,
                                +gamecomp::StarvationPhase::Phase1, 
                                std::chrono::hours(24 * 3));
            setCreatureGeneWaitTime(ret, 
                                +gamecomp::StarvationPhase::Phase2, 
                                std::chrono::hours(24 * 1));
            setCreatureGeneWaitTime(ret, 
                                +gamecomp::StarvationPhase::Phase3,
                                std::chrono::minutes(10));
            setCreatureGeneWaitTime(ret, 
                                +gamecomp::StarvationPhase::Phase4, 
                                std::chrono::hours(24 * 2));
            setCreatureGeneWaitTime(ret, 
                                +gamecomp::StarvationPhase::Phase5,
                                std::chrono::minutes(5));
            setCreatureGeneWaitTime(ret, 
                                +gamecomp::StarvationPhase::Phase6, 
                                std::chrono::hours(24 * 1));
        break;
        case data::CreatureLevel::Baby2:
            setCreatureGeneWaitTime(ret,
                                +gamecomp::StarvationPhase::Phase1, 
                                std::chrono::hours(24 * 5));
            setCreatureGeneWaitTime(ret, 
                                +gamecomp::StarvationPhase::Phase2,
                                std::chrono::hours(24 * 2));
            setCreatureGeneWaitTime(ret, 
                                +gamecomp::StarvationPhase::Phase3,
                                std::chrono::minutes(20));
            setCreatureGeneWaitTime(ret, 
                                +gamecomp::StarvationPhase::Phase4, 
                                std::chrono::hours(24 * 3));
            setCreatureGeneWaitTime(ret, 
                                +gamecomp::StarvationPhase::Phase5,
                                std::chrono::minutes(10));
            setCreatureGeneWaitTime(ret, 
                                +gamecomp::StarvationPhase::Phase6, 
                                std::chrono::hours(24 * 3));
        break;
        case data::CreatureLevel::Child:
            setCreatureGeneWaitTime(ret,
                                +gamecomp::StarvationPhase::Phase1, 
                                std::chrono::hours(24 * 6));
            setCreatureGeneWaitTime(ret, 
                                +gamecomp::StarvationPhase::Phase2, 
                                std::chrono::hours(24 * 3));
            setCreatureGeneWaitTime(ret, 
                                +gamecomp::StarvationPhase::Phase3,
                                std::chrono::hours(3));
            setCreatureGeneWaitTime(ret, 
                                +gamecomp::StarvationPhase::Phase4, 
                                std::chrono::hours(24 * 5));
            setCreatureGeneWaitTime(ret, 
                                +gamecomp::StarvationPhase::Phase5,
                                std::chrono::hours(2));
            setCreatureGeneWaitTime(ret, 
                                +gamecomp::StarvationPhase::Phase6, 
                                std::chrono::hours(24 * 3));
        break;
        case data::CreatureLevel::Adult:
        case data::CreatureLevel::Perfect:
        case data::CreatureLevel::Ultimate:
            setCreatureGeneWaitTime(ret,
                                +gamecomp::StarvationPhase::Phase1, 
                                std::chrono::hours(24 * 3));
            setCreatureGeneWaitTime(ret, 
                                +gamecomp::StarvationPhase::Phase2, 
                                std::chrono::hours(24 * 1));
            setCreatureGeneWaitTime(ret, 
                                +gamecomp::StarvationPhase::Phase3,
                                std::chrono::hours(8));
            setCreatureGeneWaitTime(ret, 
                                +gamecomp::StarvationPhase::Phase4, 
                                std::chrono::hours(24 * 7));
            setCreatureGeneWaitTime(ret, 
                                +gamecomp::StarvationPhase::Phase5,
                                std::chrono::hours(5));
            setCreatureGeneWaitTime(ret, 
                                +gamecomp::StarvationPhase::Phase6,
                                std::chrono::hours(24 * 4));
        break;
        case data::CreatureLevel::END:
        break;
    }

    return ret;
}

gamecomp::CreatureGeneWaitTime::waittime_t<gamecomp::CreatureActivity>
CreatureEntityCreator::createShortTermMemoryWaitTime(data::CreatureLevel creature_level) {
    gamecomp::CreatureGeneWaitTime::waittime_t<gamecomp::CreatureActivity> ret;

    switch(creature_level){
        case data::CreatureLevel::Egg:
        case data::CreatureLevel::Baby:
            for (auto activity : earr::Enum<gamecomp::CreatureActivity>()) {
                setCreatureGeneWaitTime(ret, activity, 
                    std::chrono::minutes(10));
            }
        break;
        case data::CreatureLevel::Baby2:
            for (auto activity : earr::Enum<gamecomp::CreatureActivity>()) {
                setCreatureGeneWaitTime(ret, activity, 
                    std::chrono::minutes(20));
            }
        break;
        case data::CreatureLevel::Child:
            for (auto activity : earr::Enum<gamecomp::CreatureActivity>()) {
                setCreatureGeneWaitTime(ret, activity, 
                    std::chrono::minutes(45));
            }
        break;
        case data::CreatureLevel::Adult:
        case data::CreatureLevel::Perfect:
        case data::CreatureLevel::Ultimate:
            for (auto activity : earr::Enum<gamecomp::CreatureActivity>()) {
                setCreatureGeneWaitTime(ret, activity, 
                    std::chrono::minutes(30));
            }
        break;
        case data::CreatureLevel::END:
        break;
    }
    

    return ret;
}

gamecomp::CreatureGeneWaitTime::waittime_t<gamecomp::CreatureActivity>
CreatureEntityCreator::createMediumTermMemoryWaitTime(data::CreatureLevel creature_level) {
    gamecomp::CreatureGeneWaitTime::waittime_t<gamecomp::CreatureActivity> ret;

    switch(creature_level){
        case data::CreatureLevel::Egg:
        case data::CreatureLevel::Baby:
            for (auto activity : earr::Enum<gamecomp::CreatureActivity>()) {
                setCreatureGeneWaitTime(ret, activity, 
                    std::chrono::hours(10));
            }
        break;
        case data::CreatureLevel::Baby2:
            for (auto activity : earr::Enum<gamecomp::CreatureActivity>()) {
                setCreatureGeneWaitTime(ret, activity, 
                    std::chrono::hours(20));
            }
        break;
        case data::CreatureLevel::Child:
            for (auto activity : earr::Enum<gamecomp::CreatureActivity>()) {
                setCreatureGeneWaitTime(ret, activity, 
                    std::chrono::hours(24 * 3));
            }
        break;
        case data::CreatureLevel::Adult:
        case data::CreatureLevel::Perfect:
        case data::CreatureLevel::Ultimate:
            for (auto activity : earr::Enum<gamecomp::CreatureActivity>()) {
                setCreatureGeneWaitTime(ret, activity, 
                    std::chrono::hours(24 * 2));
            }
        break;
        case data::CreatureLevel::END:
        break;
    }

    return ret;
}


gamecomp::CreatureGeneComponent CreatureEntityCreator::createCreatureGene(const data::Creature& creature) {
    gamecomp::CreatureGeneComponent ret;

    ret.gender = data::CreatureGender::None;
    ret.generationnr = 1;


    ret.max_bodysize = creature.getMaxBodySize();
    ret.min_weight = creature.getMinWeight();
    ret.max_weight = creature.getMaxWeight();
    
    double ideal_weight = ret.min_weight * 2.5;
    double ideal_bodysize = creature.getMinBodySize() * 1.43;
   
    double pseudomass_dif = -(ret.min_weight * (MIN_BMI / 2.0 / MAX_BMI));
    double pseudomass =
        (std::sqrt(ideal_bodysize * ideal_weight + ret.min_weight) - IDEAL_BMI) / pseudomass_dif;
    if (pseudomass < 0) {
        ret.min_bmi = HIGH_MIN_BMI;
        ret.ideal_bmi = HIGH_IDEAL_BMI;
        ret.max_bmi = HIGH_MAX_BMI;
    } else if (pseudomass > 50) {
        ret.min_bmi = LOW_MIN_BMI;
        ret.ideal_bmi = LOW_IDEAL_BMI;
        ret.max_bmi = LOW_MAX_BMI;
    } else {
        ret.min_bmi = MIN_BMI;
        ret.ideal_bmi = IDEAL_BMI;
        ret.max_bmi = MAX_BMI;
    }

    ret.bodymass = getBodyMass(creature, ret);


    ret.cangosleep_at_tired = CANGOSLEEP_AT_TIRED;
    ret.max_digestionheap = MAX_DIGESTIONHEAP;

    ret.totalmaxlifetime = min_totallifetime_;

    auto& perevolution_egg = earr::enum_array_at(ret.perevolution, +data::CreatureLevel::Egg);
    auto& perevolution_baby = earr::enum_array_at(ret.perevolution, +data::CreatureLevel::Baby);
    auto& perevolution_baby2 = earr::enum_array_at(ret.perevolution, +data::CreatureLevel::Baby2);
    auto& perevolution_child = earr::enum_array_at(ret.perevolution, +data::CreatureLevel::Child);
    auto& perevolution_adult = earr::enum_array_at(ret.perevolution, +data::CreatureLevel::Adult);
    auto& perevolution_perfect = earr::enum_array_at(ret.perevolution, +data::CreatureLevel::Perfect);
    auto& perevolution_ultimate = earr::enum_array_at(ret.perevolution, +data::CreatureLevel::Ultimate);

    perevolution_egg.needsleepinpercent = 90;
    perevolution_baby.needsleepinpercent = 95;
    perevolution_baby2.needsleepinpercent = 90;
    perevolution_child.needsleepinpercent = 80;
    perevolution_adult.needsleepinpercent = 70;
    perevolution_perfect.needsleepinpercent = 75;
    perevolution_ultimate.needsleepinpercent = 70;
    
    perevolution_egg.needrestinhospitalinpercent = 100;
    perevolution_baby.needrestinhospitalinpercent = 100;
    perevolution_baby2.needrestinhospitalinpercent = 100;
    perevolution_child.needrestinhospitalinpercent = 95;
    perevolution_adult.needrestinhospitalinpercent = 90;
    perevolution_perfect.needrestinhospitalinpercent = 80;
    perevolution_ultimate.needrestinhospitalinpercent = 85;

    perevolution_egg.training.max_hungryoverlay_intraining = 0.001;
    perevolution_baby.training.max_hungryoverlay_intraining = 0.001;
    perevolution_baby2.training.max_hungryoverlay_intraining = 5;
    perevolution_child.training.max_hungryoverlay_intraining = 20;
    perevolution_adult.training.max_hungryoverlay_intraining = 30;
    perevolution_perfect.training.max_hungryoverlay_intraining = 30;
    perevolution_ultimate.training.max_hungryoverlay_intraining = 20;

    perevolution_egg.training.max_thirstyoverlay_intraining = 0.001;
    perevolution_baby.training.max_thirstyoverlay_intraining = 0.001;
    perevolution_baby2.training.max_thirstyoverlay_intraining = 2;
    perevolution_child.training.max_thirstyoverlay_intraining = 5;
    perevolution_adult.training.max_thirstyoverlay_intraining = 10;
    perevolution_perfect.training.max_thirstyoverlay_intraining = 20;
    perevolution_ultimate.training.max_thirstyoverlay_intraining = 10;

    perevolution_egg.training.max_tiredoverlay_intraining = 0.001;
    perevolution_baby.training.max_tiredoverlay_intraining = 0.001;
    perevolution_baby2.training.max_tiredoverlay_intraining = 1;
    perevolution_child.training.max_tiredoverlay_intraining = 4;
    perevolution_adult.training.max_tiredoverlay_intraining = 10;
    perevolution_perfect.training.max_tiredoverlay_intraining = 15;
    perevolution_ultimate.training.max_tiredoverlay_intraining = 10;

    perevolution_egg.training.min_trainitime = std::chrono::minutes(30);
    perevolution_baby.training.min_trainitime = std::chrono::minutes(30);
    perevolution_baby2.training.min_trainitime = std::chrono::minutes(30);
    perevolution_child.training.min_trainitime = std::chrono::minutes(30);
    perevolution_adult.training.min_trainitime = std::chrono::hours(2);
    perevolution_perfect.training.min_trainitime = std::chrono::hours(3);
    perevolution_ultimate.training.min_trainitime = std::chrono::hours(4);

    perevolution_egg.training.middle_trainitime = std::chrono::minutes(30);
    perevolution_baby.training.middle_trainitime = std::chrono::minutes(30);
    perevolution_baby2.training.middle_trainitime = std::chrono::minutes(30);
    perevolution_child.training.middle_trainitime = std::chrono::minutes(40);
    perevolution_adult.training.middle_trainitime = std::chrono::hours(3);
    perevolution_perfect.training.middle_trainitime = std::chrono::hours(6);
    perevolution_ultimate.training.middle_trainitime = std::chrono::hours(5);

    perevolution_egg.training.good_trainitime = std::chrono::minutes(30);
    perevolution_baby.training.good_trainitime = std::chrono::minutes(30);
    perevolution_baby2.training.good_trainitime = std::chrono::minutes(30);
    perevolution_child.training.good_trainitime = std::chrono::hours(1);
    perevolution_adult.training.good_trainitime = std::chrono::hours(8);
    perevolution_perfect.training.good_trainitime = std::chrono::hours(8);
    perevolution_ultimate.training.good_trainitime = std::chrono::hours(7);

    perevolution_egg.runawaytime_unluck = std::chrono::minutes(20);
    perevolution_baby.runawaytime_unluck = std::chrono::minutes(30);
    perevolution_baby2.runawaytime_unluck = std::chrono::hours(1);
    perevolution_child.runawaytime_unluck = std::chrono::hours(6);
    perevolution_adult.runawaytime_unluck = std::chrono::hours(24);
    perevolution_perfect.runawaytime_unluck = std::chrono::hours(24);
    perevolution_ultimate.runawaytime_unluck = std::chrono::hours(22);




    perevolution_egg.waittime.timer = createTimerWaitTime(data::CreatureLevel::Egg);
    perevolution_baby.waittime.timer = createTimerWaitTime(data::CreatureLevel::Baby);
    perevolution_baby2.waittime.timer = createTimerWaitTime(data::CreatureLevel::Baby2);
    perevolution_child.waittime.timer = createTimerWaitTime(data::CreatureLevel::Child);
    perevolution_adult.waittime.timer = createTimerWaitTime(data::CreatureLevel::Adult);
    perevolution_perfect.waittime.timer = createTimerWaitTime(data::CreatureLevel::Perfect);
    perevolution_ultimate.waittime.timer = createTimerWaitTime(data::CreatureLevel::Ultimate);

    perevolution_egg.waittime.callback = createCallbackWaitTime(data::CreatureLevel::Egg);
    perevolution_baby.waittime.callback = createCallbackWaitTime(data::CreatureLevel::Baby);
    perevolution_baby2.waittime.callback = createCallbackWaitTime(data::CreatureLevel::Baby2);
    perevolution_child.waittime.callback = createCallbackWaitTime(data::CreatureLevel::Child);
    perevolution_adult.waittime.callback = createCallbackWaitTime(data::CreatureLevel::Adult);
    perevolution_perfect.waittime.callback = createCallbackWaitTime(data::CreatureLevel::Perfect);
    perevolution_ultimate.waittime.callback = createCallbackWaitTime(data::CreatureLevel::Ultimate);

    perevolution_egg.waittime.increment = createIncrementWaitTime(data::CreatureLevel::Egg);
    perevolution_baby.waittime.increment = createIncrementWaitTime(data::CreatureLevel::Baby);
    perevolution_baby2.waittime.increment = createIncrementWaitTime(data::CreatureLevel::Baby2);
    perevolution_child.waittime.increment = createIncrementWaitTime(data::CreatureLevel::Child);
    perevolution_adult.waittime.increment = createIncrementWaitTime(data::CreatureLevel::Adult);
    perevolution_perfect.waittime.increment = createIncrementWaitTime(data::CreatureLevel::Perfect);
    perevolution_ultimate.waittime.increment = createIncrementWaitTime(data::CreatureLevel::Ultimate);


    perevolution_egg.waittime.starvation = createStarvationWaitTime(data::CreatureLevel::Egg);
    perevolution_baby.waittime.starvation = createStarvationWaitTime(data::CreatureLevel::Baby);
    perevolution_baby2.waittime.starvation = createStarvationWaitTime(data::CreatureLevel::Baby2);
    perevolution_child.waittime.starvation = createStarvationWaitTime(data::CreatureLevel::Child);
    perevolution_adult.waittime.starvation = createStarvationWaitTime(data::CreatureLevel::Adult);
    perevolution_perfect.waittime.starvation = createStarvationWaitTime(data::CreatureLevel::Perfect);
    perevolution_ultimate.waittime.starvation = createStarvationWaitTime(data::CreatureLevel::Ultimate);

    perevolution_egg.waittime.shorttermmemory = createShortTermMemoryWaitTime(data::CreatureLevel::Egg);
    perevolution_baby.waittime.shorttermmemory = createShortTermMemoryWaitTime(data::CreatureLevel::Baby);
    perevolution_baby2.waittime.shorttermmemory = createShortTermMemoryWaitTime(data::CreatureLevel::Baby2);
    perevolution_child.waittime.shorttermmemory = createShortTermMemoryWaitTime(data::CreatureLevel::Child);
    perevolution_adult.waittime.shorttermmemory = createShortTermMemoryWaitTime(data::CreatureLevel::Adult);
    perevolution_perfect.waittime.shorttermmemory = createShortTermMemoryWaitTime(data::CreatureLevel::Perfect);
    perevolution_ultimate.waittime.shorttermmemory = createShortTermMemoryWaitTime(data::CreatureLevel::Ultimate);

    perevolution_egg.waittime.mediumtermmemory = createMediumTermMemoryWaitTime(data::CreatureLevel::Egg);
    perevolution_baby.waittime.mediumtermmemory = createMediumTermMemoryWaitTime(data::CreatureLevel::Baby);
    perevolution_baby2.waittime.mediumtermmemory = createMediumTermMemoryWaitTime(data::CreatureLevel::Baby2);
    perevolution_child.waittime.mediumtermmemory = createMediumTermMemoryWaitTime(data::CreatureLevel::Child);
    perevolution_adult.waittime.mediumtermmemory = createMediumTermMemoryWaitTime(data::CreatureLevel::Adult);
    perevolution_perfect.waittime.mediumtermmemory = createMediumTermMemoryWaitTime(data::CreatureLevel::Perfect);
    perevolution_ultimate.waittime.mediumtermmemory = createMediumTermMemoryWaitTime(data::CreatureLevel::Ultimate);

    return ret;
}

} // namespace gameentity
