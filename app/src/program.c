/*============================================================================
 * License: 
 * Author: 
 * Date: 
 *===========================================================================*/

/*==================[inclusions]=============================================*/

#include "program.h"   // <= Own header
#include "sapi.h"      // <= sAPI library
#include "gsm.h"
#include "sim900.h"
#include "string.h"
/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/
void console(char* msg)
{
 uartWriteString(UART_USB, msg);
 uartWriteByte( UART_USB, '\r' );
  uartWriteByte( UART_USB, '\n' );
}
void printLine(char* msg)
{
 uartWriteString(UART_USB, msg);
 
}
void leerBuffer()
{
    char buffer[STR_MAX];
    cleanBuffer(buffer,STR_MAX);
    extern char response[STR_MAX];
    cleanBuffer(response,STR_MAX);
 
    readBuffer(UART_232, response,STR_MAX, TIMEOUT_MAX);
    
    printLine("Response  :");
    console(response);
    delay(100);

   
}

void sendAT(char* AT, int t)
{
    printLine("COMAND AT :");
  console(AT);
 uartWriteString(UART_232,AT);

  uartWriteByte( UART_232, '\r' );
  
  delay(t);
  //mostrar respuesta
  leerBuffer();
}

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/
  char response[STR_MAX];
/*==================[main function]==========================================*/

// MAIN FUNCTION, ENTRY PINT TO THE PROGRAM AFTER POR OR RESET.
int main( void ){

   // ---------- SETUP ----------------------------------------


    // Initialize an configurate the board
    boardConfig();   
    uartConfig( UART_232, 9600 );//para comandos at
    uartConfig( UART_USB, 9600 );//para conexion con la PC
    extern char response[];
    console("INICIANDO PROGRAMA");
    sendAT("ADVERTISING ON",50);
    int conect = 0;


  while( TRUE )
   { 
    
 // // ---------- REPEAT FOR EVER ------------------------------
    

    leerBuffer();
    
       if(strstr(response,"OK") != NULL){   gpioWrite(LEDG,true);      }
       if(strstr(response,"OPEN_OK") != NULL){   conect = 1;      }
         if(strstr(response,"ERROR") != NULL){   conect = 0;gpioWrite(LEDR,true);gpioWrite(LEDG,false);      }
       
       if(conect == 1) {
           gpioToggle(LEDG);
           if(strstr(response,"amarillo")!= NULL)
           {
               gpioToggle(LED2);
            }
            if(strstr(response,"rojo")!= NULL)
           {
           gpioToggle(LED1);
            }
            if(strstr(response,"verde")!= NULL)
           {
               gpioToggle(LED3);
            }
            if(strstr(response,"azul")!= NULL)
           {
               gpioToggle(LEDB);
            }
           
           }
       
       
            
        
        
    //cleanBuffer(response,STR_MAX);
        
        

   } 
   // IT SHOULD NEVER COME HERE, because this program runs directly on a
   // microcontroller and is not called by any Operating System, as in
   // case of a PC program.
   return 0;
}

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/*==================[end of file]============================================*/
