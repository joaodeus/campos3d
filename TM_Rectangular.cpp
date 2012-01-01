// TM_Rectangular.cpp: implementation of the TM_Rectangular class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "campos3d.h"
#include "TM_Rectangular.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TMr::TMr()
{


	//cores para frente
	RedF=0;
	GreenF=0;
	BlueF=1;

	//cores para trás
	RedT=0;
	GreenT=1;
	BlueT=1;

	//SENTIDO ANTI HORARIO
	RedHF=1;
	GreenHF=1;
	BlueHF=0;

	//SENTIDO HORARIO
	RedHT=1;
	GreenHT=0;
	BlueHT=0;


	NCamposZ=4;//numero de campos a desenhar ao longo do eixo z
	NCamposJ=6;//numero de campos a desenhar transversalmente

	NCamposx=10;
	NCamposy=10;

	z_inicia_desenho_grafE=0;


	Formulas.Add("Ex=Bmn/h^2*m*PI/a*C*cos(m*PI/a*x)*sin(n*PI/b*y)*cos(w*t-2*PI/Lmn*z)");
	Formulas.Add("Ey=Bmn/h^2*n*PI/b*C*sin(m*PI/a*x)*cos(n*PI/b*y)*sin(w*t-2*PI/Lmn*z)");
	Formulas.Add("Ez=C*sin(m*PI/a*x)*sin(n*PI/b*y)*cos(w*t-2*PI/Lmn*z)");

}

/*
TMr::TMr(double a_, double b_, double freq_, double Er_, double Ur_)
{
	a=a_;
	b=b_;
	f=freq_;
	Er=Er_;
	Ur=Ur_;
}*/

TMr::~TMr()
{

}

Complexo TMr::Ex(double x,double y,double z, double t)
{
	Complexo j(0,0);
	//Complexo a;
	double M_=M();
	double N_=N();
	Complexo ab=alfaB();

	if (M_==0)
		return j;

	j.r=0;
	j.i=1;

	//a=-ab/(M_+N_*N_/M_)*
	//	cos(M_*x)*sin(N_*y)*exp(j*GetW()*t-ab*z);

	//return a;
	return -ab/(M_+N_*N_/M_)*
		cos(M_*x)*sin(N_*y)*exp(j*GetW()*t-ab*z);
}


Complexo TMr::Ey(double x,double y,double z, double t)
{
	Complexo j(0,0);
	double M_=M();
	double N_=N();
	Complexo ab=alfaB();

	if (N_==0)
		return j;

	j.r=0;
	j.i=1;

	return -ab/(M_*M_/N_+N_)*
		sin(M_*x)*cos(N_*y)*exp(j*GetW()*t-ab*z);
}

Complexo TMr::Ez(double x,double y,double z, double t)
{
	Complexo j(0,1);
	double M_=M();
	double N_=N();
	Complexo ab=alfaB();

	return sin(M_*x)*sin(N_*y)*exp(j*GetW()*t-ab*z);
}

Complexo TMr::Hx(double x,double y,double z, double t)
{
	Complexo j(0,1),c(0,0);
	double M_=M();
	double N_=N();
	double W=2*PI*f;
	double E=Er*Eo;
	Complexo ab=alfaB();

	if (N_==0)
		return c;

	return j*W*E/(M_*M_/N_+N_)*
		sin(M_*x)*cos(N_*y)*exp(j*GetW()*t-ab*z);
}


Complexo TMr::Hy(double x,double y,double z, double t)
{
	Complexo j(0,1),c(0,0);
	double M_=M();
	double N_=N();
	double W=2*PI*f;
	double E=Er*Eo;
	Complexo ab=alfaB();

	if (M_==0)
		return c;

	return -j*W*E/(M_+N_*N_/M_)*
		cos(M_*x)*sin(N_*y)*exp(j*GetW()*t-ab*z);
}

Complexo TMr::Hz(double x,double y,double z, double t)
{
	Complexo Hz(0,0);
	return Hz;
}

double TMr::Sav_z(double x,double y,double z, double t)
{
	return (Ex(x,y,z,t)*conj(Hy(x,y,z,t))
		-Ey(x,y,z,t)*conj(Hx(x,y,z,t))).r/2;
}


void TMr::GetZero_E(double t, double &z1, double &z2)
{
	
	double k_aux;
	int k;

	k_aux=2.5-2*f*t;
	k = int(k_aux);

	//if (k < k_aux)
	//	k--;

	z2=GetLmn() * ( (GetW()*t-PI/2+k*PI)/(2*PI) );
	
	k--;
	z1=GetLmn() * ( (GetW()*t-PI/2+k*PI)/(2*PI) );


}


void TMr::GetZero_H(double t, double &z1, double &z2)
{
	
	double k_aux;
	int k;

	k_aux=2*f*t;
	k = int(k_aux);

	//if (k < k_aux)
	//	k--;

	z2=GetLmn() * ( (GetW()*t-k*PI) / (2*PI) );
	
	k--;
	z1=GetLmn() * ( (GetW()*t-k*PI) / (2*PI) );


}



void TMr:: DrawE(double t)
{
	
	double Vx,Vy,Vz;	//vector
	double Vmax;		//vector maximo
	double p_x,p_y,p_z;	//point

	double i,j;
	int z;

	
	nLinhasA=NCamposx;
	nLinhasB=NCamposy;

	double distA;
	double distB;

	double L;
	double z1,z2;//pontos em que Ex se anula - limiar onde se começa a desenhar as linhas de força

	int k=0;	//contador das linhas de força
	double Q = 100;//factor qualidade, nº de linhas segmentos de cada linha de força
	double scaleVector;

	distA=a/nLinhasA;
	distB=b/nLinhasB;

	L=GetLmn();


	graf_E.SetSize(2*nLinhasA*nLinhasB);


	z1=GetLmn()/4;
	z2=GetLmn()*3/4;




	// 1º parte do guia - zona para frente de 'z_inicia_desenho_grafE'
	for (i = distA/2; i < a ; i += distA)
	{		
		for(j = distB/2 ; j < b ; j += distB)
		{
			p_x=i;
			p_y=j;	
			//p_z=z1-L/(Q*4);
			p_z=z_inicia_desenho_grafE;
		

			if ( graf_E[k].Ex_arrai.GetSize() < 1)	graf_E[k].Ex_arrai.Add(p_x);
			else	graf_E[k].Ex_arrai[0]=p_x;
			
					
			if (graf_E[k].Ey_arrai.GetSize() < 1)	graf_E[k].Ey_arrai.Add(p_y);
			else	graf_E[k].Ey_arrai[0]=p_y;

			if (graf_E[k].Ez_arrai.GetSize() < 1)	graf_E[k].Ez_arrai.Add(p_z);
			else	graf_E[k].Ez_arrai[0]=p_z;


			
			//for(z=l/Q;z<l;z=z+l/Q)
			for(z=0;z<Q;z++)
			{
				Vx=Ex(p_x,p_y,p_z,t).r;
				Vy=Ey(p_x,p_y,p_z,t).r;
				Vz=Ez(p_x,p_y,p_z,t).r;

				if (Vz <0 )//se é negativo, desenha para a frente com a cor negativa
				{
					Vx=-Vx;
					Vy=-Vy;
					Vz=-Vz;
					
					graf_E[k].RedE=RedT;
					graf_E[k].GreenE=GreenT;
					graf_E[k].BlueE=BlueT;
				}
				else
				{
					graf_E[k].RedE=RedF;
					graf_E[k].GreenE=GreenF;
					graf_E[k].BlueE=BlueF;
				}
				
			
				Vmax=VectorMax(Vx,Vy,Vz);


				if ( Vmax > L/Q)
				{
					scaleVector=L/(Q*Vmax);
					Vx*=scaleVector; Vy*=scaleVector; Vz*=scaleVector;
				}
					
				p_x=p_x+Vx;	p_y=p_y+Vy;	p_z=p_z+Vz;

				if (p_x<0 || p_x>a || p_y<0 || p_y>b || p_z>z1)
				//if (p_x<=0 || p_x>=a || p_y<=0 || p_y>=b || p_z>=z1)
			
				{
					graf_E[k].Ex_arrai.SetSize(z+1);
					graf_E[k].Ey_arrai.SetSize(z+1);
					graf_E[k].Ez_arrai.SetSize(z+1);
					break;
				}

					
				
				if (graf_E[k].Ex_arrai.GetSize() < z+2)	
					graf_E[k].Ex_arrai.Add(p_x);
				else	
					graf_E[k].Ex_arrai[z+1]=p_x;

				
				if (graf_E[k].Ey_arrai.GetSize() < z+2)
					graf_E[k].Ey_arrai.Add(p_y);
				else
					graf_E[k].Ey_arrai[z+1]=p_y;


				if (graf_E[k].Ez_arrai.GetSize() < z+2)
					graf_E[k].Ez_arrai.Add(p_z);
				else
					graf_E[k].Ez_arrai[z+1]=p_z;			
			}
		

			k++;
		}
	}





	// 1º parte do guia - zona para trás de 'z_inicia_desenho_grafE'
	for (i = distA/2; i < a ; i += distA)
	{		
		for(j = distB/2 ; j < b ; j += distB)
		{
			p_x=i;
			p_y=j;	
			//p_z=z1-L/(Q*4);
			p_z=z_inicia_desenho_grafE;
		

			if ( graf_E[k].Ex_arrai.GetSize() < 1)	graf_E[k].Ex_arrai.Add(p_x);
			else	graf_E[k].Ex_arrai[0]=p_x;
			
					
			if (graf_E[k].Ey_arrai.GetSize() < 1)	graf_E[k].Ey_arrai.Add(p_y);
			else	graf_E[k].Ey_arrai[0]=p_y;

			if (graf_E[k].Ez_arrai.GetSize() < 1)	graf_E[k].Ez_arrai.Add(p_z);
			else	graf_E[k].Ez_arrai[0]=p_z;


			
			//for(z=l/Q;z<l;z=z+l/Q)
			for(z=0;z<Q;z++)
			{
				Vx=Ex(p_x,p_y,p_z,t).r;
				Vy=Ey(p_x,p_y,p_z,t).r;
				Vz=Ez(p_x,p_y,p_z,t).r;

				if (Vz >0 )//se é positivo, desenha para trás com a cor positiva
				{
					Vx=-Vx;
					Vy=-Vy;
					Vz=-Vz;
					
					graf_E[k].RedE=RedF;
					graf_E[k].GreenE=GreenF;
					graf_E[k].BlueE=BlueF;
				}
				else
				{
					graf_E[k].RedE=RedT;
					graf_E[k].GreenE=GreenT;
					graf_E[k].BlueE=BlueT;
				}
				
				
				Vmax=VectorMax(Vx,Vy,Vz);

				if ( Vmax > L/Q)
				{
					scaleVector=L/(Q*Vmax);
					Vx*=scaleVector; Vy*=scaleVector; Vz*=scaleVector;
				}
					
				p_x=p_x+Vx;	p_y=p_y+Vy;	p_z=p_z+Vz;

				
				if (p_x<0 || p_x>a || p_y<0 || p_y>b || p_z< (-z1) )
			//	if (p_x<=0 || p_x>=a || p_y<=0 || p_y>=b || p_z <= (-z1) )
				{
					graf_E[k].Ex_arrai.SetSize(z+1);
					graf_E[k].Ey_arrai.SetSize(z+1);
					graf_E[k].Ez_arrai.SetSize(z+1);
					break;
				}

					
				
				if (graf_E[k].Ex_arrai.GetSize() < z+2)	
					graf_E[k].Ex_arrai.Add(p_x);
				else	
					graf_E[k].Ex_arrai[z+1]=p_x;

				
				if (graf_E[k].Ey_arrai.GetSize() < z+2)
					graf_E[k].Ey_arrai.Add(p_y);
				else
					graf_E[k].Ey_arrai[z+1]=p_y;


				if (graf_E[k].Ez_arrai.GetSize() < z+2)
					graf_E[k].Ez_arrai.Add(p_z);
				else
					graf_E[k].Ez_arrai[z+1]=p_z;			
			}
		

			k++;
		}
	}




}







