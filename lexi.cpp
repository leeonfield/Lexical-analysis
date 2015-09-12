#include<stdio.h>
#include<ctype.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
int TESTparse();
int program();

int statement();
int statement_list();

int expression();
int expression_stat();

int declaration_stat();
int declaration_list();

int if_stat();
int for_stat();
int read_stat();
int write_stat();
int while_stat();
int compound_stat();

int term();
int factor();
int bool_expr();
int additive_expr();

char token[20], token1[40];//token���浥�ʷ��ţ�token1���浥��ֵ
extern char Scanout[300];//����ʷ���������ļ���
FILE *fp;//����ָ�������ļ���ָ��

int TESTparse()
{
	int es = 0;
	if ((fp = fopen(Scanout, "r")) == NULL)
	{
		printf("\n Open %s error !\n", Scanout);
		es = 10;
	}
	if (es == 0)
	{
		es = program();
	}
	printf("=========Result!=========\n");
	switch (es)
	{
		case 0:printf("Grammar analysis succeed!\n"); break;
		case 10:printf("Open %s error!\n", Scanout); break;
		case 1:printf("Lack {    \n"); break;
		case 2:printf("Lack }    \n"); break;
		case 3:printf("Lack !    \n"); break;
		case 4:printf("Lack ;   \n"); break;
		case 5:printf("Lack (    \n"); break;
			case 6:printf("Lack )    \n"); break;
	case 7:printf("Lack operand \n"); break;//ȱ�ٲ�����
}
fclose(fp);
return (es);
}


//<����>::={<��������><�������>}
//program::=={<declaration_list><statement_list>}
int program()
{
	int es = 0;
	fscanf(fp, "%s%s\n", &token, &token1);
	printf("%s	%s\n", token, token1);
	if (strcmp(token, "{"))
	{
		es = 1;
		return (es);
	}
	fscanf(fp, "%s%s\n", &token, &token1);
	printf("%s	%s\n", token, token1);
	es = declaration_list();
	if (es > 0)
	{
		return (es);
	}
	es = statement_list();
	if (es > 0)
	{
		return (es);
	}
	if (strcmp(token, "}"))
	{
		es = 2;
		return (es);
	}
	return (es);
}


//<��������>::=<��������><�������>|<�������>
//<declaration_list>:: = <declaration_list><declaration_stat> | �ĳ�<declaration_list>:: = {<declaration_stat> }

int declaration_list()
{
	int es = 0;
	while (strcmp(token, "int") == 0)
	{
		es = declaration_stat();
		if (es > 0)
		{
			return (es);
		}
	}
	return (es);
}


//<�������>::=int<����>
//<declaration_stat>:: = int ID;
int  declaration_stat()
{
	int es = 0;

	fscanf(fp, "%s%s\n", &token, &token1);
	printf("%s	%s\n", token, token1);
	if (strcmp(token, "ID"))
	{
		return (es = 3);//���Ǳ�ʶ��
	}
	fscanf(fp, "%s%s\n", &token, &token1);
	printf("%s	%s\n", token, token1);
	if (strcmp(token, ";"))
	{
		return (es = 4);//���Ǳ�ʶ��
	}
	fscanf(fp, "%s%s\n", &token, &token1);
	printf("%s	%s\n", token, token1);
	return (es);
}

//<�������>::=<�������><���>|
//<statement_list>::=<statement_list><statement>|       �ĳ�     <statement_list>::={<statement>}
int statement_list()
{
	int es = 0;
	while (strcmp(token, "}"))
	{
		es = statement();
		if (es > 0)
		{
			return (es);
		}
	}
	return (es);
}


//<���>::=<if���>|<while���>|<for���>|<read���>|<write���>|<�������>|<���ʽ���>

//<statement>::=<if_stat>|<while_stat>|<for_stat>|<compound_stat>|<expression_stat>
int statement()
{
	int es = 0;
	if (es == 0 && strcmp(token, "if") == 0)
	{
		es = if_stat();
	}

	if (es == 0 && strcmp(token, "while") == 0)
	{
		es = while_stat();
	}

	if (es == 0 && strcmp(token, "for") == 0)
	{
		es = for_stat();
	}

	if (es == 0 && strcmp(token, "read") == 0)
	{
		es = read_stat();
	}

	if (es == 0 && strcmp(token, "write") == 0)
	{
		es = write_stat();
	}

	if (es == 0 && strcmp(token, "{") == 0)
	{
		es = compound_stat();						//�������
	}

	if (es == 0 && strcmp(token, "ID") == 0 || strcmp(token, "NUM") == 0 || strcmp(token, "(") == 0)
	{
		es = expression_stat();
	}
	return (es);
}



