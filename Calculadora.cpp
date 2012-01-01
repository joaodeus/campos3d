// Calculadora.cpp: implementation of the Calculadora class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "campos3d.h"
#include "Calculadora.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

	

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////







Calculadora::Calculadora()
{
	flag_graus_rad_grados = 1;
	lista.inicio=NULL;
	lista.fim=NULL;
	ERRO=false;
	INFINITO=0;
	flag_graus_rad_grados=1;
}

Calculadora::~Calculadora()
{

	solucoes_equacao.RemoveAll();
	solucoes_equacao_Complexas.RemoveAll();
}


CString Calculadora::resolve_derivada()
{

	list_d *paux;//y;
	char erro='0';
	Complexo y;

	CString fx_derivada;

	int num_x=0;
	int level=0;

	/*typedef struct funcao
	{
		struct funcao *anterior,*proximo;
		long double operando;
		long double j;
		char operador;
		char flag;
		char priori;
		
		//derivadas
		char derivada;
		int nivel;

	}list_d;*/


	
	for(paux=lista.inicio;paux!=NULL;paux=paux->proximo)
	{

		if ( paux->derivada == '1' )
			num_x++;


		if ( paux->operador == '(' )
			level++;
		if ( paux->operador == ')' )
			level--;

		paux->nivel+=level;

		if (paux->operador == ')' )
			paux->nivel++;
	}


	if (num_x == 0)
	{
		fx_derivada="0";
		return fx_derivada;
	}





	return fx_derivada;
}

/* A fun‡„o resolve() trabalha a lista duplamente ligada e remove as
estruturas sempre que as prioridades permitem efectuar uma opera‡„o.
Quando s¢ existir uma estrutura, que ‚ o resultado final da express„o
a fun‡„o resolve() guarda este valor e devolve-o.
*/
Complexo Calculadora::resolve()
{
	list_d *paux;//y;
	char erro='0';
	Complexo y;


	for(paux=lista.inicio;paux!=NULL;paux=paux->proximo)
	{

	while (paux->flag != 's' && paux->proximo)
		paux=paux->proximo;



	if ((paux->operador=='*' || paux->operador=='/')
		&& ((paux->anterior==NULL)  || (paux->proximo==NULL)))
		{
			break;
		}



	if ((paux->operador=='*' || paux->operador=='/')
		&& paux->anterior->flag=='n' && paux->proximo->flag=='n'
		&& (paux->anterior->anterior==NULL
			|| paux->anterior->anterior->priori<='1')
		&& (paux->proximo->proximo==NULL
			|| paux->proximo->proximo->priori<='1'))
		{
		erro='1';
		opera(paux);
		return resolve();
		}



	if ((paux->operador=='^' || paux->operador=='E')
		&& ((paux->anterior==NULL)  || (paux->proximo==NULL)))
		{
			break;
		}


	if ((paux->operador=='^' || paux->operador=='E')
		&& paux->anterior->flag=='n' && paux->proximo->flag=='n')
		{
		erro='1';
		opera(paux);
		return resolve();
		}

	if (paux->operador=='E' && paux->proximo->flag=='n'
		&& (paux->anterior->flag=='s' || paux->anterior==NULL))
		{
		erro='1';
		opera2(paux);
		return resolve();
		}



	if ((paux->operador=='+' || paux->operador=='-')
		&& (paux->anterior==NULL)  && (paux->proximo==NULL))
		{
			break;
		}

	
	if ((paux->operador=='+' || paux->operador=='-')
		&& (paux->anterior==NULL || paux->anterior->operador=='|' 
					|| paux->anterior->operador=='(' || paux->anterior->operador=='^'
					|| paux->anterior->operador=='E'|| paux->anterior->operador=='E' 
					|| paux->anterior->operador=='*'|| paux->anterior->operador=='/'))

		{
		erro='1';
		opera2(paux);
		return resolve();
		}


	if ((paux->operador=='+' || paux->operador=='-')
		&& paux->anterior!=NULL
		&& paux->anterior->flag=='n' 
		&& paux->proximo!=NULL
		&& paux->proximo->flag=='n'
		&& (paux->anterior->anterior==NULL 
					|| paux->anterior->anterior->operador=='|' 
					|| paux->anterior->anterior->operador=='('
					|| paux->anterior->anterior->priori=='0')
		
		&& (paux->proximo->proximo==NULL 
					|| paux->proximo->proximo->operador=='|'
					|| paux->proximo->proximo->operador==')'
					|| paux->proximo->proximo->priori=='0')
					)
		{
		erro='1';
		opera(paux);
		return resolve();
		}



	/*if ((paux->operador=='+' || paux->operador=='-')
		&& paux->anterior->flag=='n' && paux->proximo->flag=='n'
		&& (paux->anterior->anterior==NULL || paux->anterior->anterior->operador=='|' 
					|| paux->anterior->anterior->operador=='('
					|| paux->anterior->anterior->priori=='0')
		
		&& (paux->proximo->proximo==NULL || paux->proximo->proximo->operador=='|'
					|| paux->proximo->proximo->operador==')'
					|| paux->proximo->proximo->priori=='0'))
		{
		erro='1';
		opera(paux);
		return resolve();
		}*/



	if (paux->operador=='(' && paux->proximo!=NULL
		&& paux->proximo->flag=='n'
		&& paux->proximo->proximo!=NULL
		&& paux->proximo->proximo->operador==')')
		{
		erro='1';
		paux=paux->proximo;
		chaveta(paux);
		return resolve();
		}

	/*if (paux->operador=='(' && paux->proximo->flag=='n'
		&& paux->proximo->proximo->operador==')')
		{
		erro='1';
		paux=paux->proximo;
		chaveta(paux);
		return resolve();
		}*/


	if (paux->operador=='|' && paux->proximo!=NULL
		&& paux->proximo->flag=='n'
		&& paux->proximo->proximo!=NULL
		&& paux->proximo->proximo->operador=='|')
		{
		erro='1';
		paux=paux->proximo;
		chaveta(paux);
		return resolve();
		}

	
/*	if (paux->operador=='|' && paux->proximo->flag=='n'
		&& paux->proximo->proximo->operador=='|')
		{
		erro='1';
		paux=paux->proximo;
		chaveta(paux);
		return resolve();
		}*/



/*	sen ; 	s		PI = 3.14..;  		^ = 'elevado a ...'
	cos ; 	c		e = 2.71...;    	E = 'vezes 10 elevado a...'
	tg  ; 	t     log ;   L         ( )= chavetas
	cotg; 	g	  ln ;    l         | |= m¢dulo
	sqrt;	r     exp;    e         j = imagin rio
	cosh; 	o     senh;   i         i = imagin rio (igual a j)
	tgh;  	T     cotgh;  h
	arcsen; S     arccos; C
	arctg   a     acotg;  A
	step;   p     sinc;   n
	sgf ;   f     dirac;  d
	rect;   R     square; Q(trem de rectangulos)
				  trem;   M(trem de impulsos)
	
    asinh;	b	  acosh;  B
	atanh;	D	  acotgh; F

	*/

//strcmp

	if ((	   paux->operador=='s'  || paux->operador=='c'
			|| paux->operador=='t'	|| paux->operador=='L'
			|| paux->operador=='g'	|| paux->operador=='l'
			|| paux->operador=='r'	|| paux->operador=='e'
			|| paux->operador=='o'	|| paux->operador=='i'
			|| paux->operador=='T'	|| paux->operador=='h'
			|| paux->operador=='S'	|| paux->operador=='C'
			|| paux->operador=='a'	|| paux->operador=='A'
			|| paux->operador=='p'	|| paux->operador=='n'
			|| paux->operador=='f'	|| paux->operador=='d'
			|| paux->operador=='R'	|| paux->operador=='Q'
			|| paux->operador=='M'	|| paux->operador=='b'
			|| paux->operador=='B'	|| paux->operador=='D'
			|| paux->operador=='F'
			)
			&& paux->proximo!=NULL
			&& paux->proximo->flag=='n')
		{
		erro='1';
		opera2(paux);
		return resolve();
		}

	}
 //  }

	if ((lista.inicio==lista.fim) && lista.inicio->flag=='n')
	{
	erro='1';
	}


	if (erro=='0')
	{
		liberta();
		ERRO=true;
		return y;
	//	printf("\nErro detectado.");
	//	printf("\nVerifique a sintaxe da express„o matem tica");
	//	AfxMessageBox("Erro!!!\nVerifique a sintaxe da expressão.\n O programa será encerrado!");
	//	exit(0);
	}


	paux=lista.inicio;
	y.r=paux->operando;
	y.i=paux->j;
	paux=lista.inicio=lista.fim=NULL;
	free(paux); //delete
	return y;
}


						//f(CString str,double x,CString u)
