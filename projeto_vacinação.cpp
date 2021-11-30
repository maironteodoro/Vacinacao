#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
void menu(int *A); //menu
void cadastrar(FILE *); //cadastro OP:1
void consultar(FILE *arq); //consultar OP:2
void Svacina(FILE *); //  Status da 2ªdose OP:3
void gerar(FILE *); // Gerar o Arquivo OP:4

int tamanho(FILE *);

struct RG
{
	char nome[35];
	char dia[10];
	char mes[10];
	char ano[10];
	char idade[10];
	char vacina[15];
	char retorno[15];
	char status[15];
};
// principal
int main()
{
	setlocale(LC_ALL,"");
	int OP;
	FILE *arq;
	if ((arq = fopen("dados.dat", "rb+")) == NULL)
	{
		if ((arq = fopen("dados.dat", "wb+")) == NULL)
		{
			printf("\nFalha ao abrir o arquivo!\n");
			system("pause");
		}
	}
	do
	{
		menu(&OP);
		
		switch(OP)
		{
			case 1:
				{
					cadastrar(arq);
					break;
				}
			case 2:
				{
					consultar(arq);
					break;
				}
			case 3:
				{
					Svacina(arq);
					break;
				}
			case 4:
				{
					gerar(arq);
					break;
				}
		}
	}while(OP!=0);
	fclose(arq);
	return 0;
}
	//menu
void menu(int *A )
{
	FILE *arq;
	system("CLS");
	printf("==========================================\n");
	printf("1. Cadastrar:\n");
	printf("2. Consulta:\n");
	printf("3. Confirmar segunda dose:\n");
	printf("4. Gerar arquivo:\n");
	printf("0. Sair:\n");
	printf("==========================================\n");
	printf("Opção: ");scanf("%d%*c",&*A);
}
	//cadastro OP:1
void cadastrar(FILE *arq)
{ 	
	int Idia,Imes,Iano; //int dia,mes e ano
	RG  registro; 
	char confirma;
	int B;
	char X[5],Y[5],Z[5];
	fflush(stdin);
	system("CLS");
	printf("============Cadastro de vacinados:==========\n");
	printf("Número de cadastro da pessoa:%d\n",tamanho(arq)+1);
	printf("Nome............:");gets(registro.nome);
	printf("Idade...........:"); gets(registro.idade);
	printf("Dia da vanicação:"); gets(registro.dia);
	printf("Mês da vanicação:"); gets(registro.mes);
	printf("Ano da vanicação:"); gets(registro.ano);
	
	Idia=atoi(registro.dia); //transformando de string para int
	Imes=atoi(registro.mes); //transformando de string para int
	Iano=atoi(registro.ano); //transformando de string para int
	fflush(stdin);
	system("CLS");
	printf("================Vacina Usada==============\n");
	printf("1. CoronaVac:\n");
	printf("2. AstraZeneca:\n");
	printf("3. Pfizer:\n");
	printf("4. Janssen:\n");
	printf("==========================================\n");
	printf("Opção: ");scanf("%d%*c",&B);
	switch(B)
	{
		case 1:
			{
				setbuf(stdin, NULL);
				Idia=Idia+28;
				if (Idia>30)
				{
					Idia=Idia-30;
					Imes=Imes+1;
					if (Imes>12)
					{
						Imes=Imes-12;
						Iano=Iano+1;
					}
				}
					itoa(Idia,X,10);
					itoa(Imes,Y,10);
					itoa(Iano,Z,10);
					strcpy(registro.retorno,X);
					strcat(registro.retorno,".");
					strcat(registro.retorno,Y);
					strcat(registro.retorno,".");
					strcat(registro.retorno,Z);
					strcat(registro.vacina,"CoronaVac");
					strcpy(registro.status,"Pendente");
					break;
					
			}
		case 2:
			{
				setbuf(stdin, NULL);
				Imes=Imes+3;
				if(Imes>12)
				{
					Imes=Imes-12;
					Iano=Iano+1;
				}
					itoa(Idia,X,10);
					itoa(Imes,Y,10);
					itoa(Iano,Z,10);
					strcpy(registro.retorno,X);
					strcat(registro.retorno,".");
					strcat(registro.retorno,Y);
					strcat(registro.retorno,".");
					strcat(registro.retorno,Z);
					strcat(registro.vacina,"AstraZeneca");
					strcpy(registro.status,"Pendente");
					break;
			}
		case 3:
			{
				setbuf(stdin, NULL);
				Imes=Imes+2;
				if(Imes>12)
				{
					Imes=Imes-12;
					Iano=Iano+1;
				}
					itoa(Idia,X,10);
					itoa(Imes,Y,10);
					itoa(Iano,Z,10);
					strcpy(registro.retorno,X);
					strcat(registro.retorno,".");
					strcat(registro.retorno,Y);
					strcat(registro.retorno,".");
					strcat(registro.retorno,Z);
					strcat(registro.vacina,"Pfizer");
					strcpy(registro.status,"Pendente");
					break;
			}
		case 4:
			{
				setbuf(stdin, NULL);
				strcpy(registro.retorno,"Dose única");
				strcat(registro.vacina,"Janssen");
				strcpy(registro.status,"Vacinado");
				break;
			}
	}	
	printf("\nConfirma <s/n>:");
	scanf("%c", &confirma);
	if (toupper(confirma) == 'S')
	{
		printf("\n Salvo com Sucesso!\n");
		fseek(arq, 0, SEEK_END);
		fwrite(&registro, sizeof(RG), 1, arq);
	}
}
	//CONSULTA OP:2
