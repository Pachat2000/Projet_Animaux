#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <exception>
#include <stdexcept>
#include <stdlib.h> 
#include <chrono>
#include <thread>


using namespace std;

enum Animaux{
    vide=1,
    herbe=2,
    mineraux=3,
    loup=4,
    mouton=5,
};

class Objet{
    public:
    Objet(){};
    virtual int QuiSuisJe(){
        return -1;
    }
    virtual int getTherbe(){
        return -1;
    }
    virtual int getAge(){
        return -1;
    }
    virtual  void Sacoupleto0(){
    }
    virtual int getposx(){
        return -1;
    }
    virtual int getposy(){
        return -1;
    }
    virtual void incrfamnie(){
    }
    virtual void incrSacouple(){
    }
    virtual void increTherber(){
    }
    virtual void incrAge(){
    }
    virtual void incrjaster(){
    }
    virtual int getfamine(){
        return -1;
    }
    virtual void editActionto0(){}
    virtual void deplacement(vector<vector<Objet*>> &terrain,int MaxUx, int MaxUy)=0;
    virtual int Sacouple(){
        return -1;
    }
    virtual void enfant(vector<vector<Objet*>> &terrain,vector<vector<int>> tab){}
    virtual string getsexe(){
        string a;
        return a;
    }

    virtual int getjaster(){
        return -1;
    }
    virtual void editjaster(){
    }

    virtual void editAction(){}
    virtual int getAction(){
        return -1;
    }
    virtual vector<vector<int>> place_libre(int id,vector<vector<Objet*>> &terrain,int MaxUx, int MaxUy){
        vector<vector<int>> p ;
        return p;
    }
    virtual vector<vector<int>> place_libre_acouchement(vector<vector<Objet*>> &terrain,int MaxUx, int MaxUy){
        vector<vector<int>> p ;
        return p;
    }
    virtual void manger(vector<vector<Objet*>> &terrain, vector<vector<int>>tab,vector<vector<Objet*>> &nbanimaux){}
    virtual void editcouple(){}
};

class Vide: public Objet{
    private:
    int id;
    public:
    void deplacement(vector<vector<Objet*>> &terrain,int MaxUx, int MaxUy){}
    Vide(){
        id = vide;
    }
    int QuiSuisJe(){
        return id;
    }
};

class Pose: public Objet{
    protected:
    int posx, posy;
    public:

    int action; // variable pour verifier si l'animal a  deja agi durant le tours
    int sacouple; // immobilise pendant 1 tour si il sont entrain de s'accouplé
    int jasteter; // variable qui dit quand l'animal a le droit de s'accoupler (5)

    Pose(int Posx, int Posy,int Sacouple):posx(Posx),posy(Posy),sacouple(Sacouple),action(0){}

    int getposx(){
        return posx;
    }
    int getposy(){
        return posy;
    }

    int Sacouple(){
        return sacouple;
    }
    void Sacoupleto0(){
        sacouple = 0;
    }
    void incrSacouple(){
        sacouple++;
    }
    void editAction(){
        action = 1;
    } 
    void editActionto0(){
        action = 0;
    } 
    int getAction(){
        return action;
    }
    int getjaster(){
        return jasteter;
    }
    void incrjaster(){
        jasteter++;
    }
    void editjaster(){
        jasteter = 0;
    }
    vector<vector<int>> place_libre_acouchement(vector<vector<Objet*>> &terrain,int MaxUx, int MaxUy){
        vector<int> p ;
        vector<vector<int>> resulta;
        for (int i = -1; i <= 1; i++) {
            for (int y = -1; y <=1; y++) {
                if (i ==0 && y ==0) {
                    
                }
                else {
                    if((y+posx>0 &&y+posx<MaxUx) && (i+posy>0 &&i+posy<MaxUy) && (terrain[posy+ i][posx +y]->QuiSuisJe() == vide  || terrain[posy+ i][posx +y]->QuiSuisJe() == herbe)){
                        p.push_back(posy+ i);
                        p.push_back(posx+ y);
                        resulta.push_back(p);  
                    } 
                }
            }
        }
        return resulta;
    }

