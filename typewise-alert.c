#include "typewise-alert.h"
#include <stdio.h>

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
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

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
  int lowerLimit = 0;
  int upperLimit = 0;
  if(coolingType == PASSIVE_COOLING) 
  {
      lowerLimit = 0;
      upperLimit = 35;
  }
  else if(coolingType == HI_ACTIVE_COOLING)
  {
      lowerLimit = 0;
      upperLimit = 45;
  }
  else
   {
      lowerLimit = 0;
      upperLimit = 40;
  }
  return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

int checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {
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

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void printMessage(char *recepient,char *breachType)
{
    printf("To:%s \n, Hi, the temperature is %s \n ", message,breachType);
}

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  if(breachType == TOO_LOW)
  {
      printMessage(recepient,breachType);
  }
  else if(breachType == TOO_HIGH)
  {
      printMessage(recepient,breachType);
  }
}
