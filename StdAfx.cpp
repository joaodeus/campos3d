// stdafx.cpp : source file that includes just the standard includes
//	Campos3D.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"




double VectorMax(double a, double b, double c)
{
	a=fabs(a);
	b=fabs(b);
	c=fabs(c);

	if (b > a)
		a=b;
	if (c > a)
		a=c;

	return a;
}




void Cone(double x, double y, double z, double r, double h)
{
	

	glPushMatrix();
	
	glTranslated(x,y,z);
	
	//auxSolidSphere(r);
	
	//glEnable(GL_DEPTH_TEST);
	glDisable(GL_DEPTH_TEST);
	
	if (h < 0)
	{
		h=-h;
		glRotated(180.0 ,1.0, 0.0, 0.0);
	}
		

	auxSolidCone(r,h);

	glPopMatrix();

	

}

/*
	glPushMatrix();	
	glRotated(pDoc->onda.xRot,1.0,0.0,0.0);
	glRotated(pDoc->onda.yRot,0.0,1.0,0.0);
	glRotated(pDoc->onda.zRot,0.0,0.0,1.0);*/