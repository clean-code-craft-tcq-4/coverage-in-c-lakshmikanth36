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
  int status =-1;
  if(alertTarget == TO_CONTROLLER)
     {
      status = sendToController(breachType);
     }
   else 
     {
      status = sendToEmail(breachType);
     }
  return status;
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  if(breachType == TOO_LOW)
  {
      printf("To: Recepient : %s\n, Hi, the temperature is too low\n", recepient);
  }
  else if(breachType == TOO_HIGH)
  {
      printf("To: Receepient : %s\n, Hi, the temperature is too high\n", recepient);
  }
  else 
  {
    printf("To: Receepient : %s\n, Hi, the temperature is Normal\n", recepient);
  }
}