    vector<vector<int>> place_libre(int id,vector<vector<Objet*>> &terrain,int MaxUx, int MaxUy){ // renvoie un vecteur avec les pos de place libre
        vector<int> p ;
        vector<vector<int>> resulta;
        for (int i = -1; i <= 1; i++) {
            for (int y = -1; y <=1; y++) {
                if (i ==0 && y ==0) {
                    
                }
                else {
                    if((y+posx>0 &&y+posx<MaxUx) && (i+posy>0 &&i+posy<MaxUy) && terrain[posy+ i][posx +y]->QuiSuisJe() == id){
                        p.push_back(posy+ i);
                        p.push_back(posx+ y);
                        resulta.push_back(p);  
                    } 
                }
            }
        }
        return resulta;
    }

    void deplacement(vector<vector<Objet*>> &terrain,int MaxUx, int MaxUy){ // permet de faire les deplacement des animaux(aléatoire)

        int nposx = (rand()%3)-1;
        int nposy = (rand()%3)-1;
        if ((terrain[posy][posx]->Sacouple()) ==2 ) {
            return;
        }

        if ( (nposx+posx>=0 &&nposx+posx<MaxUx) &&(nposy+posy>=0 &&nposy+posy<MaxUy)) {
            if (terrain[posy][posx]->getAction() == 0 && terrain[posy+nposy][posx+nposx]->QuiSuisJe() != mouton && terrain[posy+nposy][posx+nposx]->QuiSuisJe() != loup && terrain[posy+nposy][posx+nposx]->QuiSuisJe() != mineraux) {
                terrain[posy][posx]->editAction();
                terrain[posy].erase(begin(terrain[posy]) + posx );
                terrain[posy].insert( begin(terrain[posy]) + posx , new Vide());
                terrain[posy + nposy].erase(begin(terrain[posy + nposy]) + (posx + nposx));
                terrain[posy + nposy].insert( begin(terrain[posy + nposy]) + (posx + nposx),this);
                posx = nposx+posx;
                posy = nposy+posy;   
            }
        }else{
            return; // reste immobile si le resulta est en dehors de l'Univer 
        }
    }
};


class Mineraux: public Objet{
    private:
    int id;
    int Therbe; // temp avant qu'il se transforme en herbe
    int posx, posy; // pose du minerai
    public:
    int getposx(){
        return posx;
    }
    int getposy(){
        return posy;
    }
    void deplacement(vector<vector<Objet*>> &terrain,int MaxUx, int MaxUy){}
    Mineraux(int x, int y){
        posx = x;
        posy = y;
        Therbe = 0;
        id = mineraux;
    }
    int QuiSuisJe(){
        return id;
    }
    int getTherbe(){
        return Therbe;
    }
    void increTherber(){
        Therbe++;
    }
};

class Loup:public Pose{
     private:
    int age; // 60 tours avant de mourir de viellesse
    int famine; // 10 tours avant de mourir de famine

    public:
    string sexe;
    int id;
    Loup(int pox,int poy,string Sexe): Pose(pox, poy,0){
        sexe= Sexe;
        id = loup;
        age = 0;
        famine = 0;
    }
    void editcouple(){
        sacouple = 1;
    }
    string getsexe(){
        return sexe;
    }
    int getfamine(){
        return famine;
    }
    void incrfamnie(){
        famine++;
    }

    void incrAge(){
        age++;
    }

    int getAge(){
        return age;
    }

    

