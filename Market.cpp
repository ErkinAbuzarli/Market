#include <iostream>
#include <string>
#include <conio.h> 
#include <limits>


using namespace std;


void clrcin()
{
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


class Market
{
    public:
        int maxRowLength = 100, maxStrLength = -100, malzemeSayi = 16, boslukSayi = 10;
        double toplam = 0;

        double fiyatlar[16] = { 
                            1.5,0.5,1.0,2.0,5.0,
                            1.0,4.0,8.0,2.0,1.5,
                            0.8,1.6,3.5,2.80,3.0,2.5 
                            }; 

        string malzemeler[16] = {
                            "Domates", "Kabak", "Havuc", "Patlican", "Iceberg",
                            "Salatalik", "Marul", "Lahana", "Elma", "Portakal",
                            "Mandalina", "Armut", "Cips", "Kola", "IceTea", "Kek"
                            };

        int sepet[16] = {
                            0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0
                        };

        int sira[16] = {
                            -1, -1, -1, -1, -1,
                            -1, -1, -1, -1, -1,
                            -1, -1, -1, -1, -1, -1
                        };

        void maxStrLengthCal();
        void maxRowLengthCal();
        int urunSayi();


        void printHeader();
        void printFisHeader();
        void printFisFooter();
        void printLine_(string, string); 
        void printBosluk(int);
        void printMalzemeler();
        void printBox();
        void printSepet();

        void malzemeSec();
        void sepeteEkle(int, int);
        void alis_veris();
        void fis();
};








void Market::maxRowLengthCal()
{
    //     numaralandırma alanı           Satirdaki malzeme sayi      Ondeki ve arkadaki bosluklar
    //              v                                v                v
    maxRowLength = (2 + maxStrLength + boslukSayi) * 4 - boslukSayi + 6;
}

void Market::maxStrLengthCal()
{
    for (int i = 0; i < malzemeSayi; i++)
    {
        int s = malzemeler[i].size();
        maxStrLength = s > maxStrLength ? s : maxStrLength;
    }
}

int Market::urunSayi()
{
    int sayi = 0;

    for (int i = 0; i < malzemeSayi; i++)
    {
        if (sepet[i] != 0) sayi++;
    }

    return sayi;
}









void Market::printBosluk(int n)
{
    for (int i = 0; i < n; i++) cout << " ";
}

void Market::printLine_(string s, string end)
{
    cout << end;

    for (int i = 0; i < maxRowLength; i++)
        cout << s;
    
    cout << end << endl;
}




void Market::printHeader()
{
    string urun = "Sepetteki Urun [ " + to_string(urunSayi()) + " ]";
    int yaziBaslangic = maxRowLength - 26;
    cout << " ";

    for (int i = 0; i < maxRowLength; i++)
    {
        if (i == yaziBaslangic) cout << urun;
        else if (i > yaziBaslangic && i < yaziBaslangic + urun.size()) continue;
        else cout << "_";
    }

    cout << endl ;
}

void Market::printFisHeader()
{
    printLine_("_", " ");
    printLine_(" ", "|");
    cout << "|";
    printBosluk(maxRowLength / 2 - 8);
    cout << "Sepetteki Urunler";
    printBosluk(maxRowLength / 2 - 9);
    cout << "|" << endl;
    printLine_("_", "|");
    cout << endl;
}

void Market::printFisFooter()
{
    printLine_("_", " ");
    cout << endl << "   TOPLAM";
    printBosluk(30);
    cout << toplam << " TL" << endl << endl
        << "Cikmak icin Herhangi bir Tusa basin";
    _getch();
}

void Market::printMalzemeler()
{
    bool buIkinciDortmu = false;

    for (int i = 0; i < malzemeSayi +3; i = i + 4)
    {
        i = i % 15;

        if (i == 0)
            if (buIkinciDortmu)
                i = 15;
            else
                buIkinciDortmu = !buIkinciDortmu;
        
        if (i < 4) cout << "|  ";
        cout << i + 1 << "." << malzemeler[i];

        if (i == 8) printBosluk(maxStrLength - malzemeler[i].size() + boslukSayi + 1);
        else if (i < 12) printBosluk(maxStrLength - malzemeler[i].size() + boslukSayi);
        else
        {
            printBosluk(maxStrLength - malzemeler[i].size());
            cout << "  |" << endl;
        }

        if (i == 15) break;
    }
}


void Market::printBox()
{
    system("cls");
    printHeader();
    printLine_(" ", "|");
    printLine_(" ", "|");
    printMalzemeler();
    printLine_(" ", "|");
    printLine_(" ", "|");
    printLine_("_", "|");
}

void Market::printSepet()
{
    int s = urunSayi();

    for (int i = 0; sira[i] != -1; i++)
    {
        int n = sira[i];

        if (sepet[n] != 0)
        {
            double f = fiyatlar[n] * sepet[n];
            toplam += f;
            printBosluk(3);
            cout << malzemeler[n];
            printBosluk(maxStrLength - malzemeler[n].size());
            cout << " x " << sepet[n];
            printBosluk(boslukSayi);
            cout << fiyatlar[n] << " TL x " << sepet[n] << " = " << f << " TL" << endl;
        }
    }
}





void Market::malzemeSec()
{
    while (true)
    {
        int secim = -1;
        int adet = 0;

        cout << "\nMalzeme Secin:";
        if (cin >> secim)
        {
            if (secim > 0 && secim < 17)
            {
                while (true)
                {
                    cout << endl << malzemeler[secim-1] << "(Adet " << fiyatlar[secim-1] << " TL) Adedi Girin:";

                    if (cin >> adet)
                    {
                        sepeteEkle(secim-1, adet);
                        break;
                    }
                    else
                    {
                        cout << "Hatali Bir Islem Yaptiniz. Tekrar Deneyin." << endl << endl;
                        clrcin();
                        continue;
                    }
                }
            }
            else
            {
                cout << "Girdiyiniz Sayi Listede Yok. Tekrar Deneyin." << endl << endl;
                clrcin();
                continue;
            }
                

            break;
        }
        else
        {
            cout << "Hatali Bir Islem Yaptiniz" << endl << endl;
            clrcin();
            continue;
        }
            
    }
}


void Market::sepeteEkle(int secim, int adet)
{
    string str;
    int i = 0;

    if (sepet[secim] != 0) str = "\nUrun Zaten Mevcuttu Miktar bilgisi Guncellendi\n\n";
    else
    {
        str = "\nUrun Sepete Eklendi\n\n";  
        
        while(true)
        {
            if (sira[i] == -1) 
            {
                sira[i] = secim;
                break;
            }
            i++;
        }        
    } 

    sepet[secim] += adet;

    printBox();
    cout << str;
}

void Market::alis_veris()
{
    char g;
    bool devam = true;
    bool hata = false;

    while (devam)
    {
        

        printBox();
        
        if (hata) cout << "\nHatali Bir Islem Yaptiniz\n" << endl;
        else malzemeSec();
        
        hata = false;

        cout << "Baska Urun Eklemek Ister misiniz (y/n)?";
        g = _getch();

        switch (g)
        {
        case 'y':
            break;

        case 'Y':
            break;

        case 'n':
            fis();
            devam = false;
            break;

        case 'N':
            fis();
            devam = false;
            break;

        default:
            hata = true;
            break;
        }
    }
}

void Market::fis()
{
    system("cls");
    maxRowLength = 45 + maxStrLength;
    printFisHeader();
    printSepet();
    printFisFooter();
}




int main()
{
    Market market;

    market.maxStrLengthCal();
    market.maxRowLengthCal();

    market.alis_veris();
}