CString Calculadora::Derivada(CString str, CString u )
{

	int n,l=0;
	char *ptr,exp[1024],t;
	char num[500];

	ptr=exp;
	t=u.GetAt(0);


	ERRO=false;

	char erro;
	CString err="Erro";


	if (str.GetLength()==0)
	{
		ERRO=true;
		return err;
	}

	for(int j=0;j<str.GetLength();j++)
	{
		exp[j]=str.GetAt(j);
	}
	exp[j]='\0';


	l=0;
	while(l < str.GetLength())
	{
	erro='0';
	n=0;
	// Introduz um numero na pilha
	if (isdigit(*ptr) || *ptr=='.')
	{
		erro='1';
		while (isdigit(*ptr) || *ptr=='.' )
		{
			num[n]=*ptr;
			ptr++;
			n++;
		}
		l=l+n;
		num[n]='\0';
		inserir(atof(num),'0','n','0',0);

		//EX: 2x  -> 2*x : introduz o * para a multiplicação
		if (*(ptr)==t)
		{
			erro='1';
			inserir(0,'*','s','1',0);
		}


		if ((*ptr=='p' || *ptr=='P') && (*(ptr+1)=='i' || *(ptr+1)=='I'))
		{
			erro='1';
			inserir(0,'*','s','1',0);
			//inserir(3.141592654,'0','n','0',0);
			//ptr=ptr+2;
			//l=l+2;
		}

	 }


	//imaginário
	if (*ptr=='j' || *ptr=='J' || *ptr=='i' || *ptr=='I' )
	{
	erro='1';
	inserir(0,'0','n','0',1);
	if (isdigit(*(ptr+1)) || *(ptr+1)=='.' || *(ptr+1)=='c'
		|| *(ptr+1)=='C' || *(ptr+1)=='s' || *(ptr+1)=='S'
		|| *(ptr+1)=='t' || *(ptr+1)=='T' || *(ptr+1)=='l'
		|| *(ptr+1)=='L' || *(ptr+1)==t   || *(ptr+1)=='s'
		|| *(ptr+1)=='S' || *(ptr+1)=='g' || *(ptr+1)=='G'
		|| *(ptr+1)=='a' || *(ptr+1)=='A' || *(ptr+1)=='d'
		|| *(ptr+1)=='D' || *(ptr+1)=='p' || *(ptr+1)=='P'
		|| *(ptr+1)=='e' || *(ptr+1)=='E' || *(ptr+1)=='('
		|| *(ptr+1)=='|' || *(ptr+1)=='R' || *(ptr+1)=='Q'
		|| *(ptr+1)=='M'
		)
	inserir(0,'*','s','1',0);
	ptr++;
	l++;
	}






	//exp

	if ((*ptr=='e' || *ptr=='E') && (*(ptr+1)=='x' || *(ptr+1)=='X')
	&& (*(ptr+2)=='p' || *(ptr+2)=='P'))
	{
	erro='1';
	inserir(0,'e','s','1',0);
	ptr=ptr+3;
	l=l+3;
	}

	//nepper

	if (*ptr=='e')
	{
		erro='1';
		inserir(2.718281828,'0','n','0',0);
		l++;
		ptr++;
	}

	//pi

	if ((*ptr=='p' || *ptr=='P') && (*(ptr+1)=='i' || *(ptr+1)=='I'))
	{
		erro='1';
		inserir(3.141592654,'0','n','0',0);
		ptr=ptr+2;
		l=l+2;
	}
	// Introduz um operador na pilha ou a variavel x

	if (*ptr=='+' || *ptr=='-')
	{
		if (*ptr=='-' && l==0)
		{
			inserir(0,'0','n','0',0);
		}
		erro='1';
		//funcoes[0]=*ptr;
		//funcoes[1]='\0';
		inserir(0,*ptr,'s','0',0);
		ptr++;
		l++;
	}

	if (*ptr=='/' || *ptr=='*' || *ptr=='(' || *ptr==')' || *ptr=='|')
	{
	erro='1';
	//funcoes[0]=*ptr;
	//funcoes[1]='\0';
	inserir(0,*ptr,'s','1',0);
	ptr++;
	l++;
	}



	//acosh

	if ((*ptr=='a' || *ptr=='A') && (*(ptr+1)=='c' || *(ptr+1)=='C') &&
	(*(ptr+2)=='o' || *(ptr+2)=='O') && (*(ptr+3)=='s' || *(ptr+3)=='S')
	&& (*(ptr+4)=='h' || *(ptr+4)=='H'))
	{
	erro='1';
//	inserir(0,"acosh",'s','1',0);
	inserir(0,'B','s','1',0);
	ptr=ptr+5;
	l=l+5;
	}


	//cosh

	if ((*ptr=='c' || *ptr=='C') && (*(ptr+1)=='o' || *(ptr+1)=='O') &&
	(*(ptr+2)=='s' || *(ptr+2)=='S') && (*(ptr+3)=='h' || *(ptr+3)=='H'))
	{
	erro='1';
//	inserir(0,"cosh",'s','1',0);
	inserir(0,'o','s','1',0);
	ptr=ptr+4;
	l=l+4;
	}

	//acos
	
	if ((*ptr=='a' || *ptr=='A') && (*(ptr+1)=='c' || *(ptr+1)=='C') &&
	(*(ptr+2)=='o' || *(ptr+2)=='O') && (*(ptr+3)=='s' || *(ptr+3)=='S'))
	{
	erro='1';
//	inserir(0,"acos",'s','1',0);
	inserir(0,'C','s','1',0);
	ptr=ptr+4;
	l=l+4;
	}

	//cos

	if ((*ptr=='c' || *ptr=='C') && (*(ptr+1)=='o' || *(ptr+1)=='O')
	&& (*(ptr+2)=='s' || *(ptr+2)=='S'))
	{
	erro='1';
	//inserir(0,"cos",'s','1',0);
	inserir(0,'c','s','1',0);
	ptr=ptr+3;
	l=l+3;
	}



	//asinh

	if ((*ptr=='a' || *ptr=='A') && (*(ptr+1)=='s' || *(ptr+1)=='S') &&
	(*(ptr+2)=='i' || *(ptr+2)=='I') && (*(ptr+3)=='n' || *(ptr+3)=='N')
	&& (*(ptr+4)=='h' || *(ptr+4)=='H'))
	{
	erro='1';
	//inserir(0,"asinh",'s','1',0);
	inserir(0,'b','s','1',0);
	ptr=ptr+5;
	l=l+5;
	}


	//sinh

	if ((*ptr=='s' || *ptr=='S') && (*(ptr+1)=='i' || *(ptr+1)=='I') &&
	(*(ptr+2)=='n' || *(ptr+2)=='N') && (*(ptr+3)=='h' || *(ptr+3)=='H'))
	{
	erro='1';
	//inserir(0,"sinh",'s','1',0);
	inserir(0,'i','s','1',0);
	ptr=ptr+4;
	l=l+4;
	}


	//asin

	if ((*ptr=='a' || *ptr=='A') && (*(ptr+1)=='s' || *(ptr+1)=='S') &&
	(*(ptr+2)=='i' || *(ptr+2)=='I') && (*(ptr+3)=='n' || *(ptr+3)=='N'))
	{
	erro='1';
	//inserir(0,"asin",'s','1',0);
	inserir(0,'S','s','1',0);
	ptr=ptr+4;
	l=l+4;
	}




	//sinc

	if ((*ptr=='s' || *ptr=='S') && (*(ptr+1)=='i' || *(ptr+1)=='I')
	&& (*(ptr+2)=='n' || *(ptr+2)=='N') && (*(ptr+3)=='c' || *(ptr+3)=='C') )
	{
	erro='1';
	//inserir(0,"sinc",'s','1',0);
	inserir(0,'n','s','1',0);
	ptr=ptr+4;
	l=l+4;
	}



	//sin

	if ((*ptr=='s' || *ptr=='S') && (*(ptr+1)=='i' || *(ptr+1)=='I')
	&& (*(ptr+2)=='n' || *(ptr+2)=='N'))
	{
	erro='1';
	//inserir(0,"sin",'s','1',0);
	inserir(0,'s','s','1',0);
	ptr=ptr+3;
	l=l+3;
	}

	


	//atanh

	if ((*ptr=='a' || *ptr=='A') && (*(ptr+1)=='t' || *(ptr+1)=='T') &&
	(*(ptr+2)=='a' || *(ptr+2)=='A') && (*(ptr+3)=='n' || *(ptr+3)=='N')
	&& (*(ptr+4)=='h' || *(ptr+4)=='H'))
	{
	erro='1';
	//inserir(0,"atanh",'s','1',0);
	inserir(0,'D','s','1',0);
	ptr=ptr+5;
	l=l+5;
	}

	//atan

	if ((*ptr=='a' || *ptr=='A') && (*(ptr+1)=='t' || *(ptr+1)=='T') &&
	(*(ptr+2)=='a' || *(ptr+2)=='A') && (*(ptr+3)=='n' || *(ptr+3)=='N'))
	{
	erro='1';
	//inserir(0,"atan",'s','1',0);
	inserir(0,'a','s','1',0);
	ptr=ptr+4;
	l=l+4;
	}


	//tanh

	if ((*ptr=='t' || *ptr=='T') && (*(ptr+1)=='a' || *(ptr+1)=='A')
	&& (*(ptr+2)=='n' || *(ptr+2)=='N') && (*(ptr+3)=='h' || *(ptr+3)=='H'))
	{
	erro='1';
//	inserir(0,"tanh",'s','1',0);
	inserir(0,'T','s','1',0);
	ptr=ptr+4;
	l=l+4;
	}

	//tan

	if ((*ptr=='t' || *ptr=='T') && (*(ptr+1)=='a' || *(ptr+1)=='A') 
		&& (*(ptr+2)=='n' || *(ptr+2)=='N'))
	{
	erro='1';
	//inserir(0,"tan",'s','1',0);
	inserir(0,'t','s','1',0);
	ptr=ptr+3;
	l=l+3;
	}


	//cotgh

	if ((*ptr=='c' || *ptr=='C') && (*(ptr+1)=='o' || *(ptr+1)=='O')
	&& (*(ptr+2)=='t' || *(ptr+2)=='T') && (*(ptr+3)=='g' || *(ptr+3)=='G')
	&& (*(ptr+4)=='h' || *(ptr+4)=='H'))
	{
	erro='1';
	//inserir(0,"cotgh",'s','1',0);
	inserir(0,'h','s','1',0);
	ptr=ptr+5;
	l=l+5;
	}


	//acotgh

	if ((*ptr=='a' || *ptr=='A') && (*(ptr+1)=='c' || *(ptr+1)=='C') &&
	(*(ptr+2)=='o' || *(ptr+2)=='O') && (*(ptr+3)=='t' || *(ptr+3)=='T') &&
	(*(ptr+4)=='g' || *(ptr+4)=='G') && (*(ptr+5)=='h' || *(ptr+5)=='H'))
	{
	erro='1';
	//inserir(0,"acotgh",'s','1',0);
	inserir(0,'F','s','1',0);
	ptr=ptr+6;
	l=l+6;
	}


	//acotg

	if ((*ptr=='a' || *ptr=='A') && (*(ptr+1)=='c' || *(ptr+1)=='C') &&
	(*(ptr+2)=='o' || *(ptr+2)=='O') && (*(ptr+3)=='t' || *(ptr+3)=='T') &&
	(*(ptr+4)=='g' || *(ptr+4)=='G'))
	{
	erro='1';
	//inserir(0,"acotg",'s','1',0);
	inserir(0,'A','s','1',0);
	ptr=ptr+5;
	l=l+5;
	}

	//cotg

	if ((*ptr=='c' || *ptr=='C') && (*(ptr+1)=='o' || *(ptr+1)=='O')
	&& (*(ptr+2)=='t' || *(ptr+2)=='T') && (*(ptr+3)=='g' || *(ptr+3)=='G'))
	{
	erro='1';
	//inserir(0,"cotg",'s','1',0);
	inserir(0,'g','s','1',0);
	ptr=ptr+4;
	l=l+4;
	}

	//sqrt

	if ((*ptr=='s' || *ptr=='S') && (*(ptr+1)=='q' || *(ptr+1)=='Q')
	&& (*(ptr+2)=='r' || *(ptr+2)=='R')
	&& (*(ptr+3)=='t' || *(ptr+3)=='T'))
	{
	erro='1';
	//inserir(0,"sqrt",'s','1',0);
	inserir(0,'r','s','1',0);
	ptr=ptr+4;
	l=l+4;
	}

	//log

	if ((*ptr=='l' || *ptr=='L') && (*(ptr+1)=='o' || *(ptr+1)=='O')
	&& (*(ptr+2)=='g' || *(ptr+2)=='G'))
	{
	erro='1';
	//inserir(0,"log",'s','1',0);
	inserir(0,'L','s','1',0);
	ptr=ptr+3;
	l=l+3;
	}

	//ln

	if ((*ptr=='l' || *ptr=='L') && (*(ptr+1)=='n' || *(ptr+1)=='N'))
	{
	erro='1';
	//inserir(0,"ln",'s','1',0);
	inserir(0,'l','s','1',0);
	ptr=ptr+2;
	l=l+2;
	}


	//step

	if ((*ptr=='s' || *ptr=='S') && (*(ptr+1)=='t' || *(ptr+1)=='T')
	&& (*(ptr+2)=='e' || *(ptr+2)=='E') && (*(ptr+3)=='p' || *(ptr+3)=='P'))
	{
	erro='1';
	//inserir(0,"step",'s','1',0);
	inserir(0,'p','s','1',0);
	ptr=ptr+4;
	l=l+4;
	}


	//sgf

	if ((*ptr=='s' || *ptr=='S') && (*(ptr+1)=='g' || *(ptr+1)=='G')
	&& (*(ptr+2)=='f' || *(ptr+2)=='F') )
	{
	erro='1';
	//inserir(0,"sgf",'s','1',0);
	inserir(0,'f','s','1',0);
	ptr=ptr+3;
	l=l+3;
	}

	//dirac
	if ((*ptr=='d' || *ptr=='D') && (*(ptr+1)=='i' || *(ptr+1)=='I')
	&& (*(ptr+2)=='r' || *(ptr+2)=='R') && (*(ptr+3)=='a' || *(ptr+3)=='A')
	&& (*(ptr+4)=='c' || *(ptr+4)=='C'))
	{
	erro='1';
	//inserir(0,"dirac",'s','1',0);
	inserir(0,'d','s','1',0);
	ptr=ptr+5;
	l=l+5;
	}

	//rect - fun‡Æo onda quadrada
	if ((*ptr=='r' || *ptr=='R') && (*(ptr+1)=='e' || *(ptr+1)=='E')
	&& (*(ptr+2)=='c' || *(ptr+2)=='C') && (*(ptr+3)=='t' || *(ptr+3)=='T'))
	{
	erro='1';
	//inserir(0,"rect",'s','1',0);
	inserir(0,'R','s','1',0);
	ptr=ptr+4;
	l=l+4;
	}

	//trem - trem de impulsos
	if ((*ptr=='t' || *ptr=='T') && (*(ptr+1)=='r' || *(ptr+1)=='R')
	&& (*(ptr+2)=='e' || *(ptr+2)=='E') && (*(ptr+3)=='m' || *(ptr+3)=='M'))
	{
	erro='1';
	//inserir(0,"trem",'s','1',0);
	inserir(0,'M','s','1',0);
	ptr=ptr+4;
	l=l+4;
	}



	//square - trem de rectangulos
	if ((*ptr=='s' || *ptr=='S') && (*(ptr+1)=='q' || *(ptr+1)=='Q')
	&& (*(ptr+2)=='u' || *(ptr+2)=='U') && (*(ptr+3)=='a' || *(ptr+3)=='A')
	&& (*(ptr+4)=='r' || *(ptr+4)=='R') && (*(ptr+5)=='e' || *(ptr+5)=='E'))
	{
	erro='1';
	//inserir(0,"square",'s','1',0);
	inserir(0,'Q','s','1',0);
	ptr=ptr+6;
	l=l+6;
	}


	if (*ptr=='^' || *ptr=='E')
		{
		erro='1';
		//funcoes[0]=*ptr;
		//funcoes[1]='\0';
		//inserir(0,funcoes,'s','2',0);
		inserir(0,*ptr,'s','2',0);
		l++;
		ptr++;
		}

	if (*ptr==t)
	{
	erro='1';
	//inserir(u,'0','n','0',0);
	inserir_derivada(1,'0','n','0',0,'x',0);
	l++;
	ptr++;
	}

	if (erro=='0')
	{
		if (l>0)
			liberta();

		ERRO=true;
	//	AfxMessageBox("Erro!!!\nVerifique a sintaxe da expressão.\n O programa será encerrado!");
	//	exit(0);
		return err;
		
	}

	}



 return resolve_derivada();

}



