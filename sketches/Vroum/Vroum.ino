/* This is a simple car game written for a 16x2 LCD screen connected to a Arduino Uno.
It was written by Pierre Massat:
http://guitarextended.wordpress.com/

It uses pins 12, 11, 6, 5 and 4 to connect the LCD. 
It uses the LiquidCrystal library for Arduino :
http://arduino.cc/en/Reference/LiquidCrystal

Note that this codes was written for an ad-hoc pad of 10 buttons connected to the board. 
Only two simple push buttons are required to control the game. I don't change the code due to
lack of time, but you'll simply have to remove the "detect()" function, and adapt the code in
the "initial()" function and at the beginning of the main loop (using a simple digitalRead()).

Please refer to this page if you have trouble wiring your buttons :
http://www.arduino.cc/en/Tutorial/Pushbutton

The only magic there is to this game lies in the use of the extra memory for custom characters 
available in the LCD screen (a maximum of 8 characters can be created) :
http://arduino.cc/en/Reference/LiquidCrystalCreateChar

Have fun!
----------------------------------------------------------------------------------------------
Voici un jeu de voiture très simple écrit pour un écran LCD 16x2 connecté à un Arduino Uno.
Il a ét écrit par Pierre Massat:
http://guitarextended.wordpress.com/

Il utilise les entrées 12, 11, 6, 5 et 4 pour connecter le LCD.
Il utilise également la bibliothèque LiquidCrystal pour Arduino:
http://arduino.cc/en/Reference/LiquidCrystal

Veuillez noter que ce code a été écrit pour un pad ad-hoc de 10 boutons poussoirs connecté à l'Arduino.
Seuls 2 boutons poussoirs simples sont nécessaires pour contrôler le jeu. Je n'ai pas changé le code par 
manque de temps, mais vous pourrez simplement supprimer la fonction "detect()", et adapter le code dans 
la fonction "initial()" et au début de la boucle principale (en utilisant un simple digitalRead()).

Référez-vous à la page suivante si vous avez du mal à connecter vos boutons:
http://www.arduino.cc/en/Tutorial/Pushbutton

La seule magie tient à l'utilisation de la mémoire disponible pour des caractères sur mesure dans
l'écran LCD (un maximum de 8 caractères peuvent être créés):
http://arduino.cc/en/Reference/LiquidCrystalCreateChar

Amusez-vous bien!*/

//Setup the Arduino LCD Keypad Shield
#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
#define btnRight     0
#define btnUp        1
#define btnDown      2
#define btnLeft      3
#define btnSelect    4
#define btnNone      5


int pos=0;
// We define all the graphical obects here as arrays of bytes. 
// We use the memory for custom characters featured in the LCD screen.
//------------------------------------------------------------------------
// On définit les objects graphiques ici sous forme de tableaux d'octets.
// On utilise la mémoire interne à l'écrant LCD dédiée aux caractères créés par l'utilisateur.
byte backslash[8] ={ // Définition du caractère backslash
  B00000,
  B10000,
  B01000,
  B00100,
  B00010,
  B00001,
  B00000,
};
// Car (straight up)
//-------------
// Voiture (droite)
byte voiture[8] = { 
  B00000,
  B00000,
  B01010,
  B00100,
  B00100,
  B01110,
  B00000,
};
// Car (truning to the left)
//---------------
// Voiture (tournant vers la gauche)
byte voitureG[8] = {
  B00000,
  B01000,
  B11000,
  B00101,
  B00010,
  B00100,
  B00000,
};
// Car (truning to the right)
//---------------
// Voiture (tournant vers la droite)
byte voitureD[8] = {
  B00000,
  B00010,
  B00011,
  B10100,
  B01000,
  B00100,
  B00000,
};
// Cow...
//---------
// Vache...
byte vache[8] = {
  B00000,
  B00000,
  B11000,
  B01111,
  B01010,
  B00000,
  B00000,
};
// Tree...
//---------
// Arbre...
byte arbre[8] = {
  B01110,
  B11111,
  B11111,
  B01110,
  B00100,
  B00100,
  B00100,
};
// Pine tree
//----------
// Sapin
byte sapin[8] = {
  B00000,
  B00000,
  B00100,
  B01110,
  B01110,
  B11111,
  B00100,
};
// House
//---------
// Maison
byte maison[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B01110,
  B11111,
  B11011,
};
// Various variables used later on...
//-----------------------------------
// Diverses variables utilisées plus bas...
char haut[16] = "               ";
int posRoute;
int oldposRoute=5;
int actuDir=1;
int bouton;
unsigned long getTime;
unsigned long getTimeVoiture;
int collision=0;
unsigned long initTime;
int largRoute; // Largeur de la route
int limitDroite; // Limite à gauche de la route pour ne pas dépasser à droite.
int moveVoiture=1;
int posVoiture;
int posConc1;
int obsConc;
int compteurConc;


