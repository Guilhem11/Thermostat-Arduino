  //bibliothèques
  #include <Wire.h>
  #include <rgb_lcd.h>


  //couleur du fond
  rgb_lcd lcd;
  const int colorR = 255;
  const int colorG = 255;
  const int colorB = 255;


  //Déclaration des variables du BUZZER
  float sinVal;
  int toneVal;


  //remise à zéro du temps
  int times = 0;


  //Déclaration des variables pour le temps
  long Jours = 0;
  long heures = 0;
  long minutes = 0;
  long secondes = 0;

  
  //Déclaration des variables des sondes TMP36
  int inter_PIN = 0;
  int ext_PIN = 1;
  int valeur_brute_inter;
  int valeur_brute_ext;
  int time;


  //température en celsius
  float temperature_celsius_inte;
  float temperature_celsius_ext;
  float diff_temp_c;
  float diff_temp_f;


  //température en fahrenheit
  float temperature_fahrenheit_inte;
  float temperature_fahrenheit_ext;

  
  //Déclaration des boutons pour les différents affichages
  int value_UP = 0;
  int value_DOWN = 0;
  int UP = 6;
  int DOWN = 7;
  int memoire_PLUS;
  int memoire_DOWN;
  byte equal;


  //Déclaration du relais pour le chauffage
  int chauffage = 4;

    
  //Déclaration du bouton pour le chauffage
  int chauff_ON = 0;
  int chau_OFF = 0;
  int OFF = 3;
  int ON = 3;
  int memoire_ON;
  int memoire_OFF;
  byte EQUAL;




void setup() {
 
  
  times = millis();
  
  memoire_DOWN = 1;
  memoire_PLUS = 1;
  memoire_ON = 1;
  memoire_OFF = 1;

  
  lcd.begin(16, 2);
  lcd.setRGB(colorR, colorG, colorB);


  //Déclaration des pins du BUZZER
  pinMode(8, OUTPUT);


  //Déclaration des pins du TMP36 intérieure
  pinMode(inter_PIN, INPUT);


  //Déclaration des pins du TMP36 extérieure
  pinMode(ext_PIN, INPUT);


  //initialisation de série de transmission et vitesse de transmission des données
  Serial.begin(1200);


  //Déclaration des pins pour les boutons up/down
  pinMode(UP, INPUT);
  pinMode(DOWN, INPUT);
  equal = 0;


  //Déclaration du pin du bouton on/off
  pinMode(ON, INPUT);
  pinMode(OFF, INPUT);
  EQUAL = 0;


  //déclaration du pin du relais
  pinMode(chauffage, OUTPUT);

}




