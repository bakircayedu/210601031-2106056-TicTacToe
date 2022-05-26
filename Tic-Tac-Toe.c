#include <stdio.h>
#include <conio.h>
#include <unistd.h>
#include <string.h>

struct oyuncu{int numara; char isim[20]; char sifre[20];}oyuncuBir,oyuncuIki,kaydolanSonOyuncu,tarananOyuncuVerileri;
enum{arkaPlan=6,yazi};
enum {kapali=0,acik};

int kutulardakiSemboller[10]={0,0,0,0,0,0,0,0,0,0};
int oyuncununHamlesi=0;
int enterBasma=acik;
char sembloller[3]={' ','X','O'};
char renk[9]="color 07";
FILE *pOyuncular, *pKazanmalar, *pKaybetmeler, *pBeraberlikler;


void acilisAyarlari();

void acilisSekansi();

void menu();
    void oyun();
        void kutulardakiSembolleriSifirla();
        void tabloCiz();
        int kazananKontrol();
        void kazanmaSekansi(int kazananOyuncu);
            void kazananlaraEkle(int eklenecekNumara);
            void kaybedenlereEkle(int eklenecekNumara);
        void beraberlikSekansi();
            void beraberligeEkle(int eklenecekNumara);
        int oyuncuHamlesiniAl();
        void hamleUygunMu();
    int oyuncuGiris();
    int oyuncuKayit();
    void istatistikGosterici();
        void istatistikTarayici(int arananNumara);
    int ayarlarMenusu();
        int sembolAyari();
            int semboluDegistir(int degistirilecekSembol);
                int klavyeHariciSemboller(int degistirilecekSembol);
        int renkAyari();
            int renkKatalogu(int degistirilecekYer);
        int enterBasmaDegistir();



int main(){

    acilisAyarlari();
    acilisSekansi();
    menu();

    return 0;

}

void acilisSekansi(){

    int i;
system("color a");
    printf("##########            \n");usleep(50000);system("color b");
    printf("|   ||   |   #        \n");usleep(50000);system("color c");
    printf("    ||                \n");usleep(50000);system("color d");
    printf("    ||      ###    ###\n");usleep(50000);system("color e");
    printf("    ||       ||   #   \n");usleep(50000);system("color f");
    printf("    ||       ||   #   \n");usleep(50000);system("color 1");
    printf("    ||       ||   #   \n");usleep(50000);system("color 2");
    printf("    ||       ||   #   \n");usleep(50000);system("color 3");
    printf("   ####     ####   ###\n\n");usleep(50000);system("color 4");
    printf("           ##########                        \n");usleep(50000);system("color 5");
    printf("           |   ||   |                        \n");usleep(50000);system("color 6");
    printf("               ||                            \n");usleep(50000);system("color 7");
    printf("               ||       ###     ###          \n");usleep(50000);system("color 8");
    printf("   ______      ||          #   #      ______ \n");usleep(50000);system("color 9");
    printf("  |######|     ||       ####   #     |######|\n");usleep(50000);system("color a");
    printf("               ||      #   #   #             \n");usleep(50000);system("color b");
    printf("               ||      #   #   #             \n");usleep(50000);system("color c");
    printf("              ####     ######   ###          \n\n");usleep(50000);system("color d");
    printf("##########            \n");usleep(50000);system("color e");
    printf("|   ||   |            \n");usleep(50000);system("color f");
    printf("    ||                \n");usleep(50000);system("color 1");
    printf("    ||      ####    ###\n");usleep(50000);system("color 2");
    printf("    ||     #    #  #   #\n");usleep(50000);system("color 3");
    printf("    ||     #    #  # ###\n");usleep(50000);system("color 4");
    printf("    ||     #    #  #     \n");usleep(50000);system("color 5");
    printf("    ||     #    #  #   #  \n");usleep(50000);system("color 6");
    printf("   ####     ####    ###                              v0.3.13\n");sleep(2);
    for(i=0;i<50;i++){
            printf("\n");
            usleep(7000);
    }
    system("cls");
    system("color 7");

    char ilkYazi[]="Hos geldiniz.\nOyunun temel mantigi 3 adet kendi sembolunuzu (dikey, yatay veya capraz sekilde) yan yana getirmektir.";
    for(i=0;i<strlen(ilkYazi);i++)
    {
        printf("%c",ilkYazi[i]);
        usleep(9000);
    }

    sleep(1);
printf("\n\n\n");
printf("\t\t     |     |     \n");
printf("\t\t  1  |  2  |  3  \n");
printf("\t\t_____|_____|_____\n");
printf("\t\t     |     |     \n");
printf("\t\t  4  |  5  |  6  \n");
printf("\t\t_____|_____|_____\n");
printf("\t\t     |     |     \n");
printf("\t\t  7  |  8  |  9  \n");
printf("\t\t     |     |     \n");
sleep(1);

char ikinciYazi[]="\nKutu numaralari yukaridaki gibidir.\nSirasi gelen oyuncu sembolunu yerlestirmek istedigi kutu numarasini tuslayarak sembolu yerlestirir.\n";
for(i=0;i<strlen(ikinciYazi);i++)
    {
        printf("%c",ikinciYazi[i]);
        usleep(9000);
    }
printf("\n\nDevam etmek icin bir tusa basin...");
            getch();
}