/*  A  fun‡„o f descarta os caracteres da string, agrupa os caracteres
digitos numa string que ‚ convertida para um n§ real (float). Estes n§
reais juntamente com os caracteres que representam as fun‡”es s„o
introduzidos na lista duplamente ligada, atrav‚s da chamada … fun‡„o
inserir
*/
/*
A fun‡„o f reconhece as seguintes fun‡”es e constantes:
As fun‡äes sÆo identificadas com as letras a seguir indicadas

	sen ; 	s		PI = 3.14..;  		^ = 'elevado a ...'
	cos ; 	c		e = 2.71...;    	E = 'vezes 10 elevado a...'
	tg  ; 	t     log ;   L         ( )= chavetas
	cotg; 	g	  ln ;    l         | |= m¢dulo
	sqrt;	r     exp;    e         j = imagin rio
	cosh; 	o     senh;   i         i = imagin rio (igual a j)
	tgh;  	T     cotgh;  h
	arcsen; S     arccos; C
	arctg   a     acotg;  A
	step;   p     sinc;   n
	sgf ;   f     dirac;  d
	rect;   R     square; Q(trem de rectangulos)
				  trem;   M(trem de impulsos)

	asinh;	b	  acosh;  B
	atanh;	D	  acotgh; F

*/
Complexo Calculadora::f(CString str,double x,CString u)
{
	int n,l=0;
	char *ptr,exp[1024],t;
	char num[500];
//	char funcoes[20];
	ptr=exp;
	t=u.GetAt(0);

	ERRO=false;

	char erro;
	Complexo err(0,0);


	if (str.GetLength()==0)
	{
		ERRO=true;
		return err;
	}

	for(int j=0;j<str.GetLength();j++)
	{
		exp[j]=str.GetAt(j);
	}
	exp[j]='\0';


	l=0;
	while(l < str.GetLength())
	{
	erro='0';
	n=0;
	// Introduz um numero na pilha
	if (isdigit(*ptr) || *ptr=='.')
	{
		erro='1';
		while (isdigit(*ptr) || *ptr=='.' )
		{
			num[n]=*ptr;
			ptr++;
			n++;
		}
		l=l+n;
		num[n]='\0';
		inserir(atof(num),'0','n','0',0);

		//EX: 2x  -> 2*x : introduz o * para a multiplicação
		if (*(ptr)==t)
		{
			erro='1';
			inserir(0,'*','s','1',0);
		}


		if ((*ptr=='p' || *ptr=='P') && (*(ptr+1)=='i' || *(ptr+1)=='I'))
		{
			erro='1';
			inserir(0,'*','s','1',0);
			//inserir(3.141592654,'0','n','0',0);
			//ptr=ptr+2;
			//l=l+2;
		}

	 }


	//imaginário
	if (*ptr=='j' || *ptr=='J' || *ptr=='i' || *ptr=='I' )
	{
	erro='1';
	inserir(0,'0','n','0',1);
	if (isdigit(*(ptr+1)) || *(ptr+1)=='.' || *(ptr+1)=='c'
		|| *(ptr+1)=='C' || *(ptr+1)=='s' || *(ptr+1)=='S'
		|| *(ptr+1)=='t' || *(ptr+1)=='T' || *(ptr+1)=='l'
		|| *(ptr+1)=='L' || *(ptr+1)==t   || *(ptr+1)=='s'
		|| *(ptr+1)=='S' || *(ptr+1)=='g' || *(ptr+1)=='G'
		|| *(ptr+1)=='a' || *(ptr+1)=='A' || *(ptr+1)=='d'
		|| *(ptr+1)=='D' || *(ptr+1)=='p' || *(ptr+1)=='P'
		|| *(ptr+1)=='e' || *(ptr+1)=='E' || *(ptr+1)=='('
		|| *(ptr+1)=='|' || *(ptr+1)=='R' || *(ptr+1)=='Q'
		|| *(ptr+1)=='M'
		)
	inserir(0,'*','s','1',0);
	ptr++;
	l++;
	}






	//exp

	if ((*ptr=='e' || *ptr=='E') && (*(ptr+1)=='x' || *(ptr+1)=='X')
	&& (*(ptr+2)=='p' || *(ptr+2)=='P'))
	{
	erro='1';
	inserir(0,'e','s','1',0);
	ptr=ptr+3;
	l=l+3;
	}

	//nepper

	if (*ptr=='e')
	{
		erro='1';
		inserir(2.718281828,'0','n','0',0);
		l++;
		ptr++;
	}

	//pi

	if ((*ptr=='p' || *ptr=='P') && (*(ptr+1)=='i' || *(ptr+1)=='I'))
	{
		erro='1';
		inserir(3.141592654,'0','n','0',0);
		ptr=ptr+2;
		l=l+2;
	}
	// Introduz um operador na pilha ou a variavel x

	if (*ptr=='+' || *ptr=='-')
	{
		if (*ptr=='-' && l==0)
		{
			inserir(0,'0','n','0',0);
		}
		erro='1';
		//funcoes[0]=*ptr;
		//funcoes[1]='\0';
		inserir(0,*ptr,'s','0',0);
		ptr++;
		l++;
	}

	if (*ptr=='/' || *ptr=='*' || *ptr=='(' || *ptr==')' || *ptr=='|')
	{
	erro='1';
	//funcoes[0]=*ptr;
	//funcoes[1]='\0';
	inserir(0,*ptr,'s','1',0);
	ptr++;
	l++;
	}



	//acosh

	if ((*ptr=='a' || *ptr=='A') && (*(ptr+1)=='c' || *(ptr+1)=='C') &&
	(*(ptr+2)=='o' || *(ptr+2)=='O') && (*(ptr+3)=='s' || *(ptr+3)=='S')
	&& (*(ptr+4)=='h' || *(ptr+4)=='H'))
	{
	erro='1';
//	inserir(0,"acosh",'s','1',0);
	inserir(0,'B','s','1',0);
	ptr=ptr+5;
	l=l+5;
	}


	//cosh

	if ((*ptr=='c' || *ptr=='C') && (*(ptr+1)=='o' || *(ptr+1)=='O') &&
	(*(ptr+2)=='s' || *(ptr+2)=='S') && (*(ptr+3)=='h' || *(ptr+3)=='H'))
	{
	erro='1';
//	inserir(0,"cosh",'s','1',0);
	inserir(0,'o','s','1',0);
	ptr=ptr+4;
	l=l+4;
	}

	//acos
	
	if ((*ptr=='a' || *ptr=='A') && (*(ptr+1)=='c' || *(ptr+1)=='C') &&
	(*(ptr+2)=='o' || *(ptr+2)=='O') && (*(ptr+3)=='s' || *(ptr+3)=='S'))
	{
	erro='1';
//	inserir(0,"acos",'s','1',0);
	inserir(0,'C','s','1',0);
	ptr=ptr+4;
	l=l+4;
	}

	//cos

	if ((*ptr=='c' || *ptr=='C') && (*(ptr+1)=='o' || *(ptr+1)=='O')
	&& (*(ptr+2)=='s' || *(ptr+2)=='S'))
	{
	erro='1';
	//inserir(0,"cos",'s','1',0);
	inserir(0,'c','s','1',0);
	ptr=ptr+3;
	l=l+3;
	}



	//asinh

	if ((*ptr=='a' || *ptr=='A') && (*(ptr+1)=='s' || *(ptr+1)=='S') &&
	(*(ptr+2)=='i' || *(ptr+2)=='I') && (*(ptr+3)=='n' || *(ptr+3)=='N')
	&& (*(ptr+4)=='h' || *(ptr+4)=='H'))
	{
	erro='1';
	//inserir(0,"asinh",'s','1',0);
	inserir(0,'b','s','1',0);
	ptr=ptr+5;
	l=l+5;
	}


	//sinh

	if ((*ptr=='s' || *ptr=='S') && (*(ptr+1)=='i' || *(ptr+1)=='I') &&
	(*(ptr+2)=='n' || *(ptr+2)=='N') && (*(ptr+3)=='h' || *(ptr+3)=='H'))
	{
	erro='1';
	//inserir(0,"sinh",'s','1',0);
	inserir(0,'i','s','1',0);
	ptr=ptr+4;
	l=l+4;
	}


	//asin

	if ((*ptr=='a' || *ptr=='A') && (*(ptr+1)=='s' || *(ptr+1)=='S') &&
	(*(ptr+2)=='i' || *(ptr+2)=='I') && (*(ptr+3)=='n' || *(ptr+3)=='N'))
	{
	erro='1';
	//inserir(0,"asin",'s','1',0);
	inserir(0,'S','s','1',0);
	ptr=ptr+4;
	l=l+4;
	}




	//sinc

	if ((*ptr=='s' || *ptr=='S') && (*(ptr+1)=='i' || *(ptr+1)=='I')
	&& (*(ptr+2)=='n' || *(ptr+2)=='N') && (*(ptr+3)=='c' || *(ptr+3)=='C') )
	{
	erro='1';
	//inserir(0,"sinc",'s','1',0);
	inserir(0,'n','s','1',0);
	ptr=ptr+4;
	l=l+4;
	}



	//sin

	if ((*ptr=='s' || *ptr=='S') && (*(ptr+1)=='i' || *(ptr+1)=='I')
	&& (*(ptr+2)=='n' || *(ptr+2)=='N'))
	{
	erro='1';
	//inserir(0,"sin",'s','1',0);
	inserir(0,'s','s','1',0);
	ptr=ptr+3;
	l=l+3;
	}

	


	//atanh

	if ((*ptr=='a' || *ptr=='A') && (*(ptr+1)=='t' || *(ptr+1)=='T') &&
	(*(ptr+2)=='a' || *(ptr+2)=='A') && (*(ptr+3)=='n' || *(ptr+3)=='N')
	&& (*(ptr+4)=='h' || *(ptr+4)=='H'))
	{
	erro='1';
	//inserir(0,"atanh",'s','1',0);
	inserir(0,'D','s','1',0);
	ptr=ptr+5;
	l=l+5;
	}

	//atan

	if ((*ptr=='a' || *ptr=='A') && (*(ptr+1)=='t' || *(ptr+1)=='T') &&
	(*(ptr+2)=='a' || *(ptr+2)=='A') && (*(ptr+3)=='n' || *(ptr+3)=='N'))
	{
	erro='1';
	//inserir(0,"atan",'s','1',0);
	inserir(0,'a','s','1',0);
	ptr=ptr+4;
	l=l+4;
	}


	//tanh

	if ((*ptr=='t' || *ptr=='T') && (*(ptr+1)=='a' || *(ptr+1)=='A')
	&& (*(ptr+2)=='n' || *(ptr+2)=='N') && (*(ptr+3)=='h' || *(ptr+3)=='H'))
	{
	erro='1';
//	inserir(0,"tanh",'s','1',0);
	inserir(0,'T','s','1',0);
	ptr=ptr+4;
	l=l+4;
	}

	//tan

	if ((*ptr=='t' || *ptr=='T') && (*(ptr+1)=='a' || *(ptr+1)=='A') 
		&& (*(ptr+2)=='n' || *(ptr+2)=='N'))
	{
	erro='1';
	//inserir(0,"tan",'s','1',0);
	inserir(0,'t','s','1',0);
	ptr=ptr+3;
	l=l+3;
	}


	//cotgh

	if ((*ptr=='c' || *ptr=='C') && (*(ptr+1)=='o' || *(ptr+1)=='O')
	&& (*(ptr+2)=='t' || *(ptr+2)=='T') && (*(ptr+3)=='g' || *(ptr+3)=='G')
	&& (*(ptr+4)=='h' || *(ptr+4)=='H'))
	{
	erro='1';
	//inserir(0,"cotgh",'s','1',0);
	inserir(0,'h','s','1',0);
	ptr=ptr+5;
	l=l+5;
	}


	//acotgh

	if ((*ptr=='a' || *ptr=='A') && (*(ptr+1)=='c' || *(ptr+1)=='C') &&
	(*(ptr+2)=='o' || *(ptr+2)=='O') && (*(ptr+3)=='t' || *(ptr+3)=='T') &&
	(*(ptr+4)=='g' || *(ptr+4)=='G') && (*(ptr+5)=='h' || *(ptr+5)=='H'))
	{
	erro='1';
	//inserir(0,"acotgh",'s','1',0);
	inserir(0,'F','s','1',0);
	ptr=ptr+6;
	l=l+6;
	}


	//acotg

	if ((*ptr=='a' || *ptr=='A') && (*(ptr+1)=='c' || *(ptr+1)=='C') &&
	(*(ptr+2)=='o' || *(ptr+2)=='O') && (*(ptr+3)=='t' || *(ptr+3)=='T') &&
	(*(ptr+4)=='g' || *(ptr+4)=='G'))
	{
	erro='1';
	//inserir(0,"acotg",'s','1',0);
	inserir(0,'A','s','1',0);
	ptr=ptr+5;
	l=l+5;
	}

	//cotg

	if ((*ptr=='c' || *ptr=='C') && (*(ptr+1)=='o' || *(ptr+1)=='O')
	&& (*(ptr+2)=='t' || *(ptr+2)=='T') && (*(ptr+3)=='g' || *(ptr+3)=='G'))
	{
	erro='1';
	//inserir(0,"cotg",'s','1',0);
	inserir(0,'g','s','1',0);
	ptr=ptr+4;
	l=l+4;
	}

	//sqrt

	if ((*ptr=='s' || *ptr=='S') && (*(ptr+1)=='q' || *(ptr+1)=='Q')
	&& (*(ptr+2)=='r' || *(ptr+2)=='R')
	&& (*(ptr+3)=='t' || *(ptr+3)=='T'))
	{
	erro='1';
	//inserir(0,"sqrt",'s','1',0);
	inserir(0,'r','s','1',0);
	ptr=ptr+4;
	l=l+4;
	}

	//log

	if ((*ptr=='l' || *ptr=='L') && (*(ptr+1)=='o' || *(ptr+1)=='O')
	&& (*(ptr+2)=='g' || *(ptr+2)=='G'))
	{
	erro='1';
	//inserir(0,"log",'s','1',0);
	inserir(0,'L','s','1',0);
	ptr=ptr+3;
	l=l+3;
	}

	//ln

	if ((*ptr=='l' || *ptr=='L') && (*(ptr+1)=='n' || *(ptr+1)=='N'))
	{
	erro='1';
	//inserir(0,"ln",'s','1',0);
	inserir(0,'l','s','1',0);
	ptr=ptr+2;
	l=l+2;
	}


	//step

	if ((*ptr=='s' || *ptr=='S') && (*(ptr+1)=='t' || *(ptr+1)=='T')
	&& (*(ptr+2)=='e' || *(ptr+2)=='E') && (*(ptr+3)=='p' || *(ptr+3)=='P'))
	{
	erro='1';
	//inserir(0,"step",'s','1',0);
	inserir(0,'p','s','1',0);
	ptr=ptr+4;
	l=l+4;
	}


	//sgf

	if ((*ptr=='s' || *ptr=='S') && (*(ptr+1)=='g' || *(ptr+1)=='G')
	&& (*(ptr+2)=='f' || *(ptr+2)=='F') )
	{
	erro='1';
	//inserir(0,"sgf",'s','1',0);
	inserir(0,'f','s','1',0);
	ptr=ptr+3;
	l=l+3;
	}

	//dirac
	if ((*ptr=='d' || *ptr=='D') && (*(ptr+1)=='i' || *(ptr+1)=='I')
	&& (*(ptr+2)=='r' || *(ptr+2)=='R') && (*(ptr+3)=='a' || *(ptr+3)=='A')
	&& (*(ptr+4)=='c' || *(ptr+4)=='C'))
	{
	erro='1';
	//inserir(0,"dirac",'s','1',0);
	inserir(0,'d','s','1',0);
	ptr=ptr+5;
	l=l+5;
	}

	//rect - fun‡Æo onda quadrada
	if ((*ptr=='r' || *ptr=='R') && (*(ptr+1)=='e' || *(ptr+1)=='E')
	&& (*(ptr+2)=='c' || *(ptr+2)=='C') && (*(ptr+3)=='t' || *(ptr+3)=='T'))
	{
	erro='1';
	//inserir(0,"rect",'s','1',0);
	inserir(0,'R','s','1',0);
	ptr=ptr+4;
	l=l+4;
	}

	//trem - trem de impulsos
	if ((*ptr=='t' || *ptr=='T') && (*(ptr+1)=='r' || *(ptr+1)=='R')
	&& (*(ptr+2)=='e' || *(ptr+2)=='E') && (*(ptr+3)=='m' || *(ptr+3)=='M'))
	{
	erro='1';
	//inserir(0,"trem",'s','1',0);
	inserir(0,'M','s','1',0);
	ptr=ptr+4;
	l=l+4;
	}



	//square - trem de rectangulos
	if ((*ptr=='s' || *ptr=='S') && (*(ptr+1)=='q' || *(ptr+1)=='Q')
	&& (*(ptr+2)=='u' || *(ptr+2)=='U') && (*(ptr+3)=='a' || *(ptr+3)=='A')
	&& (*(ptr+4)=='r' || *(ptr+4)=='R') && (*(ptr+5)=='e' || *(ptr+5)=='E'))
	{
	erro='1';
	//inserir(0,"square",'s','1',0);
	inserir(0,'Q','s','1',0);
	ptr=ptr+6;
	l=l+6;
	}


	if (*ptr=='^' || *ptr=='E')
		{
		erro='1';
		//funcoes[0]=*ptr;
		//funcoes[1]='\0';
		//inserir(0,funcoes,'s','2',0);
		inserir(0,*ptr,'s','2',0);
		l++;
		ptr++;
		}

	if (*ptr==t)
	{
	erro='1';
	inserir(x,'0','n','0',0);
	l++;
	ptr++;
	}

	if (erro=='0')
	{
		if (l>0)
			liberta();

		ERRO=true;
	//	AfxMessageBox("Erro!!!\nVerifique a sintaxe da expressão.\n O programa será encerrado!");
	//	exit(0);
		return err;
		
	}

	}

   return resolve();
}

//fxy é semelhante a f só que recebe duas variáveis

