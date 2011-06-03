/**-----------------------------------------------------------
Autor       : Neumair Günther
Class       : Quart
Date        : 06.11.2010
Description : Representation of Rotation and translation
-------------------------------------------------------------*/

#include "quart.h"
Quart::Quart(Quart * Q)
{
    float T[4];
    float P[3];
    Q->get_position(P);
    Q->get_quart(T);

    set_position(P[0], P[1], P[2]);
    set_quart(T[0],T[1],T[2],T[3]);
}

Quart::Quart()
{
    //Set everything zero
    for (size_t i = 0; i< 3 ; i++)
    {
        M[i]=0;
    }


    for (size_t i = 0; i< 3 ; i++)
    {
        R[i]=0;
    }

    set_zero();

}

void Quart::set_zero()
{
    Q[0] = 1;
    Q[1] = 0;
    Q[2] = 0;
    Q[3] = 0;
}

void Quart::add(Quart*Q)
{
    ///TODO Rotation has currently no influence !!!!!!!!!!!!!11
    //multiply(this,Q);
    float P[3];
    Q->get_position(P);
    M[0] +=P[0];
    M[1] +=P[1];
    M[2] +=P[2];
    normalize();
}

void Quart::rotate(float x , float y, float z)
{

    R[0] += x;
    R[1] += y;
    R[2] += z;

    set_zero();
    Quart t;
    t.set_quart(cos(R[0]/20),sin(R[0]/20),0,0);
    Quart k;
    k.set_quart(cos(R[1]/20),0,sin(R[1]/20),0);
    Quart f;
    f.set_quart(cos(R[2]/20),0,0,sin(R[2]/20));

    multiply(this,&f);
    multiply(this,&k);
    multiply(this,&t);
    normalize();
}


void Quart::set_quart(float w , float x , float y ,float z)
{
    Q[0] = w;
    Q[1] = x;
    Q[2] = y;
    Q[3] = z;
}

void Quart::get_quart(float *T) const
{
    T[0] = Q[0];
    T[1] = Q[1];
    T[2] = Q[2];
    T[3] = Q[3];
}

void Quart::get_position(float *P) const
{
    P[0] = M[0];
    P[1] = M[1];
    P[2] = M[2];
}

void Quart::set_position( float x , float y, float z)
{
    M[0] = x;
    M[1] = y;
    M[2] = z;
}

void Quart::move(float x, float y, float z)
{
    M[0] += x;
    M[1] += y;
    M[2] += z;
}


void Quart::normalize()
{

/// XXX Improvement for SIMD optimisation
    float length = sqrt(Q[0]*Q[0] + Q[1]*Q[1] + Q[2]*Q[2] + Q[3]*Q[3]);
    Q[0] /= length;
    Q[1] /= length;
    Q[2] /= length;
    Q[3] /= length;
}


Quart *Quart::conjugate()
{
    Quart *q = new Quart();

    float x = -Q[1];
    float y = -Q[2];
    float z = -Q[3];

    q->set_quart(1,x,y,z);
    return q;
}

void  Quart::multiply(Quart* Q1, Quart* Q2)
{
    float q1[4];
    Q1->get_quart(q1);
    float q2[4];
    Q2->get_quart(q2);
    float QR[4];

    QR[0] = q1[0]*q2[0] - q1[1]*q2[1] - q1[2]*q2[2] - q1[3]*q2[3];
    QR[1] = q1[0]*q2[1] + q1[1]*q2[0] + q1[2]*q2[3] - q1[3]*q2[2];
    QR[2] = q1[0]*q2[2] - q1[1]*q2[3] + q1[2]*q2[0] + q1[3]*q2[1];
    QR[3] = q1[0]*q2[3] + q1[1]*q2[2] - q1[2]*q2[1] + q1[3]*q2[0];
    set_quart(QR[0],QR[1],QR[2],QR[3]);

}

void Quart::push_ogl()
{
    glPushMatrix();
    normalize();

    E[0] = 1 - 2*(Q[2]*Q[2] + Q[3]*Q[3]);
    E[1] = 2*(Q[1]*Q[2] + Q[0]*Q[3]);
    E[2] = 2*(Q[1]*Q[3] - Q[0]*Q[2]);
    E[3] = 0;
    E[4] = 2*(Q[1]*Q[2] - Q[0]*Q[3]);
    E[5] = 1 - 2*(Q[1]*Q[1] + Q[3]*Q[3]);
    E[6] = 2*(Q[2]*Q[3] + Q[0]*Q[1]);
    E[7] = 0;
    E[8] = 2*(Q[1]*Q[3] + Q[0]*Q[2]);
    E[9] = 2*(Q[2]*Q[3] - Q[0]*Q[1]);
    E[10] = 1 - 2*(Q[1]*Q[1] + Q[2]*Q[2]);
    E[11] = 0;
    E[12] = M[0];
    E[13] = M[1];
    E[14] = M[2];
    E[15] = 1;

    glMultMatrixf(E);

}

void Quart::load_quart(scanner &s)
{

#ifdef MY_DEBUG
    add_news_save("lade Quart",N_Info);
#endif

    M[0] = load_float(s);
    M[1] = load_float(s);
    M[2] = load_float(s);
    Q[0] = load_float(s);
    Q[1] = load_float(s);
    Q[2] = load_float(s);
    Q[3] = load_float(s);
}



void Quart::save_quart(std::ostream &os)
{
//Position
    os << std::fixed << M[0] << std::endl;
    os << M[1] << std::endl;
    os << M[2] << std::endl;
//Rotation
    os << std::fixed << Q[0] << std::endl;
    os << Q[1] << std::endl;
    os << Q[2] << std::endl;
    os << Q[3] << std::endl;
}