    void manger(vector<vector<Objet*>> &terrain, vector<vector<int>>tab,vector<vector<Objet*>> &nbanimaux){ 
        if (tab.size() == 0) {
            return;
        }
        else{
            if (sacouple == 0 && action == 0) {//si il n'a pas fait d'action et qu'il n'est pas deja en couple
                int random = (rand() % tab.size()) -1;
                if(random == -1){
                    random =0;
                }
                for (int i = 0;  i <nbanimaux[mouton-1].size(); i++){// on efface le mouton du tab des animaux
                    if (nbanimaux[mouton-1][i]->getposy() == tab[random][0] &&nbanimaux[mouton-1][i]->getposx()== tab[random][1] ) {
                        nbanimaux[mouton-1].erase(begin(nbanimaux[mouton-1])+ i);
                    }
                }// on insère le mineraux a la pos de l'animal mort
                terrain[tab[random][0]].erase(begin(terrain[tab[random][0]]) +tab[random][1]);
                Mineraux* lo = new Mineraux(tab[random][1],tab[random][0]);
                nbanimaux[lo->QuiSuisJe()-1].push_back(lo);
                terrain[tab[random][0]].insert(begin(terrain[tab[random][0]]) +tab[random][1],lo);
                famine = 0; // on remet la famine a 0
                action =1;  // et on dit qu'il a fait une action
            }
        }
    }
    void enfant(vector<vector<Objet*>> &terrain,vector<vector<int>> tab){ // on met sacouple a 1 au tours suivant il sera incrémenter a 2 et un enfant naitra
        if (tab.size() == 0) { // tab potentiel acouplement dispo adjacent
            return;
        }
        if (action ==0 &&jasteter>=5 && sacouple==0) { //si il n'a pas fait d'action et qu'il n'est pas deja en couple
            for (long unsigned int i = 0; i < tab.size(); i++) { // on choisi en random le sexe de l'enfant
               if(terrain[tab[i][0]][tab[i][1]]->getAction() == 0 &&  terrain[tab[i][0]][tab[i][1]]->Sacouple()== 0 && terrain[tab[i][0]][tab[i][1]]->getjaster() >=5){
                   if (sexe == "male" && terrain[tab[i][0]][tab[i][1]]->getsexe() =="femelle") {
                        sacouple = 1;
                        action = 1;

                        terrain[tab[i][0]][tab[i][1]]->editcouple();
                        terrain[tab[i][0]][tab[i][1]]->editAction();
                        return;
                   }
                   else if (sexe == "femelle" && terrain[tab[i][0]][tab[i][1]]->getsexe() =="male") {
                        sacouple = 1;
                        action = 1;

                        terrain[tab[i][0]][tab[i][1]]->editcouple();
                        terrain[tab[i][0]][tab[i][1]]->editAction();
                        return;
                   }
                   else {
                    
                   }
               }
            }
        }
    }

    int QuiSuisJe(){
        return id;
    }
};
class Mouton:public Pose{
    private:
    int age; // durée de vie de l'animal 50 ans
    int famine; // meurt si il mange pas au 5ème tours

    public:
    string sexe;
    int id;
    Mouton(int pox,int poy,string Sexe): Pose(pox, poy,0){
        sexe= Sexe;
        id = mouton;
        age = 0;
        famine = 0;
    }
    int QuiSuisJe(){
        return id;
    }
    string getsexe(){
        return sexe;
    }
    int getAge(){
        return age;
    }
    int getfamine(){
        return famine;
    }

    void editcouple(){
        sacouple = 1;
    }
    void incrfamnie(){
        famine++;
    }

    void incrAge(){
        age++;
    }

    void manger(vector<vector<Objet*>> &terrain, vector<vector<int>>tab,vector<vector<Objet*>> &nbanimaux){
        if (tab.size() == 0) {
            return;
        }
        else{
            if (sacouple == 0 && action == 0) {//si il n'a pas fait d'action et qu'il n'est pas deja en couple
                int random = (rand() % tab.size()) -1;
                if (random == -1) {
                    random =0;
                }// on insère le vide a la pos de de l'herbe
                terrain[tab[random][0]].erase(begin(terrain[tab[random][0]]) +tab[random][1]);
                terrain[tab[random][0]].insert(begin(terrain[tab[random][0]]) +tab[random][1],new Vide());
                famine = 0; // on remet la famine a 0
                action =1;  // et on dit qu'il a fait une action 
            }
        }
    }
    void enfant(vector<vector<Objet*>> &terrain,vector<vector<int>> tab){ // on met sacouple a 1 au tours suivant il sera incrémenter a 2 et un enfant naitra
        if (tab.size() == 0) { // tab potentiel acouplement dispo adjacent
            return;
        }
        if (action ==0 &&jasteter>=5 && sacouple==0) {//si il n'a pas fait d'action et qu'il n'est pas deja en couple
            for (long unsigned int i = 0; i < tab.size(); i++) { // on choisi en random le sexe de l'enfant
               if(terrain[tab[i][0]][tab[i][1]]->getAction() == 0 &&  terrain[tab[i][0]][tab[i][1]]->Sacouple()== 0 && terrain[tab[i][0]][tab[i][1]]->getjaster() >=5){
                   if (sexe == "male" && terrain[tab[i][0]][tab[i][1]]->getsexe() =="femelle") {
                        sacouple = 1;
                        action = 1;

                        terrain[tab[i][0]][tab[i][1]]->editcouple(); // on met a la variable acouple du femelle
                        terrain[tab[i][0]][tab[i][1]]->editAction(); // on dit qu'il a fait une action du femelle
                        return;
                   }
                   else if (sexe == "femelle" && terrain[tab[i][0]][tab[i][1]]->getsexe() =="male") {
                        sacouple = 1;
                        action = 1;

                        terrain[tab[i][0]][tab[i][1]]->editcouple();// on met a la variable acouple de la male
                        terrain[tab[i][0]][tab[i][1]]->editAction(); // on dit qu'il a fait une action de la male
                        return;
                   }
                   else {
                    
                   }
               }
            }
        }
    }

};


