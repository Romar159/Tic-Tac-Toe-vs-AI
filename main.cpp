#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


#define TAB_LGNS 3
#define TAB_COLS 3

using namespace std;

int checkState();
void debugAffichageBoard();
void afficherBoard();
int checkResult(int x);
bool drawTab(int x, int player);
void copyBoard2Buff();
void copyBuff2Board();
void couche1_IA();
int couche1_IA_choice();

void couche1_IA_j2();
int couche1_IA_choice_j2();

 // 0: vide | 1: croix | 2: rond.
int board[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };

int bufferBoard[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };

int val_case[9];
int list_zero[9] = {0};
bool debug = false;
bool ia_vs_ia = false;

void debugAffichageBoardBuffer() {
    int i, j;
    for(i=0; i<TAB_LGNS; i++) {
        for(j=0; j<TAB_COLS; j++) {
         cout << " BuffTab[ "<< i << " ][ "<< j << " ] = "<< bufferBoard[i][j] <<endl;
        }
    }
}

int getCaseValueOfBufferBoard(int id) {
    if(id == 1) return bufferBoard[0][0];
    if(id == 2) return bufferBoard[0][1];
    if(id == 3) return bufferBoard[0][2];

    if(id == 4) return bufferBoard[1][0];
    if(id == 5) return bufferBoard[1][1];
    if(id == 6) return bufferBoard[1][2];

    if(id == 7) return bufferBoard[2][0];
    if(id == 8) return bufferBoard[2][1];
    if(id == 9) return bufferBoard[2][2];
}

int getCaseValueOfBoard(int id) {
    if(id == 1) return board[0][0];
    if(id == 2) return board[0][1];
    if(id == 3) return board[0][2];

    if(id == 4) return board[1][0];
    if(id == 5) return board[1][1];
    if(id == 6) return board[1][2];

    if(id == 7) return board[2][0];
    if(id == 8) return board[2][1];
    if(id == 9) return board[2][2];
}

int main() {
    int usr_case = 0;
    bool enchainer = false;
    bool reprendre = true;
    int lastUser = 2;
    int user = 0;
    int choice_menu = 0;

    cout << "Tic Tac Toe VS IA" << endl << "-----------------" << endl << "1. J1 vs IA (default)" << endl << "2. IA VS IA" << endl << "-----------------" << endl;
        cout << "Menu: ";
        cin >> choice_menu;
    
    cout << endl << endl;
    if(choice_menu == 2) ia_vs_ia = true;
    else ia_vs_ia = false;

    cout << "Debug mod ?" << endl << "1.oui" << endl << "2.non (default)" << endl;
    cin >> choice_menu;

    cout << endl << endl;
    if(choice_menu == 1) debug = true;
    else debug = false;

    //afficherBoard(); // première fois


    while(checkResult(checkState()) == 0) {
        enchainer = false;
        afficherBoard();

        while(!enchainer) {
            if(lastUser == 1) user = 2;
            if(lastUser == 2) user = 1;

            if(user == 2) { // IA !
                    cout << "L'IA réfléchi !" << endl;
                while(reprendre) {
                    copyBoard2Buff();
                    couche1_IA();
                    copyBuff2Board();
                    int choice = couche1_IA_choice();
                    

                    if(!drawTab(choice, 2)) {
                        reprendre = true;
                    } else {
                        cout << "L'IA Joue : " << choice << endl;
                        reprendre = false;
                    }
                }

                lastUser = user;
                enchainer = true;
                reprendre = true;
            }

        if(ia_vs_ia == true) {
            if(user == 1) { // IA !
                    cout << "L'IA2 réfléchi !" << endl;
                while(reprendre) {
                    copyBoard2Buff();
                    couche1_IA_j2();
                    copyBuff2Board();
                    int choice = couche1_IA_choice_j2();
                    

                    if(!drawTab(choice, 1)) {
                        reprendre = true;
                    } else {
                        cout << "L'IA2 Joue : " << choice << endl;
                        reprendre = false;
                    }
                }

                lastUser = user;
                enchainer = true;
                reprendre = true;
            }
        } else {
            if(user == 1) { // Joueur
                while(!enchainer) {
                    cout << "Choisissez votre case Joueur " << user << " :";
                    cin >> usr_case;

                    if(usr_case < 1 || usr_case > 9) {
                        enchainer = false;
                    } else {
                        enchainer = drawTab(usr_case, user);
                        lastUser = user;
                    }
                }
            } 
        }
            
        }
    }

    return 0;
}

