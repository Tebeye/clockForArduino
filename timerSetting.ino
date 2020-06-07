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
	 
	  }
      ///////////////
          if(kullanilanButonlar.butonlar[1].butonDurum == kullanilanButonlar.butonlar[1].butonOncekiDurum){
      if(kullanilanButonlar.butonlar[1].butonDurum == ButonDusuk){
   		(kullanilanButonlar.butonlar[1].butonSayac)++;
      }
   	 else {
           kullanilanButonlar.butonlar[1].butonSayac=0;
     }   
	 }
           /////////////////
       if(kullanilanButonlar.butonlar[2].butonDurum == kullanilanButonlar.butonlar[2].butonOncekiDurum){
      if(kullanilanButonlar.butonlar[2].butonDurum == ButonDusuk){
   		(kullanilanButonlar.butonlar[2].butonSayac)++;
      }
   	 else {
           kullanilanButonlar.butonlar[2].butonSayac=0;
     }   
	 }
         ///////////////
         if(kullanilanButonlar.butonlar[3].butonDurum == kullanilanButonlar.butonlar[3].butonOncekiDurum){
      if(kullanilanButonlar.butonlar[3].butonDurum == ButonDusuk){
   		(kullanilanButonlar.butonlar[3].butonSayac)++;
      }
   	 else {
           kullanilanButonlar.butonlar[3].butonSayac=0;
     }
      
      
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