void acilisAyarlari(){

            kaydolanSonOyuncu.numara=0;
            strcpy(oyuncuBir.isim,"1.oyuncu");
            strcpy(oyuncuIki.isim,"2.oyuncu");
            oyuncuBir.numara=0;
            oyuncuIki.numara=0;

    pOyuncular=fopen("oyuncular.txt","r");
    if (pOyuncular==NULL)
    {
        fclose(pOyuncular);
        pOyuncular=fopen("oyuncular.txt","w");
    }
    else
        while(!feof(pOyuncular))
            fscanf(pOyuncular,"%d %s %s",&kaydolanSonOyuncu.numara,&kaydolanSonOyuncu.isim,&kaydolanSonOyuncu.sifre);
    fclose(pOyuncular);

    pKazanmalar=fopen("kazanmalar.txt","r");
    if(pKazanmalar==NULL)
    {
            fclose(pKazanmalar);
            pKazanmalar=fopen("kazanmalar.txt","w");
    }
    fclose(pKazanmalar);

        pKaybetmeler=fopen("kaybetmeler.txt","r");
    if(pKaybetmeler==NULL)
    {
            fclose(pKaybetmeler);
            pKaybetmeler=fopen("kaybetmeler.txt","w");
    }
    fclose(pKaybetmeler);

        pBeraberlikler=fopen("beraberlikler.txt","r");
    if(pBeraberlikler==NULL)
    {
            fclose(pBeraberlikler);
            pBeraberlikler=fopen("beraberlikler.txt","w");
    }
    fclose(pBeraberlikler);


}

void menu(){
    char anaMenuSecimi;

anaMenu:
            system("cls");
    printf("Lutfen yapmak istediginiz islemi secin.\n");
    printf("\t0.Cikis\n");
    printf("\t1.Yeni oyuna baslama\n");
    printf("\t2.Oyuncu girisi\n");
    printf("\t3.Yeni oyuncu kayit\n");
    printf("\t4.Istatistik Goruntuleme\n");
    printf("\t5.Ayarlar\n");
    if(oyuncuBir.numara!=0)
        printf("\t6.Birinci oyuncu cikis.\n");
    if(oyuncuIki.numara!=0)
        printf("\t7.Ikinci oyuncu cikis.\n");

while(1)
    {
        anaMenuSecimi=getch();

        if(anaMenuSecimi=='0')
            exit (0);

        if(anaMenuSecimi=='1')
            oyun();

        if(anaMenuSecimi=='2'){
            system("cls");
            oyuncuGiris();
            goto anaMenu;}

        if(anaMenuSecimi=='3'){
            system("cls");
            oyuncuKayit();
            goto anaMenu;}

        if(anaMenuSecimi=='4'){
            system("cls");
            istatistikGosterici();
            goto anaMenu;}

        if(anaMenuSecimi=='5'){
            system("cls");
            ayarlarMenusu();
            goto anaMenu;}

        if(oyuncuBir.numara!=0&&anaMenuSecimi=='6'){
            oyuncuBir.numara=0;
            strcpy(oyuncuBir.isim,"1.oyuncu");
            goto anaMenu;
        }


        if(oyuncuIki.numara!=0&&anaMenuSecimi=='7'){
            oyuncuIki.numara=0;
            strcpy(oyuncuIki.isim,"2.oyuncu");
            goto anaMenu;
        }

    }
}

