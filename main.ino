#include <LiquidCrystal.h>
/*
DEFINE KISIMLARI
*/
#define temperatureSensorPIN	A0
#define ButonCurrentTime		10
#define ButonAlarmSet			9
#define ButonTemperatureScale	8
#define ButonSnoozeAlarm		7
#define ButonYuksek				1
#define	ButonDusuk				0
#define ButonSayisi				4
#define PiezoBuzzerPIN			13
/*
DEFINE KISIMLARI BITIS
*/
int blinkSaatCounter = 0;
int blinkDakikaCounter = 0;
int blinkAlarmSaatCounter = 0;
int blinkAlarmDakikaCounter = 0;

int timerCounter = 0;
int buttonState = 0;
bool alarmKurulduMu = false;
/*
ENUM TANIMLAMA BASLANGIC
*/
enum CLOCKTYPE {
    HOUR24TYPE = 0,
    HOUR12TYPE = 1,
};
enum SICAKLIKTIPI{
  CELCIUS		= 0,
  FAHRENHEIT	= 1,
  
};

/*
ENUM TANIMLAMA BITIS
*/

/*
STRUCT TANIMLAMA BASLANGIC
*/
struct butonHandler_t{
  int butonPin;
  int butonDurum;
  int butonOncekiDurum;
  int butonSayac;	//Interrupt icinde kontrol edilecek. belli bir sayiya 
  					//eristigi durumlarda belli islevleri yerine getirecek.
  					//ornegin 3 saniye basili tutma durumu burada denetlenecek.
};
struct butonlar_t{
  butonHandler_t butonlar[4]; //4 Butonun durum, basilma suresi, pin numarasi burada kayitli.
  
};
struct alarmSaati_t{ // AlarmSaati Structi ile hedeflenen normal saat(zamanolcer) ile cakisma durumlari.
  	int				saat24;
  	int				saat12;
	int				dakika;
	CLOCKTYPE		saatDefaultOr12H;  
	bool			alarmKurulduMu; 
  	bool			alarmKuruluyorMu;
  	bool			alarmCaliyorMu;
};
struct zamanOlcer_t{
	int				saat24;
	int 			saat12;
	int 			dakika;
  	int 			saniye;
	int 			timerCounter;
  	bool			saatAyarlaniyorMu;
  	CLOCKTYPE 		saatDefaultOr12H;
  	SICAKLIKTIPI 	sicaklikTipi;

  
};

/*
STRUCT TANIMLAMA BITIS
*/

/*
STRUCT INITIALIZE BASLANGIC
*/
butonlar_t kullanilanButonlar = {0};
zamanOlcer_t zamanOlcer = {13,1,59,55,0,false,HOUR24TYPE,CELCIUS}; 
alarmSaati_t alarm = {14,0,0,HOUR24TYPE,true,false,false};

/*
STRUCT INITIALIZE BITIS
*/
int sensePin = A0;  //This is the Arduino Pin that will read the sensor output
int sensorInput;    //The variable we will use to store the sensor input
double degreeC;        //The variable we will use to store temperature in degrees. 
double degreeF;        
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  


void alarmAyarlamaButonuKontrol(){
  
}

void saatAyarlamaButonuKontrol(){
  
  
}


void saatGuncelle(zamanOlcer_t &saatim);
void saatGuncelle(zamanOlcer_t &saatim){
  if(saatim.saniye==60){
    
    saatim.saniye=0;
    saatim.dakika++;
  }
  
  if(saatim.dakika==60){
	saatim.dakika=0;
    saatim.saat24++;
    
  }
}
void alarmDurumunuLCDYazdir(alarmSaati_t& alarmim);

void alarmDurumunuLCDYazdir(alarmSaati_t& alarmim){
  if(alarmim.alarmKurulduMu == true){
    lcd.setCursor(0,0);
    lcd.print("ALARM ON ");
    
  }
  
  else {
        lcd.setCursor(0,0);
    lcd.print("ALARM OFF");
    
    
  }
  
  
}
void saatBiriminiDegistir(){
  Serial.println("SAAT TIPI " + zamanOlcer.saatDefaultOr12H);
  if(zamanOlcer.saatDefaultOr12H == HOUR24TYPE){
    zamanOlcer.saatDefaultOr12H = HOUR12TYPE;
  }
  
  else {   
        zamanOlcer.saatDefaultOr12H = HOUR24TYPE;
  }
  
}