///////////////////

/*
void TMr:: DrawE_alternativo(double t)
{

	double Vx,Vy,Vz;	//vector
	double Vmax;		//vector maximo
	double p_x,p_y,p_z;	//point

	double i,j;
	int z;

	//nLinhasA=10;
	//nLinhasB=10;
	nLinhasA=NCamposx;
	nLinhasB=NCamposy;

	double distA;
	double distB;

	double L;
	double z1,z2;//pontos em que Ex se anula - limiar onde se começa a desenhar as linhas de força

	int k=0;	//contador das linhas de força
	double Q = 100;//factor qualidade, nº de linhas segmentos de cada linha de força
	double scaleVector;

	distA=a/nLinhasA;
	distB=b/nLinhasB;

	L=GetLmn();


	graf_E.SetSize(6*nLinhasA*nLinhasB);



	z1=GetLmn()/4;
	z2=GetLmn()*3/4;


	color_i=distA/2;
	color_j=distB/2;
	color_z=z_inicia_desenho_grafE;
	color_t=t;



	// 1º parte do guia - zona para frente de 'z_inicia_desenho_grafE'
	for (i = distA/2; i < a ; i += distA)
	{		
		for(j = distB/2 ; j < b ; j += distB)
		{
			p_x=i;
			p_y=j;	
			//p_z=z1-L/(Q*4);
			p_z=z_inicia_desenho_grafE;
		

			if ( graf_E[k].Ex_arrai.GetSize() < 1)	graf_E[k].Ex_arrai.Add(p_x);
			else	graf_E[k].Ex_arrai[0]=p_x;
			
					
			if (graf_E[k].Ey_arrai.GetSize() < 1)	graf_E[k].Ey_arrai.Add(p_y);
			else	graf_E[k].Ey_arrai[0]=p_y;

			if (graf_E[k].Ez_arrai.GetSize() < 1)	graf_E[k].Ez_arrai.Add(p_z);
			else	graf_E[k].Ez_arrai[0]=p_z;


			
			//for(z=l/Q;z<l;z=z+l/Q)
			for(z=0;z<Q;z++)
			{
				Vx=Ex(p_x,p_y,p_z,t).r;
				Vy=Ey(p_x,p_y,p_z,t).r;
				Vz=Ez(p_x,p_y,p_z,t).r;

				if (Vz <0 )//se é negativo, desenha para a frente com a cor negativa
				{
					Vx=-Vx;
					Vy=-Vy;
					Vz=-Vz;
					
					graf_E[k].RedE=RedT;
					graf_E[k].GreenE=GreenT;
					graf_E[k].BlueE=BlueT;
				}
				else
				{
					graf_E[k].RedE=RedF;
					graf_E[k].GreenE=GreenF;
					graf_E[k].BlueE=BlueF;
				}
				
			
				Vmax=VectorMax(Vx,Vy,Vz);


				if ( Vmax > L/Q)
				{
					scaleVector=L/(Q*Vmax);
					Vx*=scaleVector; Vy*=scaleVector; Vz*=scaleVector;
				}
					
				p_x=p_x+Vx;	p_y=p_y+Vy;	p_z=p_z+Vz;

				if (p_x<0 || p_x>a || p_y<0 || p_y>b || p_z>z1)
				//if (p_x<0 || p_x>a || p_y<0 || p_y>b || p_z< (-z1) || p_z>z1)
				{
					graf_E[k].Ex_arrai.SetSize(z+1);
					graf_E[k].Ey_arrai.SetSize(z+1);
					graf_E[k].Ez_arrai.SetSize(z+1);
					break;
				}

					
				
				if (graf_E[k].Ex_arrai.GetSize() < z+2)	
					graf_E[k].Ex_arrai.Add(p_x);
				else	
					graf_E[k].Ex_arrai[z+1]=p_x;

				
				if (graf_E[k].Ey_arrai.GetSize() < z+2)
					graf_E[k].Ey_arrai.Add(p_y);
				else
					graf_E[k].Ey_arrai[z+1]=p_y;


				if (graf_E[k].Ez_arrai.GetSize() < z+2)
					graf_E[k].Ez_arrai.Add(p_z);
				else
					graf_E[k].Ez_arrai[z+1]=p_z;			
			}
		

			k++;
		}
	}





	// 1º parte do guia - zona para trás de 'z_inicia_desenho_grafE'
	for (i = distA/2; i < a ; i += distA)
	{		
		for(j = distB/2 ; j < b ; j += distB)
		{
			p_x=i;
			p_y=j;	
			//p_z=z1-L/(Q*4);
			p_z=z_inicia_desenho_grafE;
		

			if ( graf_E[k].Ex_arrai.GetSize() < 1)	graf_E[k].Ex_arrai.Add(p_x);
			else	graf_E[k].Ex_arrai[0]=p_x;
			
					
			if (graf_E[k].Ey_arrai.GetSize() < 1)	graf_E[k].Ey_arrai.Add(p_y);
			else	graf_E[k].Ey_arrai[0]=p_y;

			if (graf_E[k].Ez_arrai.GetSize() < 1)	graf_E[k].Ez_arrai.Add(p_z);
			else	graf_E[k].Ez_arrai[0]=p_z;


			
			//for(z=l/Q;z<l;z=z+l/Q)
			for(z=0;z<Q;z++)
			{
				Vx=Ex(p_x,p_y,p_z,t).r;
				Vy=Ey(p_x,p_y,p_z,t).r;
				Vz=Ez(p_x,p_y,p_z,t).r;

				if (Vz >0 )//se é positivo, desenha para trás com a cor positiva
				{
					Vx=-Vx;
					Vy=-Vy;
					Vz=-Vz;
					
					graf_E[k].RedE=RedF;
					graf_E[k].GreenE=GreenF;
					graf_E[k].BlueE=BlueF;
				}
				else
				{
					graf_E[k].RedE=RedT;
					graf_E[k].GreenE=GreenT;
					graf_E[k].BlueE=BlueT;
				}
				
				
				Vmax=VectorMax(Vx,Vy,Vz);

				if ( Vmax > L/Q)
				{
					scaleVector=L/(Q*Vmax);
					Vx*=scaleVector; Vy*=scaleVector; Vz*=scaleVector;
				}
					
				p_x=p_x+Vx;	p_y=p_y+Vy;	p_z=p_z+Vz;

				//if (p_x<0 || p_x>a || p_y<0 || p_y>b || p_z<0 || p_z>z1)
				if (p_x<0 || p_x>a || p_y<0 || p_y>b || p_z< (-z1) )
				{
					graf_E[k].Ex_arrai.SetSize(z+1);
					graf_E[k].Ey_arrai.SetSize(z+1);
					graf_E[k].Ez_arrai.SetSize(z+1);
					break;
				}

					
				
				if (graf_E[k].Ex_arrai.GetSize() < z+2)	
					graf_E[k].Ex_arrai.Add(p_x);
				else	
					graf_E[k].Ex_arrai[z+1]=p_x;

				
				if (graf_E[k].Ey_arrai.GetSize() < z+2)
					graf_E[k].Ey_arrai.Add(p_y);
				else
					graf_E[k].Ey_arrai[z+1]=p_y;


				if (graf_E[k].Ez_arrai.GetSize() < z+2)
					graf_E[k].Ez_arrai.Add(p_z);
				else
					graf_E[k].Ez_arrai[z+1]=p_z;			
			}
		

			k++;
		}
	}




	// 2º parte do guia - zona para frente de 'z_inicia_desenho_grafE'
	for (i = distA/2; i < a ; i += distA)
	{		
		for(j = distB/2 ; j < b ; j += distB)
		{
			p_x=i;
			p_y=j;	
			//p_z=z1-L/(Q*4);
			p_z=z_inicia_desenho_grafE+L/2;
		

			if ( graf_E[k].Ex_arrai.GetSize() < 1)	graf_E[k].Ex_arrai.Add(p_x);
			else	graf_E[k].Ex_arrai[0]=p_x;
			
					
			if (graf_E[k].Ey_arrai.GetSize() < 1)	graf_E[k].Ey_arrai.Add(p_y);
			else	graf_E[k].Ey_arrai[0]=p_y;

			if (graf_E[k].Ez_arrai.GetSize() < 1)	graf_E[k].Ez_arrai.Add(p_z);
			else	graf_E[k].Ez_arrai[0]=p_z;


			
			//for(z=l/Q;z<l;z=z+l/Q)
			for(z=0;z<Q;z++)
			{
				Vx=Ex(p_x,p_y,p_z,t).r;
				Vy=Ey(p_x,p_y,p_z,t).r;
				Vz=Ez(p_x,p_y,p_z,t).r;

				if (Vz <0 )//se é negativo, desenha para a frente com a cor negativa
				{
					Vx=-Vx;
					Vy=-Vy;
					Vz=-Vz;
					
					graf_E[k].RedE=RedT;
					graf_E[k].GreenE=GreenT;
					graf_E[k].BlueE=BlueT;
				}
				else
				{
					graf_E[k].RedE=RedF;
					graf_E[k].GreenE=GreenF;
					graf_E[k].BlueE=BlueF;
				}
				
			
				Vmax=VectorMax(Vx,Vy,Vz);


				if ( Vmax > L/Q)
				{
					scaleVector=L/(Q*Vmax);
					Vx*=scaleVector; Vy*=scaleVector; Vz*=scaleVector;
				}
					
				p_x=p_x+Vx;	p_y=p_y+Vy;	p_z=p_z+Vz;

				if (p_x<0 || p_x>a || p_y<0 || p_y>b || p_z<z1 || p_z>z2)
				//if (p_x<0 || p_x>a || p_y<0 || p_y>b || p_z< (-z1) || p_z>z1)
				{
					graf_E[k].Ex_arrai.SetSize(z+1);
					graf_E[k].Ey_arrai.SetSize(z+1);
					graf_E[k].Ez_arrai.SetSize(z+1);
					break;
				}

					
				
				if (graf_E[k].Ex_arrai.GetSize() < z+2)	
					graf_E[k].Ex_arrai.Add(p_x);
				else	
					graf_E[k].Ex_arrai[z+1]=p_x;

				
				if (graf_E[k].Ey_arrai.GetSize() < z+2)
					graf_E[k].Ey_arrai.Add(p_y);
				else
					graf_E[k].Ey_arrai[z+1]=p_y;


				if (graf_E[k].Ez_arrai.GetSize() < z+2)
					graf_E[k].Ez_arrai.Add(p_z);
				else
					graf_E[k].Ez_arrai[z+1]=p_z;			
			}
		

			k++;
		}
	}





	// 2º parte do guia - zona para trás de 'z_inicia_desenho_grafE'
	for (i = distA/2; i < a ; i += distA)
	{		
		for(j = distB/2 ; j < b ; j += distB)
		{
			p_x=i;
			p_y=j;	
			//p_z=z1-L/(Q*4);
			p_z=z_inicia_desenho_grafE+L/2;
		

			if ( graf_E[k].Ex_arrai.GetSize() < 1)	graf_E[k].Ex_arrai.Add(p_x);
			else	graf_E[k].Ex_arrai[0]=p_x;
			
					
			if (graf_E[k].Ey_arrai.GetSize() < 1)	graf_E[k].Ey_arrai.Add(p_y);
			else	graf_E[k].Ey_arrai[0]=p_y;

			if (graf_E[k].Ez_arrai.GetSize() < 1)	graf_E[k].Ez_arrai.Add(p_z);
			else	graf_E[k].Ez_arrai[0]=p_z;


			
			//for(z=l/Q;z<l;z=z+l/Q)
			for(z=0;z<Q;z++)
			{
				Vx=Ex(p_x,p_y,p_z,t).r;
				Vy=Ey(p_x,p_y,p_z,t).r;
				Vz=Ez(p_x,p_y,p_z,t).r;

				if (Vz >0 )//se é positivo, desenha para trás com a cor positiva
				{
					Vx=-Vx;
					Vy=-Vy;
					Vz=-Vz;
					
					graf_E[k].RedE=RedF;
					graf_E[k].GreenE=GreenF;
					graf_E[k].BlueE=BlueF;
				}
				else
				{
					graf_E[k].RedE=RedT;
					graf_E[k].GreenE=GreenT;
					graf_E[k].BlueE=BlueT;
				}
				
				
				Vmax=VectorMax(Vx,Vy,Vz);

				if ( Vmax > L/Q)
				{
					scaleVector=L/(Q*Vmax);
					Vx*=scaleVector; Vy*=scaleVector; Vz*=scaleVector;
				}
					
				p_x=p_x+Vx;	p_y=p_y+Vy;	p_z=p_z+Vz;

				//if (p_x<0 || p_x>a || p_y<0 || p_y>b || p_z<0 || p_z>z1)
				if (p_x<0 || p_x>a || p_y<0 || p_y>b || p_z<z1 || p_z>z2 )
				{
					graf_E[k].Ex_arrai.SetSize(z+1);
					graf_E[k].Ey_arrai.SetSize(z+1);
					graf_E[k].Ez_arrai.SetSize(z+1);
					break;
				}

					
				
				if (graf_E[k].Ex_arrai.GetSize() < z+2)	
					graf_E[k].Ex_arrai.Add(p_x);
				else	
					graf_E[k].Ex_arrai[z+1]=p_x;

				
				if (graf_E[k].Ey_arrai.GetSize() < z+2)
					graf_E[k].Ey_arrai.Add(p_y);
				else
					graf_E[k].Ey_arrai[z+1]=p_y;


				if (graf_E[k].Ez_arrai.GetSize() < z+2)
					graf_E[k].Ez_arrai.Add(p_z);
				else
					graf_E[k].Ez_arrai[z+1]=p_z;			
			}
		

			k++;
		}
	}





	// 3º parte do guia - zona para frente de 'z_inicia_desenho_grafE'
	for (i = distA/2; i < a ; i += distA)
	{		
		for(j = distB/2 ; j < b ; j += distB)
		{
			p_x=i;
			p_y=j;	
			//p_z=z1-L/(Q*4);
			p_z=z_inicia_desenho_grafE+L;
		

			if ( graf_E[k].Ex_arrai.GetSize() < 1)	graf_E[k].Ex_arrai.Add(p_x);
			else	graf_E[k].Ex_arrai[0]=p_x;
			
					
			if (graf_E[k].Ey_arrai.GetSize() < 1)	graf_E[k].Ey_arrai.Add(p_y);
			else	graf_E[k].Ey_arrai[0]=p_y;

			if (graf_E[k].Ez_arrai.GetSize() < 1)	graf_E[k].Ez_arrai.Add(p_z);
			else	graf_E[k].Ez_arrai[0]=p_z;


			
			//for(z=l/Q;z<l;z=z+l/Q)
			for(z=0;z<Q;z++)
			{
				Vx=Ex(p_x,p_y,p_z,t).r;
				Vy=Ey(p_x,p_y,p_z,t).r;
				Vz=Ez(p_x,p_y,p_z,t).r;

				if (Vz <0 )//se é negativo, desenha para a frente com a cor negativa
				{
					Vx=-Vx;
					Vy=-Vy;
					Vz=-Vz;
					
					graf_E[k].RedE=RedT;
					graf_E[k].GreenE=GreenT;
					graf_E[k].BlueE=BlueT;
				}
				else
				{
					graf_E[k].RedE=RedF;
					graf_E[k].GreenE=GreenF;
					graf_E[k].BlueE=BlueF;
				}
				
			
				Vmax=VectorMax(Vx,Vy,Vz);


				if ( Vmax > L/Q)
				{
					scaleVector=L/(Q*Vmax);
					Vx*=scaleVector; Vy*=scaleVector; Vz*=scaleVector;
				}
					
				p_x=p_x+Vx;	p_y=p_y+Vy;	p_z=p_z+Vz;

				if (p_x<0 || p_x>a || p_y<0 || p_y>b || p_z<z2 || p_z> L*5/4)
				//if (p_x<0 || p_x>a || p_y<0 || p_y>b || p_z< (-z1) || p_z>z1)
				{
					graf_E[k].Ex_arrai.SetSize(z+1);
					graf_E[k].Ey_arrai.SetSize(z+1);
					graf_E[k].Ez_arrai.SetSize(z+1);
					break;
				}

					
				
				if (graf_E[k].Ex_arrai.GetSize() < z+2)	
					graf_E[k].Ex_arrai.Add(p_x);
				else	
					graf_E[k].Ex_arrai[z+1]=p_x;

				
				if (graf_E[k].Ey_arrai.GetSize() < z+2)
					graf_E[k].Ey_arrai.Add(p_y);
				else
					graf_E[k].Ey_arrai[z+1]=p_y;


				if (graf_E[k].Ez_arrai.GetSize() < z+2)
					graf_E[k].Ez_arrai.Add(p_z);
				else
					graf_E[k].Ez_arrai[z+1]=p_z;			
			}
		

			k++;
		}
	}





	// 3º parte do guia - zona para trás de 'z_inicia_desenho_grafE'
	for (i = distA/2; i < a ; i += distA)
	{		
		for(j = distB/2 ; j < b ; j += distB)
		{
			p_x=i;
			p_y=j;	
			//p_z=z1-L/(Q*4);
			p_z=z_inicia_desenho_grafE+L;
		

			if ( graf_E[k].Ex_arrai.GetSize() < 1)	graf_E[k].Ex_arrai.Add(p_x);
			else	graf_E[k].Ex_arrai[0]=p_x;
			
					
			if (graf_E[k].Ey_arrai.GetSize() < 1)	graf_E[k].Ey_arrai.Add(p_y);
			else	graf_E[k].Ey_arrai[0]=p_y;

			if (graf_E[k].Ez_arrai.GetSize() < 1)	graf_E[k].Ez_arrai.Add(p_z);
			else	graf_E[k].Ez_arrai[0]=p_z;


			
			//for(z=l/Q;z<l;z=z+l/Q)
			for(z=0;z<Q;z++)
			{
				Vx=Ex(p_x,p_y,p_z,t).r;
				Vy=Ey(p_x,p_y,p_z,t).r;
				Vz=Ez(p_x,p_y,p_z,t).r;

				if (Vz >0 )//se é positivo, desenha para trás com a cor positiva
				{
					Vx=-Vx;
					Vy=-Vy;
					Vz=-Vz;
					
					graf_E[k].RedE=RedF;
					graf_E[k].GreenE=GreenF;
					graf_E[k].BlueE=BlueF;
				}
				else
				{
					graf_E[k].RedE=RedT;
					graf_E[k].GreenE=GreenT;
					graf_E[k].BlueE=BlueT;
				}
				
				
				Vmax=VectorMax(Vx,Vy,Vz);

				if ( Vmax > L/Q)
				{
					scaleVector=L/(Q*Vmax);
					Vx*=scaleVector; Vy*=scaleVector; Vz*=scaleVector;
				}
					
				p_x=p_x+Vx;	p_y=p_y+Vy;	p_z=p_z+Vz;

				//if (p_x<0 || p_x>a || p_y<0 || p_y>b || p_z<0 || p_z>z1)
				if (p_x<0 || p_x>a || p_y<0 || p_y>b || p_z<z2 || p_z> L*5/4 )
				{
					graf_E[k].Ex_arrai.SetSize(z+1);
					graf_E[k].Ey_arrai.SetSize(z+1);
					graf_E[k].Ez_arrai.SetSize(z+1);
					break;
				}

					
				
				if (graf_E[k].Ex_arrai.GetSize() < z+2)	
					graf_E[k].Ex_arrai.Add(p_x);
				else	
					graf_E[k].Ex_arrai[z+1]=p_x;

				
				if (graf_E[k].Ey_arrai.GetSize() < z+2)
					graf_E[k].Ey_arrai.Add(p_y);
				else
					graf_E[k].Ey_arrai[z+1]=p_y;


				if (graf_E[k].Ez_arrai.GetSize() < z+2)
					graf_E[k].Ez_arrai.Add(p_z);
				else
					graf_E[k].Ez_arrai[z+1]=p_z;			
			}
		

			k++;
		}
	}


}
*/