void oyun(){

    int kazananOyuncu=0;
    int mevcutTur=1;

kutulardakiSembolleriSifirla();

while(1)
    {

        system("cls");
        tabloCiz();

        kazananOyuncu=kazananKontrol();

        if(kazananOyuncu!=0)
        {
            kazanmaSekansi(kazananOyuncu);
            menu();
        }

        if(mevcutTur==10)
        {
            beraberlikSekansi();
            menu();
        }

        if(mevcutTur%2==1)
            printf("%s (%c) oynuyor. Lutfen yerlesmek istediginiz kutuyu secin:",oyuncuBir.isim,sembloller[1]);

        if(mevcutTur%2==0)
            printf("%s (%c) oynuyor. Lutfen yerlesmek istediginiz kutuyu secin:",oyuncuIki.isim,sembloller[2]);

    oyuncuHamlesiniAl();

    hamleUygunMu();

        if(mevcutTur%2==1)
            kutulardakiSemboller[oyuncununHamlesi]=1;

        if(mevcutTur%2==0)
            kutulardakiSemboller[oyuncununHamlesi]=2;

mevcutTur++;
}

}

void kutulardakiSembolleriSifirla(){
int i;
for(i=0;i<10;i++)
    kutulardakiSemboller[i]=0;
}

void tabloCiz(){

printf("\n\n\n");
printf("\t\t     |     |     \n");
printf("\t\t  %c  |  %c  |  %c  \n",sembloller[kutulardakiSemboller[1]],sembloller[kutulardakiSemboller[2]],sembloller[kutulardakiSemboller[3]]);
printf("\t\t_____|_____|_____\n");
printf("\t\t     |     |     \n");
printf("\t\t  %c  |  %c  |  %c  \n",sembloller[kutulardakiSemboller[4]],sembloller[kutulardakiSemboller[5]],sembloller[kutulardakiSemboller[6]]);
printf("\t\t_____|_____|_____\n");
printf("\t\t     |     |     \n");
printf("\t\t  %c  |  %c  |  %c  \n",sembloller[kutulardakiSemboller[7]],sembloller[kutulardakiSemboller[8]],sembloller[kutulardakiSemboller[9]]);
printf("\t\t     |     |     \n");

}

int kazananKontrol(){

int kazananKombinasyonlar[8][3] = {{1,2,3},{4,5,6},{7,8,9},{1,4,7},{2,5,8},{3,6,9},{1,5,9},{3,5,7}};
int i;

for(i=0;i<8;++i){
if(kutulardakiSemboller[kazananKombinasyonlar[i][0]] != 0 &&
           kutulardakiSemboller[kazananKombinasyonlar[i][0]] == kutulardakiSemboller[kazananKombinasyonlar[i][1]] &&
           kutulardakiSemboller[kazananKombinasyonlar[i][0]] == kutulardakiSemboller[kazananKombinasyonlar[i][2]])
           return kutulardakiSemboller[kazananKombinasyonlar[i][0]];}
           return 0;

}