void consultar(FILE *arq)
{	
	system("CLS");
	RG registro;
	int NC;
	printf("=====Pesquisar cadastro=====\n");
	printf("Digite o número de cadastro:");scanf("%d", &NC);
	if((NC <= tamanho(arq))&&(NC>0))
	{
		fseek(arq,(NC-1)*sizeof(RG),SEEK_SET);
		fread(&registro,sizeof(RG),1,arq);
		printf("Número de cadastro da pessoa:%d\n",NC);
		printf("Nome............:%s\n",registro.nome);
		printf("Idade...........:%s\n",registro.idade);
		printf("Vacina..........:%s\n",registro.vacina);
		printf("1ªdose:.........:%s.%s.%s\n",registro.dia,registro.mes,registro.ano);
		printf("Retorno:........:%s\n",registro.retorno);
		printf("Status 2ªdose...:%s\n",registro.status);
	}
	else
	{
		printf("\nNumero de registro invalido!\n");
	}
	system("pause");
}

	//Tomou a 2ª dose OP:3
void Svacina(FILE *arq)
{
	RG  registro; 
	char confirmar;
	int NC;
	int V;
	system("CLS");
	printf("\nNúmero do cadastro para confirmação da 2ª dose:\n");
	scanf("%d", &NC);
	if ((NC <= tamanho(arq)) && (NC>0))
	{
		fseek(arq, (NC-1) * sizeof(RG), SEEK_SET);
		fread(&registro, sizeof(RG), 1, arq);
		V=strcmp(registro.status,"Pendente");
		if (V==0)
		{
			printf("Número de cadastro da pessoa:%d\n",NC);
			printf("Nome............:%s\n",registro.nome);
			printf("Idade...........:%s\n",registro.idade);
			printf("Vacina..........:%s\n",registro.vacina);
			printf("1ªdose:.........:%s.%s.%s\n",registro.dia,registro.mes,registro.ano);
			printf("Retorno:........:%s\n",registro.retorno);
			printf("Status 2ªdose...:%s\n",registro.status);
			printf("\nConfirma a 2ª dose: <s/n>\n");
			getchar();
			scanf("%c", &confirmar);
			
			if (toupper(confirmar) == 'S')
			{
				printf("\nconfirmando 2ª dose...\n\n");
				fseek(arq, (NC - 1) * sizeof(RG), SEEK_SET);
				strcpy(registro.status,"Vacinado");
				fwrite(&registro, sizeof(RG), 1, arq);
			}
		}
		else
		{
			printf("Registro não encontrado! \n");
		}

	}
	else
	{
		printf("\nCadastro não encontrado!\n");
	}
	system("pause");
}

 // Gerar arquivo OP:4
 void gerar (FILE *arq)
{
	system("CLS");
	char nomearq[20];
	printf("=====Criando arquivo!=====\n");
	printf("Nome do arquivo texto: ");
	scanf("%s", nomearq);
	strcat(nomearq,".txt");
	
	FILE *arqtxt = fopen(nomearq,"w");
	
	if(!arqtxt)
	{
		printf("\nNão foi encontrado o arquivo!!");
		system("pause");
	}
	else
	{
		fprintf(arqtxt, "Nome           Idade           Vacina         1ªDose        Retorno    Status");
		fprintf(arqtxt, "\n=====================================================================================\n");
		int nr;
		RG registro;
		for(nr=0; nr <tamanho(arq);nr++)
		{
			fseek(arq,nr * sizeof(RG), SEEK_SET);
			fread(&registro, sizeof(RG), 1,arq);
			fprintf(arqtxt, "%s %10s %15s %15s.%s.%s %15s %10s\n",registro.nome,registro.idade,registro.vacina,registro.dia,registro.mes,registro.ano,registro.retorno,registro.status);
		}
		fprintf(arqtxt, "\n=====================================================================================");
		fclose(arqtxt);
		printf("Aquivo %s foi criado com sucesso!\n",nomearq);
		system("pause");
	}
}
//número de cadastro da pessoa
int tamanho(FILE *arq)
{
	fseek(arq, 0, SEEK_END);
	return ftell(arq) / sizeof(RG);
}