/*

void TMr::DrawE_Draw()
{

	int k;
	int i;
	int nLinhas;
	glPushMatrix();



	nLinhas=graf_E.GetSize();

	for(k=0;k<nLinhas;k++)
	{

	
		glColor3d( graf_E[k].RedE, graf_E[k].GreenE, graf_E[k].BlueE);

		glBegin(GL_LINE_STRIP);

		for(i=0;i<graf_E[k].Ex_arrai.GetSize();i++)
		{
						
			glVertex3d(	graf_E[k].Ex_arrai[i],
						graf_E[k].Ey_arrai[i],
						graf_E[k].Ez_arrai[i]);
		}

		glEnd();
	}



	glPopMatrix();
}*/

/*
double TMr::swap_cor(double cor1, double cor2, bool cor)
{
	if (cor)
		return cor1;
	else
		return cor2;
}*/

void TMr::DrawE_Draw(double t)
{
	int k;
	int i;
	int nLinhas;


	double L;
	double z1;//1º zero 
	double z2;//2º zero

	double Vz;
	bool Inverte_cor=false;


	nLinhas=graf_E.GetSize();

	L=GetLmn();

	
	GetZero_E(t,z1,z2);

	

	if (z1 > L/2)
		z1=z1-L/2;




		
	glPushMatrix();


	glTranslated(0,0,z1-L/4);


	k=0;
	Vz=Ez(graf_E[k].Ex_arrai[0],	graf_E[k].Ey_arrai[0],	z1-L/4-5*L/100,t).r;


	if (Vz >= 0)
		Inverte_cor=true;
	else
		Inverte_cor=false;


	//1ªparte do grafico

	for(k=0;k<nLinhas;k++)
	{

		
		if (Inverte_cor== true)
		{
			glColor3d( graf_E[k].RedE, graf_E[k].GreenE, graf_E[k].BlueE);
		}
		else
		{
			if (graf_E[k].RedE == RedF && graf_E[k].GreenE ==GreenF && graf_E[k].BlueE == BlueF)
				glColor3d( RedT, GreenT, BlueT);
			else
				glColor3d( RedF, GreenF, BlueF);
		}


	//	glColor3d( graf_E[k].RedE, graf_E[k].GreenE, graf_E[k].BlueE);
		

		glBegin(GL_LINE_STRIP);

		for(i=0;i<graf_E[k].Ex_arrai.GetSize();i++)
		{
		
			if (graf_E[k].Ez_arrai[i] > L/4-z1)
			{

				glVertex3d(	graf_E[k].Ex_arrai[i],
						graf_E[k].Ey_arrai[i],
						graf_E[k].Ez_arrai[i]);
		
			}

		}

		glEnd();
	}




	//3ªparte do grafico

	k=0;
	glTranslated(0,0,L);
	for(k=0;k<nLinhas;k++)
	{

	
		if (Inverte_cor== true)
		{
			glColor3d( graf_E[k].RedE, graf_E[k].GreenE, graf_E[k].BlueE);
		}
		else
		{
			if (graf_E[k].RedE == RedF && graf_E[k].GreenE ==GreenF && graf_E[k].BlueE == BlueF)
				glColor3d( RedT, GreenT, BlueT);
			else
				glColor3d( RedF, GreenF, BlueF);
		}
		

		
		glBegin(GL_LINE_STRIP);

		for(i=0;i<graf_E[k].Ex_arrai.GetSize();i++)
		{

			if (graf_E[k].Ez_arrai[i] < L/4-z1)
				glVertex3d(	graf_E[k].Ex_arrai[i],
						graf_E[k].Ey_arrai[i],
						graf_E[k].Ez_arrai[i]);
		}

		glEnd();
	}



	Inverte_cor=!Inverte_cor;



	k=0;
	glTranslated(0,0,-L/2);
	for(k=0;k<nLinhas;k++)
	{

		if (Inverte_cor== true)
		{
			glColor3d( graf_E[k].RedE, graf_E[k].GreenE, graf_E[k].BlueE);
		}
		else
		{
			if (graf_E[k].RedE == RedF && graf_E[k].GreenE ==GreenF && graf_E[k].BlueE == BlueF)
				glColor3d( RedT, GreenT, BlueT);
			else
				glColor3d( RedF, GreenF, BlueF);
		}
			
		
		glBegin(GL_LINE_STRIP);

		for(i=0;i<graf_E[k].Ex_arrai.GetSize();i++)
		{
						
			glVertex3d(	graf_E[k].Ex_arrai[i],
						graf_E[k].Ey_arrai[i],
						graf_E[k].Ez_arrai[i]);
		}

		glEnd();
	}

	glPopMatrix();




}