void kazanmaSekansi(int kazananOyuncu){

int i;

    printf("\n\t\t");

    for(i=0;i<25;i++)
        printf("%c",sembloller[kazananOyuncu]);

    printf("\n\t\t%c   %d.Oyuncu Kazandi.   %c",sembloller[kazananOyuncu],kazananOyuncu,sembloller[kazananOyuncu]);
    printf("\n\t\t%c      Tebrikler!       %c",sembloller[kazananOyuncu],sembloller[kazananOyuncu]);

    printf("\n\t\t");

    for(i=0;i<25;i++)
        printf("%c",sembloller[kazananOyuncu]);


        if(kazananOyuncu==1)
            {
                if(oyuncuBir.numara!=0)
                    kazananlaraEkle(oyuncuBir.numara);
                if(oyuncuIki.numara!=0)
                    kaybedenlereEkle(oyuncuIki.numara);
            }

         if(kazananOyuncu==2)
            {
                if(oyuncuIki.numara!=0)
                    kazananlaraEkle(oyuncuIki.numara);
                if(oyuncuBir.numara!=0)
                    kaybedenlereEkle(oyuncuIki.numara);
            }

            printf("\n\nAna menuye donmek icin bir tusa basin...");
            getch();
}

void kazananlaraEkle(int eklenecekNumara){

    pKazanmalar=fopen("kazanmalar.txt","a");
    fprintf(pKazanmalar," %d",eklenecekNumara);
    fclose(pKazanmalar);
}

void kaybedenlereEkle(int eklenecekNumara){

    pKaybetmeler=fopen("kaybetmeler.txt","a");
    fprintf(pKaybetmeler," %d",eklenecekNumara);
    fclose(pKaybetmeler);
}

void beraberlikSekansi(){
            printf("\n\tBerabere.\n");
            printf("\t\tBerabere.\n");
            printf("\tBerabere.\n");
            if(oyuncuBir.numara!=0)
                beraberligeEkle(oyuncuBir.numara);
            if(oyuncuIki.numara!=0)
                beraberligeEkle(oyuncuIki.numara);
            printf("\nAna menuye donmek icin bir tusa basin...");
            getch();
}

void beraberligeEkle(int eklenecekNumara){

    pBeraberlikler=fopen("beraberlikler.txt","a");
    fprintf(pBeraberlikler," %d",eklenecekNumara);
    fclose(pBeraberlikler);
}

int oyuncuHamlesiniAl(){

    if(enterBasma==acik){
            scanf("%d",&oyuncununHamlesi);
        return 0;}

    if(enterBasma==kapali)
    {
        char charOyuncuHamlesi;
       while(1){
        charOyuncuHamlesi=getch();
       if(charOyuncuHamlesi<='9'&&charOyuncuHamlesi>='0'){
        oyuncununHamlesi=charOyuncuHamlesi-'0';
       return 0;}}
    }
}

void hamleUygunMu(){
while(kutulardakiSemboller[oyuncununHamlesi]!=0||!(oyuncununHamlesi>=1&&oyuncununHamlesi<=9))
{
    if(kutulardakiSemboller[oyuncununHamlesi]!=0 &&(oyuncununHamlesi>=1&&oyuncununHamlesi<=9))
        printf("\nSecilen kutu dolu. Lutfen tekrar secin:");

    if(!(oyuncununHamlesi>=1&&oyuncununHamlesi<=9))
        {
        if(oyuncununHamlesi>9)
            printf("\nSecilen sayi cok buyuk. Lutfen tekrar secin(1-9):");

        if(oyuncununHamlesi<1)
            printf("\nSecilen sayi cok kucuk. Lutfen tekrar secin(1-9):");
        }

    oyuncuHamlesiniAl();

}}