Complexo Calculadora::fxy(CString str,double x,CString u,double y,CString v, double z, CString s)
{
	int n,l=0;
	char *ptr,exp[1000],t,t1,t2;
//	char funcoes[20];
	char num[500];
	ptr=exp;
	t=u.GetAt(0);
	t1=v.GetAt(0);
	t2=s.GetAt(0);
	char erro;
	Complexo err(0,0);


	
	if (str.GetLength()==0)
	{
		ERRO=true;
		return err;
	}

	for(int j=0;j<str.GetLength();j++)
	{
		exp[j]=str.GetAt(j);
	}
	exp[j]='\0';




	l=0;
	while(l < str.GetLength())
	{
	erro='0';
	n=0;
	// Introduz um numero na pilha
	if (isdigit(*ptr) || *ptr=='.')
	{
		erro='1';
		while (isdigit(*ptr) || *ptr=='.' )
		{
			num[n]=*ptr;
			ptr++;
			n++;
		}
		l=l+n;
		num[n]='\0';
		inserir(atof(num),'0','n','0',0);

		//EX: 2x  -> 2*x : introduz o * para a multiplicação
		if (*(ptr)==t)
		{
			erro='1';
			inserir(0,'*','s','1',0);
		}

	//	if (*(ptr)==)

		if ((*ptr=='p' || *ptr=='P') && (*(ptr+1)=='i' || *(ptr+1)=='I'))
		{
			erro='1';
			inserir(0,'*','s','1',0);
			//inserir(3.141592654,'0','n','0',0);
			//ptr=ptr+2;
			//l=l+2;
		}

	 }


	//imaginário
	if (*ptr=='j' || *ptr=='J' || *ptr=='i' || *ptr=='I' )
	{
	erro='1';
	inserir(0,'0','n','0',1);
	if (isdigit(*(ptr+1)) || *(ptr+1)=='.' || *(ptr+1)=='c'
		|| *(ptr+1)=='C' || *(ptr+1)=='s' || *(ptr+1)=='S'
		|| *(ptr+1)=='t' || *(ptr+1)=='T' || *(ptr+1)=='l'
		|| *(ptr+1)=='L' || *(ptr+1)==t   || *(ptr+1)=='s'
		|| *(ptr+1)=='S' || *(ptr+1)=='g' || *(ptr+1)=='G'
		|| *(ptr+1)=='a' || *(ptr+1)=='A' || *(ptr+1)=='d'
		|| *(ptr+1)=='D' || *(ptr+1)=='p' || *(ptr+1)=='P'
		|| *(ptr+1)=='e' || *(ptr+1)=='E' || *(ptr+1)=='('
		|| *(ptr+1)=='|' || *(ptr+1)=='R' || *(ptr+1)=='Q'
		|| *(ptr+1)=='M'
		)
	inserir(0,'*','s','1',0);
	ptr++;
	l++;
	}



	//exp

	if ((*ptr=='e' || *ptr=='E') && (*(ptr+1)=='x' || *(ptr+1)=='X')
	&& (*(ptr+2)=='p' || *(ptr+2)=='P'))
	{
	erro='1';
	inserir(0,'e','s','1',0);
	ptr=ptr+3;
	l=l+3;
	}

	//nepper

	if (*ptr=='e')
	{
		erro='1';
		inserir(2.718281828,'0','n','0',0);
		l++;
		ptr++;
	}

	//pi

	if ((*ptr=='p' || *ptr=='P') && (*(ptr+1)=='i' || *(ptr+1)=='I'))
	{
		erro='1';
		inserir(3.141592654,'0','n','0',0);
		ptr=ptr+2;
		l=l+2;
	}
	// Introduz um operador na pilha ou a variavel x

	if (*ptr=='+' || *ptr=='-')
	{
		if (*ptr=='-' && l==0)
		{
			inserir(0,'0','n','0',0);
		}
		erro='1';
		//funcoes[0]=*ptr;
		//funcoes[1]='\0';
		inserir(0,*ptr,'s','0',0);
		ptr++;
		l++;
	}

	if (*ptr=='/' || *ptr=='*' || *ptr=='(' || *ptr==')' || *ptr=='|')
	{
	erro='1';
	//funcoes[0]=*ptr;
	//funcoes[1]='\0';
	inserir(0,*ptr,'s','1',0);
	ptr++;
	l++;
	}



	//acosh

	if ((*ptr=='a' || *ptr=='A') && (*(ptr+1)=='c' || *(ptr+1)=='C') &&
	(*(ptr+2)=='o' || *(ptr+2)=='O') && (*(ptr+3)=='s' || *(ptr+3)=='S')
	&& (*(ptr+4)=='h' || *(ptr+4)=='H'))
	{
	erro='1';
//	inserir(0,"acosh",'s','1',0);
	inserir(0,'B','s','1',0);
	ptr=ptr+5;
	l=l+5;
	}


	//cosh

	if ((*ptr=='c' || *ptr=='C') && (*(ptr+1)=='o' || *(ptr+1)=='O') &&
	(*(ptr+2)=='s' || *(ptr+2)=='S') && (*(ptr+3)=='h' || *(ptr+3)=='H'))
	{
	erro='1';
//	inserir(0,"cosh",'s','1',0);
	inserir(0,'o','s','1',0);
	ptr=ptr+4;
	l=l+4;
	}

	//acos
	
	if ((*ptr=='a' || *ptr=='A') && (*(ptr+1)=='c' || *(ptr+1)=='C') &&
	(*(ptr+2)=='o' || *(ptr+2)=='O') && (*(ptr+3)=='s' || *(ptr+3)=='S'))
	{
	erro='1';
//	inserir(0,"acos",'s','1',0);
	inserir(0,'C','s','1',0);
	ptr=ptr+4;
	l=l+4;
	}

	//cos

	if ((*ptr=='c' || *ptr=='C') && (*(ptr+1)=='o' || *(ptr+1)=='O')
	&& (*(ptr+2)=='s' || *(ptr+2)=='S'))
	{
	erro='1';
	//inserir(0,"cos",'s','1',0);
	inserir(0,'c','s','1',0);
	ptr=ptr+3;
	l=l+3;
	}



	//asinh

	if ((*ptr=='a' || *ptr=='A') && (*(ptr+1)=='s' || *(ptr+1)=='S') &&
	(*(ptr+2)=='i' || *(ptr+2)=='I') && (*(ptr+3)=='n' || *(ptr+3)=='N')
	&& (*(ptr+4)=='h' || *(ptr+4)=='H'))
	{
	erro='1';
	//inserir(0,"asinh",'s','1',0);
	inserir(0,'b','s','1',0);
	ptr=ptr+5;
	l=l+5;
	}


	//sinh

	if ((*ptr=='s' || *ptr=='S') && (*(ptr+1)=='i' || *(ptr+1)=='I') &&
	(*(ptr+2)=='n' || *(ptr+2)=='N') && (*(ptr+3)=='h' || *(ptr+3)=='H'))
	{
	erro='1';
	//inserir(0,"sinh",'s','1',0);
	inserir(0,'i','s','1',0);
	ptr=ptr+4;
	l=l+4;
	}


	//asin

	if ((*ptr=='a' || *ptr=='A') && (*(ptr+1)=='s' || *(ptr+1)=='S') &&
	(*(ptr+2)=='i' || *(ptr+2)=='I') && (*(ptr+3)=='n' || *(ptr+3)=='N'))
	{
	erro='1';
	//inserir(0,"asin",'s','1',0);
	inserir(0,'S','s','1',0);
	ptr=ptr+4;
	l=l+4;
	}

	//sin

	if ((*ptr=='s' || *ptr=='S') && (*(ptr+1)=='i' || *(ptr+1)=='I')
	&& (*(ptr+2)=='n' || *(ptr+2)=='N'))
	{
	erro='1';
	//inserir(0,"sin",'s','1',0);
	inserir(0,'s','s','1',0);
	ptr=ptr+3;
	l=l+3;
	}

	//sinc

	if ((*ptr=='s' || *ptr=='S') && (*(ptr+1)=='i' || *(ptr+1)=='I')
	&& (*(ptr+2)=='n' || *(ptr+2)=='N') && (*(ptr+3)=='c' || *(ptr+3)=='C') )
	{
	erro='1';
	//inserir(0,"sinc",'s','1',0);
	inserir(0,'n','s','1',0);
	ptr=ptr+4;
	l=l+4;
	}


	//atanh

	if ((*ptr=='a' || *ptr=='A') && (*(ptr+1)=='t' || *(ptr+1)=='T') &&
	(*(ptr+2)=='a' || *(ptr+2)=='A') && (*(ptr+3)=='n' || *(ptr+3)=='N')
	&& (*(ptr+4)=='h' || *(ptr+4)=='H'))
	{
	erro='1';
	//inserir(0,"atanh",'s','1',0);
	inserir(0,'D','s','1',0);
	ptr=ptr+5;
	l=l+5;
	}

	//atan

	if ((*ptr=='a' || *ptr=='A') && (*(ptr+1)=='t' || *(ptr+1)=='T') &&
	(*(ptr+2)=='a' || *(ptr+2)=='A') && (*(ptr+3)=='n' || *(ptr+3)=='N'))
	{
	erro='1';
	//inserir(0,"atan",'s','1',0);
	inserir(0,'a','s','1',0);
	ptr=ptr+4;
	l=l+4;
	}


	//tanh

	if ((*ptr=='t' || *ptr=='T') && (*(ptr+1)=='a' || *(ptr+1)=='A')
	&& (*(ptr+2)=='n' || *(ptr+2)=='N') && (*(ptr+3)=='h' || *(ptr+3)=='H'))
	{
	erro='1';
//	inserir(0,"tanh",'s','1',0);
	inserir(0,'T','s','1',0);
	ptr=ptr+4;
	l=l+4;
	}

	//tan

	if ((*ptr=='t' || *ptr=='T') && (*(ptr+1)=='a' || *(ptr+1)=='A') 
		&& (*(ptr+2)=='n' || *(ptr+2)=='N'))
	{
	erro='1';
	//inserir(0,"tan",'s','1',0);
	inserir(0,'t','s','1',0);
	ptr=ptr+3;
	l=l+3;
	}


	//cotgh

	if ((*ptr=='c' || *ptr=='C') && (*(ptr+1)=='o' || *(ptr+1)=='O')
	&& (*(ptr+2)=='t' || *(ptr+2)=='T') && (*(ptr+3)=='g' || *(ptr+3)=='G')
	&& (*(ptr+4)=='h' || *(ptr+4)=='H'))
	{
	erro='1';
	//inserir(0,"cotgh",'s','1',0);
	inserir(0,'h','s','1',0);
	ptr=ptr+5;
	l=l+5;
	}


	//acotgh

	if ((*ptr=='a' || *ptr=='A') && (*(ptr+1)=='c' || *(ptr+1)=='C') &&
	(*(ptr+2)=='o' || *(ptr+2)=='O') && (*(ptr+3)=='t' || *(ptr+3)=='T') &&
	(*(ptr+4)=='g' || *(ptr+4)=='G') && (*(ptr+5)=='h' || *(ptr+5)=='H'))
	{
	erro='1';
	//inserir(0,"acotgh",'s','1',0);
	inserir(0,'F','s','1',0);
	ptr=ptr+5;
	l=l+5;
	}


	//acotg

	if ((*ptr=='a' || *ptr=='A') && (*(ptr+1)=='c' || *(ptr+1)=='C') &&
	(*(ptr+2)=='o' || *(ptr+2)=='O') && (*(ptr+3)=='t' || *(ptr+3)=='T') &&
	(*(ptr+4)=='g' || *(ptr+4)=='G'))
	{
	erro='1';
	//inserir(0,"acotg",'s','1',0);
	inserir(0,'A','s','1',0);
	ptr=ptr+5;
	l=l+5;
	}

	//cotg

	if ((*ptr=='c' || *ptr=='C') && (*(ptr+1)=='o' || *(ptr+1)=='O')
	&& (*(ptr+2)=='t' || *(ptr+2)=='T') && (*(ptr+3)=='g' || *(ptr+3)=='G'))
	{
	erro='1';
	//inserir(0,"cotg",'s','1',0);
	inserir(0,'g','s','1',0);
	ptr=ptr+4;
	l=l+4;
	}

	//sqrt

	if ((*ptr=='s' || *ptr=='S') && (*(ptr+1)=='q' || *(ptr+1)=='Q')
	&& (*(ptr+2)=='r' || *(ptr+2)=='R')
	&& (*(ptr+3)=='t' || *(ptr+3)=='T'))
	{
	erro='1';
	//inserir(0,"sqrt",'s','1',0);
	inserir(0,'r','s','1',0);
	ptr=ptr+4;
	l=l+4;
	}

	//log

	if ((*ptr=='l' || *ptr=='L') && (*(ptr+1)=='o' || *(ptr+1)=='O')
	&& (*(ptr+2)=='g' || *(ptr+2)=='G'))
	{
	erro='1';
	//inserir(0,"log",'s','1',0);
	inserir(0,'L','s','1',0);
	ptr=ptr+3;
	l=l+3;
	}

	//ln

	if ((*ptr=='l' || *ptr=='L') && (*(ptr+1)=='n' || *(ptr+1)=='N'))
	{
	erro='1';
	//inserir(0,"ln",'s','1',0);
	inserir(0,'l','s','1',0);
	ptr=ptr+2;
	l=l+2;
	}


	//step

	if ((*ptr=='s' || *ptr=='S') && (*(ptr+1)=='t' || *(ptr+1)=='T')
	&& (*(ptr+2)=='e' || *(ptr+2)=='E') && (*(ptr+3)=='p' || *(ptr+3)=='P'))
	{
	erro='1';
	//inserir(0,"step",'s','1',0);
	inserir(0,'p','s','1',0);
	ptr=ptr+4;
	l=l+4;
	}


	//sgf

	if ((*ptr=='s' || *ptr=='S') && (*(ptr+1)=='g' || *(ptr+1)=='G')
	&& (*(ptr+2)=='f' || *(ptr+2)=='F') )
	{
	erro='1';
	//inserir(0,"sgf",'s','1',0);
	inserir(0,'f','s','1',0);
	ptr=ptr+3;
	l=l+3;
	}

	//dirac
	if ((*ptr=='d' || *ptr=='D') && (*(ptr+1)=='i' || *(ptr+1)=='I')
	&& (*(ptr+2)=='r' || *(ptr+2)=='R') && (*(ptr+3)=='a' || *(ptr+3)=='A')
	&& (*(ptr+4)=='c' || *(ptr+4)=='C'))
	{
	erro='1';
	//inserir(0,"dirac",'s','1',0);
	inserir(0,'d','s','1',0);
	ptr=ptr+5;
	l=l+5;
	}

	//rect - fun‡Æo onda quadrada
	if ((*ptr=='r' || *ptr=='R') && (*(ptr+1)=='e' || *(ptr+1)=='E')
	&& (*(ptr+2)=='c' || *(ptr+2)=='C') && (*(ptr+3)=='t' || *(ptr+3)=='T'))
	{
	erro='1';
	//inserir(0,"rect",'s','1',0);
	inserir(0,'R','s','1',0);
	ptr=ptr+4;
	l=l+4;
	}

	//trem - trem de impulsos
	if ((*ptr=='t' || *ptr=='T') && (*(ptr+1)=='r' || *(ptr+1)=='R')
	&& (*(ptr+2)=='e' || *(ptr+2)=='E') && (*(ptr+3)=='m' || *(ptr+3)=='M'))
	{
	erro='1';
	//inserir(0,"trem",'s','1',0);
	inserir(0,'M','s','1',0);
	ptr=ptr+4;
	l=l+4;
	}



	//square - trem de rectangulos
	if ((*ptr=='s' || *ptr=='S') && (*(ptr+1)=='q' || *(ptr+1)=='Q')
	&& (*(ptr+2)=='u' || *(ptr+2)=='U') && (*(ptr+3)=='a' || *(ptr+3)=='A')
	&& (*(ptr+4)=='r' || *(ptr+4)=='R') && (*(ptr+5)=='e' || *(ptr+5)=='E'))
	{
	erro='1';
	//inserir(0,"square",'s','1',0);
	inserir(0,'Q','s','1',0);
	ptr=ptr+6;
	l=l+6;
	}







	
	if (*ptr=='^' || *ptr=='E')
		{
		erro='1';
		//funcoes[0]=*ptr;
		//funcoes[1]='\0';
		//inserir(0,funcoes,'s','2',0);
		inserir(0,*ptr,'s','2',0);
		l++;
		ptr++;
		}




	if (*ptr==t)
	{
	erro='1';
	inserir(x,'0','n','0',0);
	l++;
	ptr++;
	}



	if (*ptr==t1)
	{
	erro='1';
	inserir(y,'0','n','0',0);
	l++;
	ptr++;
	}




	if (*ptr==t2)
	{
	erro='1';
	inserir(z,'0','n','0',0);
	l++;
	ptr++;
	}


	if (erro=='0')
	{
		if (l>0)
			liberta();

		ERRO=true;
		return err;
		//AfxMessageBox("Erro!!!\nVerifique a sintaxe da expressão.\n O programa será encerrado!");
	//	exit(0);
	}

	}

   return resolve();
}