void alarmCaliyorMu(zamanOlcer_t& saatim, alarmSaati_t& alarmim);
void saat12likGoster(){
  
    lcd.setCursor(0,2);
  	Serial.println(zamanOlcer.saat12);
    if(zamanOlcer.saat24 > 12){
      zamanOlcer.saat12 = zamanOlcer.saat24 % 12; 
      lcd.print(zamanOlcer.saat12);
      lcd.print(":");
      if(zamanOlcer.dakika < 10){
      lcd.print("0");}      
      lcd.print(zamanOlcer.dakika);
      lcd.print(":");
      if(zamanOlcer.saniye  < 10){
  	lcd.print("0");      

 
  
}     
            lcd.print(zamanOlcer.saniye);
      lcd.print("PM");
    }
    else if (zamanOlcer.saat24 == 12){ 
      //Saat 12 ise bir sey yapma
  		lcd.print(zamanOlcer.saat12);
  		lcd.print(":");
        if(zamanOlcer.dakika < 10){
        lcd.print("0");}
 		 lcd.print(zamanOlcer.dakika);
 		 lcd.print(":");
      
        if(zamanOlcer.saniye  < 10){
  		lcd.print("0"); 
  
}        lcd.print(zamanOlcer.saniye);

            lcd.print("PM");

    }
    else if (zamanOlcer.saat24 < 12){
        lcd.print(zamanOlcer.saat12);
        lcd.print(":");
        if(zamanOlcer.dakika < 10){
        lcd.print("0");}
  		lcd.print(zamanOlcer.dakika);
  		lcd.print(":");  
		if(zamanOlcer.saniye  < 10){
  			lcd.print("0");}      
        lcd.print(zamanOlcer.saniye);
        lcd.print("AM");

  
    }
    


  
}


void saat24lukGoster(){
  		lcd.setCursor(0,2);
        lcd.print(zamanOlcer.saat24);
      	lcd.print(":");
        if(zamanOlcer.dakika < 10){
        lcd.print("0");}
      	lcd.print(zamanOlcer.dakika);
        lcd.print(":");
      if(zamanOlcer.saniye  < 10){
       lcd.print("0"); 
      }
      	lcd.print(zamanOlcer.saniye);
  		lcd.print("  ");
}


void saatGoster(){
	if(zamanOlcer.saatDefaultOr12H == HOUR24TYPE){

		saat24lukGoster();
  }
    
  else if(zamanOlcer.saatDefaultOr12H == HOUR12TYPE){
		saat12likGoster();
  }
  else{}
  
}

void sicaklikGoster(){
  if(zamanOlcer.sicaklikTipi == FAHRENHEIT){
  lcd.setCursor(11,2);
  lcd.print((int)degreeF);
  lcd.setCursor(15,2);
  lcd.print('F');
        Serial.println("deneme");

  }
  
  else if(zamanOlcer.sicaklikTipi == CELCIUS){
    
  lcd.setCursor(11,2);
  lcd.print((int)degreeC);
  lcd.setCursor(15,2);
  lcd.print('C');
  }
}

/*
* isiSensoruOkuma()
* Input: int * sensorInput, double * temp
* Fonksiyon TMP36 Isi sensorunden gelen veriyi okur. Veriyi belli bir algoritma ile
* gercek degerine cevirir.
*
*@return type: void
*/
void isiSensoruOkuma(int *sensorInput,double *tempC, double *tempF ){
  (*sensorInput) = analogRead(A0);    
  (*tempC) = (double)(*sensorInput) / 1024;       
  (*tempC) = ((*tempC) * 5);                 //multiply by 5V to get voltage
  (*tempC) = (*tempC) - 0.5;               //Subtract the offset 
  (*tempC) = (*tempC) * 100;               //Convert to degrees   
  
  (*tempF) = ((*tempC) * 9.0 / 5.0) + 32.0;
}


/*
* butonDurumGuncelle(void)
* Fonksiyon butonHandler_t tipindeki yapinin icerisindeki butonOncekiDurum
* ve butonDurum degiskenlerini guncellestirir.
*
*@return type: void
*/

