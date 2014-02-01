#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

#define INPUT 1  
#define NORM 2
#define MANCALA 3
#define GOAGAIN 4  
#define ENDTURN 5
#define MENU 6  

int board[3][7]; //papan permainan
int whattodo = 1; //menampung apa yang akan dilakukan selama permainan
int moves; //banyak pergerakan yang tersisa 
char slotent[5]; //inputan pemain
bool empty = true; //digunakan untuk mengecek apakan papan kosong
int turnnumber;  //giliran jalan
int goagain; //digunakan agar pemain bisa jalan lagi, bila memungkinkan
char menuoption[2]; //nomor pilihan menu
char namesquestion; //menanyakan apakan akan memasukkan nama pemain? (Y/T)
char playagain[10]; //menanyakan apakan akan main lagi? (Y/T)
char playernames [2][20]; //nama pemain 
char menureturnquestion; //verifikasi untuk kembali ke menu
int numseed = 6; //banyaknya biji yang digunakan pada awal permainan
int caseworking; //digunakan dalam switch
int currentside = 1; //memastikan sisi yang digunakan untuk looping permainan
int currentslot; //memastikan lubang yang digunakan untuk looping permainan


void output (void);
void loadoptions(void);
int slotquestion();
int norm();
int mancala();
int slot6();
int goagainfunc();
void swapside();
bool emptytest();

int main(int argc, char *argv[])
{
    menu:
    system("cls");
    cout << "::: CONGKLAK :::\n";
    cout << "================\n\n";
    cout << "1. Main\n";
    cout << "2. Keluar\n\n";
    cout << "================\n\n";
    cout << "Masukkan Pilihan Anda : ";
    cin >> menuoption;
    
    caseworking = atoi (menuoption);    
    switch (caseworking) {
    case 1: 
               goto start; break;
    case 2: 
               return(0); break;          
    default:
               cout << "Pilihan Yang Anda Masukkan Salah !" << endl << endl;
               goto menu;
    }
    
    // ************ MULAI PERMAINAN ***********
    start:
    whattodo = INPUT;
    turnnumber = 1;
    currentside = 1;
    empty = true; 
    goagain = 0;  
    
    for (int cp = 1; cp <= 2; cp++){  //inisialisasi papan permainan
        for (int cs= 1; cs <= 6; cs++){ //cp merupakan pencacah sisi pemain dan cs merupakan pencacah lubang
            board[cp][cs]= numseed;
            }
        }
    board[1][0] = board[2][0] = 0;  
    cout << "Masukkan Nama Pemain? (Y/T) Ya, Tidak : ";
    cin >> namesquestion;
    namesquestion = toupper (namesquestion);
    if (namesquestion == 'Y') {
                      enternames:  
                      cout << "Masukkan Nama Pemain Pertama : "; 
                      cin.getline (playernames[0], 20);
                      cin.getline (playernames[0], 20);
                      cout << "Masukkan Nama Pemain Kedua   : ";
                      cin.getline (playernames[1], 20);
                      if (0 == strcmp(playernames[0], playernames[1])) {  //digunakan untuk mengecek bila nama 2 pemain sama
                            cout << "Nama Pemain Tidak Boleh Sama!" << endl;
                            goto enternames;
                            }
                      }
    else if (namesquestion == 'T') { //mengisi otomatis nama pemain bila pemain tidak memasukkan nama
         strcpy (playernames[0], "Pemain 1");
         strcpy (playernames[1], "Pemain 2");
         }
    else {
         cout << "Pilihan Yang Anda Masukkan Salah!" << endl;
         }        

    system("cls");
    cout << endl;
    cout << ":::: SELAMAT BERMAIN CONGKLAK ::::\n";
    cout << "==================================\n";
    cout << "*Tekan Angka 0 Untuk Kembali ke Menu !*" << endl;
    cout << endl;
    output();
    cout << endl;

    //***************** LOOPING PERMAINAN ****************
    
    while (empty == true) {  //perulangan sampai satu sisi kosong
        if (currentslot == 7 && whattodo !=  MENU) whattodo = MANCALA;
        switch (whattodo) {
               case INPUT:        
                    slotquestion();
                    break;
               case NORM:    
                    norm();
                    break;
               case MANCALA:
                    mancala();
                    break;
               case GOAGAIN: 
                    if (emptytest() == false) continue;
                    goagainfunc();             
                    break;     
               case ENDTURN:
                    output();
                    cout << endl;
                    turnnumber = abs(turnnumber - 3);
                    currentside = turnnumber; 
                    whattodo = INPUT;
                    if (emptytest() == false) continue; 
                    break;
               case MENU:
                    goto menu;
                    break;
               }
        } 
    //**************************************************
          
    output ();
    cout << endl;
    if (board[1][0] == board[2][0]) cout << "Seri" << endl;
    else
        if (board[2][0] > board[1][0]) {
             cout << playernames[1]<< " Menang\n";
             }
        else 
           if (board[1][0] > board[2][0]) {
             cout << playernames[0] << " Menang\n";
             }     
         
         //********** AKHIR PERMAINAN **********
         cout << playernames[0] << " " << board[1][0] << "\n" << playernames[1] << " " <<board[2][0] << endl;
         cout << "Kembali ke Menu? (Y/T) Ya, Tidak : ";
         cin.getline (playagain, 10);
         cin.getline (playagain, 10);
         if (0 == strcmp(playagain, "Y")) goto menu;
         else {
              system("PAUSE");
              return (0);
         }
         
    system("PAUSE");
    return EXIT_SUCCESS;
}