/*---Y(n1,n2,n3,n4,...,nn)=F(x1,x2,x3,x4,...,xn)--------------------------------*/


//Complexo Calculadora::fxy(CString str,double x,CString u,double y,CString v, double z, CString s)
Complexo Calculadora::f_n_variaveis(CString str, double x, CString var)
{
	int n,l=0;
	int i;
	int j;
	bool flag;
	char *ptr,exp[1024];
//	char funcoes[20];
	char num[500];
	ptr=exp;
	char erro;
	Complexo err(0,0);

	
	if (str.GetLength()==0)
	{
		ERRO=true;
		return err;
	}

	for(j=0;j<str.GetLength();j++)
	{
		exp[j]=str.GetAt(j);
	}
	exp[j]='\0';


	l=0;
	while(l < str.GetLength())
	{
	erro='0';
	n=0;

	// Introduz um numero na pilha
	if (isdigit(*ptr) || *ptr=='.')
	{
		erro='1';
		while (isdigit(*ptr) || *ptr=='.' )
		{
			num[n]=*ptr;
			ptr++;
			n++;
		 }

		l=l+n;
		num[n]='\0';
		inserir(atof(num),'0','n','0',0);

		//EX: 2x  -> 2*x : introduz o * para a multiplicação
	/*	if (*(ptr)==t || *(ptr)==t1 || *(ptr)==t2)
		{
			erro='1';
			inserir(0,'*','s','1',0);
		}*/
		for(i=0;i<variaveis_n.GetSize();i++)
		{

			flag=false;
			for(j=0;j<variaveis_n[i].GetLength();j++)
			{
				if(*(ptr+j)==variaveis_n[i].GetAt(j))
					flag=true;
			}
			if (flag)
			{
				erro='1';
				inserir(0,'*','s','1',0);
			}

		}

	 }


		//imaginário
	if (*ptr=='j' || *ptr=='J' || *ptr=='i' || *ptr=='I' )
	{
	erro='1';
	inserir(0,'0','n','0',1);
	if (isdigit(*(ptr+1)) || *(ptr+1)=='.' || *(ptr+1)=='c'
		|| *(ptr+1)=='C' || *(ptr+1)=='s' || *(ptr+1)=='S'
		|| *(ptr+1)=='t' || *(ptr+1)=='T' || *(ptr+1)=='l'
		|| *(ptr+1)=='L' || *(ptr+1)=='s'
		|| *(ptr+1)=='S' || *(ptr+1)=='g' || *(ptr+1)=='G'
		|| *(ptr+1)=='a' || *(ptr+1)=='A' || *(ptr+1)=='d'
		|| *(ptr+1)=='D' || *(ptr+1)=='p' || *(ptr+1)=='P'
		|| *(ptr+1)=='e' || *(ptr+1)=='E' || *(ptr+1)=='('
		|| *(ptr+1)=='|' || *(ptr+1)=='R' || *(ptr+1)=='Q'
		|| *(ptr+1)=='M'
		)
	inserir(0,'*','s','1',0);
	ptr++;
	l++;
	}





	
	//exp

	if ((*ptr=='e' || *ptr=='E') && (*(ptr+1)=='x' || *(ptr+1)=='X')
	&& (*(ptr+2)=='p' || *(ptr+2)=='P'))
	{
	erro='1';
	inserir(0,'e','s','1',0);
	ptr=ptr+3;
	l=l+3;
	}

	//nepper

	if (*ptr=='e')
	{
		erro='1';
		inserir(2.718281828,'0','n','0',0);
		l++;
		ptr++;
	}

	//pi

	if ((*ptr=='p' || *ptr=='P') && (*(ptr+1)=='i' || *(ptr+1)=='I'))
	{
		erro='1';
		inserir(3.141592654,'0','n','0',0);
		ptr=ptr+2;
		l=l+2;
	}
	// Introduz um operador na pilha ou a variavel x

	if (*ptr=='+' || *ptr=='-')
	{
		if (*ptr=='-' && l==0)
		{
			inserir(0,'0','n','0',0);
		}
		erro='1';
		//funcoes[0]=*ptr;
		//funcoes[1]='\0';
		inserir(0,*ptr,'s','0',0);
		ptr++;
		l++;
	}

	if (*ptr=='/' || *ptr=='*' || *ptr=='(' || *ptr==')' || *ptr=='|')
	{
	erro='1';
	//funcoes[0]=*ptr;
	//funcoes[1]='\0';
	inserir(0,*ptr,'s','1',0);
	ptr++;
	l++;
	}



	//acosh

	if ((*ptr=='a' || *ptr=='A') && (*(ptr+1)=='c' || *(ptr+1)=='C') &&
	(*(ptr+2)=='o' || *(ptr+2)=='O') && (*(ptr+3)=='s' || *(ptr+3)=='S')
	&& (*(ptr+4)=='h' || *(ptr+4)=='H'))
	{
	erro='1';
//	inserir(0,"acosh",'s','1',0);
	inserir(0,'B','s','1',0);
	ptr=ptr+5;
	l=l+5;
	}


	//cosh

	if ((*ptr=='c' || *ptr=='C') && (*(ptr+1)=='o' || *(ptr+1)=='O') &&
	(*(ptr+2)=='s' || *(ptr+2)=='S') && (*(ptr+3)=='h' || *(ptr+3)=='H'))
	{
	erro='1';
//	inserir(0,"cosh",'s','1',0);
	inserir(0,'o','s','1',0);
	ptr=ptr+4;
	l=l+4;
	}

	//acos
	
	if ((*ptr=='a' || *ptr=='A') && (*(ptr+1)=='c' || *(ptr+1)=='C') &&
	(*(ptr+2)=='o' || *(ptr+2)=='O') && (*(ptr+3)=='s' || *(ptr+3)=='S'))
	{
	erro='1';
//	inserir(0,"acos",'s','1',0);
	inserir(0,'C','s','1',0);
	ptr=ptr+4;
	l=l+4;
	}

	//cos

	if ((*ptr=='c' || *ptr=='C') && (*(ptr+1)=='o' || *(ptr+1)=='O')
	&& (*(ptr+2)=='s' || *(ptr+2)=='S'))
	{
	erro='1';
	//inserir(0,"cos",'s','1',0);
	inserir(0,'c','s','1',0);
	ptr=ptr+3;
	l=l+3;
	}



	//asinh

	if ((*ptr=='a' || *ptr=='A') && (*(ptr+1)=='s' || *(ptr+1)=='S') &&
	(*(ptr+2)=='i' || *(ptr+2)=='I') && (*(ptr+3)=='n' || *(ptr+3)=='N')
	&& (*(ptr+4)=='h' || *(ptr+4)=='H'))
	{
	erro='1';
	//inserir(0,"asinh",'s','1',0);
	inserir(0,'b','s','1',0);
	ptr=ptr+5;
	l=l+5;
	}


	//sinh

	if ((*ptr=='s' || *ptr=='S') && (*(ptr+1)=='i' || *(ptr+1)=='I') &&
	(*(ptr+2)=='n' || *(ptr+2)=='N') && (*(ptr+3)=='h' || *(ptr+3)=='H'))
	{
	erro='1';
	//inserir(0,"sinh",'s','1',0);
	inserir(0,'i','s','1',0);
	ptr=ptr+4;
	l=l+4;
	}


	//asin

	if ((*ptr=='a' || *ptr=='A') && (*(ptr+1)=='s' || *(ptr+1)=='S') &&
	(*(ptr+2)=='i' || *(ptr+2)=='I') && (*(ptr+3)=='n' || *(ptr+3)=='N'))
	{
	erro='1';
	//inserir(0,"asin",'s','1',0);
	inserir(0,'S','s','1',0);
	ptr=ptr+4;
	l=l+4;
	}

	//sin

	if ((*ptr=='s' || *ptr=='S') && (*(ptr+1)=='i' || *(ptr+1)=='I')
	&& (*(ptr+2)=='n' || *(ptr+2)=='N'))
	{
	erro='1';
	//inserir(0,"sin",'s','1',0);
	inserir(0,'s','s','1',0);
	ptr=ptr+3;
	l=l+3;
	}

	//sinc

	if ((*ptr=='s' || *ptr=='S') && (*(ptr+1)=='i' || *(ptr+1)=='I')
	&& (*(ptr+2)=='n' || *(ptr+2)=='N') && (*(ptr+3)=='c' || *(ptr+3)=='C') )
	{
	erro='1';
	//inserir(0,"sinc",'s','1',0);
	inserir(0,'n','s','1',0);
	ptr=ptr+4;
	l=l+4;
	}


	//atanh

	if ((*ptr=='a' || *ptr=='A') && (*(ptr+1)=='t' || *(ptr+1)=='T') &&
	(*(ptr+2)=='a' || *(ptr+2)=='A') && (*(ptr+3)=='n' || *(ptr+3)=='N')
	&& (*(ptr+4)=='h' || *(ptr+4)=='H'))
	{
	erro='1';
	//inserir(0,"atanh",'s','1',0);
	inserir(0,'D','s','1',0);
	ptr=ptr+5;
	l=l+5;
	}

	//atan

	if ((*ptr=='a' || *ptr=='A') && (*(ptr+1)=='t' || *(ptr+1)=='T') &&
	(*(ptr+2)=='a' || *(ptr+2)=='A') && (*(ptr+3)=='n' || *(ptr+3)=='N'))
	{
	erro='1';
	//inserir(0,"atan",'s','1',0);
	inserir(0,'a','s','1',0);
	ptr=ptr+4;
	l=l+4;
	}


	//tanh

	if ((*ptr=='t' || *ptr=='T') && (*(ptr+1)=='a' || *(ptr+1)=='A')
	&& (*(ptr+2)=='n' || *(ptr+2)=='N') && (*(ptr+3)=='h' || *(ptr+3)=='H'))
	{
	erro='1';
//	inserir(0,"tanh",'s','1',0);
	inserir(0,'T','s','1',0);
	ptr=ptr+4;
	l=l+4;
	}

	//tan

	if ((*ptr=='t' || *ptr=='T') && (*(ptr+1)=='a' || *(ptr+1)=='A') 
		&& (*(ptr+2)=='n' || *(ptr+2)=='N'))
	{
	erro='1';
	//inserir(0,"tan",'s','1',0);
	inserir(0,'t','s','1',0);
	ptr=ptr+3;
	l=l+3;
	}


	//cotgh

	if ((*ptr=='c' || *ptr=='C') && (*(ptr+1)=='o' || *(ptr+1)=='O')
	&& (*(ptr+2)=='t' || *(ptr+2)=='T') && (*(ptr+3)=='g' || *(ptr+3)=='G')
	&& (*(ptr+4)=='h' || *(ptr+4)=='H'))
	{
	erro='1';
	//inserir(0,"cotgh",'s','1',0);
	inserir(0,'h','s','1',0);
	ptr=ptr+5;
	l=l+5;
	}


	//acotgh

	if ((*ptr=='a' || *ptr=='A') && (*(ptr+1)=='c' || *(ptr+1)=='C') &&
	(*(ptr+2)=='o' || *(ptr+2)=='O') && (*(ptr+3)=='t' || *(ptr+3)=='T') &&
	(*(ptr+4)=='g' || *(ptr+4)=='G') && (*(ptr+5)=='h' || *(ptr+5)=='H'))
	{
	erro='1';
	//inserir(0,"acotgh",'s','1',0);
	inserir(0,'F','s','1',0);
	ptr=ptr+5;
	l=l+5;
	}


	//acotg

	if ((*ptr=='a' || *ptr=='A') && (*(ptr+1)=='c' || *(ptr+1)=='C') &&
	(*(ptr+2)=='o' || *(ptr+2)=='O') && (*(ptr+3)=='t' || *(ptr+3)=='T') &&
	(*(ptr+4)=='g' || *(ptr+4)=='G'))
	{
	erro='1';
	//inserir(0,"acotg",'s','1',0);
	inserir(0,'A','s','1',0);
	ptr=ptr+5;
	l=l+5;
	}

	//cotg

	if ((*ptr=='c' || *ptr=='C') && (*(ptr+1)=='o' || *(ptr+1)=='O')
	&& (*(ptr+2)=='t' || *(ptr+2)=='T') && (*(ptr+3)=='g' || *(ptr+3)=='G'))
	{
	erro='1';
	//inserir(0,"cotg",'s','1',0);
	inserir(0,'g','s','1',0);
	ptr=ptr+4;
	l=l+4;
	}

	//sqrt

	if ((*ptr=='s' || *ptr=='S') && (*(ptr+1)=='q' || *(ptr+1)=='Q')
	&& (*(ptr+2)=='r' || *(ptr+2)=='R')
	&& (*(ptr+3)=='t' || *(ptr+3)=='T'))
	{
	erro='1';
	//inserir(0,"sqrt",'s','1',0);
	inserir(0,'r','s','1',0);
	ptr=ptr+4;
	l=l+4;
	}

	//log

	if ((*ptr=='l' || *ptr=='L') && (*(ptr+1)=='o' || *(ptr+1)=='O')
	&& (*(ptr+2)=='g' || *(ptr+2)=='G'))
	{
	erro='1';
	//inserir(0,"log",'s','1',0);
	inserir(0,'L','s','1',0);
	ptr=ptr+3;
	l=l+3;
	}

	//ln

	if ((*ptr=='l' || *ptr=='L') && (*(ptr+1)=='n' || *(ptr+1)=='N'))
	{
	erro='1';
	//inserir(0,"ln",'s','1',0);
	inserir(0,'l','s','1',0);
	ptr=ptr+2;
	l=l+2;
	}


	//step

	if ((*ptr=='s' || *ptr=='S') && (*(ptr+1)=='t' || *(ptr+1)=='T')
	&& (*(ptr+2)=='e' || *(ptr+2)=='E') && (*(ptr+3)=='p' || *(ptr+3)=='P'))
	{
	erro='1';
	//inserir(0,"step",'s','1',0);
	inserir(0,'p','s','1',0);
	ptr=ptr+4;
	l=l+4;
	}


	//sgf

	if ((*ptr=='s' || *ptr=='S') && (*(ptr+1)=='g' || *(ptr+1)=='G')
	&& (*(ptr+2)=='f' || *(ptr+2)=='F') )
	{
	erro='1';
	//inserir(0,"sgf",'s','1',0);
	inserir(0,'f','s','1',0);
	ptr=ptr+3;
	l=l+3;
	}

	//dirac
	if ((*ptr=='d' || *ptr=='D') && (*(ptr+1)=='i' || *(ptr+1)=='I')
	&& (*(ptr+2)=='r' || *(ptr+2)=='R') && (*(ptr+3)=='a' || *(ptr+3)=='A')
	&& (*(ptr+4)=='c' || *(ptr+4)=='C'))
	{
	erro='1';
	//inserir(0,"dirac",'s','1',0);
	inserir(0,'d','s','1',0);
	ptr=ptr+5;
	l=l+5;
	}

	//rect - fun‡Æo onda quadrada
	if ((*ptr=='r' || *ptr=='R') && (*(ptr+1)=='e' || *(ptr+1)=='E')
	&& (*(ptr+2)=='c' || *(ptr+2)=='C') && (*(ptr+3)=='t' || *(ptr+3)=='T'))
	{
	erro='1';
	//inserir(0,"rect",'s','1',0);
	inserir(0,'R','s','1',0);
	ptr=ptr+4;
	l=l+4;
	}

	//trem - trem de impulsos
	if ((*ptr=='t' || *ptr=='T') && (*(ptr+1)=='r' || *(ptr+1)=='R')
	&& (*(ptr+2)=='e' || *(ptr+2)=='E') && (*(ptr+3)=='m' || *(ptr+3)=='M'))
	{
	erro='1';
	//inserir(0,"trem",'s','1',0);
	inserir(0,'M','s','1',0);
	ptr=ptr+4;
	l=l+4;
	}



	//square - trem de rectangulos
	if ((*ptr=='s' || *ptr=='S') && (*(ptr+1)=='q' || *(ptr+1)=='Q')
	&& (*(ptr+2)=='u' || *(ptr+2)=='U') && (*(ptr+3)=='a' || *(ptr+3)=='A')
	&& (*(ptr+4)=='r' || *(ptr+4)=='R') && (*(ptr+5)=='e' || *(ptr+5)=='E'))
	{
	erro='1';
	//inserir(0,"square",'s','1',0);
	inserir(0,'Q','s','1',0);
	ptr=ptr+6;
	l=l+6;
	}








	if (*ptr=='^' || *ptr=='E')
		{
		erro='1';
		//funcoes[0]=*ptr;
		//funcoes[1]='\0';
		//inserir(0,funcoes,'s','2',0);
		inserir(0,*ptr,'s','2',0);
		l++;
		ptr++;
		}




	//---------------variaveis---------------------------//


	
	for(i=0;i<variaveis_n.GetSize();i++)
	{
		flag=false;
		for(j=0;j<variaveis_n[i].GetLength();j++)
		{
			if(*(ptr+j)==variaveis_n[i].GetAt(j))
				flag=true;
		}
		if (flag)
		{
			erro='1';
	
			inserir(xn[i],'0','n','0',0);
			ptr=ptr+variaveis_n[i].GetLength();
			l=l+variaveis_n[i].GetLength();
		}

	}



		flag=false;
		for(j=0;j<var.GetLength();j++)
		{
			if(*(ptr+j)==var.GetAt(j))
				flag=true;
		}
		if (flag)
		{
			erro='1';
	
			inserir(x,'0','n','0',0);
			ptr=ptr+var.GetLength();
			l=l+var.GetLength();
		}




	if (erro=='0')
	{
		if (l>0)
			liberta();

		ERRO=true;
		return err;
		//AfxMessageBox("Erro!!!\nVerifique a sintaxe da expressão.\n O programa será encerrado!");
	//	exit(0);
	}

	}

   return resolve();
}






