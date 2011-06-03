/**-----------------------------------------------------------
Autor       : Neumair Günther
Class       : Quart
Date        : 06.11.2010
Description : Representation of Quarternion Rotation and Position
-------------------------------------------------------------*/

#ifndef QUART_H
#define QUART_H

#include <ode/ode.h>
#include "wx/glcanvas.h"
#include "loader.h"

class Quart
{

public:

    Quart();
    Quart(Quart * Q);

    //Globally --------------------------------------
    void set_position( float x , float y, float z);         ///Set Position of Quart directly
    void rotate(float x , float y, float z);                ///Rotate Quart Euler Style
    void move(float x, float y, float z);                   ///Move Quart
    void multiply(Quart* Q1, Quart* Q2);                    ///Really needet???????????????????
    void add(Quart*Q);                                      ///Add rotation and Position to Quart
    void set_quart(float w , float x , float y ,float z);   ///set Quarternion Paremeters
    void get_quart(float *T) const;                         ///Get Quarternion Parameters
    void get_position(float *P) const;                      ///Get Poisition Parameters
    void load_quart(scanner &s);                            ///Load Quart from Scanner
    void save_quart(std::ostream &os);                      ///Save Qaurt to Stream


    void push_ode();
    void push_ogl();
    // void prepare_ode();

private:

    void set_zero();            ///Set to Union Qaurt at position zero
    void setRotationFromEulerAngles(float angleX,float angleY, float angleZ);
    void rotate_quart(float angle, float x, float y, float z);
    void normalize();           ///Pirvatly use only
    Quart* conjugate();
    float R[3];
    float M[3];
    float E[16];
    float Q[4];
};



#endif
