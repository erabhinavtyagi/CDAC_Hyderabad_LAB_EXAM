/*              
 *********************************CDAC HACKATHON AUG 2022*************************************
                          
                          TOPIC:    Smart Weather Forecasting Station
                          DURATION: Aug23, 2022 to Aug25, 2022
                           
Designed & Programmed by:  
    Abhinav Tyagi (220350330001)                    - Wind Speed & LCD Display
    Ajit Kumar Das (220350330002)                   - temperature & Humidity
    Arun V (220350330003)                           - Cloud Detection
    Bhendarkar Bhupendra Asaram(220350330004)       - Wind Speed & LCD Display
**********************************************************************************************
*/

// ****************************************************************************
// IMPORT - Required Libraries (Download these if not installed in your system)
// ****************************************************************************
    #include "WiFi.h"
   // #include <PubSubClient.h>
    #include "ThingSpeak.h"
    #include <DHT.h>
    #include <Wire.h>
    #include "rgb_lcd.h"
    

// ****************************************************************************
//  DEFINES - ESP32 pin connections
// ****************************************************************************
    #define uS_TO_S_FACTOR 1000000ULL       /* Conversion factor for micro seconds to seconds */
    #define TIME_TO_SLEEP  20               /* Time ESP32 will go to sleep (in seconds) */

    RTC_DATA_ATTR int bootCount = 0;

    #define DHTPIN 13
    #define LDR 4
    #define inputCLK 22                   // Serial Clock SCL-pin    
    #define inputDT 21                    // Serial Data SDA-pin
    DHT dht(DHTPIN, DHT11);
    
    rgb_lcd lcd;
    
// ****************************************************************************
//  GLOBAL VARIABLES
// ****************************************************************************
    int humidity = 0;
    int temperature = 0;
    float windspeed = 0;
    int sunlight = 0;

    //********LCD Backlight RGB code***************  
    const int colorR = 255;
    const int colorG = 0;
    const int colorB = 255;

    //******** Rotary Encoder *********************
    int pState = 0;
    int lastState = 0;  
    int steps = 0;


// ****************************************************************************
// WIFI - DETAILS & SETUP
// ****************************************************************************
    WiFiClient client; 
    
    char ssid[] = "DASAHIS"; //SSID
    char pass[] = "abhinav1="; //Password

//    char ssid[] = "ajit"; //SSID
//    char pass[] = "aj.ab.tyagi"; //Password

// ****************************************************************************
// THINGSPEAK DETAILS
// ****************************************************************************
    unsigned long myChannelField = 1842444;           // ThingSpeak Channel ID
    const char *myWriteAPIKey = "VO7GQNGQ2E5WBGIR";   // Your write API Key
    

// ****************************************************************************
// MAIN SETUP() - Initialization Function (runs only one time)
// ****************************************************************************

    void setup()
    {
        Serial.begin(115200);                 /*Initialize serial communication channel with the PC*/
       
        esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);     /* Initialise deep sleep mode parameters */
        
        dht.begin();                          /*Start DHT Sensor functionality*/
        pinMode(DHT11,INPUT);                 /*Set the temperatureerature & Humidity as input*/
        pinMode(LDR,INPUT);                   /* Setup the LDR Pins*/
   
        // Set encoder pins as inputs  
        pinMode (inputCLK,INPUT);
        pinMode (inputDT,INPUT);
        // Read the initial state of inputCLK
        // Assign to previousStateCLK variable
        lastState = digitalRead(inputCLK);   
        
        lcd.begin(16, 2);                     /* set up the LCD's number of columns and rows */
        lcd.setRGB(colorR, colorG, colorB);   /* Set LCD Backlight */
        
        //-------- Calling Functionalities----------
        dhtSensor();		
        ldrSensor();
        rotarySensor();
        displaySensor();

        //To check on Serial Monitor (not required in final code.)
        //--------------------------------------------------------
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.print("degree celsius, Humidity:");
        Serial.print(humidity);
        Serial.println();
        Serial.print("Wind Speed: ");
        Serial.print(windspeed);
        Serial.println();
        //--------------------------------------------------------

        //-------Connect to WiFi network----------------
        WiFi.begin(ssid, pass);                                            
        int timeout = 0;
        while (WiFi.status() != WL_CONNECTED  && timeout < 20)
        {
          delay(500);
          Serial.print(".");
          timeout++;
        }
        if(WiFi.status() == WL_CONNECTED)
        {
          Serial.println("");
          Serial.println("WiFi connected");
          ThingSpeak.begin(client);                                        //Initialise ThingSpeak
          updateThingSpeak();                                             //Post the data to Thingspeak
        }
        else
        {
          Serial.println("");
          Serial.println("WiFi connection failed");
        }
      
        Serial.println("Going to sleep now");
        Serial.flush();
    
        esp_light_sleep_start(); 

    }
  