void butonDurumGuncelle(){
    kullanilanButonlar.butonlar[0].butonOncekiDurum = kullanilanButonlar.butonlar[0].butonDurum;
    kullanilanButonlar.butonlar[1].butonOncekiDurum = kullanilanButonlar.butonlar[1].butonDurum;
    kullanilanButonlar.butonlar[2].butonOncekiDurum = kullanilanButonlar.butonlar[2].butonDurum;
    kullanilanButonlar.butonlar[3].butonOncekiDurum = kullanilanButonlar.butonlar[3].butonDurum;

    kullanilanButonlar.butonlar[0].butonDurum = digitalRead(ButonCurrentTime);
  	kullanilanButonlar.butonlar[1].butonDurum = digitalRead(ButonAlarmSet);
  	kullanilanButonlar.butonlar[2].butonDurum = digitalRead(ButonTemperatureScale);
  	kullanilanButonlar.butonlar[3].butonDurum = digitalRead(ButonSnoozeAlarm);

  
  
}
/*
* butonInitialize(void)
* Fonksiyon butonHandler_t tipindeki yapinin icerisindeki butonPin
* ve butonDurum degiskenlerine baslangic atamasi yapar. (initializing).  
* Buton 1 - Zaman Gosterim Tipi (12 / 24)
* Buton 2 - Alarm Kurulum
* Buton 3 - Sicaklik Gosterim Tipi
* Buton 4 - Alarm Sustur
*@return type: void
*/
void butonInitialize(){

  	kullanilanButonlar.butonlar[0].butonPin = ButonCurrentTime;
    kullanilanButonlar.butonlar[1].butonPin = ButonAlarmSet;
    kullanilanButonlar.butonlar[2].butonPin = ButonTemperatureScale;
    kullanilanButonlar.butonlar[3].butonPin = ButonSnoozeAlarm;
  	kullanilanButonlar.butonlar[0].butonDurum = ButonYuksek;
    kullanilanButonlar.butonlar[1].butonDurum = ButonYuksek;
    kullanilanButonlar.butonlar[2].butonDurum = ButonYuksek;
    kullanilanButonlar.butonlar[3].butonDurum = ButonYuksek;

    pinMode(ButonCurrentTime, INPUT_PULLUP); //Butonlar PULLUP tanimlandigi icin initalize 1 durumunda.
    pinMode(ButonAlarmSet, INPUT_PULLUP);
    pinMode(ButonTemperatureScale, INPUT_PULLUP);
    pinMode(ButonSnoozeAlarm, INPUT_PULLUP);
  	pinMode(PiezoBuzzerPIN, OUTPUT);
  
}
void sicaklikBiriminiDegistir(){
  if(zamanOlcer.sicaklikTipi == CELCIUS){
    zamanOlcer.sicaklikTipi = FAHRENHEIT;
  }
  
  else {   
        zamanOlcer.sicaklikTipi = CELCIUS;
  }
  
}
void butonSayacGuncelle(){

   /* if(kullanilanButonlar.butonlar[1].butonDurum == kullanilanButonlar.butonlar[1].butonOncekiDurum){
      if(kullanilanButonlar.butonlar[1].butonDurum == ButonDusuk){
   		(kullanilanButonlar.butonlar[1].butonSayac)++;
      }
   	 else {
           kullanilanButonlar.butonlar[1].butonSayac=0;
     }
  	if(kullanilanButonlar.butonlar[1].butonSayac == 3){
		zamanOlcer.saatDefaultOr12H = HOUR12TYPE;
    }
    }
  */
  
}
            
void alarmCaliyorMu(zamanOlcer_t& saatim, alarmSaati_t& alarmim){
  Serial.println(alarmim.alarmCaliyorMu);
  if(saatim.dakika == alarmim.dakika && alarmim.saat24 == saatim.saat24) 
    // Bu durumda alarm calacaktir.
  {
    alarmim.alarmCaliyorMu = true;	
  }
  
  else 
    // Tasarladigim sey bu alarmin bir sure calmasi ve bunu da TIMER uzerinden kontrol edecegim.
  {
    
  }
  
  if(alarmim.alarmCaliyorMu == true){ // Kontrolu iki asamalı yapmak testi kolaylaştırdı eve gidince değiştirme
    
        digitalWrite(PiezoBuzzerPIN,HIGH);
    }
  
    else{
        digitalWrite(PiezoBuzzerPIN,LOW);
    }
  
  
} 

            
void setup() {
	butonInitialize();
  	/* Piezo Test - Calisti. 
  	digitalWrite(PiezoBuzzerPIN,HIGH);
    */
  /*
  
  Interrupt 
  
  */
  
    
    TCNT1 = 49910;  // 65536-15625-1 (Saniyede 15625 cycle donecek.)
  //Counter Default degeri 65536 ise arasındaki farktan başlatırsam 1 sn olur.
    TCCR1A = 0x00;
    TCCR1B = (1<<CS10) | (1<<CS12);
    TIMSK1 = (1 << TOIE1) ;
    sei();
  
  
  
  
  Serial.begin(9600); //Start the Serial Port at 9600 baud (default)
  lcd.begin(16, 2); /* Kullandigimiz LCDnin sutun ve satir sayisini belirtmeliyiz */
  //lcd.print("TEBEYE"); /* Ekrana yazi yazalim */
}
void loop() {
  saatGuncelle(zamanOlcer);
  saatGoster();
  alarmDurumunuLCDYazdir(alarm);
  butonDurumGuncelle();
  alarmCaliyorMu(zamanOlcer, alarm);
  //lcd.setCursor(5,1);
  //lcd.print(kullanilanButonlar.butonlar[2].butonSayac);
  isiSensoruOkuma(&sensorInput,&degreeC,&degreeF);
  sicaklikGoster();
    //Serial.print(zamanOlcer.sicaklikTipi);
delay(100);
}