void output (void) //papan permainan
{
    int pit;
    cout << "  ";
    for (pit = 1; pit <= 6; pit++) { //sisi 1 (atas)
        cout << board[1][pit];
        if (board[1][pit] < 10) cout << "  ";
        else cout << " ";
        }
    cout  << endl << board[2][0] << "                  " << board[1][0] << endl << "  "; //lubang induk
    for (pit = 1; pit <= 6; pit++) { //sisi 2 (bawah)
        cout << board[2][abs(pit - 7)];
        if (board[2][abs(pit - 7)] < 10) cout << "  ";
        else cout << " ";
        }
}

int slotquestion() {
    cout << playernames[turnnumber - 1] << endl;        
    slotent:
          cin >> slotent;
          currentslot = atoi (slotent);
          switch (currentslot) {
          case 0: 
               cout << "Main Lagi? (Y/T) Ya, Tidak" << endl;
               cin >> menureturnquestion;
               menureturnquestion = toupper (menureturnquestion);
               if ((menureturnquestion == 'T') || (menureturnquestion == 't')) {
                  whattodo = MENU;
                  return(whattodo);
                  }
               else 
                   if ((menureturnquestion == 'Y') || (menureturnquestion == 'y')) {
                    output ();
                    cout << endl;
                    goto slotent;
                   }
          default:  
              if (turnnumber == 2) currentslot = abs(currentslot-7);  
              if (board[turnnumber][currentslot] == 0 || atoi (slotent) > 6) {
                 cout << "*Lubang Yang Anda Pilih Salah / Kosong.. Ulangi!*\n";
                 goto slotent;
                 }
              moves = board[turnnumber][currentslot];
              board[turnnumber][currentslot] = 0;
              if (currentslot == 6) {
                              whattodo = MANCALA;
                              return(whattodo);
                              }
              else {
                   whattodo = NORM;    
                   currentslot++;
                   }
          } 
      }     
int norm(){     
     if (moves == 0) {
               whattodo = ENDTURN;
               return(whattodo);
               }
         if (moves == 1) { //jika lubang kosong, jatuhkan biji giliran berakhir
               if (currentside != turnnumber) {
                   board[currentside][currentslot]++;
                   whattodo = ENDTURN;
                   return(whattodo);
                   }
               else if (board[turnnumber][currentslot] == 0) {
                      board[currentside][currentslot]++;
                      whattodo = ENDTURN;
                      return (whattodo);
                      }
               else { //ambil biji dan maju terus ke lubang berikutnya
                    moves = board[currentside][currentslot] + 1;
                    board[currentside][currentslot] = 0;
                    currentslot++;
                    return(whattodo);
                    }
               }
         else {
              board[currentside][currentslot]++;
              moves--;
              currentslot++;
             }
     }
int mancala(){
     currentslot = 1;
     moves--;
     if (turnnumber == currentside) {
        board[currentside][0]++;       
        switch(moves) {
            case 0:
               if (turnnumber == currentside) {
               goagain = turnnumber;
               whattodo = GOAGAIN;
               }
               else whattodo = ENDTURN;
               return(whattodo);
            default:
               swapside();
               whattodo = NORM;
               return(whattodo);
             }
        }
     else {
     whattodo = NORM; 
     moves++; 
     swapside();
     }
     }
int goagainfunc() {
    output();
    turnnumber = goagain;
    goagain = 0;
    whattodo = INPUT;
    cout << endl << "***********LAGI**********" << endl;
}
void swapside () {
     currentside = abs(currentside -3);  //ganti sisi
}
bool emptytest () {
     int count1, count2;
     for (count1 = 1; count1 <= 2; count1++){
         empty = 0; //mereset, sehingga selanjutnya akan dicek lagi 
         for (count2= 1; count2 <= 6; count2++){
             empty += board[count1][count2];
             }
             
     if (empty == 0) return false; //mengecek papan kosong       
     }
     
     return true;
}