void TMr::DrawE_Draw_2Dz(double t)
{

	int k;
	double L;
	bool Inverte_cor=false;

	double r;
	double h;

	int nLinhas=graf_E.GetSize();

	L=GetLmn();
		
	glPushMatrix();



	/*	if (graf_E[0].Ez_arrai[k] > 0)
			glColor3d( RedF, GreenF, BlueF);
		else
			glColor3d( RedT, GreenT, BlueT);
	*/

	r=0.0002;//raio do cone
	h=0.0005;// altura do cone

	for(k=0;k<nLinhas;k++)
	{
		glColor3d(graf_E[k].RedE,graf_E[k].GreenE,graf_E[k].BlueE);		
	
		if (graf_E[k].GreenE==GreenF) //frente
		{
			Cone(graf_E[k].Ex_arrai[0],graf_E[k].Ey_arrai[0],graf_E[k].Ez_arrai[0],r,h);	

			glBegin(GL_LINE_STRIP);
			//glBegin(GL_POINTS);
			glVertex3d(	graf_E[k].Ex_arrai[0], graf_E[k].Ey_arrai[0], graf_E[k].Ez_arrai[0]);
			glVertex3d(	graf_E[k].Ex_arrai[0], graf_E[k].Ey_arrai[0], graf_E[k].Ez_arrai[0]+h);
			glEnd();

		}
		else
		{
			Cone(graf_E[k].Ex_arrai[0],graf_E[k].Ey_arrai[0],graf_E[k].Ez_arrai[0],r,-h);

			glBegin(GL_LINE_STRIP);
			//glBegin(GL_POINTS);
			glVertex3d(	graf_E[k].Ex_arrai[0], graf_E[k].Ey_arrai[0], graf_E[k].Ez_arrai[0]);
			glVertex3d(	graf_E[k].Ex_arrai[0], graf_E[k].Ey_arrai[0], graf_E[k].Ez_arrai[0]-h);
			glEnd();

		}


			

		
	}

	

	glPopMatrix();

}



