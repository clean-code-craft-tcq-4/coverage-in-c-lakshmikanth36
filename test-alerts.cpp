#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"
#include "string.h"

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
  REQUIRE(inferBreach(31, 20, 30) == TOO_HIGH);
  REQUIRE(inferBreach(20, 20, 30) == NORMAL);
  REQUIRE(inferBreach(30, 20, 30) == NORMAL);
}

TEST_CASE("classify breach")
{
    REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, -1) == TOO_LOW);
    REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING,36) == TOO_HIGH);
    REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING,25) == NORMAL);
    REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 46) == TOO_HIGH);
    REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING,40) == NORMAL);
    REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 41) == TOO_HIGH);
    REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 0) == NORMAL);
    REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING,50) == TOO_HIGH);
}

TEST_CASE("Check and Alert of coolingType Temperature") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType = PASSIVE_COOLING;
  assert(checkAndAlert(TO_CONTROLLER,batteryChar,0));
  assert(checkAndAlert(TO_CONTROLLER,batteryChar,10));
  assert(checkAndAlert(TO_EMAIL,batteryChar,20));		
  assert(checkAndAlert(TO_EMAIL,batteryChar,35));		
  batteryChar.coolingType = MED_ACTIVE_COOLING;
  assert(checkAndAlert(TO_CONTROLLER,batteryChar,0));
  assert(checkAndAlert(TO_EMAIL,batteryChar,41));	
  batteryChar.coolingType = HI_ACTIVE_COOLING;
  assert(checkAndAlert(TO_CONTROLLER,batteryChar,40));
  assert(checkAndAlert(TO_EMAIL,batteryChar,46));
}