class Herbe: public Objet{ 
    private:
    int id;
    public:
    void deplacement(vector<vector<Objet*>> &terrain,int MaxUx, int MaxUy){}
    Herbe(){
        id = herbe;
    }
    ~Herbe(){
        delete [] this;
    }
    int QuiSuisJe(){
        return id;
    }
};

class Univer{
    
    protected:
    int tour; // nombre de tour de l'univer
    vector<vector<Objet*>> terrain; // l'univer en question
    vector<vector<Objet*>> nbanimaux;
    int casx, casy;
    public:
    Univer(int nb_mouton, int nb_loup, int Xcase, int Ycase){
        if (nb_mouton + nb_loup > Xcase*Ycase) { // renvoie un exeption
            throw invalid_argument("le nombre d'animaux dépace la taille de l'univers");; // lance une exeption car les valeur rentré sont faut 
        }
        else{
            
            vector<Objet*> tmp(Xcase,new Herbe()); //je remplie les terrain d'herbe initialement 
            vector<vector<Objet*>> tmp2(Ycase, tmp);

            vector<Objet*> xp;
            vector<vector<Objet*>> xp2(5,xp);

            casx = Xcase;
            casy = Ycase;
            srand (time (0)); 
            while (nb_mouton != 0 || nb_loup != 0) {
                int randx = rand()%Xcase;
                int randy = rand()%Ycase;
                // on choisie le sexe de l'animal au hasard
                if (randx == -1) {
                    randy = 0;
                }
                if ( randy == -1) {
                    randy = 0;
                }
                string sexe;
                if (randx%2 == 0) {
                    sexe = "male";
                }
                else if(randx%2 == 1) {
                     sexe = "femelle";
                }
                
                if (nb_mouton ==0 && nb_loup != 0) {
                    
                    if (tmp2[randy][randx]->QuiSuisJe() == loup || tmp2[randy][randx]->QuiSuisJe() == mouton) {
                        
                    }
                    else {
                        Loup * lo= new Loup(randx,randy,sexe); // on insere un loup
                        xp2[lo->QuiSuisJe()-1].push_back(lo);
                        tmp2[randy].erase(tmp2[randy].begin() + randx);
                        tmp2[randy].insert(tmp2[randy].begin() + randx, lo);
                        nb_loup --;  
                    }
                }
                else {
                    if (tmp2[randy][randx]->QuiSuisJe() == mouton || tmp2[randy][randx]->QuiSuisJe() == loup) {
                        
                    }
                    else{ // on insere un mouton
                        Objet * lo = new Mouton(randx,randy,sexe);
                        xp2[lo->QuiSuisJe()-1].push_back(lo);
                        tmp2[randy].erase(tmp2[randy].begin() + randx);
                        tmp2[randy].insert(tmp2[randy].begin() + randx, lo);
                        nb_mouton --; 
                    }
                }
            }
            nbanimaux = xp2;
            terrain = tmp2;
            tour = 0;
            
        }
    }