int oyuncuGiris(){
    struct oyuncu girisYapanOyuncu;
    char kacinciOyuncuOlacak;
    int kiyaslamaSonucu;

    printf("Kacici oyuncu olarak oynamak istersiniz.\n");
    printf("0.Ana menuye don\n");
    printf("1.Birinci Oyuncu\n");
    printf("2.Ikinci Oyuncu");
    while(1)
    {
        kacinciOyuncuOlacak=getch();
        if(kacinciOyuncuOlacak=='0')
            return 0;

        if(kacinciOyuncuOlacak=='1'){
            system("cls");
            printf("1.oyuncu secili\n");
            break;}

        if(kacinciOyuncuOlacak=='2'){
            system("cls");
            printf("2.oyuncu secili\n");
            break;}
    }
    printf("Kullanici adini giriniz:");
    scanf("%s",&girisYapanOyuncu.isim);
 pOyuncular=fopen("oyuncular.txt","r");
 while(!feof(pOyuncular)){
    fscanf(pOyuncular,"%d %s %s",&tarananOyuncuVerileri.numara,&tarananOyuncuVerileri.isim,&tarananOyuncuVerileri.sifre);

    kiyaslamaSonucu=strcmp(tarananOyuncuVerileri.isim,girisYapanOyuncu.isim);
    if(kiyaslamaSonucu==0)
        {
        printf("Sifrenizi giriniz:");
        scanf("%s",&girisYapanOyuncu.sifre);
        kiyaslamaSonucu=strcmp(tarananOyuncuVerileri.sifre,girisYapanOyuncu.sifre);
            if(kiyaslamaSonucu==0)
            {
                if(kacinciOyuncuOlacak=='1')
                {
                    strcpy(oyuncuBir.isim,tarananOyuncuVerileri.isim);
                    oyuncuBir.numara=tarananOyuncuVerileri.numara;
                }
                if(kacinciOyuncuOlacak=='2')
                {
                    strcpy(oyuncuIki.isim,tarananOyuncuVerileri.isim);
                    oyuncuIki.numara=tarananOyuncuVerileri.numara;
                }
                printf("Giris basarili.");
            }
            else
                printf("Sifre hatali.");
                printf("\n\nAna menuye donmek icin bir tusa basin...");
            getch();
                return 0;
        }
 }
 printf("Kullanici bulunamadi.");
 printf("\n\nAna menuye donmek icin bir tusa basin...");
            getch();
 return 0;
}

int oyuncuKayit(){

    struct oyuncu kaydolacakOyuncu;
    int kiyaslamaSonucu;

    printf("En fazla 20 karekter iceren kullanici adinizi ve sifrenizi seciniz.(Yalnizca sayilar ve ingilizce harfler kullaniniz.)\n");
    printf("Kullanici adi:");
    scanf("%s",&kaydolacakOyuncu.isim);
     pOyuncular=fopen("oyuncular.txt","r");
    while(!feof(pOyuncular))
    {
        fscanf(pOyuncular,"%d %s %s",&tarananOyuncuVerileri.numara,&tarananOyuncuVerileri.isim,&tarananOyuncuVerileri.sifre);
        kiyaslamaSonucu=strcmp(tarananOyuncuVerileri.isim,kaydolacakOyuncu.isim);
        if (kiyaslamaSonucu==0)
        {
            printf("Kullanici adi maalesef alinmis.");
            fclose(pOyuncular);
            printf("\n\nAna menuye donmek icin bir tusa basin...");
            getch();
            return 0;
        }
        fclose(pOyuncular);
        printf("Kullanici adi musait.\n");
        printf("Sifre:");
        scanf("%s",kaydolacakOyuncu.sifre);
        pOyuncular=fopen("oyuncular.txt","a");
        fprintf(pOyuncular,"%d %s %s\n",++kaydolanSonOyuncu.numara,kaydolacakOyuncu.isim,kaydolacakOyuncu.sifre);
        fclose(pOyuncular);
        printf("Kayit basarili.");
         printf("\n\nAna menuye donmek icin bir tusa basin...");
            getch();
            return 0;

    }

}

