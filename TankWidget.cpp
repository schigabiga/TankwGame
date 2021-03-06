#include "TankWidget.hpp"
#include "JatekMester.hpp"

#include <math.h>
#include <ctime>
#include <time.h>
#include <string>
#include <sstream>

using namespace genv;

TankWidget::TankWidget(int x, int y, int sx, int sy,int s,int sp,int nez, JatekMester* parent): Widget(x,y,sx,sy)
{
    _checked=true;
    ks=sp;
    sz=(  s/(180/3.141592654));

    start=false;
    vege=false;

    ir=nez;

    _parent=parent;

    _ki="Senki";
}

void TankWidget::draw()
{

    gout<<move_to(_x+_size_x/2,_y-20)<<color(153, 204, 255)<<line_to(av,ev);

    gout << move_to(_x, _y) << color(44,213,55) << box(_size_x,_size_y);

    gout << move_to(_x+_size_x/2-10, _y-20) << color(44,213,55) << box(20,20);


    gout << move_to(_x, _y+20) << color(31, 31, 20) << box(10,10);
    gout << move_to(_x+20, _y+20) << color(31, 31, 20) << box(10,10);
    gout << move_to(_x+40, _y+20) << color(31, 31, 20) << box(10,10);
    gout << move_to(_x+60, _y+20) << color(31, 31, 20) << box(10,10);


    double    rx=40;
    double    _iy=0;
    double    ss=sz;
    ix= rx*cos(ss) - _iy*sin(ss);
    iy= rx*sin(ss) + _iy*cos(ss);

    xi=_x+_size_x/2+ix;
    yi=_y-iy-20;

    gout << move_to(_x+_size_x/2,_y-20) << color(213,55,33) << line_to(_x+_size_x/2+ix,_y-iy-20);

    yb=yi;

    av=_x+_size_x/2+ix;
    ev=_y-iy-20;

}

void TankWidget::handle(event ev)
{
    if (ev.type == ev_key && (ev.keycode == key_enter || ev.keycode == ' ')) {
            _checked = !_checked;
    }
    if (ev.type == ev_mouse && is_selected(ev.pos_x, ev.pos_y) && ev.button==btn_left) {
        _checked = !_checked;
    }

    if(start==true){


        start=false;

        const double rad= 180/3.141592654;
        const double grav=9.81;

        double kseb=ks;

        int ax=xi;
        int ay=yi;

        double timerr=0;

        double c=0.45;

        double xx=ax;
        double yy=ay;

        double v_l;
        if(ir==1){
            v_l=szell;
        }
        else
            v_l=-szell;



        double w=kseb*sin(sz);
        double u=kseb*cos(sz);

        double px=0;
        double py=0;

        bool t=false;

        gin.timer(1);

        double kezdetix=xx;

        if(_fegyver=="Szell toro"){
            v_l=1;
        }



        while(gin>>ev && t==false){


            if(ev.type==ev_timer){
                if (v_l<0)
                {
                    u-=v_l*cos(sz)/1000;
                    w-=v_l*sin(sz)/1000;
                }
                px=xx;
                py=yy;

                double r=sqrt(u*u+w*w);

                double f_x=1.073*0.0011157*c*pow(u/10+v_l*cos(sz),2);
                double f_y=1.073*0.0011157*c*pow(w/10+v_l*sin(sz),2);

                timerr+=0.02;

                xx=ax+u*timerr-f_x*timerr*timerr;
                yy=ay-w*timerr+(grav/2)*timerr*timerr+f_y*timerr*timerr;

                if(xx>=900 && xx<=970 && yy>=_ipy){
                    _parent->vege();
                    _parent->nyertesjatekos("Elso tank");
                }
                if(xx>=130 && xx<=200 && yy>=_ipy){
                    _parent->vege();
                    _parent->nyertesjatekos("Masodik tank");
                }

                if(yy<_y+20 && yy>95 && xx>0 && xx <1100){
                    gout<<move_to(px,py)<<color(153, 204, 255)<<box(10,10);

                    gout<<move_to(xx,yy)<<color(77, 77, 51)<<box(10,10);

                    gout<<refresh;
                }
                else{
                    t=true;
                    gin.timer(0);
                    _ki=_parent->getkijon();
                    _parent->lepes();
                }
            }

        }
    }


}
double TankWidget::yback(){
    return yb;
}

void TankWidget::kisy(double y){
    _ipy=y;
}

string TankWidget::fegyverback(){
    return _fegyver;
}

string TankWidget::getszoveg()
{
	return _ki;
}

void TankWidget::szello(double e){
    szell=e;
}

bool TankWidget::is_checked()
{
    return _checked;
}

void TankWidget::Degree(double fok)
{
    sz=fok/(180/3.141592654);
}

void TankWidget::Speed(double s){
    ks=s;
}

string TankWidget::Wind(){
    string w;
    stringstream ss;
    ss<<wind;
    ss>>w;
    return w;
}

void TankWidget::Start(){
    start=true;
}

void TankWidget::setfegyver(string f){
    _fegyver=f;
}