//<if���>::=if(<���ʽ>)<���>[else<���>]
//<if_stat>:: = if (<expression>)<statement>[else<statement>]

int if_stat()
{
	int es = 0;
	fscanf(fp, "%s%s\n", &token, &token1);
	printf("%s	%s\n", token, token1);

	if (strcmp(token, "("))
	{
		return (es = 5);
	}
	fscanf(fp, "%s%s\n", &token, &token1);
	printf("%s	%s\n", token, token1);
	es = expression();
	if (es > 0)
	{
		return (es);
	}
	if (strcmp(token, ")"))
	{
		return (es = 6);
	}
	fscanf(fp, "%s%s\n", &token, &token1);
	printf("%s	%s\n", token, token1);
	es = statement();
	if (es > 0)
	{
		return (es);
	}
	if (strcmp(token, "else") == 0)
	{
		fscanf(fp, "%s%s\n", &token, &token1);
		printf("%s	%s\n", token, token1);
		es = statement();
		if (es > 0)
		{
			return (es);
		}
	}
	return (es);
}

//<while���>::=while(<���>)<���>
//<while_stat>:: = while (<expr>)<statement>
int while_stat()
{
	int es = 0;
	fscanf(fp, "%s%s\n", &token, &token1);
	printf("%s	%s\n", token, token1);
	if (strcmp(token, "("))
	{
		return (es = 5);
	}
	fscanf(fp, "%s%s\n", &token, &token1);
	printf("%s	%s\n", token, token1);

	es = expression();
	if (es > 0)
	{
		return (es);
	}
	if (strcmp(token, ")"))
	{
		return (es = 6);
	}
	fscanf(fp, "%s%s\n", &token, &token1);
	printf("%s	%s\n", token, token1);

	es = statement();
	return (es);
}

//<for���>::=for(<���ʽ>;<���ʽ>;<���ʽ>)<���>
//<for_stat>:: = (<expression>; <expression>;<expression>)<statement>
int for_stat()
{
	int es = 0;

	fscanf(fp, "%s%s\n", &token, &token1);
	printf("%s	%s\n", token, token1);

	if (strcmp(token, "("))
	{
		return (es = 5);
	}

	fscanf(fp, "%s%s\n", &token, &token1);
	printf("%s	%s\n", token, token1);
	es = expression();
	if (es > 0)
	{
		return (es);
	}
	if (strcmp(token, ";"))
	{
		return (es = 4);
	}
	fscanf(fp, "%s%s\n", &token, &token1);
	printf("%s	%s\n", token, token1);
	es = expression();


	if (es > 0)
	{
		return (es);
	}
	if (strcmp(token, ";"))
	{
		return (es = 4);
	}
	fscanf(fp, "%s%s\n", &token, &token1);
	printf("%s	%s\n", token, token1);
	es = expression();

	if (es > 0)
	{
		return (es);
	}
	if (strcmp(token, ")"))
	{
		return (es = 6);
	}
	fscanf(fp, "%s%s\n", &token, &token1);
	printf("%s	%s\n", token, token1);
	es = statement();
	return (es);
}


//<write_���>::=write<���ʽ>
//<write_stat>::=write<expression>
int write_stat()
{
	int es = 0;

	fscanf(fp, "%s%s\n", &token, &token1);
	printf("%s	%s\n", token, token1);

	es = expression();

	if (es > 0)
	{
		return (es);
	}
	if (strcmp(token, ";"))
	{
		return (es = 4);
	}
	fscanf(fp, "%s%s\n", &token, &token1);
	printf("%s	%s\n", token, token1);
	return (es);
}

//<read_���>::=read<����>;
//<read_stat>:: = read ID;
int read_stat()
{
	int es = 0;

	fscanf(fp, "%s%s\n", &token, &token1);
	printf("%s	%s\n", token, token1);

	if (strcmp(token, "ID"))
	{
		return (es = 3);
	}
	fscanf(fp, "%s%s\n", &token, &token1);
	printf("%s	%s\n", token, token1);

	if (strcmp(token, ";"))
	{
		return (es = 4);
	}
	fscanf(fp, "%s%s\n", &token, &token1);
	printf("%s	%s\n", token, token1);
	return (es);
}


//<�������>::={<�������>}
//<compound_Stat>:: = {<statement_list>}
int compound_stat()
{
	int es = 0;

	fscanf(fp, "%s%s\n", &token, &token1);
	printf("%s	%s\n", token, token1);

	es = statement_list();
	return (es);
}

