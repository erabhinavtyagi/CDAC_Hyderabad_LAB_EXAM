// INPUT: This is Hyderabadi
// OUTPUT: hTsi si yHedarabid

#include <stdio.h>
int main()
{
	char str[50]="India is a great country";
	int i,j;
	printf("%s\n",str);
	for(i=0;str[i]!='\0';i++)
	{
		if((str[i]==' ' && str[i+1]==' ') || (str[i] != ' ' && str[i+1] == ' ') || (str[i] != ' ' && str[i+1] =='\0') || str[i] ==' ')
			continue;
		char temp=str[i];
		str[i]=str[i+1];
		str[i+1]=temp;
		i++;
	}
	printf("%s\n",str);
return 0;
}

