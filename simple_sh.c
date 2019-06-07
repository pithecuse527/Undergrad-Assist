//간단한 셸 구현입니다.
//cd와 pwd명령이 있고, exit를 누르면 종료합니다.
//없는 명령어를 입력하면 그걸 그대로 출력합니다.

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<dirent.h>
#include<pwd.h>

#define MAX_STR_LEN 200

int main()
{
	char str[MAX_STR_LEN];						// 명령어 입력 받는곳			
	char *ptr = "\0";					        // 구분된 명령어들	
	char dirname[MAX_STR_LEN];					// 디렉토리 이름
	char temp[MAX_STR_LEN];						// 임시 저장
	char homeDir[MAX_STR_LEN] = "/home/";		// 홈디렉토리 주소를 이어가기 위한 것
	struct passwd *user;				        // 홈디렉토리로 가기 위한 유저 이름을 담고 있는 구조체.
	int i = 0;
	int length;

	while (1) {
		printf("prompt$ ");
		fgets(str, MAX_STR_LEN, stdin);

		strcpy(temp,str);
		
		// printf("temp : %s\n", temp)
		
		ptr = strtok(str," ");
		
		if ( !strcmp(str, "pwd\n") )    //pwd 명령 구현
		{
			getcwd(dirname, 50);
			printf("%s\n",dirname);
			continue;
		}
		
		if (!(strcmp(ptr, "cd")))       // cd 명령
		{
			getcwd(dirname, 50);
			
			length = strlen(temp);
			
			if(temp[3] != '/'){
				for(i=1;i< length - 1;i++){
					temp[i] = temp[i+2];
				}
				temp[0] = '/';
				temp[length-3] = '\0'; 

				strcat(dirname,temp);
			
				chdir(dirname);
			
				if(chdir(dirname)){printf("No such directory\n");}
			}else{
				for(i=0;i<length;i++){
					temp[i] = temp[i+3];
				}
				
				temp[length-4] = '\0';
				temp[length-5] = '\0';
				puts(temp);
				
				chdir(temp);
				
				if(chdir(dirname)){printf("No such directory\n");}
			}
			
			continue;
		}

		if (!(strcmp(str, "cd\n"))) {	// cd만 입력시 홈 디렉토리로 이동하는 것
			user = getpwuid(getuid());
			strcat(homeDir,user->pw_name);
			chdir(homeDir);
			continue;			
		}

		if (!(strcmp(str, "exit\n")))
			return 0;

		if (strlen(str) == 0)
			continue;
		else
			puts(str);
	}
}
