// TEr.cpp: implementation of the TEr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "campos3d.h"
#include "TEr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TEr::TEr()
{
		
	//cores para frente
	RedF=0;
	GreenF=0;
	BlueF=1;

	//cores para trás
	RedT=0;
	GreenT=1;
	BlueT=1;



	NCamposx=10;
	NCamposy=10;

	z_inicia_desenho_grafH=0;
}

/*TEr::TEr(double a_, double b_, double freq_, double Er_, double Ur_)
{
	a=a_;
	b=b_;
	f=freq_;
	Er=Er_;
	Ur=Ur_;
}*/


TEr::~TEr()
{

}



Complexo TEr::Ex(double x,double y,double z, double t)
{
	Complexo j(0,1);
	Complexo zero(0,0);
	double M_=M();
	double N_=N();
	double W=GetW();
	double U=GetU();
	Complexo ab=alfaB();

	if (W==0)return zero;
	if (U==0)return zero;
	if (N_==0)return zero;


	return j*W*U*N_/(pow(M_,2)+pow(N_,2))
		*cos(M_*x)*sin(N_*y)*exp(j*W*t-ab*z);
}

Complexo TEr::Ey(double x,double y,double z, double t)
{
	Complexo j(0,1);
	Complexo zero(0,0);
	double M_=M();
	double N_=N();
	double W=GetW();
	double U=GetU();
	Complexo ab=alfaB();

	if (W==0)return zero;
	if (U==0)return zero;
	if (M_==0)return zero;

	return -j*W*U*M_/(pow(M_,2)+pow(N_,2))
		*sin(M_*x)*cos(N_*y)*exp(j*W*t-ab*z);
}

Complexo TEr::Ez(double x,double y,double z, double t)
{
	Complexo Ez(0,0);
	return Ez;
}

Complexo TEr::Hx(double x,double y,double z, double t)
{
	Complexo j(0,1);
	Complexo zero(0,0);
	double M_=M();
	double N_=N();
	double W=GetW();
	double U=GetU();
	Complexo ab=alfaB();

	if (M_==0)return zero;

	return ab*M_/(pow(M_,2)+pow(N_,2))
		*sin(M_*x)*cos(N_*y)*exp(j*W*t-ab*z);


}

Complexo TEr::Hy(double x,double y,double z, double t)
{
	Complexo j(0,1);
	Complexo zero(0,0);
	double M_=M();
	double N_=N();
	double W=GetW();
	double U=GetU();
	Complexo ab=alfaB();


	return ab*N_/(pow(M_,2)+pow(N_,2))
		*cos(M_*x)*sin(N_*y)*exp(j*W*t-ab*z);
}

Complexo TEr::Hz(double x,double y,double z, double t)
{
	Complexo j(0,1);
	Complexo zero(0,0);
	double M_=M();
	double N_=N();
	double W=GetW();
	double U=GetU();
	Complexo ab=alfaB();

	return cos(M_*x)*cos(N_*y)*exp(j*W*t-ab*z);
} 

double TEr::Sav_z(double x,double y,double z, double t)
{
	return (Ex(x,y,z,t)*conj(Hy(x,y,z,t))
		-Ey(x,y,z,t)*conj(Hx(x,y,z,t))).r/2;
}


//funcao que calcula os pontos do campo electrico