void loop() {

  
    //code bouton UP
    value_UP = digitalRead(UP);
    if((value_UP != memoire_PLUS) && (value_UP == LOW))
    
    {
  
    equal = equal + 1;
    if (equal>=3) 
    {equal=3;}
   
    }

   
    // on enregistre l'état du bouton pour le tour suivant
    memoire_PLUS = value_UP;
  
    
    //code bouton DOWN
    value_UP = digitalRead(DOWN);
    if((value_UP != memoire_DOWN) && (value_UP == LOW))
    
    {
        
    equal = equal - 1;
    if (equal==0 or equal==255) 
    {equal=0;}
   
    }

   
  // on enregistre l'état du bouton pour le tour suivant
  memoire_DOWN = value_UP;

  
  Serial.println(equal);
  delay(100);
  
  //code pour le BUZZER
  if (temperature_celsius_inte >= 50)
  {
    digitalWrite(8, HIGH);
    delay(1000);
    digitalWrite(8, LOW);
    delay(1000);
    digitalWrite(8, HIGH);
    delay(1000);
    digitalWrite(8, LOW);
    delay(1000);
    digitalWrite(8, HIGH);
    delay(1000);
    digitalWrite(8, LOW);
    delay(1000);
    lcd.clear();
    lcd.print("temperature");
    lcd.setCursor(0, 1);
    lcd.print("superieure 50");
    lcd.print((char)223);
    lcd.print("C");
  }
  
  else {
    
    if (temperature_celsius_inte < temperature_celsius_ext)
    {
      //code pour le BUZZER
      digitalWrite(8, HIGH);
      delay(1000);
      digitalWrite(8, LOW);
      delay(1000);
      digitalWrite(8, HIGH);
      delay(1000);
      digitalWrite(8, LOW);
      delay(1000);
      digitalWrite(8, HIGH);
      delay(1000);
      digitalWrite(8, LOW);
      delay(1000);
      
      lcd.setCursor(0, 0);
      lcd.clear();
      lcd.print("Temperature");
      lcd.setCursor(0,1);
      lcd.print("int<ext!");
      lcd.print((char)223);
      lcd.print("C");
    }
   
    else {
      
      //code pour la sonde de température TMP36 intérieure
      if (equal == 0)
      
      {

        lcd.setCursor(0, 0);
        lcd.print("Temperature interieure :");
        valeur_brute_inter = analogRead(inter_PIN);
        temperature_celsius_inte = ((valeur_brute_inter * 0.004882) - 0.50) * 100;
        lcd.setCursor(0, 1);
        lcd.print(temperature_celsius_inte);

        lcd.setCursor(6, 1);
        lcd.print((char)223);
        lcd.print("C");

        temperature_fahrenheit_inte = (temperature_celsius_inte * 9 / 5) + 32 ;
        lcd.setCursor(9, 1);
        lcd.print(temperature_fahrenheit_inte);

        lcd.setCursor(14, 1);
        lcd.print((char)223);
        lcd.print("F");
        delay(100);

      }


      //code pour la sonde de température TMP36 extérieure
      if (equal == 1)
      
      {

        lcd.setCursor(0, 0);
        lcd.print("Temperature exterieure :");
        valeur_brute_ext = analogRead(ext_PIN);
        temperature_celsius_ext = ((valeur_brute_ext * 0.004882) - 0.50) * 100;
        lcd.setCursor(0, 1);
        lcd.print(temperature_celsius_ext);

        lcd.setCursor(6, 1);
        lcd.print((char)223);
        lcd.print("C");

        temperature_fahrenheit_ext = (temperature_celsius_ext * 9 / 5) + 32 ;
        lcd.setCursor(9, 1);
        lcd.print(temperature_fahrenheit_ext);

        lcd.setCursor(14, 1);
        lcd.print((char)223);
        lcd.print("F");
        delay(100);
      
      }



      //code pour la différence de température
      if (equal == 2)
      
      {

        lcd.setCursor(0, 0);
        lcd.clear();
        lcd.print("Diff de Temp:");
        diff_temp_c = temperature_celsius_inte - temperature_celsius_ext;
        lcd.setCursor(0, 1);
        lcd.print(diff_temp_c);
        lcd.setCursor(6, 1);
        lcd.print((char)223);
        lcd.print("C");

        diff_temp_f = (diff_temp_c * 9 / 5) + 32 ;
        lcd.setCursor(9, 1);
        lcd.print(diff_temp_f);

        lcd.setCursor(14, 1);
        lcd.print((char)223);
        lcd.print("F");
        delay(100);
      
      }


      //code pour le temps
      if (equal == 3)
      
      {
      
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Temps :");

       
        secondes = millis()/1000; //convertie millisecondes en secondes
        minutes=secondes/60; //convertie secondes en minutes
        heures=minutes/60; //convertie minutes en heures
        Jours=heures/24; //convertie heures en Jours

        secondes=secondes-(minutes*60); // soustraire les secondes converties afin d'afficher 59 secondes 
        minutes=minutes-(heures*60);    //soustraire les minutes converties afin d'afficher 59 minutes 
        heures=heures-(Jours*24);       //soustraire les heures converties afin d'afficher 59 heures 
       
        if (Jours>0) // Les jours ne seront affichés que si la valeur est supérieure à zéro
        {
        lcd.print(Jours);
        lcd.print(" Jours:");
        }

        lcd.setCursor(0, 1);
        lcd.print(heures);
        lcd.print(":");
        lcd.print(minutes);
        lcd.print(":");
        lcd.println(secondes);
        delay(1000);
}
      }

  }

    //code bouton ON
    chauff_ON = digitalRead(ON);
    if((chauff_ON != memoire_ON) && (chauff_ON == LOW))
    
    {
  
    EQUAL = EQUAL + 1;
    if (EQUAL>=1) 
    {EQUAL=1;}
   
    }

   
    // on enregistre l'état du bouton pour le tour suivant
    memoire_ON = chauff_ON;


    //code bouton OFF
    chauff_ON = digitalRead(OFF);
    if((chauff_ON != memoire_OFF) && (chauff_ON == LOW));  
    
    {
        
    EQUAL = EQUAL - 1;
    if (EQUAL==0 or EQUAL==255) 
    {EQUAL=0;}
   
    }
  
    // on enregistre l'état du bouton pour le tour suivant
    memoire_OFF = chauff_ON;



    //code pour le chauffage
    if (EQUAL == 0)

    {
      digitalWrite(chauffage, LOW);
      
    }

    if (EQUAL == 1)

    {
      digitalWrite(chauffage, HIGH);
    }
 
  
  }