    void affiche(){ // affiche le terrain
        cout << "   " ; 
        for (int i = 1; i <= casx ; i++) {
            cout <<i << "     " ; 
        }
        cout <<endl;
        for (int i = 1; i <= casx; i++) {
            cout <<" +---+" ; 
        }
        cout <<endl;
        for (int i = 1,c= 0; i <= casy; i++,c++) {
            cout <<i ; 
            for(int y = 0; y < casx; y++){
                if (terrain[c][y]->QuiSuisJe() == vide) {
                    cout <<"|  V  " ;
                }
                if (terrain[c][y]->QuiSuisJe() == loup) {
                    cout <<"|  L  " ;
                }
                if (terrain[c][y]->QuiSuisJe() == mouton) {
                    cout <<"|  M  " ;
                }
                if (terrain[c][y]->QuiSuisJe() ==mineraux) {
                    cout <<"|  S  " ;
                }
                if (terrain[c][y]->QuiSuisJe() == herbe) {
                    cout <<"|  H  " ;
                } 
            }
            cout <<endl;
            for (int i = 1; i <= casx; i++) {
                cout <<" +---+" ; 
            }
            cout <<endl;
        }
        cout <<endl;
        cout << "Tour " << tour<< " | Loups : " <<nbanimaux[loup-1].size() << " | Moutons : " << nbanimaux[mouton-1].size()  <<endl;
    }

    void deplacerAnimaux(){ // fonction pour deplacer les animaux
       
        for (int i = 3; i <=4; i++) {
            for (long unsigned int y= 0; y <nbanimaux[i].size(); y++) {
                (nbanimaux[i][y])->deplacement(terrain,casx,casy);
            }
        }
    }

    void accoupleAnimaux(){ // fonction pour le loup
        for (int i = 3; i <=4; i++) {
            for (long unsigned int y= 0; y <nbanimaux[i].size(); y++) {
                if ( i ==loup-1) { // loup
                    vector<vector<int>> resulta = (nbanimaux[i][y])->place_libre(loup,terrain,casx,casy);
                    (nbanimaux[i][y])->enfant(terrain,resulta);
                }
                else { //mouton
                    vector<vector<int>> resulta =(nbanimaux[i][y])->place_libre(mouton,terrain,casx,casy);
                    (nbanimaux[i][y])->enfant(terrain,resulta);
                }
            }
        }
    }


