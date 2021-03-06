//Library for the watchdog
#include <avr/wdt.h>


//Library for the Lwm
#include "lwm.h"
#include "atmegarfr2.h"
#include "hal.h"
#include "halTimer.h"
#include "nwk.h"
#include "nwkCommand.h"
#include "nwkDataReq.h"
#include "nwkFrame.h"
#include "nwkGroup.h"
#include "nwkRoute.h"
#include "nwkRouteDiscovery.h"
#include "nwkRx.h"
#include "nwkSecurity.h"
#include "nwkTx.h"
#include "phy.h"
#include "sys.h"
#include "sysConfig.h"
#include "sysEncrypt.h"
#include "sysTimer.h"
#include "sysTypes.h"

//Library for the Xbee
#include "XBee.h"


#include "coordinatore.h"
int contatore=0;

void setup() {
  wdt_disable();
 /*--------------------------------------------------------------------*/ 
 ApioCoordinatorSetup(); //inizializzazione coordinatore
  
 /*--------------------------------------------------------------------*/  
  wdt_enable(WDTO_8S);
}

// the loop routine runs over and over again forever:
void loop() {
  SYS_TaskHandler(); //task management LWM
  if(Serial1.available()>0)
  {
      comunication_protocol = ReadFromWebServer();
              
        switch(comunication_protocol)
        {
          case('z'):
            //Serial11.println("case z"); //debug
            XBeeOutput_62(deviceAddr, content);
            //Serial1.println(contatore++);  
          break;
        
          case('l'):
            //Serial11.println("case l"); //debug
            LwmOutput_109(deviceAddr,content);
            //Serial1.println(contatore++);  
            
          break;
        }
        
    content="";
    deviceAddr="";
    comunication_protocol=NULL;
    contatore++;
   } 
   if(contatore>1000)
   {
     wdt_enable(WDTO_30MS);
     while(true)
     {
     }
   }
     
 /*--------------------------------------------------------------------*/ 
  wdt_reset(); //watchdog reset
  
}