/* chaveta(): ... + . ( . 'A' . ) . + ....
	Depois da lista j  ter sido atuada por resolve pode acontecer
	ficar um numero entre duas chavetas. A fun‡„o chaveta() retira
   as chavetas fazendo as liga‡”es de 'A' com as estruturas posterior
	e anterior de 'A'. Esta fun‡„o tamb‚m ‚ usada para o m¢dulo | A |.
*/
void Calculadora::chaveta(list_d *paux)
{
	list_d *liberta1,*liberta2;

   liberta1=paux->anterior;
   liberta2=paux->proximo;

	if (paux->anterior->operador=='|' && paux->proximo->operador=='|')
	{
	if (paux->operando==0)
	     paux->operando=fabs(paux->j);
	else if (paux->j==0)
		  paux->operando=fabs(paux->operando);
	else if (paux->operando <= paux->j)
		  paux->operando=fabs(paux->j)*sqrt(1+pow(paux->operando/paux->j,2));
	else
		  paux->operando=fabs(paux->operando)*sqrt(1+pow(paux->j/paux->operando,2));
	paux->j=0;
	}


   if (paux->anterior->anterior)
	{
	paux->anterior=paux->anterior->anterior;
	paux->anterior->proximo=paux;
	}
	else
	{
	paux->anterior=NULL;
	lista.inicio=paux;
	}

   if (paux->proximo->proximo)
	{
	paux->proximo=paux->proximo->proximo;
	paux->proximo->anterior=paux;
	}
   else
	{
	paux->proximo=NULL;
	lista.fim=paux;
	}

   free(liberta1);
   free(liberta2);
}

/* opera() : .... + . A . '*' . B . + ....
	Liberta as estruturas com A e B, coloca o valor da opera‡„o na
	estrutura '*' e faz as liga‡”es de paux … estrutura anterior de A
	e posterior de B
*/


void Calculadora::opera(list_d *paux)
{
	list_d *liberta1,*liberta2;

	Complexo a(paux->anterior->operando,paux->anterior->j);
	Complexo b(paux->proximo->operando,paux->proximo->j);
	Complexo z;

/*	if (paux->operador=='*')
	{
	paux->operando=paux->anterior->operando*paux->proximo->operando
				 -paux->anterior->j*paux->proximo->j;
	paux->j=paux->anterior->operando*paux->proximo->j
				 +paux->anterior->j*paux->proximo->operando;
	}
  */
	if (paux->operador=='*')
	{
	z=a*b;
	paux->operando=z.r;
	paux->j=z.i;
	}


	INFINITO=0;

	if (paux->operador=='/')
	{
	z=a/b;
	paux->operando=z.r;
	paux->j=z.i;

		if ((b.r==0) && (b.i==0))
		{
			if (a.r>0)
				INFINITO=1;
			if (a.r<0)
				INFINITO=-1;		
		}
	}


	if (paux->operador=='+')
	{
	paux->operando=paux->anterior->operando+paux->proximo->operando;
	paux->j=paux->anterior->j+paux->proximo->j;
	}

	if (paux->operador=='-')
	{
	paux->operando=paux->anterior->operando-paux->proximo->operando;
	paux->j=paux->anterior->j-paux->proximo->j;
	}

	//The complex pow is defined by
	//pow(base, expon) = exp(expon log(base))

	if (paux->operador=='^')
	{
  //	paux->operando=pow(paux->anterior->operando,paux->proximo->operando);
	z=a^b;
	paux->operando=z.r;
	paux->j=z.i;
	}


	if (paux->operador=='E')
	{
	//paux->operando=paux->anterior->operando*pow(10,paux->proximo->operando);

	z=a*(10^b);
	paux->operando=z.r;
	paux->j=z.i;
	}

	paux->operador='0';
//	paux->operador[0]='0';
//	paux->operador[1]='\0';
	paux->priori='-';
	paux->flag='n';

	liberta1=paux->anterior;
	liberta2=paux->proximo;

	if (paux->proximo->proximo)
	{
	paux->proximo=paux->proximo->proximo;
	paux->proximo->anterior=paux;
	}
	else
	{
	paux->proximo=NULL;
	lista.fim=paux;
	}

	if (paux->anterior->anterior)
	{
	paux->anterior=paux->anterior->anterior;
	paux->anterior->proximo=paux;
	}
	else
	{
	paux->anterior=NULL;
	lista.inicio=paux;
	}

	free(liberta1);
	free(liberta2);
}

