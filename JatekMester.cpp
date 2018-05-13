#include "JatekMester.hpp"
#include "graphics.hpp"
#include "TextBox.hpp"
#include "FocusedCheckBox.hpp"
#include "vButton.hpp"
#include "TankWidget.hpp"
#include "numberchanger.hpp"
#include "map.hpp"
#include <vector>
#include <string>
#include <iostream>
using namespace genv;
using namespace std;


TextBox * t1=new TextBox(410,495,50,50,"");

TankWidget * a1;
TankWidget * a2;


numberchanger *n1=new numberchanger(60,480,80,80,10,90,60);
numberchanger *n2=new numberchanger(180,480,80,80,10,200,30);

numberchanger *n3=new numberchanger(620,480,80,80,10,90,60);
numberchanger *n4=new numberchanger(760,480,80,80,10,200,40);

Map *m1=new Map(0,420,900,180);


vButton *b1;
vButton *b2;

JatekMester::JatekMester()
{
    a1=new TankWidget(30,390,70,20,60,60,1,this);
    a2=new TankWidget(800,390,70,20,120,60,2,this);

    s1= new TextBox(325,60,250,50,"Els� tank k�vezketik");

	widgets.push_back(m1);

	widgets.push_back(n1);
	widgets.push_back(n2);
	widgets.push_back(n3);
	widgets.push_back(n4);

    b1=new vButton(300,495,50,50,"Set1!",this);
	b2=new vButton(510,495,50,50,"Set2!",this);

	widgets.push_back(b1);
	widgets.push_back(b2);

	widgets.push_back(t1);

	widgets.push_back(a1);

	widgets.push_back(a2);

    double i=m1->szelirany();
    cout<<i<<endl;
    if(i==1){
        a2->szello(m1->szelgeneral());
        t1->texting(m1->szelgeneral());
    }
    else{
        a2->szello(-(m1->szelgeneral()));
        t1->texting(-(m1->szelgeneral()));
    }

    widgets.push_back(s1);

    vege_a_jateknak=false;
    kijon="Els� tank";

}

void JatekMester::lepes_tortent(){


    if(!vege_a_jateknak){
        double i=m1->szelirany();
        string who="";

        if(kijon=="Els� tank"){
            //szell
            if(i==1){
                a2->szello(m1->szelgeneral());
                t1->texting(m1->szelgeneral());
            }
            else{
                a2->szello(-(m1->szelgeneral()));
                t1->texting(-(m1->szelgeneral()));
            }
            //
            kijon="M�sodik tank";
        }
        else{
            //szel
            if(i==1){
                a1->szello(m1->szelgeneral());
                t1->texting(m1->szelgeneral());
            }
            else{
                a1->szello(-(m1->szelgeneral()));
                t1->texting(-(m1->szelgeneral()));
            }
            //
            kijon="Els� tank";
        }

        who=kijon;
        who+=" k�vetkezik";

        s1->settext(who);
    }

}

string JatekMester::getkijon(){
    return kijon;
}

void JatekMester::event(string m)
{
    if(m=="Set1!"){
        a1->Degree(n1->GetNumber());
        a1->Speed(n2->GetNumber());
        a1->Start();


    }

    if(m=="Set2!"){

        a2->Degree(180-n3->GetNumber());
        a2->Speed(n4->GetNumber());
        a2->Start();


    }
}