void TMr:: DrawE_2Da(double t, double a)
{
  
	double Vx,Vy,Vz;	//vector
	double Vmax;		//vector maximo
	double p_x,p_y,p_z;	//point

	double i,j;
	int z;

	//nLinhasA=10;
	//nLinhasB=10;
	nLinhasA=NCamposx;
	nLinhasB=NCamposy;

	double distA;
	double distB;

	double L;
	double z1,z2;//pontos em que Ex se anula - limiar onde se começa a desenhar as linhas de força

	int k=0;	//contador das linhas de força
	double Q = 100;//factor qualidade, nº de linhas segmentos de cada linha de força
	double scaleVector;

	distA=a/nLinhasA;
	distB=b/nLinhasB;

	L=GetLmn();


	graf_E.SetSize(2*nLinhasB);

	z1=GetLmn()/4;
	z2=GetLmn()*3/4;

	i=a;



	//--Letras-------------------------------------------------------------

//	SmallFont  = FontCreateBitmaps(m_hDC, "Courier", 16,  FW_BOLD, 0);

//	glRasterPos3d(10,10,0);//-xx
	//FontPuts(SmallFont, "-x");

	

//	FontDelete(SmallFont);

//---------------------------------------------------------------------


	for(j = distB/2 ; j < b ; j += distB)
	{
		p_x=i;
		p_y=j;	
		//p_z=z1-L/(Q*4);
		p_z=z_inicia_desenho_grafE;
	
		if ( graf_E[k].Ex_arrai.GetSize() < 1)	graf_E[k].Ex_arrai.Add(p_x);
		else	graf_E[k].Ex_arrai[0]=p_x;
		
				
		if (graf_E[k].Ey_arrai.GetSize() < 1)	graf_E[k].Ey_arrai.Add(p_y);
		else	graf_E[k].Ey_arrai[0]=p_y;

		if (graf_E[k].Ez_arrai.GetSize() < 1)	graf_E[k].Ez_arrai.Add(p_z);
		else	graf_E[k].Ez_arrai[0]=p_z;

			
		//for(z=l/Q;z<l;z=z+l/Q)
		for(z=0;z<Q;z++)
		{
			Vx=Ex(p_x,p_y,p_z,t).r;
			Vy=Ey(p_x,p_y,p_z,t).r;
			Vz=Ez(p_x,p_y,p_z,t).r;

			if (Vz <0 )//se é negativo, desenha para a frente com a cor negativa
			{
				Vx=-Vx;
				Vy=-Vy;
				Vz=-Vz;
				
				graf_E[k].RedE=RedT;
				graf_E[k].GreenE=GreenT;
				graf_E[k].BlueE=BlueT;
			}
			else
			{
				graf_E[k].RedE=RedF;
				graf_E[k].GreenE=GreenF;
				graf_E[k].BlueE=BlueF;
			}
			
			Vmax=VectorMax(Vx,Vy,Vz);


			if ( Vmax > L/Q)
			{
				scaleVector=L/(Q*Vmax);
				Vx*=scaleVector; 
				Vy*=scaleVector; Vz*=scaleVector;
			}
				
			p_x=a;	
			p_y=p_y+Vy;	p_z=p_z+Vz;

			//if (p_x<0 || p_x>a || p_y<0 || p_y>b || p_z>z1)
			if (p_y<0 || p_y>b || p_z>z1)			
			{
				graf_E[k].Ex_arrai.SetSize(z+1);
				graf_E[k].Ey_arrai.SetSize(z+1);
				graf_E[k].Ez_arrai.SetSize(z+1);
				break;
			}
					
			
			if (graf_E[k].Ex_arrai.GetSize() < z+2)	
				graf_E[k].Ex_arrai.Add(p_x);
			else	
				graf_E[k].Ex_arrai[z+1]=p_x;

				
			if (graf_E[k].Ey_arrai.GetSize() < z+2)
				graf_E[k].Ey_arrai.Add(p_y);
			else
				graf_E[k].Ey_arrai[z+1]=p_y;


			if (graf_E[k].Ez_arrai.GetSize() < z+2)
				graf_E[k].Ez_arrai.Add(p_z);
			else
				graf_E[k].Ez_arrai[z+1]=p_z;			
		}
		

		k++;
	}






	// 1º parte do guia - zona para trás de 'z_inicia_desenho_grafE'
	for(j = distB/2 ; j < b ; j += distB)
	{
		p_x=i;
		p_y=j;	
		//p_z=z1-L/(Q*4);
		p_z=z_inicia_desenho_grafE;
	
		if ( graf_E[k].Ex_arrai.GetSize() < 1)	graf_E[k].Ex_arrai.Add(p_x);
		else	graf_E[k].Ex_arrai[0]=p_x;
			
					
		if (graf_E[k].Ey_arrai.GetSize() < 1)	graf_E[k].Ey_arrai.Add(p_y);
		else	graf_E[k].Ey_arrai[0]=p_y;

		if (graf_E[k].Ez_arrai.GetSize() < 1)	graf_E[k].Ez_arrai.Add(p_z);
		else	graf_E[k].Ez_arrai[0]=p_z;


			
		//for(z=l/Q;z<l;z=z+l/Q)
		for(z=0;z<Q;z++)
		{
			Vx=Ex(p_x,p_y,p_z,t).r;
			Vy=Ey(p_x,p_y,p_z,t).r;
			Vz=Ez(p_x,p_y,p_z,t).r;

			if (Vz >0 )//se é positivo, desenha para trás com a cor positiva
			{
				Vx=-Vx;
				Vy=-Vy;
				Vz=-Vz;
				
				graf_E[k].RedE=RedF;
				graf_E[k].GreenE=GreenF;
				graf_E[k].BlueE=BlueF;
			}
			else
			{
				graf_E[k].RedE=RedT;
				graf_E[k].GreenE=GreenT;
				graf_E[k].BlueE=BlueT;
			}
			
			
			Vmax=VectorMax(Vx,Vy,Vz);

			if ( Vmax > L/Q)
			{
				scaleVector=L/(Q*Vmax);
				Vx*=scaleVector; 
				Vy*=scaleVector; Vz*=scaleVector;
			}
				
			p_x=a;	
			p_y=p_y+Vy;	p_z=p_z+Vz;

			//if (p_x<0 || p_x>a || p_y<0 || p_y>b || p_z<0 || p_z>z1)
			if ( p_y<0 || p_y>b || p_z< (-z1) )
			{
				graf_E[k].Ex_arrai.SetSize(z+1);
				graf_E[k].Ey_arrai.SetSize(z+1);
				graf_E[k].Ez_arrai.SetSize(z+1);
				break;
			}

					
				
			if (graf_E[k].Ex_arrai.GetSize() < z+2)	
				graf_E[k].Ex_arrai.Add(p_x);
			else	
				graf_E[k].Ex_arrai[z+1]=p_x;
				

			if (graf_E[k].Ey_arrai.GetSize() < z+2)
				graf_E[k].Ey_arrai.Add(p_y);
			else
				graf_E[k].Ey_arrai[z+1]=p_y;


			if (graf_E[k].Ez_arrai.GetSize() < z+2)
				graf_E[k].Ez_arrai.Add(p_z);
			else
				graf_E[k].Ez_arrai[z+1]=p_z;			
		}
		

		k++;
	}
	
	

}






