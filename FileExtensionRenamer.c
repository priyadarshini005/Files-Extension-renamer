#include<regex.h>
#include<stdio.h>
#include<dirent.h>
#include<stdlib.h>
#include<string.h>
void getNewName(char OldName[300], char OldExt[10], char NewExt[10], char NewName[300]);
int main()
{
	DIR *d;
	regex_t reg;
	char dir_name[150], newFileName[300], old_ext[10], new_ext[10], oldFileName[300], regexp[50], newFileName1[300];
	int ret;
	struct dirent *dir;
	printf("Enter the name of the directory\n");
	scanf("%s", dir_name);
	printf("Enter the Extension of the File to be replaced\n");
	scanf("%s", old_ext);
	printf("Enter the Extension of the File that has to be replaced by\n");
	scanf("%s", new_ext);
	snprintf(regexp, 50 * sizeof(char), "%s%s%s", "(.)*.", old_ext, "$");
	ret = regcomp(&reg, regexp, REG_ICASE|REG_EXTENDED);
	if(ret)
	{
		printf("Regular expression compilation error\n");
		exit(1);
	}
	d = opendir(dir_name);
	if(d == NULL)
	{
		printf("Error!\n");
		exit(1);
	}
	while((dir = readdir(d)) != NULL)
	{
		ret = regexec(&reg, dir->d_name, 0, NULL, 0);
		if(!ret)
		{
			getNewName(dir->d_name, old_ext, new_ext, newFileName1);
			snprintf(oldFileName, 300 * sizeof(char), "%s%s%s", dir_name, "/", dir->d_name);
			snprintf(newFileName, 300 * sizeof(char), "%s%s%s", dir_name, "/", newFileName1);
			rename(oldFileName, newFileName);
			printf("Renamed from %s to %s\n", oldFileName, newFileName);
		}
		else
			printf("%s no match to the regular expression %s\n\n", dir->d_name, regexp);
	}
	printf("Renaming of files extension successful\n");
}
void getNewName(char OldName[300], char OldExt[10], char NewExt[10], char *NewName)
{
	char *result;
	char OldNameTemp[300], OldExtTemp[10];
	int index, i;
	strcpy(OldNameTemp, OldName);
	strcpy(OldExtTemp, OldExt);
	strcat(OldNameTemp, "$");
	snprintf(OldExtTemp, 10 * sizeof(char), "%s%s%s", ".", OldExt, "$");
	result = strstr(OldNameTemp, OldExtTemp);
	index = result - OldNameTemp;
	for(i = 0; i <= index; i++)
		NewName[i] = OldNameTemp[i];
	NewName[i] = '\0';
	strcat(NewName, NewExt);
	NewName[strlen(NewName)] = '\0';
	printf("New name evaluated:%s\n", NewName);
}