    void verifall(){ //verifie l'ensemble de l'univer
        for (int i = 2; i <=4; i++) {
            for (long unsigned int y= 0; y <nbanimaux[i].size(); y++) {
                if (i ==loup-1 && nbanimaux[i][y]->getAge() == 60 ) {  // le loup meurt de vieillesse 
                    Mineraux * lo = new Mineraux(nbanimaux[i][y]->getposx(),nbanimaux[i][y]->getposy());
                    nbanimaux[lo->QuiSuisJe()-1].push_back(lo);
                    
                    terrain[nbanimaux[i][y]->getposy()].erase( begin(terrain[nbanimaux[i][y]->getposy()]) + nbanimaux[i][y]->getposx());
                    terrain[nbanimaux[i][y]->getposy()].insert( begin(terrain[nbanimaux[i][y]->getposy()]) + nbanimaux[i][y]->getposx(),lo);
                    nbanimaux[i].erase(begin(nbanimaux[i])+y);
                    y += -1;
                }
                else if (i == loup-1 && nbanimaux[i][y]->getfamine() ==10) { // le loup meurt de faim
                    Mineraux * lo = new Mineraux(nbanimaux[i][y]->getposx(),nbanimaux[i][y]->getposy());
                    nbanimaux[lo->QuiSuisJe()-1].push_back(lo);
                    terrain[nbanimaux[i][y]->getposy()].erase(begin(terrain[nbanimaux[i][y]->getposy()]) + nbanimaux[i][y]->getposx());
                    terrain[nbanimaux[i][y]->getposy()].insert(begin(terrain[nbanimaux[i][y]->getposy()]) + nbanimaux[i][y]->getposx(),lo);

                    nbanimaux[i].erase(begin(nbanimaux[i])+y);
                    y += -1;
                }
                else if (i == mouton-1 && nbanimaux[i][y]->getfamine() ==5) { //mouton meurt de famine
                    Mineraux * lo = new Mineraux(nbanimaux[i][y]->getposx(),nbanimaux[i][y]->getposy());
                    nbanimaux[lo->QuiSuisJe()-1].push_back(lo);
                    terrain[nbanimaux[i][y]->getposy()].erase(begin(terrain[nbanimaux[i][y]->getposy()]) + nbanimaux[i][y]->getposx());
                    terrain[nbanimaux[i][y]->getposy()].insert(begin(terrain[nbanimaux[i][y]->getposy()]) + nbanimaux[i][y]->getposx(),lo);
                   
                    nbanimaux[i].erase(begin(nbanimaux[i])+y);
                    y += -1;
                }
                else if(i == mouton-1 && nbanimaux[i][y]->getAge() == 50){//mouton meurt de vieillesse
                    Mineraux * lo = new Mineraux(nbanimaux[i][y]->getposx(),nbanimaux[i][y]->getposy());
                    nbanimaux[lo->QuiSuisJe()-1].push_back(lo);
                    terrain[nbanimaux[i][y]->getposy()].erase(begin(terrain[nbanimaux[i][y]->getposy()]) + nbanimaux[i][y]->getposx());
                    terrain[nbanimaux[i][y]->getposy()].insert(begin(terrain[nbanimaux[i][y]->getposy()]) + nbanimaux[i][y]->getposx(),lo);
                
                    nbanimaux[i].erase(begin(nbanimaux[i])+y);
                    y += -1;
                }
                else if (i == 2 && nbanimaux[i][y]->getTherbe() >=2) { // le minerais se transforme en plante
                    terrain[nbanimaux[i][y]->getposy()].erase(begin(terrain[nbanimaux[i][y]->getposy()]) + nbanimaux[i][y]->getposx());
                    terrain[nbanimaux[i][y]->getposy()].insert(begin(terrain[nbanimaux[i][y]->getposy()]) + nbanimaux[i][y]->getposx(),new Herbe());
            
                    nbanimaux[i].erase(begin(nbanimaux[i])+y);
                    y += -1;
                }


                else if ((i == 3 ||i==4) &&  nbanimaux[i][y]->Sacouple() == 3 && nbanimaux[i][y]->getsexe() == "femelle"){ // le loup le mouton femelle acouche 
                    vector<vector<int>> tab = nbanimaux[i][y]->place_libre_acouchement(terrain,casx,casy);
                    if (tab.size() == 0) {
                        nbanimaux[i][y]->Sacoupleto0();
                        nbanimaux[i][y]->editjaster();
                    }else { 
                        int random = (rand() % tab.size()) -1;
                        if (random == -1) {
                            random =0;
                        }
                        if (random %2 == 0) {
                            if (i==3) {
                                string nom = "male";
                                Loup * lo = new Loup(tab[random][1],tab[random][0],nom);
                                nbanimaux[lo->QuiSuisJe()-1].push_back(lo);


                                terrain[tab[random][0]].erase(begin(terrain[tab[random][0]])+tab[random][1]);
                                terrain[tab[random][0]].insert(begin(terrain[tab[random][0]])+tab[random][1],lo);
                                nbanimaux[i][y]->Sacoupleto0();
                                nbanimaux[i][y]->editjaster();
                                

                            }
                            else{
                                string nom = "male";
                                Mouton * lo = new Mouton(tab[random][1],tab[random][0],nom);
                                nbanimaux[lo->QuiSuisJe()-1].push_back(lo);
                                

                                terrain[tab[random][0]].erase(begin(terrain[tab[random][0]])+tab[random][1]);
                                terrain[tab[random][0]].insert(begin(terrain[tab[random][0]])+tab[random][1],lo);
                                nbanimaux[i][y]->Sacoupleto0();
                                nbanimaux[i][y]->editjaster();
                            }
                        }
                        else {
                             if (i==3) {
                                string nom = "femelle";
                                Loup * lo = new Loup(tab[random][1],tab[random][0],nom);
                                nbanimaux[lo->QuiSuisJe()-1].push_back(lo);


                                terrain[tab[random][0]].erase(begin(terrain[tab[random][0]])+tab[random][1]);
                                terrain[tab[random][0]].insert(begin(terrain[tab[random][0]])+tab[random][1],lo);
                                nbanimaux[i][y]->Sacoupleto0();
                                nbanimaux[i][y]->editjaster();
                            }
                            else{
                                string nom = "femelle";
                                Mouton * lo = new Mouton(tab[random][1],tab[random][0],nom);
                                nbanimaux[lo->QuiSuisJe()-1].push_back(lo);


                                terrain[tab[random][0]].erase(begin(terrain[tab[random][0]])+tab[random][1]);
                                terrain[tab[random][0]].insert(begin(terrain[tab[random][0]])+tab[random][1],lo);
                                nbanimaux[i][y]->Sacoupleto0();
                                nbanimaux[i][y]->editjaster();
                            }
                        }
                    }
                }
                else if ((i == 3 ||i==4) &&  nbanimaux[i][y]->Sacouple() == 3 && nbanimaux[i][y]->getsexe() == "male"){ // on remet a 0 jasteter et acouplé pour le mll
                    nbanimaux[i][y]->Sacoupleto0();
                    nbanimaux[i][y]->editjaster();
                }
            }
        }
    }

