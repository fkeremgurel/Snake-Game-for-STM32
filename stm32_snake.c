#define BUTTON_UP Button(&GPIOC_IDR,4,10,1)
#define BUTTON_DOWN Button(&GPIOA_IDR,14,10,1)
#define BUTTON_RIGHT Button(&GPIOB_IDR,1,10,1)
#define BUTTON_LEFT Button(&GPIOA_IDR,13,10,1)
#define BUTTON_MID Button(&GPIOC_IDR,5,10,1)

unsigned long GLCD_DataPort_Input at GPIOE_IDR;
unsigned long GLCD_DataPort_Output at GPIOE_ODR;

sbit GLCD_CS2 at GPIOE_ODR.B11;
sbit GLCD_CS1 at GPIOE_ODR.B12;
sbit GLCD_RS at GPIOE_ODR.B8;
sbit GLCD_RW at GPIOE_ODR.B9;
sbit GLCD_EN at GPIOE_ODR.B10;
sbit GLCD_RST at GPIOE_ODR.B13;
sbit BUZZER at GPIOA_ODR.B8;

int gameOver, buton, skor, basla;
int i, j, k, x, y, mX, mY, kuyrukX[1000], kuyrukY[1000], kuyrukUzunlugu, prevX, prevY, prev2X, prev2Y, poopX, poopY;

void setup(){
     // burada oyun baþlamadan önceki kurulum olacak
     gameOver = 0;
     basla = 0;

     // yılanın başlangıç pozisyonu
     x = 128 / 2;
     y = 64 / 2;
     kuyrukUzunlugu = 0;


     // meyvenin pozisyonu rastgele belirleniyor
     while (mX == 0)
           mX = rand() % 128;

     while (mY == 0)
           mY = rand() % 64;

     // skor 0 olarak belirleniyor ve oyun başlatılırken ses ve görüntü çıkışıyla tuş girdileri ayarlanıp LCD ekrandaki eski görüntü temizleniyor
     skor = 0;
     Sound_Init(&GPIOB_ODR, 8);
     Glcd_Init();
     GPIO_Digital_Input(&GPIOA_BASE,_GPIO_PINMASK_0 | _GPIO_PINMASK_14 | _GPIO_PINMASK_13);
     GPIO_Digital_Input(&GPIOB_BASE,_GPIO_PINMASK_1);
     GPIO_Digital_Input(&GPIOC_BASE,_GPIO_PINMASK_4 | _GPIO_PINMASK_5);
     Glcd_Fill(0);
     // Ana menü
     //Glcd_Write_Text("Yilan Oyunu", 31, 2, 1);
}

void kontroller(){
             if(BUTTON_UP){
                           if(buton != 2) buton = 1;
             }
             if(BUTTON_DOWN){
                           if(buton != 1) buton = 2;
             }
             if(BUTTON_LEFT){
                           if(buton != 4) buton = 3;
             }
             if(BUTTON_RIGHT){
                           if(buton != 3) buton = 4;
             }
}

void mantik(){
              // kuyruğun önceki pozisyonunu alıyor
              int prevX = kuyrukX[0];
              int prevY = kuyrukY[0];

              // kuyruğun iki önceki pozisyonu için ihtiyaçtan oluşturuldu
              int prev2X, prev2Y;

              // yılanın başının pozisyonu
              kuyrukX[0] = x;
              kuyrukY[0] = y;

              // yılanın her bir parçasının pozisyonunu kaydediyor
              for(i=1;i<kuyrukUzunlugu;i++) {
                prev2X = kuyrukX[i];
                prev2Y = kuyrukY[i];
                kuyrukX[i] = prevX;
                kuyrukY[i] = prevY;
                prevX = prev2X;
                prevY = prev2Y;
              }

              // yılanın kuyruğundan sonra LCD ekranda kalan kuyruk izlerini temizlemek için kaydedilen pozisyon. Daha şık bir isim aklıma gelmedi.
              poopX = prevX;
              poopY = prevY;
              
              switch (buton) {
              case 1:
                  x--;
                  break;
              case 2:
                  x++;
                  break;
              case 3:
                  y--;
                  break;
              case 4:
                  y++;
                  break;
              default:
                  break;
              }
              
              if (x < 0 || x >= 127 || y < 0 || y >= 63)
              gameover = 1;

              // Kuyruk çarpışmasına bakıyor
              for (i = 0; i < kuyrukUzunlugu; i++) {
                  if (kuyrukX[i] == x && kuyrukY[i] == y)
                      gameover = 1;
              }
              
              // meyveyi yiyip yemediğini kontrol edip rastgele bir yerde yeni meyve oluşturuyor
              if (x == mX && y == mY) {
                 Sound_Play(659, 30);
                 do{
                    mX = rand() % 128;
                    mY = rand() % 64;
                 }while(mX == 0 || mX == 127 || mY == 0 || mY == 63);
                 
                 skor += 10;
                 kuyrukUzunlugu++;

              }
}

void goruntu(){
       // yılanı, meyveyi ve oyun alanı sınırlarını çiziyor.
       Glcd_Rectangle(0,0,127,63,1);
       Glcd_Dot(x,y,1);
       Glcd_Dot(mX,mY,1);

       // yılanın bulunduğu her bir noktayı çiziyor
       for (i = 0; i < kuyrukUzunlugu; i++) {
           Glcd_Dot(kuyrukX[i], kuyrukY[i],1);
       }

       // yılan ilerledikçe arkasından iz kalmamasını sağlıyor
       Glcd_Dot(poopX, poopY, 0);
}

void main(){
            // Ana menü mantığı entegre etmeyi denedim
            setup();
            //while(!basla){
            //              if(BUTTON_UP){
            //                            basla = 1;
            //              }
            //}

            // oyun döngüsü
            while(!gameover){
             goruntu();
             kontroller();
             mantik();
             delay_ms(33);
            }
            // kaybedince çalan jingle
            Sound_Play(987, 30);
            Sound_Play(783, 30);
            Sound_Play(659, 30);
            Sound_Play(466, 30);
}