void setup() {
  int i;
  lcd.begin(16,2); // Initialize the LCD / Initialisation de l'écran LCD
  lcd.createChar(1,backslash); // Loading of custom characters into LCD memory / Chargement des caractères sur mesure dans la memoire du LCD
  lcd.createChar(2,voiture); 
  lcd.createChar(3,voitureG); 
  lcd.createChar(4,voitureD); 
  lcd.createChar(5,vache);
  lcd.createChar(6,arbre);
  lcd.createChar(7,sapin);
  lcd.createChar(8,maison);
  largRoute = 8; // Road width. / Largeur de la route.
  limitDroite = 6;
  initial();
  randomSeed(analogRead(A2));
}

void initial() {
  // Splash screen before the game starts.
  //----------------------------------------
  // Ecran d'accueil avant le début du jeu.
  long i=0;
  int k=btnNone;
  getTime=millis();
  // Loop until the player pushes a button
  //---------------------------------------
  // Tourne en boucle jusqu'à ce que le joueur appuie sur un bouton.
  while (k==btnNone) { 
    k=detect();
    i=i+1;
    if ((millis()-getTime)>1000) {
      if (i%2==0) {
        lcd.clear();
        lcd.setCursor(5,0);
        lcd.print("Vroum!");
        for (i=0;i<8;i++) {
          lcd.setCursor(i*2,1);
          lcd.write(4-(i%3));
        }
      }
      else {
        lcd.clear();  
        lcd.print("Press a key ... ");
      } 
      getTime=millis();
    }
  }
  // Initialize various variables when the player has pushed a button to start the game.
  //-----------------------------------------------------------------------------------
  // Initialise divers variables lorsque le joueur a appuyé sur un bouton pour commencer le jeu.
  for (i=0;i<16;i++) {
    haut[i]=' ';
  }
  getTime = millis();
  getTimeVoiture = getTime;
  initTime = getTime;
  posRoute=5;
  posVoiture = posRoute+3;
  posConc1=0;
  obsConc=0;
  compteurConc=7;
}

//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// This is the main loop. It controls the input from the buttons, 
// the animation of the road and the car, and the score if the car
// crashes out of the road.
//------------------------------------------------------------------
// C'est la boucle principale. Elle contrôle les boutons, 
// l'animation de la route et de la voiture, ainsi que le score si
// la voiture sort de la route.
void loop() {
  int i=0;
  int tmp;
  
  // Uses the "detect()" function to read the state of the buttons.
  // (This was made for an ad-hoc pad of 10 buttons. Only two simple
  // push buttons are required, but this code needs to be altered slightly).
  //-----------------------------------------------------------------------
  // Utilise la fonction "detect()" pour lire l'état des boutons.
  // (Cela a été créé pour un pad ad-hoc e 10 boutons. Seuls 2 boutons poussoirs
  // sont nécessaires en réalité, mais cette partie de code doit être modifiée légèrement).
  bouton = detect();
  if (bouton==btnLeft) tmp=0; // On bouge à gauche...
  else if (bouton==btnRight) tmp=2; // ...ou à droite...
  else tmp=1; // Ou on reste tout droit.
  moveVoiture=tmp;
  
  // The "Voit_animation()" function runs every 500 ms (car and road animation).
  // To increase the speed, replace 500 by a lower value.
  //---------------------------------------------------
  // La fonction "Voit_animation()" est lancée toutes les 500 ms (animation de la voiture et de la route).
  // Pour une plus grande vitesse, remplcer 500 par une valeur plus faible.
  if ((millis()-getTime)>500) { 
    Voit_animation();
    getTime=millis();
  }
  
  if (collision!=1) {
    if ((millis()-getTimeVoiture)>125) {
      Voit_animationVoiture();
      getTimeVoiture=millis();
    }
  }
  else Voit_score();
  
}
// Enof main loop / Fin de la boucle principale
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\_