/*  opera2():  ...+ . 'ln' . A + ....
	 Coloca o valor da opera‡„o lnA na estrutura de 'ln' e liberta
	 a estrutura de A. Faz as liga‡”es de 'ln' … estrutura
	 posterior de A e desta a 'ln'.
*/
void Calculadora::opera2(list_d *paux)
{
	list_d *liberta=paux->proximo;

	Complexo z(paux->proximo->operando,paux->proximo->j);


		/*
	sen ; 	s		PI = 3.14..;  		^ = 'elevado a ...'
	cos ; 	c		e = 2.71...;    	E = 'vezes 10 elevado a...'
	tg  ; 	t     log ;   L         ( )= chavetas
	cotg; 	g		ln ;    l         | |= m¢dulo
	sqrt;	r     exp;    e         j = imagin rio
	
	cosh; 	o     senh;   i         i = imagin rio (igual a j)
	tgh;  	T     cotgh;  h

	arcsen;  S     arccos; C
	arctg    a     acotg;  A

	step;    p     sinc;   n
	sgf ;    f     dirac;  d
	rect;		R     square; Q(trem de rectangulos)
						trem;   M(trem de impulsos)
	
	asinh;	b	  acosh;  B
	atanh;	D	  acotgh; F

	  */

	INFINITO=0;


	
/*	if (paux->operador=='sin' || paux->operador=='cos' || paux->operador=='tan' 
		|| paux->operador=='cotg' ||  paux->operador=='sinh' || paux->operador=='cosh' 
		|| paux->operador=='tanh' || paux->operador=='cotgh' || paux->operador=='sinc')*/

	if (paux->operador=='s' || paux->operador=='c' || paux->operador=='t' || paux->operador=='g' 
		/*|| paux->operador=='o' || paux->operador=='T' || paux->operador=='i' || paux->operador=='h'*/
		|| paux->operador=='n' )

	{
	
		switch(flag_graus_rad_grados)
		{
		case 0:
			z=PI/180*z; //graus

			break;
		case 1://radianos

			break;
		case 2:
			z=PI/200*z;//grados

			break;
		};

		paux->operando=z.r;
		paux->j=z.i;
	}



	if (paux->operador=='n') //sinc
	{
	z=sen(PI*z)/(PI*z);
	paux->operando=z.r;
	paux->j=z.i;
	}

	if (paux->operador=='s') //sen
	{
	z=sen(z);
	paux->operando=z.r;
	paux->j=z.i;
	}


	if (paux->operador=='c') //cos
	{
	z=cos(z);
	paux->operando=z.r;
	paux->j=z.i;
	}


	if (paux->operador=='o') //cosh
	{
	z=cosh(z);
	paux->operando=z.r;
	paux->j=z.i;
	}

	if (paux->operador=='i') //senh
	{
	z=senh(z);
	paux->operando=z.r;
	paux->j=z.i;
	}


	if (paux->operador=='t')//tan
	{
	z=tg(z);
	paux->operando=z.r;
	paux->j=z.i;
	}


	if (paux->operador=='T')//tgh
	{
	z=tgh(z);
	paux->operando=z.r;
	paux->j=z.i;
	}

	if (paux->operador=='h') //cotgh
	{
	z=cosh(z)/senh(z);
	paux->operando=z.r;
	paux->j=z.i;
	}


	if (paux->operador=='g') //cotg
	{
	z=cos(z)/sen(z);
	paux->operando=z.r;
	paux->j=z.i;
	}


	if (paux->operador=='S') //asin
	{
	z=arcsen(z);
	paux->operando=z.r;
	paux->j=z.i;
	}


	if (paux->operador=='C') // acos
	{
	z=arccos(z);
	paux->operando=z.r;
	paux->j=z.i;
	}


	if (paux->operador=='a') // atan
	{
	z=arctg(z);
	paux->operando=z.r;
	paux->j=z.i;
	}

	if (paux->operador=='A') // acotg  
	{
	z=acotg(z);
	paux->operando=z.r;
	paux->j=z.i;
	}

	//////////////////////////////////
	
	if (paux->operador=='b') //asinh
	{
	z=asinh(z);
	paux->operando=z.r;
	paux->j=z.i;
	}


	if (paux->operador=='B') // acosh
	{
	z=acosh(z);
	paux->operando=z.r;
	paux->j=z.i;
	}


	if (paux->operador=='D') // atanh
	{
	z=atanh(z);
	paux->operando=z.r;
	paux->j=z.i;
	}

	if (paux->operador=='F') // acotgh
	{
	z=acotgh(z);
	paux->operando=z.r;
	paux->j=z.i;
	}


	//arcsen;  S     arccos; C
	//arctg    a     acotg;  A
	
	/*if (paux->operador=='S' || paux->operador=='C' || paux->operador=='a' 
		|| paux->operador=='A' || paux->operador=='b' || paux->operador=='B' 
		|| paux->operador=='D' || paux->operador=='F'  )*/

	if (paux->operador=='S' || paux->operador=='C' || paux->operador=='a' 
		|| paux->operador=='A' )
	{
	
		switch(flag_graus_rad_grados)
		{
		case 0://graus
			z=180/PI*z;

			break;
		case 1://rad

			break;
		case 2://grados
			z=200/PI*z;

			break;
		};

		paux->operando=z.r;
		paux->j=z.i;	
	}



		/*
			sen ; 	s		PI = 3.14..;  		^ = 'elevado a ...'
	cos ; 	c		e = 2.71...;    	E = 'vezes 10 elevado a...'
	tg  ; 	t     log ;   L         ( )= chavetas
	cotg; 	g		ln ;    l         | |= m¢dulo
	sqrt;	r     exp;    e         j = imagin rio
	cosh; 	o     senh;   i         i = imagin rio (igual a j)
	tgh;  	T     cotgh;  h
	arcsen;  S     arccos; C
	arctg    a     acotg;  A
	step;    p     sinc;   n
	sgf ;    f     dirac;  d
	rect;		R     square; Q(trem de rectangulos)
						trem;   M(trem de impulsos)

  	asinh;	b	  acosh;  B
	atanh;	D	  acotgh; F
	*/



	if (paux->operador=='l')  //ln
	{

		if (z.r==0)
		{
		INFINITO=-1;
		}

		z=ln(z);
		paux->operando=z.r;
		paux->j=z.i;
	}

	if (paux->operador=='L')   //log
	{
		if (z.r==0)
		{
		INFINITO=-1;
		}

		z=log(z);
		paux->operando=z.r;
		paux->j=z.i;
	}

	if (paux->operador=='r')//sqrt
	{
	z=sqrt(z);
	paux->operando=z.r;
	paux->j=z.i;
	}

	if (paux->operador=='e')  //exp()
	{
	z=exp(z);
	paux->operando=z.r;
	paux->j=z.i;
	}

	//função step(x)=1 ;x >= 0
	//			step(x)=0 ;x <	 0
	if (paux->operador=='p')   //step
		{
		if (paux->proximo->operando >= 0)
			paux->operando=1;
		else
			paux->operando=0;
		}

	//função sgf(x)=1 ;x >= 0
	//			sgf(x)=-1 ;x <	 0
	if (paux->operador=='f')   //sgf
		{
		if (paux->proximo->operando >= 0)
			paux->operando=1;
		else
			paux->operando=-1;
		}

	//dirac(x)= 1 ; x = 0
	//dirac(x)= 0 ; x != 0
	if (paux->operador=='d')   //dirac
		{
		if (paux->proximo->operando == 0)
			paux->operando=1;
		else
			paux->operando=0;
		}

	if (paux->operador=='R')  //rect - fun‡Æo onda quadrada
		{
		if (paux->proximo->operando <=1 && paux->proximo->operando >= -1)
			paux->operando=1;
		else
			paux->operando=0;
		}

	if (paux->operador=='Q')  //square - trem de rectangulos
		{
		if ((paux->proximo->operando - floorl(paux->proximo->operando))
			>= (ceill(paux->proximo->operando) - paux->proximo->operando))
			if ((floorl(paux->proximo->operando)+0.75) <= paux->proximo->operando)
				paux->operando=1;
			else
				paux->operando=-1;
		else
			if ((floorl(paux->proximo->operando)+0.25) >= paux->proximo->operando)
				paux->operando=1;
			else
				paux->operando=-1;
		}


	if (paux->operador=='M')  //trem - trem de impulsos
		{
		if ((paux->proximo->operando - floorl(paux->proximo->operando))
			>= (ceill(paux->proximo->operando) - paux->proximo->operando))
			if ((floorl(paux->proximo->operando)+0.75) <= paux->proximo->operando)
				paux->operando=1;
			else
				paux->operando=0;
		else
			if ((floorl(paux->proximo->operando)+0.25) >= paux->proximo->operando)
				paux->operando=1;
			else
				paux->operando=0;
		}




	if (paux->operador=='-')
	{
	paux->operando=-paux->proximo->operando;
	paux->j=-paux->proximo->j;
	}

	if (paux->operador=='+')
	{
	paux->operando=paux->proximo->operando;
	paux->j=paux->proximo->j;
	}

	if (paux->operador=='E')
	paux->operando=0;
	paux->operador='0';
//	paux->operador[0]='0';
//	paux->operador[1]='\0';
	paux->flag='n';
	paux->priori='-';

	if (paux->proximo->proximo)
	{
	paux->proximo=paux->proximo->proximo;
	paux->proximo->anterior=paux;
	}
	else
	{
	paux->proximo=NULL;
	lista.fim=paux;
	}

	free(liberta);
}
/*
Calculadora::isempty()
{
   return !lista.inicio;
}
*/


/* Insere os caracteres que representam operadores e os numeros
na lista duplamente ligada. Para cada caractere ou numero inserido ‚
alocada uma estrutura para a lista.
*/
int Calculadora::inserir(double num,char sinal, char fl,char pri,double i)
{
	list_d *paux;
	CString sinal_aux="3";
	//sinal_aux=sinal;

   /*-------------- Aloca a estrutura --------------*/
   if (!(paux=(list_d *)malloc(sizeof(list_d))))
      {
      //printf("\nErro de aloção de memoria\\falta de memoria");
	   AfxMessageBox("\nErro de aloção de memoria\\falta de memoria");
    //  getch();
      exit(1);
      }
	paux->proximo=paux->anterior=NULL;

	paux->operando=num;

	
	paux->operador=sinal;
//	paux->operador= "43";
	//strcpy(paux->operador,sinal);
	paux->flag=fl;
	paux->priori=pri;
	paux->j=i;

	paux->derivada='0';
	paux->nivel=0;

   //if (isempty())
	if (!lista.inicio)
      lista.inicio=lista.fim=paux;
   else
	   {
	   lista.fim->proximo=paux;
		paux->anterior=lista.fim;
	   lista.fim=paux;
	   }

	return 1;
}


int Calculadora::inserir_derivada(double num,char sinal, char fl,char pri,double i, char derivada, int nivel)
{
	list_d *paux;
	CString sinal_aux="3";
	//sinal_aux=sinal;

   /*-------------- Aloca a estrutura --------------*/
   if (!(paux=(list_d *)malloc(sizeof(list_d))))
      {
      //printf("\nErro de aloção de memoria\\falta de memoria");
	   AfxMessageBox("\nErro de aloção de memoria\\falta de memoria");
    //  getch();
      exit(1);
      }
	paux->proximo=paux->anterior=NULL;

	paux->operando=num;

	
	paux->operador=sinal;
//	paux->operador= "43";
	//strcpy(paux->operador,sinal);
	paux->flag=fl;
	paux->priori=pri;
	paux->j=i;
	paux->derivada=derivada;
	paux->nivel=nivel;

   //if (isempty())
	if (!lista.inicio)
      lista.inicio=lista.fim=paux;
   else
	   {
	   lista.fim->proximo=paux;
		paux->anterior=lista.fim;
	   lista.fim=paux;
	   }

	return 1;
}



/* liberta uma lista dulpamente ligada que contenha erros de sintaxe */
void Calculadora::liberta()
{
	 list_d *paux=lista.inicio;

    while(paux != lista.fim)
    {
    paux=paux->proximo;
	 paux->anterior=NULL;
	 free(paux->anterior);
    }
    paux->proximo=NULL;
	paux=paux->proximo;
    lista.inicio=lista.fim=NULL;
    free(paux);
}

double Calculadora::Integral(CString fx, CString x, double a, double b, double m)
{

	double h;
	double Isc;
	double i;
	bool par=true;

	if (a > b)
	{
		i=a;
		a=b;
		b=i;
	}

	h=(b-a)/m;

	Isc=h/3*f(fx,a,x).r + h/3*f(fx,b,x).r;

	for(i=a+h;i<b;i=i+h)
	{
		if (par==true)
		{
			Isc=Isc+(h/3)*4*f(fx,i,x).r;
			par=false;
		}
		else
		{
			Isc=Isc+(h/3)*2*f(fx,i,x).r;
			par=true;
		}	
	}

	return Isc;
}

double Calculadora::IntegralArea(CString fx, CString x, double a, double b, double h)
{

//	double h=(b-a)/m;
	bool par=true;

	double Isc;

	Isc=fabs(h/3*f(fx,a,x).r) + fabs(h/3*f(fx,b,x).r);

	
	for(double i=a+h;i<b;i=i+h)
	{
		if (par==true)
		{
			Isc=Isc+fabs((h/3)*4*f(fx,i,x).r);
			par=false;
		}
		else
		{
			Isc=Isc+fabs((h/3)*2*f(fx,i,x).r);
			par=true;
		}	
	}

	return Isc;
}


double Calculadora::Integral_Duplo_Funcoes(CString func_xy, CString varx, CString vary, 
					double Ax, double Bx, 
					CString fAy ,CString fBy,double m)
{
	double hx;
	double hy;
	double ix,iy,i;
	double fay, fby;// fay, fby;
	bool par;
	double Isc=0;
	
	if ( Ax > Bx)//troca
	{ i=Ax;Ax=Bx;Bx=i; }
	hx=(Bx-Ax)/m;

//	::fxy(CString str,double x,CString u,double y,CString v, double z, CString s)

	for(ix=Ax;ix<=Bx;ix+=hx)
	{
		par=true;
		fay=f(fAy,ix,varx).r;
		fby=f(fBy,ix,varx).r;

		if (fay > fby) //troca 
		{ i=fay;fay=fby;fby=i; }
		hy=(fby-fay)/m;
		

		iy=fay;
		Isc+= hy/3*fxy(func_xy,fay,varx,iy,vary,1,"@").r 
			+ hy/3*fxy(func_xy,fby,varx,iy,vary,1,"@").r ;

		for(iy=fay+hy;iy<fby;iy+=hy)
		{
			if (par==true)
			{
				Isc+=hy*4/3*fxy(func_xy,ix,varx,iy,vary,1,"@").r;
				par=false;
			}
			else
			{
				Isc+=hy*2/3*fxy(func_xy,ix,varx,iy,vary,1,"@").r;
				par=true;
			}
		}

		Isc;

	}


	return Isc*hx;
}

double Calculadora::IntegralD(CString fx, CString x, CString y,double a, double b
							  , double ay, double by, double m)
{

	double h=(b-a)/m;
	double hy=(by-ay)/m;
	bool par=true;
	bool pary=true;
	double Isc=0;
	double Iy=0;

	for(double yy=ay;yy<=by;yy+=hy)
	{
		Isc+=h/3*fxy(fx,a,x,yy,y,0,"@").r + h/3*fxy(fx,b,x,yy,y,0,"@").r;
		for(double xx=a+h;xx<b;xx+=h)
		{
			if (par==true)
			{
				Isc=Isc+(h/3)*4*fxy(fx,xx,x,yy,y,0,"@").r;
				par=false;
			}
			else
			{
				Isc=Isc+(h/3)*2*fxy(fx,xx,x,yy,y,0,"@").r;
				par=true;
			}	
		}
	}


	return Isc*(by-ay)/m;
}


double Calculadora::IntegralDsc(CString fx, CString x, CString y,double a, double b
							  , double ay, double by, double m)
{

	double h=(b-a)/m;
	double hy=(by-ay)/m;
	bool par=true;
	bool pary=true;
	double Isc=0;
	double Iy=0;


	for(double yy=ay;yy<=by;yy+=hy)
	{
		Isc=0;
		Isc=h/3*fxy(fx,a,x,yy,y,0,"@").r + h/3*fxy(fx,b,x,yy,y,0,"@").r;
		for(double xx=a+h;xx<b;xx+=h)
		{
			if (par==true)
			{
				Isc=Isc+(h/3)*4*fxy(fx,xx,x,yy,y,0,"@").r;
				par=false;
			}
			else
			{
				Isc=Isc+(h/3)*2*fxy(fx,xx,x,yy,y,0,"@").r;
				par=true;
			}	

		}

		if (yy==ay || yy==by)
			Iy+=Isc*h/3;
		else
		{
			if (pary==true)
			{
				Iy+=Isc*h*4/3;
				pary=false;
			}
			else
			{
				Iy+=Isc*h*2/3;
				pary=true;
			}
		}
	}

	return Iy;
}

double Calculadora::zeros_find(CString fx,CString x, double min,double max,
							   double incremento, double precisao)
{
	double i;
	double l;
	double fa,fb;
	
//	zeros.RemoveAll();


	for(i=min ; i<max ; i+=incremento)
	{

	//	if (fabs(i)< precisao)
	//		i=0;
		fa=f(fx,i,x).r;
	
		l=i+incremento;
	//	if (fabs(l)< precisao)
	//	l=0;
		
		fb=f(fx,l,x).r;
		
		
		if( fa*fb  <= 0)
			zero(fx,x,i,l,precisao);	

	

	}

	return 1;
}

double Calculadora::zero(CString fx, CString x, double a, double b, double precisao)
{
	double fa,fb,fa2,fb2, dist_fa1_fb1, dist_fa2_fb2;
	double fd,d;
	double a2, b2, dist2;
	int n;
	
	d=(a+b)/2;

	fa=f(fx,a,x).r;
	fb=f(fx,b,x).r;
	fd=f(fx,d,x).r;



	if ( fabs(b-a) <=precisao)
	{	

		///testa se o zero é verdadeiro ou se é uma descontinuidade (polo)
		//------
		dist2= sqrt(a*a+b*b)/2 * 1.1;

		a2= d-dist2;
		b2= d+dist2;

		fa2=f(fx,a2,x).r;
		fb2=f(fx,b2,x).r;

		dist_fa1_fb1 = sqrt(pow(b - a,2) + pow(fb - fa,2));
		dist_fa2_fb2 = sqrt(pow(b2 - a2,2) + pow(fb2 - fa2,2));

		if( dist_fa1_fb1 > dist_fa2_fb2 )
			return 1;
		//------------


		//elimina zeros duplicados
		//-------------
		n=zeros.GetSize();
		if (n)
			if( fabs( fabs(zeros[n-1]) - fabs(d) ) < precisao)
			{
				double a1,a2;

				a1=zeros[n-1];
				a2=fabs(zeros[n-1] - fabs(d));
				//zeros.Add(d);
				return 1;
			}
		//-------------

		zeros.Add(d);
		return 1;
	} 

	
	if (fa*fd<=0)
		return zero(fx,x,a,d,precisao);
	else
		return zero(fx,x,d,b,precisao);
}