ISR (TIMER1_OVF_vect)    // Timer1 ISR
{
 //	butonSayacGuncelle();
      if(kullanilanButonlar.butonlar[0].butonDurum == kullanilanButonlar.butonlar[0].butonOncekiDurum){
      if(kullanilanButonlar.butonlar[0].butonDurum == ButonDusuk){
   		(kullanilanButonlar.butonlar[0].butonSayac)++;
      }
   	 else {
           kullanilanButonlar.butonlar[0].butonSayac=0;
     }
      ///////////////
          if(kullanilanButonlar.butonlar[1].butonDurum == kullanilanButonlar.butonlar[1].butonOncekiDurum){
      if(kullanilanButonlar.butonlar[1].butonDurum == ButonDusuk){
   		(kullanilanButonlar.butonlar[1].butonSayac)++;
      }
   	 else {
           kullanilanButonlar.butonlar[1].butonSayac=0;
     }   
           /////////////////
       if(kullanilanButonlar.butonlar[2].butonDurum == kullanilanButonlar.butonlar[2].butonOncekiDurum){
      if(kullanilanButonlar.butonlar[2].butonDurum == ButonDusuk){
   		(kullanilanButonlar.butonlar[2].butonSayac)++;
      }
   	 else {
           kullanilanButonlar.butonlar[2].butonSayac=0;
     }   
         ///////////////
         if(kullanilanButonlar.butonlar[3].butonDurum == kullanilanButonlar.butonlar[3].butonOncekiDurum){
      if(kullanilanButonlar.butonlar[3].butonDurum == ButonDusuk){
   		(kullanilanButonlar.butonlar[3].butonSayac)++;
      }
   	 else {
           kullanilanButonlar.butonlar[3].butonSayac=0;
     }
      
      
      
      
      
      
      
         if(kullanilanButonlar.butonlar[0].butonSayac == 3){ //Ilk buton Saat tipi icin
		saatBiriminiDegistir();
   		 }
         else if(kullanilanButonlar.butonlar[1].butonSayac == 3){ //Ikinci buton alarm kurulum
       //    alarmKurulumuIcinButonlarinGorevleriniDegistir();
           
         }
         else if(kullanilanButonlar.butonlar[2].butonSayac == 3){ //Ucuncu buton sicaklik birimi
           sicaklikBiriminiDegistir();
          
         }
         
         else if(kullanilanButonlar.butonlar[3].butonSayac == 3){ //Dorduncu buton Alarm Sustur
           //DigitalPini Lowa cek.
			alarm.alarmCaliyorMu = false;    
            alarm.dakika+=1;
           if(alarm.dakika > 59){
             alarm.saat24+=1;
           }
           if(alarm.saat24 > 23){
            alarm.saat24 = 0; 
           }
             
         }
       
    
  }
  
       }}}
  
  
  
  
  
  
  
  
  
  
  
  /*
      if(kullanilanButonlar.butonlar[0].butonDurum == kullanilanButonlar.butonlar[0].butonOncekiDurum){
      if(kullanilanButonlar.butonlar[0].butonDurum == ButonDusuk){
   		(kullanilanButonlar.butonlar[0].butonSayac)++;
      }
   	 else {
           kullanilanButonlar.butonlar[0].butonSayac=0;
     }
  	if(kullanilanButonlar.butonlar[0].butonSayac == 3){
		zamanOlcer.saatDefaultOr12H = HOUR12TYPE;
    }
    }
  
  */
	(zamanOlcer.timerCounter)++;
  zamanOlcer.saniye++;
  blinkSaatCounter++;

	TCNT1 = 49910;   // for 1 sec at 16 MHz
  
  

}