// This function is here to convert the analog values read from the ad-hoc
// pad of 10 buttons into integers between 0 and 9. For the purpose of this game
// it can be completely replaced with 2 simple push buttons and 2 simple digitalRead().
// The code in the main loop must be changed accordingly.
//------------------------------------------------------------------------
// Cette fonction sert à convertir les valeurs analogiques lues depuis le pad ad-hoc de 10 boutons 
// en entiers entre 0 et 9. Pour ce jeu cela peut être entièrement remplacé par
// 2 boutons poussoirs et deux simples digitalRead().
// Le code dans la boucle principale doit être changé en conséquence.
/*int detect(int bouton1,int moitie) {
  int k;
  if (moitie==0) k=0;
  else if (moitie==1) k=1;
  if (bouton1>1000) return 1+k*5;
  else if (bouton1<530 && bouton1>500) return 2+k*5;
  else if (bouton1<370 && bouton1>310) return 3+k*5;
  else if (bouton1<290 && bouton1>240) return 4+k*5;
  else if (bouton1<230 && bouton1>180) {
    if (k==1) return 0;
    else return 5;
  }
  else return 10;
}*/
/* New detect() function reading the buttons
 * from the Arduino LCD Keypad shield.
 */
int detect() {
  int b = analogRead(A0);
  if (b > 1000) return btnNone;
  delay(8);
  if (b < 50) return btnRight;
  if (b < 180) return btnUp;
  if (b < 330) return btnDown;
  if (b < 520) return btnLeft;
  if (b < 700) return btnSelect;
}

// This function prints some kind of a "game over" splash screen. 
// It displays the time the player managed to drive the car without
// bumping into another one or crashing out of the road. After a few seconds it
// calls the "initial()" function to display the firt splash screen again.
//----------------------------------------------------------------------------
// Cette fontion affiche une sorte de "game over". Elle affiche le temps pendant lequel le joueur est
// parvenu à conduire sa voiture sans rentrer dans une autre ni sortir de la route.
// Après quelques secondes la fonction "initial()" est appelée pour afficher de nouveau le
// premier écran d'accueil.
void Voit_score() {
  int temps;
  
  temps = (millis() - initTime)/1000;
  String chaine = "";
  chaine = chaine + temps + " sec";
  delay(800);
  lcd.clear();
  lcd.print("Game Over");
  lcd.setCursor(0,1);
  lcd.print(chaine);
  /*chaine = ",";
  chaine = chaine;
  lcd.setCursor(6,1);
  lcd.print(chaine);*/
  
  delay(3000);
  collision=0;
  initial();
}