void TEr::DrawE( double t)
{

	
	double Vx,Vy,Vz;	//vector
	double Vmax;		//vector maximo
	double p_x,p_y,p_z;	//point
	
	double z;
	
	double Q = 100;//factor qualidade, nº de linhas segmentos de cada linha de força
	int l;
	double scaleVector;

	double L=GetLmn();
	
	double NCampos=6;
	double LSpace=L/NCampos;

	double distA;
	double distB;
	double nLinhasA;
	double nLinhasB;
	double largura;
	double i, j;
//	double t=0;
	int k;


	nLinhasA=4;
	nLinhasB=4;

	distA=a/nLinhasA;
	distB=b/nLinhasB;

	if (a < b)
		largura=a;
	else
		largura=b;
	

	graf_H.SetSize(int((5+2)*nLinhasA*nLinhasB));


	k=0;
	i=distA/2;
	j=distB/2;


	for(z=LSpace; z <= L; z = z+LSpace)
	{
		for (i = distA/2; i < a ; i += distA)
		{
			for(j = distB/2 ; j < b ; j += distB)
			{
				p_x=i;p_y=j;	
				p_z=z;

				
				
				//if (graf_H[k].Hx_arrai.GetSize() < 1)	graf_H[k].Hx_arrai.Add(p_x);
				//	else	graf_H[k].Hx_arrai[0]=p_x;
					

				//Hx_arrai
				if (graf_H[k].Hx_arrai.GetSize() < 1)	graf_H[k].Hx_arrai.Add(p_x);
				else	graf_H[k].Hx_arrai[0]=p_x;
					
						
				if (graf_H[k].Hy_arrai.GetSize() < 1)	graf_H[k].Hy_arrai.Add(p_y);
				else	graf_H[k].Hy_arrai[0]=p_y;
					

				if (graf_H[k].Hz_arrai.GetSize() < 1)	graf_H[k].Hz_arrai.Add(p_z);
				else
					graf_H[k].Hz_arrai[0]=p_z;
					

				l=0;

				
				

				for(l=0;l<Q;l++)
				{
								
					Vx=Ex(p_x,p_y,p_z,t).r;
					Vy=Ey(p_x,p_y,p_z,t).r;
					Vz=Ez(p_x,p_y,p_z,t).r;

					Vmax=VectorMax(Vx,Vy,Vz);

					
					if ( Vmax > largura/Q)
					{
						scaleVector=largura/(Q*Vmax);
						Vx*=scaleVector; Vy*=scaleVector; Vz*=scaleVector;
					}
						
					p_x=p_x+Vx;	p_y=p_y+Vy;	p_z=p_z+Vz;


					if (p_x<0 || p_x>a || p_y<0 || p_y>b || p_z<0 || p_z>L)
					{
						graf_H[k].Hx_arrai.SetSize(l+1);
						graf_H[k].Hy_arrai.SetSize(l+1);
						graf_H[k].Hz_arrai.SetSize(l+1);
						break;
					}
					

				/*	int jj=pDoc->RH.GetSize();
					if (pDoc->RH.GetSize() < l-1)
					{
						pDoc->RH[l+1]=pDoc->RedF;
						pDoc->GH[l+1]=pDoc->GreenF;
						pDoc->BH[l+1]=pDoc->BlueF;
					}
					else
					{					
						pDoc->RH.Add(pDoc->RedT);
						pDoc->GH.Add(pDoc->GreenT);
						pDoc->BH.Add(pDoc->BlueT);					
					}*/
					

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




	




};




//funcao que desenha os pontos do campo electrico
void TEr::DrawE_Draw()
{


}

void TEr::GetZero_H(double t, double &z1, double &z2)
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

void TEr::DrawH( double t)
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


	graf_H.SetSize(6*nLinhasA*nLinhasB);


//	GetZero_E(t,z1,z2);

	//t=0;
//	GetZero_E(t,z1,z2);

	z1=GetLmn()/4;
	z2=GetLmn()*3/4;






//	z_inicia_desenho_grafE=GetLmn()/8;


	// 1º parte do guia - zona para frente de 'z_inicia_desenho_grafE'
	for (i = distA/2; i < a ; i += distA)
	{		
		for(j = distB/2 ; j < b ; j += distB)
		{
			p_x=i;
			p_y=j;	
			//p_z=z1-L/(Q*4);
			p_z=z_inicia_desenho_grafH;
		

			if ( graf_H[k].Hx_arrai.GetSize() < 1)	graf_H[k].Hx_arrai.Add(p_x);
			else	graf_H[k].Hx_arrai[0]=p_x;
			
					
			if (graf_H[k].Hy_arrai.GetSize() < 1)	graf_H[k].Hy_arrai.Add(p_y);
			else	graf_H[k].Hy_arrai[0]=p_y;

			if (graf_H[k].Hz_arrai.GetSize() < 1)	graf_H[k].Hz_arrai.Add(p_z);
			else	graf_H[k].Hz_arrai[0]=p_z;


			
			//for(z=l/Q;z<l;z=z+l/Q)
			for(z=0;z<Q;z++)
			{
				Vx=Hx(p_x,p_y,p_z,t).r;
				Vy=Hy(p_x,p_y,p_z,t).r;
				Vz=Hz(p_x,p_y,p_z,t).r;

				if (Vz <0 )//se é negativo, desenha para a frente com a cor negativa
				{
					Vx=-Vx;
					Vy=-Vy;
					Vz=-Vz;
					
					graf_H[k].RedH=RedT;
					graf_H[k].GreenH=GreenT;
					graf_H[k].BlueH=BlueT;
				}
				else
				{
					graf_H[k].RedH=RedF;
					graf_H[k].GreenH=GreenF;
					graf_H[k].BlueH=BlueF;
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
					graf_H[k].Hx_arrai.SetSize(z+1);
					graf_H[k].Hy_arrai.SetSize(z+1);
					graf_H[k].Hz_arrai.SetSize(z+1);
					break;
				}

					
				
				if (graf_H[k].Hx_arrai.GetSize() < z+2)	
					graf_H[k].Hx_arrai.Add(p_x);
				else	
					graf_H[k].Hx_arrai[z+1]=p_x;

				
				if (graf_H[k].Hy_arrai.GetSize() < z+2)
					graf_H[k].Hy_arrai.Add(p_y);
				else
					graf_H[k].Hy_arrai[z+1]=p_y;


				if (graf_H[k].Hz_arrai.GetSize() < z+2)
					graf_H[k].Hz_arrai.Add(p_z);
				else
					graf_H[k].Hz_arrai[z+1]=p_z;			
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
		

			if ( graf_H[k].Hx_arrai.GetSize() < 1)	graf_H[k].Hx_arrai.Add(p_x);
			else	graf_H[k].Hx_arrai[0]=p_x;
			
					
			if (graf_H[k].Hy_arrai.GetSize() < 1)	graf_H[k].Hy_arrai.Add(p_y);
			else	graf_H[k].Hy_arrai[0]=p_y;

			if (graf_H[k].Hz_arrai.GetSize() < 1)	graf_H[k].Hz_arrai.Add(p_z);
			else	graf_H[k].Hz_arrai[0]=p_z;


			
			//for(z=l/Q;z<l;z=z+l/Q)
			for(z=0;z<Q;z++)
			{
				Vx=Hx(p_x,p_y,p_z,t).r;
				Vy=Hy(p_x,p_y,p_z,t).r;
				Vz=Hz(p_x,p_y,p_z,t).r;

				if (Vz >0 )//se é positivo, desenha para trás com a cor positiva
				{
					Vx=-Vx;
					Vy=-Vy;
					Vz=-Vz;
					
					graf_H[k].RedH=RedF;
					graf_H[k].GreenH=GreenF;
					graf_H[k].BlueH=BlueF;
				}
				else
				{
					graf_H[k].RedH=RedT;
					graf_H[k].GreenH=GreenT;
					graf_H[k].BlueH=BlueT;
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
					graf_H[k].Hx_arrai.SetSize(z+1);
					graf_H[k].Hy_arrai.SetSize(z+1);
					graf_H[k].Hz_arrai.SetSize(z+1);
					break;
				}

					
				
				if (graf_H[k].Hx_arrai.GetSize() < z+2)	
					graf_H[k].Hx_arrai.Add(p_x);
				else	
					graf_H[k].Hx_arrai[z+1]=p_x;

				
				if (graf_H[k].Hy_arrai.GetSize() < z+2)
					graf_H[k].Hy_arrai.Add(p_y);
				else
					graf_H[k].Hy_arrai[z+1]=p_y;


				if (graf_H[k].Hz_arrai.GetSize() < z+2)
					graf_H[k].Hz_arrai.Add(p_z);
				else
					graf_H[k].Hz_arrai[z+1]=p_z;			
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
		

			if ( graf_H[k].Hx_arrai.GetSize() < 1)	graf_H[k].Hx_arrai.Add(p_x);
			else	graf_H[k].Hx_arrai[0]=p_x;
			
					
			if (graf_H[k].Hy_arrai.GetSize() < 1)	graf_H[k].Hy_arrai.Add(p_y);
			else	graf_H[k].Hy_arrai[0]=p_y;

			if (graf_H[k].Hz_arrai.GetSize() < 1)	graf_H[k].Hz_arrai.Add(p_z);
			else	graf_H[k].Hz_arrai[0]=p_z;


			
			//for(z=l/Q;z<l;z=z+l/Q)
			for(z=0;z<Q;z++)
			{
				Vx=Hx(p_x,p_y,p_z,t).r;
				Vy=Hy(p_x,p_y,p_z,t).r;
				Vz=Hz(p_x,p_y,p_z,t).r;

				if (Vz <0 )//se é negativo, desenha para a frente com a cor negativa
				{
					Vx=-Vx;
					Vy=-Vy;
					Vz=-Vz;
					
					graf_H[k].RedH=RedT;
					graf_H[k].GreenH=GreenT;
					graf_H[k].BlueH=BlueT;
				}
				else
				{
					graf_H[k].RedH=RedF;
					graf_H[k].GreenH=GreenF;
					graf_H[k].BlueH=BlueF;
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
					graf_H[k].Hx_arrai.SetSize(z+1);
					graf_H[k].Hy_arrai.SetSize(z+1);
					graf_H[k].Hz_arrai.SetSize(z+1);
					break;
				}

					
				
				if (graf_H[k].Hx_arrai.GetSize() < z+2)	
					graf_H[k].Hx_arrai.Add(p_x);
				else	
					graf_H[k].Hx_arrai[z+1]=p_x;

				
				if (graf_H[k].Hy_arrai.GetSize() < z+2)
					graf_H[k].Hy_arrai.Add(p_y);
				else
					graf_H[k].Hy_arrai[z+1]=p_y;


				if (graf_H[k].Hz_arrai.GetSize() < z+2)
					graf_H[k].Hz_arrai.Add(p_z);
				else
					graf_H[k].Hz_arrai[z+1]=p_z;			
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
		

			if ( graf_H[k].Hx_arrai.GetSize() < 1)	graf_H[k].Hx_arrai.Add(p_x);
			else	graf_H[k].Hx_arrai[0]=p_x;
			
					
			if (graf_H[k].Hy_arrai.GetSize() < 1)	graf_H[k].Hy_arrai.Add(p_y);
			else	graf_H[k].Hy_arrai[0]=p_y;

			if (graf_H[k].Hz_arrai.GetSize() < 1)	graf_H[k].Hz_arrai.Add(p_z);
			else	graf_H[k].Hz_arrai[0]=p_z;


			
			//for(z=l/Q;z<l;z=z+l/Q)
			for(z=0;z<Q;z++)
			{
				Vx=Hx(p_x,p_y,p_z,t).r;
				Vy=Hy(p_x,p_y,p_z,t).r;
				Vz=Hz(p_x,p_y,p_z,t).r;

				if (Vz >0 )//se é positivo, desenha para trás com a cor positiva
				{
					Vx=-Vx;
					Vy=-Vy;
					Vz=-Vz;
					
					graf_H[k].RedH=RedF;
					graf_H[k].GreenH=GreenF;
					graf_H[k].BlueH=BlueF;
				}
				else
				{
					graf_H[k].RedH=RedT;
					graf_H[k].GreenH=GreenT;
					graf_H[k].BlueH=BlueT;
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
					graf_H[k].Hx_arrai.SetSize(z+1);
					graf_H[k].Hy_arrai.SetSize(z+1);
					graf_H[k].Hz_arrai.SetSize(z+1);
					break;
				}

					
				
				if (graf_H[k].Hx_arrai.GetSize() < z+2)	
					graf_H[k].Hx_arrai.Add(p_x);
				else	
					graf_H[k].Hx_arrai[z+1]=p_x;

				
				if (graf_H[k].Hy_arrai.GetSize() < z+2)
					graf_H[k].Hy_arrai.Add(p_y);
				else
					graf_H[k].Hy_arrai[z+1]=p_y;


				if (graf_H[k].Hz_arrai.GetSize() < z+2)
					graf_H[k].Hz_arrai.Add(p_z);
				else
					graf_H[k].Hz_arrai[z+1]=p_z;			
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
		

			if ( graf_H[k].Hx_arrai.GetSize() < 1)	graf_H[k].Hx_arrai.Add(p_x);
			else	graf_H[k].Hx_arrai[0]=p_x;
			
					
			if (graf_H[k].Hy_arrai.GetSize() < 1)	graf_H[k].Hy_arrai.Add(p_y);
			else	graf_H[k].Hy_arrai[0]=p_y;

			if (graf_H[k].Hz_arrai.GetSize() < 1)	graf_H[k].Hz_arrai.Add(p_z);
			else	graf_H[k].Hz_arrai[0]=p_z;


			
			//for(z=l/Q;z<l;z=z+l/Q)
			for(z=0;z<Q;z++)
			{
				Vx=Hx(p_x,p_y,p_z,t).r;
				Vy=Hy(p_x,p_y,p_z,t).r;
				Vz=Hz(p_x,p_y,p_z,t).r;

				if (Vz <0 )//se é negativo, desenha para a frente com a cor negativa
				{
					Vx=-Vx;
					Vy=-Vy;
					Vz=-Vz;
					
					graf_H[k].RedH=RedT;
					graf_H[k].GreenH=GreenT;
					graf_H[k].BlueH=BlueT;
				}
				else
				{
					graf_H[k].RedH=RedF;
					graf_H[k].GreenH=GreenF;
					graf_H[k].BlueH=BlueF;
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
					graf_H[k].Hx_arrai.SetSize(z+1);
					graf_H[k].Hy_arrai.SetSize(z+1);
					graf_H[k].Hz_arrai.SetSize(z+1);
					break;
				}

					
				
				if (graf_H[k].Hx_arrai.GetSize() < z+2)	
					graf_H[k].Hx_arrai.Add(p_x);
				else	
					graf_H[k].Hx_arrai[z+1]=p_x;

				
				if (graf_H[k].Hy_arrai.GetSize() < z+2)
					graf_H[k].Hy_arrai.Add(p_y);
				else
					graf_H[k].Hy_arrai[z+1]=p_y;


				if (graf_H[k].Hz_arrai.GetSize() < z+2)
					graf_H[k].Hz_arrai.Add(p_z);
				else
					graf_H[k].Hz_arrai[z+1]=p_z;			
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
		

			if ( graf_H[k].Hx_arrai.GetSize() < 1)	graf_H[k].Hx_arrai.Add(p_x);
			else	graf_H[k].Hx_arrai[0]=p_x;
			
					
			if (graf_H[k].Hy_arrai.GetSize() < 1)	graf_H[k].Hy_arrai.Add(p_y);
			else	graf_H[k].Hy_arrai[0]=p_y;

			if (graf_H[k].Hz_arrai.GetSize() < 1)	graf_H[k].Hz_arrai.Add(p_z);
			else	graf_H[k].Hz_arrai[0]=p_z;


			
			//for(z=l/Q;z<l;z=z+l/Q)
			for(z=0;z<Q;z++)
			{
				Vx=Hx(p_x,p_y,p_z,t).r;
				Vy=Hy(p_x,p_y,p_z,t).r;
				Vz=Hz(p_x,p_y,p_z,t).r;

				if (Vz >0 )//se é positivo, desenha para trás com a cor positiva
				{
					Vx=-Vx;
					Vy=-Vy;
					Vz=-Vz;
					
					graf_H[k].RedH=RedF;
					graf_H[k].GreenH=GreenF;
					graf_H[k].BlueH=BlueF;
				}
				else
				{
					graf_H[k].RedH=RedT;
					graf_H[k].GreenH=GreenT;
					graf_H[k].BlueH=BlueT;
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
					graf_H[k].Hx_arrai.SetSize(z+1);
					graf_H[k].Hy_arrai.SetSize(z+1);
					graf_H[k].Hz_arrai.SetSize(z+1);
					break;
				}

				
				int zzz=graf_H[k].Hx_arrai.GetSize() ;
				
				if (graf_H[k].Hx_arrai.GetSize() < z+2)	
					graf_H[k].Hx_arrai.Add(p_x);
				else	
					graf_H[k].Hx_arrai[z+1]=p_x;

				
				if (graf_H[k].Hy_arrai.GetSize() < z+2)
					graf_H[k].Hy_arrai.Add(p_y);
				else
					graf_H[k].Hy_arrai[z+1]=p_y;


				if (graf_H[k].Hz_arrai.GetSize() < z+2)
					graf_H[k].Hz_arrai.Add(p_z);
				else
					graf_H[k].Hz_arrai[z+1]=p_z;			
			}
		

			k++;
		}
	}

}



void TEr::DrawH_Draw(double t)
{
	int k;
	int i;
	int nLinhas;
	glPushMatrix();

	double L;
	double z1;//1º zero 
	double z2;//2º zero
	double Hzz;



	nLinhas=graf_H.GetSize();

	L=GetL();

	
	GetZero_H(t,z1,z2);

	Hzz=Hz(a/2,b/2,z1+L/100,t).r;

	if (Hzz < 0)
		glTranslated(0,0,z1-L/2);
	
	if(Hzz > 0)
		glTranslated(0,0,z1-L);

	if (Hzz == 0)
		glTranslated(0,0,0);



	for(k=0;k<nLinhas;k++)
	{

	
		glColor3d( graf_H[k].RedH, graf_H[k].GreenH, graf_H[k].BlueH);
	//	glColor3d(1,0,0);

		glBegin(GL_LINE_STRIP);

		for(i=0;i<graf_H[k].Hx_arrai.GetSize();i++)
		{
						
			glVertex3d(	graf_H[k].Hx_arrai[i],
						graf_H[k].Hy_arrai[i],
						graf_H[k].Hz_arrai[i]);
		}

		glEnd();
	}



	glPopMatrix();

}