void TMr:: DrawE_2Db(double t, double b)
{
  
	double Vx,Vy,Vz;	//vector
	double Vmax;		//vector maximo
	double p_x,p_y,p_z;	//point

	double i,j;
	int z;

	//nLinhasA=10;
	//nLinhasB=10;
	nLinhasA=NCamposx;
	nLinhasB=NCamposy;

	double distA;
	double distB;

	double L;
	double z1,z2;//pontos em que Ex se anula - limiar onde se começa a desenhar as linhas de força

	int k=0;	//contador das linhas de força
	double Q = 100;//factor qualidade, nº de linhas segmentos de cada linha de força
	double scaleVector;

	distA=a/nLinhasA;
	distB=b/nLinhasB;

	L=GetLmn();


	graf_E.SetSize(2*nLinhasA);

	z1=GetLmn()/4;
	z2=GetLmn()*3/4;


	j=b;


	for(i = distA/2 ; i < a ; i += distA)
	{
		p_x=i;
		p_y=j;	
		//p_z=z1-L/(Q*4);
		p_z=z_inicia_desenho_grafE;
	
		if ( graf_E[k].Ex_arrai.GetSize() < 1)	graf_E[k].Ex_arrai.Add(p_x);
		else	graf_E[k].Ex_arrai[0]=p_x;
		
				
		if (graf_E[k].Ey_arrai.GetSize() < 1)	graf_E[k].Ey_arrai.Add(p_y);
		else	graf_E[k].Ey_arrai[0]=p_y;

		if (graf_E[k].Ez_arrai.GetSize() < 1)	graf_E[k].Ez_arrai.Add(p_z);
		else	graf_E[k].Ez_arrai[0]=p_z;

			
		//for(z=l/Q;z<l;z=z+l/Q)
		for(z=0;z<Q;z++)
		{
			Vx=Ex(p_x,p_y,p_z,t).r;
			Vy=Ey(p_x,p_y,p_z,t).r;
			Vz=Ez(p_x,p_y,p_z,t).r;

			if (Vz <0 )//se é negativo, desenha para a frente com a cor negativa
			{
				Vx=-Vx;
				Vy=-Vy;
				Vz=-Vz;
				
				graf_E[k].RedE=RedT;
				graf_E[k].GreenE=GreenT;
				graf_E[k].BlueE=BlueT;
			}
			else
			{
				graf_E[k].RedE=RedF;
				graf_E[k].GreenE=GreenF;
				graf_E[k].BlueE=BlueF;
			}
			
			Vmax=VectorMax(Vx,Vy,Vz);


			if ( Vmax > L/Q)
			{
				scaleVector=L/(Q*Vmax);
				Vx*=scaleVector; 
				Vy*=scaleVector; Vz*=scaleVector;
			}
				
			p_x=p_x+Vx;
			
			p_y=b;	
			
			p_z=p_z+Vz;

			//if (p_x<0 || p_x>a || p_y<0 || p_y>b || p_z>z1)
			if (p_x<0 || p_x>a || p_z>z1)			
			{
				graf_E[k].Ex_arrai.SetSize(z+1);
				graf_E[k].Ey_arrai.SetSize(z+1);
				graf_E[k].Ez_arrai.SetSize(z+1);
				break;
			}
					
			
			if (graf_E[k].Ex_arrai.GetSize() < z+2)	
				graf_E[k].Ex_arrai.Add(p_x);
			else	
				graf_E[k].Ex_arrai[z+1]=p_x;

				
			if (graf_E[k].Ey_arrai.GetSize() < z+2)
				graf_E[k].Ey_arrai.Add(p_y);
			else
				graf_E[k].Ey_arrai[z+1]=p_y;


			if (graf_E[k].Ez_arrai.GetSize() < z+2)
				graf_E[k].Ez_arrai.Add(p_z);
			else
				graf_E[k].Ez_arrai[z+1]=p_z;			
		}
		

		k++;
	}






	// 1º parte do guia - zona para trás de 'z_inicia_desenho_grafE'
	for(i = distA/2 ; i < a ; i += distA)
	{
		p_x=i;
		p_y=j;	
		//p_z=z1-L/(Q*4);
		p_z=z_inicia_desenho_grafE;
	
		if ( graf_E[k].Ex_arrai.GetSize() < 1)	graf_E[k].Ex_arrai.Add(p_x);
		else	graf_E[k].Ex_arrai[0]=p_x;
			
					
		if (graf_E[k].Ey_arrai.GetSize() < 1)	graf_E[k].Ey_arrai.Add(p_y);
		else	graf_E[k].Ey_arrai[0]=p_y;

		if (graf_E[k].Ez_arrai.GetSize() < 1)	graf_E[k].Ez_arrai.Add(p_z);
		else	graf_E[k].Ez_arrai[0]=p_z;


			
		//for(z=l/Q;z<l;z=z+l/Q)
		for(z=0;z<Q;z++)
		{
			Vx=Ex(p_x,p_y,p_z,t).r;
			Vy=Ey(p_x,p_y,p_z,t).r;
			Vz=Ez(p_x,p_y,p_z,t).r;

			if (Vz >0 )//se é positivo, desenha para trás com a cor positiva
			{
				Vx=-Vx;
				Vy=-Vy;
				Vz=-Vz;
				
				graf_E[k].RedE=RedF;
				graf_E[k].GreenE=GreenF;
				graf_E[k].BlueE=BlueF;
			}
			else
			{
				graf_E[k].RedE=RedT;
				graf_E[k].GreenE=GreenT;
				graf_E[k].BlueE=BlueT;
			}
			
			
			Vmax=VectorMax(Vx,Vy,Vz);

			if ( Vmax > L/Q)
			{
				scaleVector=L/(Q*Vmax);
				Vx*=scaleVector; 
				Vy*=scaleVector; Vz*=scaleVector;
			}
				
			p_x=p_x+Vx;
						
			p_y=b;	
			
			p_z=p_z+Vz;

			//if (p_x<0 || p_x>a || p_y<0 || p_y>b || p_z<0 || p_z>z1)
			if ( p_x<0 || p_x>a || p_z< (-z1) )
			{
				graf_E[k].Ex_arrai.SetSize(z+1);
				graf_E[k].Ey_arrai.SetSize(z+1);
				graf_E[k].Ez_arrai.SetSize(z+1);
				break;
			}

					
				
			if (graf_E[k].Ex_arrai.GetSize() < z+2)	
				graf_E[k].Ex_arrai.Add(p_x);
			else	
				graf_E[k].Ex_arrai[z+1]=p_x;
				

			if (graf_E[k].Ey_arrai.GetSize() < z+2)
				graf_E[k].Ey_arrai.Add(p_y);
			else
				graf_E[k].Ey_arrai[z+1]=p_y;


			if (graf_E[k].Ez_arrai.GetSize() < z+2)
				graf_E[k].Ez_arrai.Add(p_z);
			else
				graf_E[k].Ez_arrai[z+1]=p_z;			
		}
		

		k++;
	}
	
	

}