//<���ʽ���>::=<<���ʽ>>��|��
//<expression_stat>:: = <expression>; | ;
int expression_stat()
{
	int es = 0;

	if (strcmp(token, ";")==0)
	{
		fscanf(fp, "%s%s\n", &token, &token1);
		printf("%s	%s\n", token, token1);
		return (es);
	}
	es = expression();
	if (es > 0)
	{
		return (es);
	}
	if (es == 0 && strcmp(token, ";") == 0)
	{
		fscanf(fp, "%s%s\n", &token, &token1);
		printf("%s	%s\n", token, token1);
		return (es);
	}
	else
	{
		es = 4;
		return (es);
	}
}
//<���ʽ>::=<��ʶ��>=<�������ʽ>|<�������ʽ>
//<expression>::=ID=<bool_expr>|<bool_expr>
int expression()
{
	int es = 0, fileadd;
	char token2[20], token3[40];
	if (strcmp(token, "ID") == 0)
	{
		fileadd = ftell(fp);//��ס��ǰ�ļ�λ��
		fscanf(fp, "%s%s\n", &token2, &token3);
		printf("%s	%s\n", token2, token3);
		if (strcmp(token2, "=") == 0)
		{
			fscanf(fp, "%s%s\n", &token, &token1);
			printf("%s	%s\n", token, token1);
			es = bool_expr();
			if (es > 0)
			{
				return (es);
			}
		}
		else
		{
			fseek(fp, fileadd, 0);//���ǡ�=�������ļ�ָ��ص�'='ǰ�ı�ʶ��
			printf("%s	%s\n", token, token1);
			es = bool_expr();
			if (es > 0)
			{
				return (es);
			}
		}
	}
	else
	{
		es = bool_expr();
	}
	return (es);
}


//<�������ʽ>::=<�������ʽ>|<�������ʽ>(>|<|>=|<=|==|!=)<�������ʽ>    
//<bool_expr>:: = <additive_expr> | <additive_expr>(> | < | >= | <= |= = | != )<additive_expr>
int bool_expr()
{
	int es = 0;
	es = additive_expr();
	if (es > 0)
	{
		return (es);
	}
	if (strcmp(token, ">") == 0 || strcmp(token, ">=") == 0 || strcmp(token, "<") == 0 || strcmp(token, "<=") == 0 || strcmp(token, "==") == 0 || strcmp(token, "!=") == 0)
	{
		fscanf(fp, "%s%s\n", &token, &token1);
		printf("%s	%s\n", token, token1);
		es = additive_expr();
		if (es > 0)
		{
			return (es);
		}
	}
	return (es);
}


//<�������ʽ>::=<��>{(+|-)<term>}
//<additive_expr>:: = <term>{(+|-)<term>}
int additive_expr()
{
	int es = 0;
	es = term();
	if (es > 0)
	{
		return (es);
	}
	while (strcmp(token, "+") == 0 || strcmp(token, "-") == 0)
	{
		fscanf(fp, "%s%s\n", &token, &token1);
		printf("%s	%s\n", token, token1);
		es = term();
		if (es > 0)
		{
			return (es);
		}
	}
	return (es);
}


//<��>::=<����>{(*|/)<����>}
//<term>:: = <factor>{(*|/)<factor>}
int term()
{
	int es = 0;
	es = factor();
	if (es > 0)
	{
		return (es);
	}
	while (strcmp(token, "*") == 0 || strcmp(token, "/") == 0)
	{
		fscanf(fp, "%s%s\n", &token, &token1);
		printf("%s	%s\n", token, token1);

		es = factor();
		if (es > 0)
		{
			return (es);
		}
	}
	return (es);
}


//<����>::=(<���ʽ>)|<��ʶ��>|<�޷�������>
//<factor>:: = (<expression>)|ID|NUM
int factor()
{
	int es = 0;
	if (strcmp(token, "(") == 0)
	{
		fscanf(fp, "%s%s\n", &token, &token1);
		printf("%s	%s\n", token, token1);
		es = expression();
		if (es > 0)
		{
			return (es);
		}
		if (strcmp(token, ")"))
		{
			return (es = 6);
		}
		fscanf(fp, "%s%s\n", &token, &token1);
		printf("%s	%s\n", token, token1);
	}
	else
	{
		if (strcmp(token, "ID") == 0 || strcmp(token, "NUM") == 0)
		{
			fscanf(fp, "%s%s\n", &token, &token1);
			printf("%s	%s\n", token, token1);
			return (es);
		}
		else
		{
			es = 7;
			return (es);
		}
	}
	return (es);
}