void istatistikGosterici(){

    if(oyuncuBir.numara==0)
        printf("\n1.oyuncu istatistikleri goruntulenemiyor cunku oyuncu giris yapmamis.");
    else
    {
        printf("\t1.oyuncu\n");
        printf("Isim:%s\n",oyuncuBir.isim);
        istatistikTarayici(oyuncuBir.numara);
    }

    if(oyuncuIki.numara==0)
        printf("\n2.oyuncu istatistikleri goruntulenemiyor cunku oyuncu giris yapmamis.");
    else
    {
        printf("\n\t2.oyuncu\n");
        printf("Isim:%s\n",oyuncuIki.isim);
        istatistikTarayici(oyuncuIki.numara);
    }
    printf("\n\nAna menuye donmek icin bir tusa basin...");
            getch();
            system("cls");
}

void istatistikTarayici(int arananNumara){

    int tarananNumara=0;
    int i;

        i=0;
        pKazanmalar=fopen("kazanmalar.txt","r");
        while(!feof(pKazanmalar))
            {
                fscanf(pKazanmalar," %d",&tarananNumara);
                if(tarananNumara==arananNumara)
                    i++;
            }
            fclose(pKazanmalar);
        printf("Kazanma:%d\n",i);

        i=0;tarananNumara=0;
        pKaybetmeler=fopen("kaybetmeler.txt","r");
        while(!feof(pKaybetmeler))
            {
                fscanf(pKaybetmeler," %d",&tarananNumara);
                if(tarananNumara==arananNumara)
                    i++;
            }
            fclose(pKaybetmeler);
        printf("Kaybetme:%d\n",i);

        i=0;tarananNumara=0;
        pBeraberlikler=fopen("beraberlikler.txt","r");
        while(!feof(pBeraberlikler))
            {
                fscanf(pBeraberlikler," %d",&tarananNumara);
                if(tarananNumara==arananNumara)
                    i++;
            }
            fclose(pBeraberlikler);
        printf("Beraberlik:%d\n",i);
}

int ayarlarMenusu(){

char ayarlarMenusuSecimi;


        ayarlarMenu:
            system("cls");
printf("Lutfen yapmak istediginiz ayari secin.\n");
    printf("\t0.Ana menuye don\n");
    printf("\t1.Yerlestirilecek semboller\n");
    printf("\t2.Renk\n");
    printf("\t3.Hamle yapmak icin 'enter' tuslama: ");
    if(enterBasma==acik)
        printf("Acik");
    if(enterBasma==kapali)
        printf("Kapali");

    while(1)
    {
        ayarlarMenusuSecimi=getch();

        if(ayarlarMenusuSecimi=='0')
            return 0;

        if(ayarlarMenusuSecimi=='1'){
            sembolAyari();
            goto ayarlarMenu;}

        if(ayarlarMenusuSecimi=='2'){
            renkAyari();
            goto ayarlarMenu;}

        if(ayarlarMenusuSecimi=='3'){
            system("cls");
            enterBasmaDegistir();
            goto ayarlarMenu;}
}}

int sembolAyari(){

char sembolAyariSecimi;

sembolAyariMenu:

    system("cls");
printf("                                 \t\t\t\t1.oyuncunun sembolu:%c\n",sembloller[1]);
printf("                                 \t\t\t\t2.oyuncunun sembolu:%c",sembloller[2]);
printf("\n\n\n");
printf("                                 \t\t\t\t     |     |     \n");
printf("0.Ayarlar menusune don           \t\t\t\t  %c  |     |     \n",sembloller[1]);
printf("1.Birinci oyuncu sembolu degistir\t\t\t\t_____|_____|_____\n");
printf("2.Ikinci oyuncu sembolu degistir \t\t\t\t     |     |     \n");
printf("                                 \t\t\t\t     |  %c  |     \n",sembloller[2]);
printf("                                 \t\t\t\t_____|_____|_____\n");
printf("                                 \t\t\t\t     |     |     \n");
printf("                                 \t\t\t\t  %c  |     |  %c  \n",sembloller[2],sembloller[1]);
printf("                                 \t\t\t\t     |     |     \n");


while(1)
{
    sembolAyariSecimi=getch();

    if(sembolAyariSecimi=='0')
        return 0;

    if(sembolAyariSecimi=='1'){
        semboluDegistir(1);
        goto sembolAyariMenu;
    }
    if(sembolAyariSecimi=='2'){
        semboluDegistir(2);
        goto sembolAyariMenu;
    }

}

}