void TMr:: DrawE_2Dz(double t, double z)
{
  
	
	double Vz;	//vector
	double i,j;


	nLinhasA=NCamposx;
	nLinhasB=NCamposy;

	double distA;
	double distB;


	int k;		//contador das linhas de força


	distA=a/nLinhasA;
	distB=b/nLinhasB;

//	L=GetLmn();



	graf_E.SetSize(nLinhasA*nLinhasB);



	k=0;
	for (i = distA/2; i < a ; i += distA)
	{		
		for(j = distB/2 ; j < b ; j += distB)
		{
	
	
			Vz=Ez(i,j,z,t).r;

			graf_E[k].Ex_arrai.SetSize(1);
			graf_E[k].Ey_arrai.SetSize(1);
			graf_E[k].Ez_arrai.SetSize(1);

		
			graf_E[k].Ex_arrai[0]=i;
			graf_E[k].Ey_arrai[0]=j;
			graf_E[k].Ez_arrai[0]=z;


			if (Vz >0 )//se é positivo, desenha para a frente com a cor positiva
			{
				graf_E[k].RedE=RedF;
				graf_E[k].GreenE=GreenF;
				graf_E[k].BlueE=BlueF;				
			}
			else
			{
				graf_E[k].RedE=RedT;
				graf_E[k].GreenE=GreenT;
				graf_E[k].BlueE=BlueT;
			}
			

			k++;

						
		}
		

	}



	

}






/*
void TMr::DrawH(double t)
{

	double Vx,Vy,Vz;	//vector
	double Vmax;		//vector maximo
	double p_x,p_y,p_z;	//point


	double z;
	double Q = 100;//factor qualidade, nº de linhas segmentos de cada linha de força
	int l;
	double scaleVector;

	double largura;
	double distA;//distancia entre as linhas de força no eixo x
	double distB;//distancia entre as linhas de força no eixo y
	int nLinhasA;
	int nLinhasB;
	double distAm;// distancia do modo m
	double distBn;// distancia do modo n
	double i, j;
	double ii, jj;
	int k;

	double L=GetLmn();
	
	int NCampos=6;//numero de campos a desenhar ao longo do eixo z

	//distância entre campos, o comprimetno de onda L é divido em 'NCampos+1' espaços iguais
	double LSpace=L/(NCampos);

	distAm=a/m;
	distBn=b/n;

	nLinhasA=6;
	nLinhasB=6;

	if (a < b)
		largura=a;
	else
		largura=b;

	//distR=diametro/nLinhasR;
	
	distA=a/nLinhasA;
	distB=b/nLinhasB;


	graf_H.SetSize( (NCampos+1)*nLinhasA*nLinhasB);// ?
	//graf_H.SetSize( NCampos*nLinhasR*2);


	
	k=0;
//	i=distA/2;
//	j=distB/2;



	for(z=LSpace/2; z < L; z = z+LSpace)
	{

		for (i = distA/2; i < a ; i += distA)
		{
			for (j = distB/2; j < b ; j += distB)
			{
			
				p_x=i;p_y=j;	
				p_z=z;



				if (graf_H[k].Hx_arrai.GetSize() < 1)
					graf_H[k].Hx_arrai.Add(p_x);
				else
					graf_H[k].Hx_arrai[0]=p_x;
						
				if (graf_H[k].Hy_arrai.GetSize() < 1)
					graf_H[k].Hy_arrai.Add(p_y);
				else
					graf_H[k].Hy_arrai[0]=p_y;

				if (graf_H[k].Hz_arrai.GetSize() < 1)
					graf_H[k].Hz_arrai.Add(p_z);
				else
					graf_H[k].Hz_arrai[0]=p_z;

											
				
				graf_H[k].RedH=RedT;
				graf_H[k].GreenH=GreenT;
				graf_H[k].BlueH=BlueT;


				/////---detecta se a linha do campo magnetico----------
				/////---gira no sentido horario ou anti-horario--------

				Vx=Hx(p_x,p_y,p_z,t).r;	
				Vy=Hy(p_x,p_y,p_z,t).r;

				for(ii=distAm;ii<=a;ii+=distAm)
				{
					for(jj=distBn;jj<=b;jj+=distBn)
					{
						if ( ((ii-distAm) < Vx) &&  ( Vx < ii ) 
							&& ( (jj-distBn) < Vy) &&   (Vy < jj) )
						{

							if ( Vy >=  (jj-distBn)/2 )//parte superior
							{


							}
							else //parte inferior
							{


							}

						}
					}
				}



				/////---fim--------------------------------------------


				for(l=0;l<Q;l++)
				{
								
					Vx=Hx(p_x,p_y,p_z,t).r;
					Vy=Hy(p_x,p_y,p_z,t).r;
					//Vz=Hz(p_x,p_y,p_z,t).r;
					Vz=0;

					Vmax=VectorMax(Vx,Vy,0);

						
					if ( Vmax > largura/Q)
					{
						scaleVector=largura/(Q*Vmax);
						Vx*=scaleVector; Vy*=scaleVector; //Vz*=scaleVector;
					}
							
					p_x=p_x+Vx;	p_y=p_y+Vy;		//p_z=p_z+Vz;


					if (p_x<0 || p_x>a || p_y<0 || p_y>b || p_z<0 || p_z>L)
					{
						graf_H[k].Hx_arrai.SetSize(l+1);
						graf_H[k].Hy_arrai.SetSize(l+1);
						graf_H[k].Hz_arrai.SetSize(l+1);
						break;
					}
						

									

					if (graf_H[k].Hx_arrai.GetSize() < l+2)
						graf_H[k].Hx_arrai.Add(p_x);
					else
						graf_H[k].Hx_arrai[l+1]=p_x;

					if (graf_H[k].Hy_arrai.GetSize() < l+2)
						graf_H[k].Hy_arrai.Add(p_y);
					else
						graf_H[k].Hy_arrai[l+1]=p_y;


					if (graf_H[k].Hz_arrai.GetSize() < l+2)
						graf_H[k].Hz_arrai.Add(p_z);
					else
						graf_H[k].Hz_arrai[l+1]=p_z;
						
					
				}

			
				k++;

			}
		}			
		
	}


}*/