int checkState() { //1 croix, 2 rond, 0 nulle, -1 pas fini.
    int i, j;
    if(board[0][0] == 1 && board[0][1] == 1 && board[0][2] == 1) return 1;
    if(board[1][0] == 1 && board[1][1] == 1 && board[1][2] == 1) return 1;
    if(board[2][0] == 1 && board[2][1] == 1 && board[2][2] == 1) return 1;
       
    if(board[0][0] == 1 && board[1][0] == 1 && board[2][0] == 1) return 1;
    if(board[0][1] == 1 && board[1][1] == 1 && board[2][1] == 1) return 1;
    if(board[0][2] == 1 && board[1][2] == 1 && board[2][2] == 1) return 1;
       
    if(board[0][0] == 1 && board[1][1] == 1 && board[2][2] == 1) return 1;
    if(board[0][2] == 1 && board[1][1] == 1 && board[2][0] == 1) return 1; // croix gagne


    if(board[0][0] == 2 && board[0][1] == 2 && board[0][2] == 2) return 2;
    if(board[1][0] == 2 && board[1][1] == 2 && board[1][2] == 2) return 2;
    if(board[2][0] == 2 && board[2][1] == 2 && board[2][2] == 2) return 2;
       
    if(board[0][0] == 2 && board[1][0] == 2 && board[2][0] == 2) return 2;
    if(board[0][1] == 2 && board[1][1] == 2 && board[2][1] == 2) return 2;
    if(board[0][2] == 2 && board[1][2] == 2 && board[2][2] == 2) return 2;
       
    if(board[0][0] == 2 && board[1][1] == 2 && board[2][2] == 2) return 2;
    if(board[0][2] == 2 && board[1][1] == 2 && board[2][0] == 2) return 2; // rond gagne

    else {
        for (i=0; i<TAB_LGNS; i++) {
            for (j=0; j<TAB_COLS; j++) {
                if(board[i][j] == 0) return -1; // jeu pas fini.
            }
        }
        return 0; // fini, partie nulle.
    }

}

void debugAffichageBoard() {
    int i, j;
    for(i=0; i<TAB_LGNS; i++) {
        for(j=0; j<TAB_COLS; j++) {
         cout << " tab[ "<< i << " ][ "<< j << " ] = "<< board[i][j] <<endl;
        }
    }
}

void afficherBoard() {
    int i, j;

    cout << "---------" << endl;
    
    for(i=0; i<TAB_LGNS; i++) {
        for(j=0; j<TAB_COLS; j++) {
            if(board[i][j] == 0) cout << " * ";
            if(board[i][j] == 1) cout << " X ";
            if(board[i][j] == 2) cout << " O ";
            if(i == 0 && j == 2) cout << endl;
            if(i == 1 && j == 2) cout << endl;
            if(i == 2 && j == 2) cout << endl;
        }
    }

    cout << "---------" << endl;
}

int checkResult(int x) {
    if(x == -1) return 0; // rien
    
    afficherBoard();
    if(x == 1) cout << "Le Joueur 1 Gagne. (Croix)" << endl;
    if(x == 2) cout << "Le Joueur 2 Gagne. (Rond)" << endl;
    if(x == 0) cout << "Partie nulle." << endl;
    return 1;
}