//=======================================================================================================================
// Actual animation (including random generation of obstacles and scenery).
//----------------------------------------------------------------
// Animation à proprement parler (dont génération aléatoire des obstacles et du décor).
void Voit_animation() {
  int i;
  int increment=0;
  int rand;
  int typeConc;
  int oldDir;
  int posDec1=1000;
  int posDec2=1000;
  int posDec3=1000;
  int posDec4=1000;
  int typeDec1;
  int typeDec2;
  int typeDec3;
  int typeDec4;
  
  
  oldDir = actuDir;
  oldposRoute = posRoute;
  
  // Generation of random scenery
  //-----------------------------------
  // Génération aléatoire du décor
  if (random(0,100)>60) { // Décor 1
    typeDec1=random(0,4);
    if (random(0,2)>0) {
      posDec1=posRoute-random(2,5);
    }
    else posDec1=posRoute+largRoute+random(0,4)+2;
  }
  else posDec1=1000;
  if (random(0,100)>50) { // Décor 2
    typeDec2=random(0,4);
    if (random(0,2)>0) {
      posDec2=posRoute-random(2,5);
    }
    else posDec2=posRoute+largRoute+random(0,4)+2;
  }
  else posDec2=1000;
  if (random(0,100)>50) { // Décor 3
    typeDec3=random(0,4);
    if (random(0,2)>0) {
      posDec3=posRoute-random(2,5);
    }
    else posDec3=posRoute+largRoute+random(0,4)+2;
  }
  else posDec3=1000;  
  if (random(0,100)>80) { // Décor 4
    typeDec4=random(0,4);
    if (random(0,2)>0) {
      posDec4=posRoute-random(2,5);
    }
    else posDec4=posRoute+largRoute+random(0,4)+2;
  }
  else posDec4=1000;
  // Random generation of new road direction (depending on constraints)
  //-----------------------------------------
  // Génération aléatoire de la direction de la route (en fonction des contraintes)
  if (posRoute==0) rand = random(1,3); // only staight or to the right / seulement devant ou à droite
  else if (posRoute==limitDroite) rand = random(0,2); // Only straight or to the left / seulement devant ou à gauche
  else rand = random(0,3); // no constraints / pas de contraintes
  
  // Moves the road sideways when necessary
  //--------------------------------
  // Décale la route wuand c'est nécessaire
  if (oldDir==0) {
    if (rand!=2 && posRoute!=0) posRoute = posRoute-1;
  }
  else if (oldDir==2) {
    if (rand!=0 && posRoute!=limitDroite) posRoute = posRoute+1;
  }
  actuDir = rand;
  
  // Copy top line to bottom line.
  //----------------------------
  // Copie la ligne du haut en bas.
  lcd.clear();
  lcd.setCursor(0,1);
  for (i=0;i<16;i++) { 
    lcd.setCursor(i,1);
    if (haut[i]=='*') lcd.write(1);
    else if (haut[i]=='V') lcd.write(5);
    else if (haut[i]=='A') lcd.write(6);
    else if (haut[i]=='S') lcd.write(7);
    else if (haut[i]=='M') lcd.write(8);
    else lcd.write(haut[i]);
  }
  
  // Create and print the top line based on the direction and the position of the road.
  //-------------------------------------------------------------------------------
  // Ecriture de la ligne du haut, générée en fonction de la direction et de la position de la route.
  for (i=0;i<16;i++) { // (we write the top line) / (On écrit en haut)
    lcd.setCursor(i,0);
    if (i==posRoute || i==posRoute+largRoute) { // If left or right border of the road / Si limite gauche ou droite de la route.
      if (actuDir==0) {
        lcd.write(1); // We use a custom character for the backlash when turning left / On met un '\' si tourne à gauche 
        haut[i]='*';
      }
      else if (actuDir==1) {
        lcd.write('|');
        haut[i]='|';
      }
      else if (actuDir==2) {
        lcd.write('/');
        haut[i]='/';
      }
    }
    else if (i==posDec1) {
      lcd.write(typeDec1+5);
      if (typeDec1==0) haut[i]='V';
      else if (typeDec1==1) haut[i]='A';
      else if (typeDec1==2) haut[i]='S';
      else if (typeDec1==3) haut[i]='M';
    }
    else if (i==posDec2) {
      lcd.write(typeDec2+5);
      if (typeDec2==0) haut[i]='V';
      else if (typeDec2==1) haut[i]='A';
      else if (typeDec2==2) haut[i]='S';
      else if (typeDec2==3) haut[i]='M';
    }
    else if (i==posDec3) {
      lcd.write(typeDec3+5);
      if (typeDec3==0) haut[i]='V';
      else if (typeDec3==1) haut[i]='A';
      else if (typeDec3==2) haut[i]='S';
      else if (typeDec3==3) haut[i]='M';
    }
    else if (i==posDec4) {
      lcd.write(typeDec4+5);
      if (typeDec4==0) haut[i]='V';
      else if (typeDec4==1) haut[i]='A';
      else if (typeDec4==2) haut[i]='S';
      else if (typeDec4==3) haut[i]='M';
    }
    else { // Nothing special to write / Rien à écrire de spécial.
      lcd.write(' ');
      haut[i]=' ';
    }
  }
  
  // Other cars
  //-------------------------
  // Autres voitures
  if (compteurConc>6) { // Create new car when the last one has disapeared / Si voiture précédente disparue, on en cré une nouvelle
    obsConc=1000;
    if (random(0,100)>70) {
      posConc1 = random(1,largRoute); // Random position on top line / Position aléatoire sur la ligne du haut  
      compteurConc = 0;  
    }
  }
  else { // If the car is still there, update screen / Si voiture toujours là, on met à jour l'écriture sur l'écran
    if (compteurConc<3) { // The car stays a little in the top line... / elle reste un peu en haut...
      lcd.setCursor(posConc1 + posRoute,0);
      // We adapt the direction of the car to that of the road / On adapte la direction de la voiture à celle de la route.
      if (actuDir==0) typeConc=3;
      else if (actuDir==1) typeConc = 2;
      else typeConc = 4;
      lcd.write(typeConc);  
      compteurConc = compteurConc + 1;  
    }
    else { // ... then it moves to the bottom line / ... puis elle passe en bas.
      lcd.setCursor(posConc1 + oldposRoute,1);
      obsConc = posConc1 + oldposRoute;
      // We adapt the direction of the car to that of the road / On adapte la direction de la voiture à celle de la route.
      if (oldDir==0) typeConc=3;
      else if (oldDir==1) typeConc = 2;
      else typeConc = 4;
      lcd.write(typeConc);
      compteurConc = compteurConc + 1;       
    }
  }
}