void TMr::DrawH_alternativo(double t)
{

	double Vx,Vy,Vz;	//vector
	double VxBreak;
	double Vmax;		//vector maximo
	double p_x,p_y,p_z;	//point


	double Q = 500;//factor qualidade, nº de linhas segmentos de cada linha de força
	int l;
	double scaleVector;

	double largura;
	double distA;
	double distB;
	double distR;
	double spacej;
	int mm;
	int nn;
//	int nLinhasA;
//	int nLinhasB;
	double i, j;
	double z;
	int k;

	double L=GetLmn();
	

	
	//distância entre campos, o comprimento de onda L é divido em 'NCampos+1' espaços iguais
	double LSpace=L/(NCamposZ);

	
	if (a > b)
		largura=a;
	else
		largura=b;


	//distR=diametro/nLinhasR;
	
	distA=a/m;
	distB=b/n;
	distR=distB/2; // =b/(2*n);
	
	spacej=distR/NCamposJ; // =b/(2*n*NCampos)


	//graf_H.SetSize( 2*NCamposZ*(NCamposJ)*m*n);
	graf_H.SetSize( 2*NCamposZ*(NCamposJ)*m*n);



	k=0;

	//for(z=LSpace; z < L; z = z+LSpace)
	for(z=LSpace/2; z < L; z = z+LSpace)
	{
		for(nn=0;nn<n;nn++)
		{

			for(mm=0;mm<m;mm++)
			{
				i=distA/2+ distA*mm;



				for( j=spacej/2 + nn*distB; j < distR + nn*distB ; j=j+spacej )
				{

					p_x=i;p_y=j;	
					p_z=z;


					if (graf_H[k].Hx_arrai.GetSize() < 1)	graf_H[k].Hx_arrai.Add(p_x);
					else	graf_H[k].Hx_arrai[0]=p_x;
							
					if (graf_H[k].Hy_arrai.GetSize() < 1)	graf_H[k].Hy_arrai.Add(p_y);
					else	graf_H[k].Hy_arrai[0]=p_y;

					if (graf_H[k].Hz_arrai.GetSize() < 1)	graf_H[k].Hz_arrai.Add(p_z);
					else	graf_H[k].Hz_arrai[0]=p_z;

					
					if ( Hx(p_x,p_y,p_z,t).r >= 0 )
					{
						graf_H[k].RedH=RedHF;	graf_H[k].GreenH=GreenHF;	graf_H[k].BlueH=BlueHF;
					}
					else
					{
						graf_H[k].RedH=RedHT;	graf_H[k].GreenH=GreenHT;	graf_H[k].BlueH=BlueHT;
					}



					Vx=Hx(p_x,p_y,p_z,t).r;
					Vy=Hy(p_x,p_y,p_z,t).r;
					Vz=0;

					VxBreak=Vx;

					Vmax=VectorMax(Vx,Vy,0);



					for(l=0;l<Q*NCamposJ;l++)
					{
									
						Vx=Hx(p_x,p_y,p_z,t).r;
						Vy=Hy(p_x,p_y,p_z,t).r;
						//Vz=Hz(p_x,p_y,p_z,t).r;
						Vz=0;

					
						scaleVector=largura/(Q*Vmax);
						Vx*=scaleVector; Vy*=scaleVector; //Vz*=scaleVector;
													
						p_x=p_x+Vx;	p_y=p_y+Vy;		//p_z=p_z+Vz;


						if (VxBreak > 0)
						{
							if (p_x < i)
							{
								graf_H[k].Hx_arrai.SetSize(l+1);
								graf_H[k].Hy_arrai.SetSize(l+1);
								graf_H[k].Hz_arrai.SetSize(l+1);
								break;
							}
						}
						else
						{
							if (p_x > i)
							{
								graf_H[k].Hx_arrai.SetSize(l+1);
								graf_H[k].Hy_arrai.SetSize(l+1);
								graf_H[k].Hz_arrai.SetSize(l+1);
								break;
							}
						}

					

						
						if (graf_H[k].Hx_arrai.GetSize() < l+2)
							graf_H[k].Hx_arrai.Add(p_x);
						else
							graf_H[k].Hx_arrai[l+1]=p_x;

						if (graf_H[k].Hy_arrai.GetSize() < l+2)
							graf_H[k].Hy_arrai.Add(p_y);
						else
							graf_H[k].Hy_arrai[l+1]=p_y;


						if (graf_H[k].Hz_arrai.GetSize() < l+2)
							graf_H[k].Hz_arrai.Add(p_z);
						else
							graf_H[k].Hz_arrai[l+1]=p_z;


					}


					k++;

				}







				for( j=distB-spacej/2 + nn*distB; j > distR + nn*distB ; j=j-spacej )
				{

					p_x=i;p_y=j;	
					p_z=z;


					if (graf_H[k].Hx_arrai.GetSize() < 1)	graf_H[k].Hx_arrai.Add(p_x);
					else	graf_H[k].Hx_arrai[0]=p_x;
							
					if (graf_H[k].Hy_arrai.GetSize() < 1)	graf_H[k].Hy_arrai.Add(p_y);
					else	graf_H[k].Hy_arrai[0]=p_y;

					if (graf_H[k].Hz_arrai.GetSize() < 1)	graf_H[k].Hz_arrai.Add(p_z);
					else	graf_H[k].Hz_arrai[0]=p_z;

					
					if ( Hx(p_x,p_y,p_z,t).r >= 0 )
					{
						graf_H[k].RedH=RedHT;	graf_H[k].GreenH=GreenHT;	graf_H[k].BlueH=BlueHT;
					}
					else
					{
						graf_H[k].RedH=RedHF;	graf_H[k].GreenH=GreenHF;	graf_H[k].BlueH=BlueHF;
					}



					Vx=Hx(p_x,p_y,p_z,t).r;
					Vy=Hy(p_x,p_y,p_z,t).r;
					Vz=0;
					VxBreak=Vx;

					Vmax=VectorMax(Vx,Vy,0);



					for(l=0;l<Q*NCamposJ;l++)
					{
									
						Vx=Hx(p_x,p_y,p_z,t).r;
						Vy=Hy(p_x,p_y,p_z,t).r;
						//Vz=Hz(p_x,p_y,p_z,t).r;
						Vz=0;

					
						scaleVector=largura/(Q*Vmax);
						Vx*=scaleVector; Vy*=scaleVector; //Vz*=scaleVector;
				
								
						p_x=p_x+Vx;	p_y=p_y+Vy;		//p_z=p_z+Vz;


					
						if (VxBreak > 0)
						{
							if (p_x < i)
							{
								graf_H[k].Hx_arrai.SetSize(l+1);
								graf_H[k].Hy_arrai.SetSize(l+1);
								graf_H[k].Hz_arrai.SetSize(l+1);
								break;
							}
						}
						else
						{
							if (p_x > i)
							{
								graf_H[k].Hx_arrai.SetSize(l+1);
								graf_H[k].Hy_arrai.SetSize(l+1);
								graf_H[k].Hz_arrai.SetSize(l+1);
								break;
							}
						}


					
						
						if (graf_H[k].Hx_arrai.GetSize() < l+2)
							graf_H[k].Hx_arrai.Add(p_x);
						else
							graf_H[k].Hx_arrai[l+1]=p_x;

						if (graf_H[k].Hy_arrai.GetSize() < l+2)
							graf_H[k].Hy_arrai.Add(p_y);
						else
							graf_H[k].Hy_arrai[l+1]=p_y;


						if (graf_H[k].Hz_arrai.GetSize() < l+2)
							graf_H[k].Hz_arrai.Add(p_z);
						else
							graf_H[k].Hz_arrai[l+1]=p_z;


					}


					k++;

				}



			}

		}
	}




}




void TMr::DrawH_Draw(double t)
{

	int k;
	int i;
	int nLinhas;

	double L;
	double z1;//1º zero 
	double z2;//2º zero
	double Vx;


	bool Inverte_cor=false;

		
	L=GetLmn();
	GetZero_H(t,z1,z2);



	glPushMatrix();
	glTranslated(0,0,z1-L/2);

	
	nLinhas=graf_H.GetSize();

	k=0;
	Vx=Hx(graf_H[k].Hx_arrai[0], graf_H[k].Hy_arrai[0],	z1-L/2,t).r;


	if (Vx >= 0)
		Inverte_cor=true;
	else
		Inverte_cor=false;



	
	for(k=0;k<nLinhas;k++)
	{

	
		if (Inverte_cor==true)
			glColor3d(graf_H[k].RedH,graf_H[k].GreenH,graf_H[k].BlueH);
		else
		{
			if (graf_H[k].RedH == RedHF && graf_H[k].GreenH == GreenHF && graf_H[k].BlueH ==BlueHF)
				glColor3d(RedHT,GreenHT,BlueHT);
			else
				glColor3d(RedHF,GreenHF,BlueHF);
		}

		
//		glColor3d(graf_H[k].RedH,graf_H[k].GreenH,graf_H[k].BlueH);


		
		glPushMatrix();
		if ( ( graf_H[k].Hz_arrai[0] + z1-L/2 ) > L)
			glTranslated(0,0,-L);



		glBegin(GL_LINE_STRIP);

		for(i=0;i<graf_H[k].Hx_arrai.GetSize();i++)
		{
						
			glVertex3d(	graf_H[k].Hx_arrai[i],
						graf_H[k].Hy_arrai[i],
						graf_H[k].Hz_arrai[i]);
		}

		glEnd();


		glPopMatrix();
	}



	glPopMatrix();

}