bool drawTab(int x, int player) { // récupère l'entrée et remplie le plateau de jeu (player contient une valeur entre 1 et 2 pour croix et rond)

    switch(x) {
        case 1:
            if(board[0][0] != 0) {
                if(ia_vs_ia == false && player == 1)
                    cout << "Cette case est déjà pleine." << endl;
                return false;
            } else {
                board[0][0] = player;
                return true;
            }
            

        break;
        case 2:
            if(board[0][1] != 0) {
                if(ia_vs_ia == false && player == 1)
                    cout << "Cette case est déjà pleine." << endl;
                return false;
            } else {
                board[0][1] = player;
                return true;

            }
        
        break;
        case 3:
            if(board[0][2] != 0) {
                if(ia_vs_ia == false && player == 1)
                    cout << "Cette case est déjà pleine." << endl;
                return false;;
            } else {
                board[0][2] = player;
                return true;
            }
        
        break;

        case 4:
            if(board[1][0] != 0) {
                if(ia_vs_ia == false && player == 1)
                    cout << "Cette case est déjà pleine." << endl;
                return false;
            } else {
                board[1][0] = player;
                return true;
            }
        
        break;
        case 5:
            if(board[1][1] != 0) {
                if(ia_vs_ia == false && player == 1)
                    cout << "Cette case est déjà pleine." << endl;
                return false;
            } else {
                board[1][1] = player;
                return true;
            }
        
        break;
        case 6:
            if(board[1][2] != 0) {
                if(ia_vs_ia == false && player == 1)
                    cout << "Cette case est déjà pleine." << endl;
                return false;
            } else {
                board[1][2] = player;
                return true;
            }
        
        break;
        
        case 7:
            if(board[2][0] != 0) {
                if(ia_vs_ia == false && player == 1)
                    cout << "Cette case est déjà pleine." << endl;
                return false;
            } else {
                board[2][0] = player;
                return true;
            }
        
        break;
        case 8:
            if(board[2][1] != 0) {
                if(ia_vs_ia == false && player == 1)
                    cout << "Cette case est déjà pleine." << endl;
                return false;
            } else {
                board[2][1] = player;
                return true;
            }
        
        break;
        case 9:
            if(board[2][2] != 0) {
                if(ia_vs_ia == false && player == 1)
                    cout << "Cette case est déjà pleine." << endl;
                return false;
            } else {
                board[2][2] = player;
                return true;
            }
            
        break;
    }
}

void copyBoard2Buff() {
    int i, j;

    for(i=0; i<3; i++) {
        for(j=0; j<3; j++) {
            bufferBoard[i][j] = board[i][j]; 
        }
    }
}

void copyBuff2Board() {
    int i, j;

    for(i=0; i<3; i++) {
        for(j=0; j<3; j++) {
            board[i][j] = bufferBoard[i][j]; 
        }
    }
}

void couche1_IA() {
    int x, y, case_count = 0;
    for(x=0; x<3; x++) {
        for(y=0; y<3; y++) {

            case_count++;
            if(board[x][y] == 0) { //Si la case est vide
                drawTab(case_count, 1);

                if(checkState() == 1) val_case[case_count - 1] = -1000;
                if(checkState() == 2) val_case[case_count - 1] = 1000;
                if(checkState() == -1) val_case[case_count - 1] = 0;
                if(checkState() == 0) val_case[case_count - 1] = 0;

                copyBuff2Board();
                
            }   
        }
    }

    // check si l'IA peut gagner
    case_count = 0;
    for(x=0; x<3; x++) {
        for(y=0; y<3; y++) {

            case_count++;
            if(board[x][y] == 0) { //Si la case est vide
                drawTab(case_count, 2);

                
                if(checkState() == 2) val_case[case_count - 1] = 1000;
                

                copyBuff2Board();
                
            }   
        }
    }

    if(debug) {
        for(int ww=0; ww<9; ww++) {
            cout << "VAL CASE: " << val_case[ww] << endl;
        }
    }
}