    void mangerAnimaux(){ // la fonction pour que les animaux mange dansc ce tours
       
        for (int i = 3; i <=4; i++) {
            for (long unsigned int y= 0; y <nbanimaux[i].size(); y++) {
                if ( i ==loup-1) { // loup
                    vector<vector<int>> resulta = (nbanimaux[i][y])->place_libre(mouton,terrain,casx,casy);
                    (nbanimaux[i][y])->manger(terrain,resulta,nbanimaux);
                }
                else { //mouton
                    vector<vector<int>> resulta =(nbanimaux[i][y])->place_libre(herbe,terrain,casx,casy);
                    (nbanimaux[i][y])->manger(terrain,resulta,nbanimaux);
                }
            }
        }
    }

    void incrementerall(){ // incremente toutes les states de famine, age, jasteter et acouplement
        for (int i =2; i < 5; i++) {
            for (int y = 0; y < nbanimaux[i].size(); y++) {
                if (nbanimaux[i][y]->QuiSuisJe() == mineraux) {
                    nbanimaux[i][y]->increTherber();
                }
                if (nbanimaux[i][y]->QuiSuisJe() ==loup) {
                    nbanimaux[i][y]->editActionto0();
                    nbanimaux[i][y]->incrjaster();
                    nbanimaux[i][y]->incrfamnie();
                    nbanimaux[i][y]->incrAge();
                    if (nbanimaux[i][y]->Sacouple() != 0) {
                        nbanimaux[i][y]->incrSacouple();
                    }
                }
                if (nbanimaux[i][y]->QuiSuisJe() == mouton) {
                    nbanimaux[i][y]->editActionto0();
                    nbanimaux[i][y]->incrjaster();
                    nbanimaux[i][y]->incrfamnie();
                    nbanimaux[i][y]->incrAge();
                    if (nbanimaux[i][y]->Sacouple() != 0) {
                        nbanimaux[i][y]->incrSacouple();
                    }
                }
            }
        }
    }

    void toursuivant(){
        tour++;
        static int a = 0;
        if (a == 0) {
            a = 1;
            affiche();
        }
        incrementerall();
        verifall();
        accoupleAnimaux();
        mangerAnimaux();
        deplacerAnimaux();
        affiche();
    }

};

int main(){
   try {
       int nbloup,nbmouton, casx,casy, tours;
       cout << "entrer le nombre de mouton" <<endl;
       cin >> nbmouton;
       if(cin.fail()){
        cin.clear();
        throw invalid_argument("argument donné n'est pas un int");
       }
       cout << "entrer le nombre de loup" <<endl;
       cin >> nbloup;
       if(cin.fail()){
        cin.clear();
        throw invalid_argument("argument donné n'est pas un int");
       }
       cout << "entrer le nombre de cas en x" <<endl;
       cin >> casx;
       if(cin.fail()){
        cin.clear();
        throw invalid_argument("argument donné n'est pas un int");
       }
       cout << "entrer le nombre de cas en y" <<endl;
       cin >> casy;
       if(cin.fail()){
        cin.clear();
        throw invalid_argument("argument donné n'est pas un int");
       }
       cout << "entrer le nombre tours ou -1 pour que le nombre de tours soit infini" <<endl;
       cin >> tours;
       if(cin.fail()){
        cin.clear();
        throw invalid_argument("argument donné n'est pas un int");
       }
       Univer p (nbmouton,nbloup,casx,casy);
       if (tours < 0) {
           while (1) {
                p.toursuivant();
                this_thread::sleep_for(std::chrono::milliseconds(2000));
           }
       }else {
            for (int i = 0; i < tours; i++) {
                p.toursuivant();
                this_thread::sleep_for(std::chrono::milliseconds(2000));
            }
       }
       
   }
   catch(const exception& a){
       cerr << "Caught: " << a.what() << endl;
   }
}