// ****************************************************************************
// USER- DEFINED FUNCTIONS
// ****************************************************************************

/************* Function to check temperature & Humidity **********************/
   void dhtSensor()
   {
      temperature = dht.readTemperature();
      humidity = dht.readHumidity();
      
      if(isnan(humidity) || isnan(temperature))
      {
        Serial.println("Failed to read from DHT sensor");
      }
      
   }


/************* Function to check Wind Speed *************************************/   
    void rotarySensor()
    {
      int timer;
      float radius = 0.1;
      Wire.requestFrom(0x62, 1);                // I2C device found at address 0x62
     
      if(Wire.available())
      {
        Serial.println(" Encoder Found at 0x62. ");
      
         pState = digitalRead(inputCLK);      // Reads the "current" state of the inputCLK i.e SCL pin.
        // If the previous and the current state of the inputDT are different, that means a Pulse has occured
        if (pState != lastState)
        {     
         // If the inputCLK state is different to the inputDT state, that means the encoder is rotating.
         if (digitalRead(inputDT) != pState)
         { 
          for (timer =0; timer <=20; timer++) 
          steps++;
         } 
        }
       lastState = pState; // Updates the previous state of the last state with the current state
      }
      
      else
      {
        Serial.print(" Encoder not found on given address. ");
      }
      
      //windspeed = 2 * 3.14 * 0.1 * 3 * steps;
     windspeed = 1.884 * radius * steps;          // (circumference of anemometer * rpm), where let Radius = 0.1 metres
     Serial.print(" Steps of Encoder: ");
     Serial.println(steps);
       
  }



/************* Function to check Sunlight *************************************/   
   int ldrSensor()
   {
      int ld = analogRead(LDR);
      
      if(ld < 500)                                // Value Less than Threshold
      {
        sunlight = 0;
        Serial.println("Its Dark Outside");         
      }
      else
      {
        sunlight = 1;
        Serial.println("Its a Shinny Day");
      }
      delay(1000);
      
    return sunlight;
   }


    
/************* Function to Display Output to LCD at Local Weather Station *******/   
    void displaySensor()
    {
        Wire.beginTransmission(0x3E);      // I2C device found at address 0x3E
                      
        lcd.print("T:");                  /* Display Temperature */
        lcd.print(temperature);           /* Display Temperature */
        lcd.print(" H:");                 /* Display Humidity */
        lcd.print(humidity);              /* Display Humidity */
        lcd.print(" W:");                 /* Display Windspeed */
        lcd.print(windspeed);             /* Display Windspeed */
        delay(100);     
        lcd.setCursor(0, 1);              /* set the cursor to column 0, line 1 (**NOTE: line 1 is the second row, since counting begins with 0)*/
        
        if((windspeed < 20) && (temperature > 25) && (humidity > 50))
        {
        lcd.print("It's Hot Today");  
        }
        else
        if((windspeed > 20) && (temperature < 25) && (humidity < 50))
        {
        lcd.print("It's Cold Today");  
        }
        else
        lcd.print("It's Rain Today");  
        
        delay(100);
        Wire.endTransmission();
    }


// ****************************************************************************
// MAIN- LOOP FUNCTION
// ****************************************************************************
    
    void loop()
    {
        //EMPTY   
    }


// ****************************************************************************
// Function to post data to Thingspeak
// ****************************************************************************

    void updateThingSpeak ()                                             
    {
      ThingSpeak.setField(1, temperature);
      ThingSpeak.setField(2, humidity);
      ThingSpeak.setField(3, windspeed);
      ThingSpeak.setField(4, sunlight);
      
      int x = ThingSpeak.writeFields(myChannelField, myWriteAPIKey);
      if(x == 200)
      {
        Serial.println("Channel update successful.");
      }
      else
      {
        Serial.println("Problem updating channel. HTTP error code " + String(x));
      }
    }



//*****************************END OF CODE ********************************