// This function controls the animation of the car itself.
//------------------------------------------------------------
// Cette fonction contrôle l'animation de la voiture.
void Voit_animationVoiture() {
  int typeVoiture;  

  lcd.setCursor(posVoiture,1);
  lcd.print(' ');
  // Computes new position and direction of the car.
  //--------------------------------------------------
  // Calcule les nouvelles position et direction de la voiture.
  if (moveVoiture==0) {
    if (posVoiture!=0) {
      posVoiture = posVoiture - 1; // Move the car to the left / On décale la voiture vers la gauche
      typeVoiture = 3; // Custom character for the car turning to the left / Caractère de la voiture tournant vers la gauche.
    }
    else typeVoiture = 2;
  }
  else if (moveVoiture==2) {
    if (posVoiture!=15) {
      posVoiture = posVoiture + 1; // Move the car to the right / On décale la voiture vers la droite
      typeVoiture = 4;  // Custom character for the car turning to the right / Caractère de la voiture tournant vers la droite.
    }
    else typeVoiture = 2;
  }
  else {
    typeVoiture = 2;  // Custom character for the car moving straight ahead / Caractère de la voiture allant droit devant.
  }
  // If no collision, print the car on the screen...
  //------------------------------------------
  // Si pas de collision, on affiche la voiture sur l'écran...
  if (posVoiture!=posRoute && posVoiture!=(posRoute + largRoute) && posVoiture!=obsConc) { 
    lcd.setCursor(posVoiture,1);
    lcd.write(typeVoiture);
  }
  else {  // ... else : boom! / ... sinon : boom!
    lcd.setCursor(posVoiture-2,1);
    lcd.print("Boom!");
    collision = 1;
  }  
}