int klavyeHariciSemboller(int degistirilecekSembol){

    int secilenSembol;

    secilenSembolMenusu:
   system("cls");
printf("\t%d.oyuncu secili.\n",degistirilecekSembol);
printf("\n\n\n");
printf("      0.Geri don                 \t\t\t\t     |     |     \n");
printf("                                 \t\t\t\t  %c  |     |     \n",sembloller[1]);
printf("01)%c  02)%c  03)%c  04)%c           \t\t\t\t_____|_____|_____\n",1,2,3,4);
printf("05)%c  06)%c  07)%c  08)%c           \t\t\t\t     |     |     \n",5,6,14,15);
printf("09)%c  10)%c  11)%c  12)%c           \t\t\t\t     |  %c  |     \n",16,17,18,19,sembloller[2]);
printf("13)%c  14)%c  15)%c  16)%c           \t\t\t\t_____|_____|_____\n",20,21,22,23);
printf("17)%c  18)%c  19)%c  20)%c           \t\t\t\t     |     |     \n",24,25,26,127);
printf("                                 \t\t\t\t  %c  |     |  %c  \n",sembloller[2],sembloller[1]);
printf("                                 \t\t\t\t     |     |     \n");

printf("NOT:Cihazlar arasi bazi ufak farklardan dolayi bazi semboller gorunmeyebilir.\n");
printf("Secmek istediginiz isatertin kodunu tuslayin:");
scanf("%d",&secilenSembol);

switch(secilenSembol)
{
    case 0:
    return 0;

    case 1:
    sembloller[degistirilecekSembol]=1;
    break;

    case 2:
    sembloller[degistirilecekSembol]=2;
    break;

    case 3:
    sembloller[degistirilecekSembol]=3;
    break;

    case 4:
    sembloller[degistirilecekSembol]=4;
    break;

    case 5:
    sembloller[degistirilecekSembol]=5;
    break;

    case 6:
    sembloller[degistirilecekSembol]=6;
    break;

    case 7:
    sembloller[degistirilecekSembol]=14;
    break;

    case 8:
    sembloller[degistirilecekSembol]=15;
    break;

    case 9:
    sembloller[degistirilecekSembol]=16;
    break;

    case 10:
    sembloller[degistirilecekSembol]=17;
    break;

    case 11:
    sembloller[degistirilecekSembol]=18;
    break;

    case 12:
    sembloller[degistirilecekSembol]=19;
    break;

    case 13:
    sembloller[degistirilecekSembol]=20;
    break;

    case 14:
    sembloller[degistirilecekSembol]=21;
    break;

    case 15:
    sembloller[degistirilecekSembol]=22;
    break;

    case 16:
    sembloller[degistirilecekSembol]=23;
    break;

    case 17:
    sembloller[degistirilecekSembol]=24;
    break;

    case 18:
    sembloller[degistirilecekSembol]=25;
    break;

    case 19:
    sembloller[degistirilecekSembol]=26;
    break;

    case 20:
    sembloller[degistirilecekSembol]=127;
    break;

    default:
    printf("Hatali bi secim yaptiniz");
}
goto secilenSembolMenusu;
}

