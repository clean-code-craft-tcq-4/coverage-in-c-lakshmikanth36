#include "typewise-alert.h"
#include <stdio.h>

BreachType inferBreach(double value, double lowerLimit, double upperLimit) 
{
  if(value < lowerLimit) 
  {
      return TOO_LOW;
  }
  else if(value > upperLimit) 
  {
      return TOO_HIGH;
  }
  else 
  {
      return NORMAL;
  }
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) 
{
  int lowerLimit = PASSIVE_COOLING_LOWER_LIMIT;
  int upperLimit = DEFAULT_COOLING_UPPER_LIMIT;
  if(coolingType == PASSIVE_COOLING) 
  {
      upperLimit = PASSIVE_COOLING_UPPER_LIMIT;
  }
  else if(coolingType == HI_ACTIVE_COOLING)
  {
      upperLimit = HI_ACTIVE_COOLING_UPPER_LIMIT;
  }
  else
   {
      upperLimit = MED_ACTIVE_COOLING_UPPER_LIMIT;
  }
  return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

int checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) 
{
  BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);
  if(alertTarget == TO_CONTROLLER)
     {
      sendToController(breachType);
     }
   else 
     {
      sendToEmail(breachType);
     }
  return 1;
}

int sendToController(BreachType breachType) 
{
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
  return 0;
}

void printMessage(const char *recepient,const char *message, const char *alertType )
{
    printf("To:%s\n %s %s", recepient,message,alertType);
}

int sendToEmail(BreachType breachType) 
{
  const char* recepient = "a.b@c.com";
  const char* message = "Hi, the temperature is ";
  const char* alertType = "NORMAL";
  if(breachType == TOO_LOW)
  {
    alertType = "TOO_LOW";
  }
  else if(breachType == TOO_HIGH)
  {
    alertType = "TOO_HIGH";
  }
  printMessage(recepient,message,alertType);
  return 0;
}