int couche1_IA_choice() {
    int x = 0;
    int losing_case = 0;

    int final_choice = 0;
    bool doit_def = false;

    for(int i=0; i<9; i++) {
        int valBuff = getCaseValueOfBufferBoard(i + 1);
        if(debug) cout << "buffboard: [" << i << "] " << valBuff << endl;
        if(val_case[i] == 1000 && valBuff == 0) {
            final_choice = i + 1; /*return i + 1;*/ // gagnant pour l'IA !
            return final_choice;
        }
        if(val_case[i] == -1000 && valBuff == 0) {
            if(debug) cout << "Va perdre. " << endl;
            losing_case = i + 1;
            //return losing_case;
            final_choice = losing_case;
            doit_def = true;
        } 
        if(val_case[i] == 0) {
            list_zero[x] = i + 1; // stock dans list_zero, toutes les cases avec la valeur 0 comme priorité !
            x++;
        }  
    }

    if(doit_def) return final_choice;

    /* for(int w=0; w<9; w++) {
        cout << "LIST ZERO: " << list_zero[w] << endl;
    } */

    srand(time(NULL));
    int min = 0;
    int max = 8;
    int random_case = min + rand() % (max + 1 - min);

    if(list_zero[0] == 0) { // aucune autre possibilité que la défaite !
        return losing_case;
    } else {
        if(debug) cout << "random: " << random_case << endl;
        return list_zero[random_case];
    }
}



// IA VS IA

void couche1_IA_j2() {
    int x, y, case_count = 0;
    for(x=0; x<3; x++) {
        for(y=0; y<3; y++) {

            case_count++;
            if(board[x][y] == 0) { //Si la case est vide
                drawTab(case_count, 2);

                if(checkState() == 2) val_case[case_count - 1] = -1000;
                if(checkState() == 1) val_case[case_count - 1] = 1000;
                if(checkState() == -1) val_case[case_count - 1] = 0;
                if(checkState() == 0) val_case[case_count - 1] = 0;

                copyBuff2Board();
                
            }   
        }
    }

    // check si l'IA peut gagner
    case_count = 0;
    for(x=0; x<3; x++) {
        for(y=0; y<3; y++) {

            case_count++;
            if(board[x][y] == 0) { //Si la case est vide
                drawTab(case_count, 1);

                
                if(checkState() == 1) val_case[case_count - 1] = 1000;
                

                copyBuff2Board();
                
            }   
        }
    }
    if(debug) {
        for(int ww=0; ww<9; ww++) {
            cout << "VAL CASE: " << val_case[ww] << endl;
        }
    }
}

int couche1_IA_choice_j2() {
    int x = 0;
    int losing_case = 0;

    int final_choice = 0;
    bool doit_def = false;

    for(int i=0; i<9; i++) {
        int valBuff = getCaseValueOfBufferBoard(i + 1);
        if(debug) cout << "buffboard: [" << i << "] " << valBuff << endl;
        if(val_case[i] == 1000 && valBuff == 0) {
            final_choice = i + 1; /*return i + 1;*/ // gagnant pour l'IA !
            return final_choice;
        }
        if(val_case[i] == -1000 && valBuff == 0) {
            if(debug) cout << "Va perdre. " << endl;
            losing_case = i + 1;
            //return losing_case;
            final_choice = losing_case;
            doit_def = true;
        } 
        if(val_case[i] == 0) {
            list_zero[x] = i + 1; // stock dans list_zero, toutes les cases avec la valeur 0 comme priorité !
            x++;
        }  
    }

    if(doit_def) return final_choice;

    /* for(int w=0; w<9; w++) {
        cout << "LIST ZERO: " << list_zero[w] << endl;
    } */

    srand(time(NULL));
    int min = 0;
    int max = 8;
    int random_case = min + rand() % (max + 1 - min);

    if(list_zero[0] == 0) { // aucune autre possibilité que la défaite !
        return losing_case;
    } else {
        if(debug) cout << "random: " << random_case << endl;
        return list_zero[random_case];
    }
}