int Calculadora::equacao_resolve_procura(CString f1, CString f2,
					CString x, double min, double max,
					double incremento, double precisao)
{
	double i;
	double l;
	double fa,fb,fa1,fb1;
	double da,db,dab,dab1;//delta
		

	int contador = 0;
	CString str;
	i=min;
	double incremento_inicial=incremento;
	double incremento_maximo=incremento;
	double incremento_minimo=incremento;
	CString aux;
	

	fa=f(f1,i,x).r;
	fb=f(f2,i,x).r;

	solucoes_equacao.RemoveAll();

	for(i=min ; i<max ; i+=incremento)
	{

		l=i+incremento;

		fa1=f(f1,l,x).r;
		fb1=f(f2,l,x).r;

		/////incremento dinamico/////////////////////////
	//	contador++;

		da=fabs(fa1-fa);
		db=fabs(fb1-fb);
		
		dab=fabs(fa-fb);
		dab1=fabs(fa1-fb1);


		if (da < db)
			da=db;

		if (dab < dab1)
			dab=dab1;

		
		if (da < 0.2*dab)
			incremento=incremento+incremento*0.05;//5%
		else
		{
			if (incremento > 0.1*incremento_inicial) //10%
			incremento=incremento-incremento*0.1;//10%
		}


		if (incremento > incremento_maximo)
			incremento_maximo=incremento;

		if (incremento < incremento_minimo)
			incremento_minimo=incremento;


		////////////////////////////////////////////////

		if (fb >= fa)
		{
			if (fb1 <= fa1)
				equacao_resolve(f1,f2,x,i,l,precisao);
		}
		else
		{
			if (fa1 < fb1)
				equacao_resolve(f1,f2,x,i,l,precisao);
		}

		fa=fa1;
		fb=fb1;

	}

//	str.Format("maximo=%lf\nminimo=%lf\ncontador=%d",incremento_maximo,incremento_minimo,contador);
//	AfxMessageBox(str);
	return 1;
}


double Calculadora::equacao_resolve(CString f1, CString f2, CString x, 
									double a, double b, double precisao)
{
	double fa,fb;
	double fa1,fb1;
	double fda,fdb;
	double d;
		
	fa=f(f1,a,x).r;
	fb=f(f2,a,x).r;
	fa1=f(f1,b,x).r;
	fb1=f(f2,b,x).r;

	d=(a+b)/2;
	fda=f(f1,d,x).r;
	fdb=f(f2,d,x).r;

	if (fda == fdb)
	{
		solucoes_equacao.Add(d);
		return 1;	
	}

	if (fabs(fda-fdb) <= precisao)
	{
		solucoes_equacao.Add(d);
		return 1;
	}


	if (fa > fb)
	{
		if (fda > fdb)
			return equacao_resolve(f1,f2,x,d,b,precisao);
		else
			return equacao_resolve(f1,f2,x,a,d,precisao);
	
	}
	else
	{
		if (fdb > fda)
			return equacao_resolve(f1,f2,x,d,b,precisao);
		else
			return equacao_resolve(f1,f2,x,a,d,precisao);
	}


}



int Calculadora::equacao_resolve_procura_Complexo(CString f1, CString f2,
					CString x, double min, double max,
					double incremento, double precisao)
{
	double i;
	double l;
	double fa,fb,fa1,fb1;
	double da,db,dab,dab1;//delta
		

	int contador = 0;
	CString str;
	i=min;
	double incremento_inicial=incremento;
	double incremento_maximo=incremento;
	double incremento_minimo=incremento;
	CString aux;
	

	fa=f(f1,i,x).r;
	fb=f(f2,i,x).r;

	solucoes_equacao.RemoveAll();

	for(i=min ; i<max ; i+=incremento)
	{

		l=i+incremento;

		fa1=f(f1,l,x).r;
		fb1=f(f2,l,x).r;

		/////incremento dinamico/////////////////////////
	//	contador++;
		da=fabs(fa1-fa);
		db=fabs(fb1-fb);
		
		dab=fabs(fa-fb);
		dab1=fabs(fa1-fb1);

		if (da < db)
			da=db;

		if (dab < dab1)
			dab=dab1;
		
		if (da < 0.2*dab)
			incremento=incremento+incremento*0.05;//5%
		else
		{
			if (incremento > 0.1*incremento_inicial) //10%
			incremento=incremento-incremento*0.1;//10%
		}

		if (incremento > incremento_maximo)
			incremento_maximo=incremento;

		if (incremento < incremento_minimo)
			incremento_minimo=incremento;
		////////////////////////////////////////////////

		if (fb >= fa)
		{
			if (fb1 <= fa1)
				equacao_resolve(f1,f2,x,i,l,precisao);
		}
		else
		{
			if (fa1 < fb1)
				equacao_resolve(f1,f2,x,i,l,precisao);
		}

		fa=fa1;
		fb=fb1;

	}

//	str.Format("maximo=%lf\nminimo=%lf\ncontador=%d",incremento_maximo,incremento_minimo,contador);
//	AfxMessageBox(str);
	return 1;
}




/*
int Calculadora::funcoes_contantes(CString funcao)
{

	int devolve=0;
	
	if (funcao == "sen")
		devolve=1;

	if (funcao == "cos")
		devolve=1;



	return devolve;
}*/

/*
	sen ; 	s		PI = 3.14..;  		^ = 'elevado a ...'
	cos ; 	c		e = 2.71...;    	E = 'vezes 10 elevado a...'
	tg  ; 	t     log ;   L         ( )= chavetas
	cotg; 	g	  ln ;    l         | |= m¢dulo
	sqrt;	r     exp;    e         j = imagin rio
	cosh; 	o     senh;   i         i = imagin rio (igual a j)
	tgh;  	T     cotgh;  h
	arcsen; S     arccos; C
	arctg   a     acotg;  A
	step;   p     sinc;   n
	sgf ;   f     dirac;  d
	rect;   R     square; Q(trem de rectangulos)
				  trem;   M(trem de impulsos)
*/

int Calculadora::find_var_formula(CString f1, CString f2)
{

	CString aux_var;
	int i;
	int j;
	int l;
	
	Formula.Format("%s=%s",f1,f2);

	
	var_substitui_aux.RemoveAll();
	var_substitui_aux_posicao.RemoveAll();

	for(i=0;i<Formula.GetLength();i++)
	{
		l=0;
		aux_var.Empty();
		if (isalpha(Formula[i]))
		{
			while(i<Formula.GetLength() && isalnum(Formula[i]))
			{
				aux_var.Insert(l,Formula[i]);
				l++;
				i++;
			}
		}

		if (aux_var.GetLength() && valida_variaveis(aux_var))
		{
			var_formula.Add(aux_var);
			var_substitui_aux.Add(aux_var);
			j=aux_var.GetLength();
			var_substitui_aux_posicao.Add(i-j+1);
		}
	}


	for(i=0;i<var_formula.GetSize();i++)
	{
		for(j=var_formula.GetSize()-1;j>i;j--)
		{
			if (var_formula[i]==var_formula[j])
				var_formula.RemoveAt(j,1);

		}
	}


	return 1;
}

int Calculadora::valida_variaveis(CString variavel)
{

	variavel.MakeUpper();

	if (variavel=="")return 0;

	if (variavel =="SIN")return 0;
	if (variavel =="COS")return 0;
	if (variavel =="TAN")return 0;
	if (variavel =="COTG")return 0;

	if (variavel =="SINH")return 0;
	if (variavel =="COSH")return 0;
	if (variavel =="TANH")return 0;
	if (variavel =="COTGH")return 0;

	if (variavel =="ASIN")return 0;
	if (variavel =="ACOS")return 0;
	if (variavel =="ATAN")return 0;
	if (variavel =="ACOTG")return 0;

	if (variavel =="ASINH")return 0;
	if (variavel =="ACOSH")return 0;
	if (variavel =="ATANH")return 0;
	if (variavel =="ACOTGH")return 0;


	if (variavel =="SQRT")return 0;
	if (variavel =="LOG")return 0;
	if (variavel =="LN")return 0;
	if (variavel =="EXP")return 0;

	
	if (variavel =="SINC")return 0;
	if (variavel =="STEP")return 0;
	if (variavel =="SGF")return 0;
	if (variavel =="DIRAC")return 0;
	if (variavel =="RECT")return 0;
	if (variavel =="SQUARE")return 0;
	if (variavel =="TREM")return 0;
	
	if (variavel =="PI")return 0;
	if (variavel =="E")return 0;
		
	if (variavel =="I")return 0;
	if (variavel =="J")return 0;

	//se é realmente uma variável devolve 1
	return 1;
}
/*	sin ; 	s		PI = 3.14..;  		^ = 'elevado a ...'
	cos ; 	c		e = 2.71...;    	E = 'vezes 10 elevado a...'
	tan  ; 	t     log ;   L         ( )= chavetas
	cotg; 	g	  ln ;    l         | |= m¢dulo
	sqrt;	r     exp;    e         j = imagin rio
	cosh; 	o     sinh;   i         i = imagin rio (igual a j)
	tgh;  	T     cotgh;  h
	asin;   S     acos; C
	atan    a     acotg;  A
	step;   p     sinc;   n
	sgf ;   f     dirac;  d
	rect;   R     square; Q(trem de rectangulos)
				  trem;   M(trem de impulsos)
*/



void Calculadora::GetVariaveis(CString f)
{

	CString aux_var;
	int i;
	int j;
	int l;
	
	//Formula.Format("%s=%s",f1,f2);

	
//	var_substitui_aux.RemoveAll();
//	var_substitui_aux_posicao.RemoveAll();
	variaveis_formula.RemoveAll();


	for(i=0;i<f.GetLength();i++)
	{
		l=0;
		aux_var.Empty();

		if (isalpha(f[i]))
		{
			while(i<f.GetLength() && isalnum(f[i]))
			{
				aux_var.Insert(l,f[i]);
				l++;
				i++;
			}
		}

		if (aux_var.GetLength() && valida_variaveis(aux_var))
		{
			variaveis_formula.Add(aux_var);
			//var_substitui_aux.Add(aux_var);
			//j=aux_var.GetLength();
			//var_substitui_aux_posicao.Add(i-j+1);
		}
	}


	for(i=0;i<variaveis_formula.GetSize();i++)
	{
		for(j=variaveis_formula.GetSize()-1;j>i;j--)
		{
			if (variaveis_formula[i]==variaveis_formula[j])
				variaveis_formula.RemoveAt(j,1);

		}
	}



}


int Calculadora::GraficoTemporal(CString f )
{
	int i;
	//int numero_variaveis;

	GetVariaveis(f);
	//numero_variaveis=variaveis_formula.GetSize();

	for(i=0;i<variaveis_formula.GetSize();i++)
	{
		if (variaveis_formula[i]=="t")
			return 1;
	}


	return 0;
}


double Calculadora::Solve_n_Variaveis(CString f, double min,double max, 
									  double incremento, double precisao)
{

	CString substitui_var;
	CString str_aux;
	CString f1;
	CString f2;
	CArray<int,int> posicao_var;
	CArray<CString,CString> var_substituir;
	int i;
	int j;
	int k;
	

	for(i=0;i<f.GetLength();i++)
	{ 
		if (isalpha(f.GetAt(i)))
		{
			k=i;
			str_aux.Empty();
			while((i<f.GetLength()) && isalnum(f.GetAt(i)))
			{
				str_aux=str_aux+f.GetAt(i);
				i++;
			}


			if (str_aux.GetLength() && valida_variaveis(str_aux))
			{
				//posicao.InserAt(0,k);
				posicao_var.Add(k);
				var_substituir.Add(str_aux);
			}
		}
	}


	for(i=posicao_var.GetSize()-1;i>=0;i--)
	{
		for(j=0;j<variaveis_formula.GetSize();j++)
		{
			if (var_substituir[i] == variaveis_formula[j])
			{
				f.Insert(posicao_var[i],variaveis_valor[j]);
				f.Delete(posicao_var[i]+variaveis_valor[j].GetLength(),
					var_substituir[i].GetLength());

			}
		}
	}

//	AfxMessageBox(f);


	i=f.GetLength();
	j=f.Find("=");

	f1.Format("%s",f);
	f2.Format("%s",f);

	f1.Delete(j,i-j);
	f2.Delete(0,j+1);



//	AfxMessageBox(f1);
//	AfxMessageBox(f2);

	equacao_resolve_procura(f1, f2, "?", min ,max, incremento, precisao);


//	f.Format("%d",solucoes_equacao.GetSize());
//		AfxMessageBox(f);


/*	for(i=0;i<solucoes_equacao.GetSize();i++)
	{
		f.Format("%lf",solucoes_equacao[i]);
//		AfxMessageBox(f);	
	}
*/
	return solucoes_equacao.GetSize();
}



//-----Interpolacao

//float newton(float x,float tab[][100],int grau)
double Calculadora::Interpolacao_Newton(double x)
{
    int n;
    double px=0;
	int grau=Interpolacao_x.GetSize();

    for(n=0;n<=grau;n++)
		px=px+Interpolacao_divid(0,n)*Interpolacao_mult(x,n);
    //px=px+divid(0,n,tab)*mult(x,n,tab);

    return  px;
}


//float divid(int a,int b,float tab[][100])
double Calculadora::Interpolacao_divid(int a, int b)
{
    if ((b-a)<=0)
       return 1;
    if ((b-a)==1)
		return (	(Interpolacao_fx[b]-Interpolacao_fx[a]) / (Interpolacao_x[b]-Interpolacao_x[a])	);
       //return ( (tab[1][b]-tab[1][a]) / (tab[0][b]-tab[0][a]) );
    else
		return ( 
		(Interpolacao_divid(a+1,b)-Interpolacao_divid(a,b-1)) 
		/ 
		(Interpolacao_x[b]-Interpolacao_x[a]) 
		);

       //return ( (divid(a+1,b,tab)-divid(a,b-1,tab)) / (tab[0][b]-tab[0][a]) );
}

//float mult(float x,int n,float tab[][100])
double Calculadora::Interpolacao_mult(double x, int n)
{
    int l;
    double y=1;
    if (n==0)
       return 0;

    for(l=0;l<n;l++)
		y=y*(x-Interpolacao_x[l]);
    //y=y*(x-tab[0][l]);

    return y;
}