int semboluDegistir(int degistirilecekSembol){

    char sembolAyariSecimi;
    SembolMenusu:

    system("cls");
printf("\t%d.oyuncu secili.\n",degistirilecekSembol);
printf("\n\n\n");
printf("                                 \t\t\t\t     |     |     \n");
printf("0.Geri don                       \t\t\t\t  %c  |     |     \n",sembloller[1]);
printf("1.Klavyeden sembol gir           \t\t\t\t_____|_____|_____\n");
printf("2.Klavye harici semboller        \t\t\t\t     |     |     \n");
printf("                                 \t\t\t\t     |  %c  |     \n",sembloller[2]);
printf("                                 \t\t\t\t_____|_____|_____\n");
printf("                                 \t\t\t\t     |     |     \n");
printf("                                 \t\t\t\t  %c  |     |  %c  \n",sembloller[2],sembloller[1]);
printf("                                 \t\t\t\t     |     |     \n");

while(1)
{
    sembolAyariSecimi=getch();

    if(sembolAyariSecimi=='0')
        return 0;

    if(sembolAyariSecimi=='1'){
        printf("Kullanmak istediginiz sembolu giriniz:");
        scanf(" %c",&sembloller[degistirilecekSembol]);
        goto SembolMenusu;}

    if(sembolAyariSecimi=='2'){
        klavyeHariciSemboller(degistirilecekSembol);
        goto SembolMenusu;}

}
}

int renkAyari(){

char menuSecimi;

renkAyarMenusu:

system("cls");
printf("                                 \t\t\t\t     |     |     \n");
printf("                                 \t\t\t\t  %c  |     |     \n",sembloller[1]);
printf("       0.Geri don                \t\t\t\t_____|_____|_____\n");
printf("       1.Arka plan rengi         \t\t\t\t     |     |     \n");
printf("       2.Yazi rengi              \t\t\t\t     |  %c  |     \n",sembloller[2]);
printf("                                 \t\t\t\t_____|_____|_____\n");
printf("                                 \t\t\t\t     |     |     \n");
printf("                                 \t\t\t\t  %c  |     |  %c  \n",sembloller[2],sembloller[1]);
printf("                                 \t\t\t\t     |     |     \n");
while(1)
{
    menuSecimi=getch();

    if(menuSecimi=='0')
        return 0;

    if(menuSecimi=='1'){
            renkKatalogu(arkaPlan);
    goto renkAyarMenusu;}

    if(menuSecimi=='2'){
        renkKatalogu(yazi);
        goto renkAyarMenusu;}


}
}

int renkKatalogu(int degistirilecekYer){

    char secilenRenk;

    system("cls");
    if(degistirilecekYer==6)
        printf("\t\t\t Arka plan rengi degistiriliyor\n");
    if(degistirilecekYer==7)
        printf("\t\t\t Yazi rengi degistiriliyor\n");
printf("      0.Geri don                 \t\t\t\t     |     |     \n");
printf("1.Mavi           2.Yesil         \t\t\t\t  %c  |     |     \n",sembloller[1]);
printf("3.Su mavisi      4.Kirmizi       \t\t\t\t_____|_____|_____\n");
printf("5.Mor            6.Sari          \t\t\t\t     |     |     \n");
printf("7.Beyaz          8.Gri           \t\t\t\t     |  %c  |     \n",sembloller[2]);
printf("9.Acik mavi      A.Acik yesil    \t\t\t\t_____|_____|_____\n");
printf("B.Acik su mavisi C.Acik kirmizi  \t\t\t\t     |     |     \n");
printf("D.Acik mor       E.Acik sari     \t\t\t\t  %c  |     |  %c  \n",sembloller[2],sembloller[1]);
printf("F.Parlak beyaz   G.Siyah         \t\t\t\t     |     |     \n");

while(1)
{
   secilenRenk=getch();
   secilenRenk=toupper(secilenRenk);
   if(secilenRenk=='0')
    return 0;
   if((secilenRenk>='1'&&secilenRenk<='9')||secilenRenk>='A'&&secilenRenk<='G'){
    if(secilenRenk=='G')
    secilenRenk='0';
   renk[degistirilecekYer]=secilenRenk;
   system(renk);
   }


}
}

int enterBasmaDegistir(){

if(enterBasma==acik){
    enterBasma=kapali;
    return 0;}

if(enterBasma==kapali){
    enterBasma=acik;
    return 0;}
}


