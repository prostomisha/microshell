#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
void Help();
int wlasnepolecenia(char** args) 
{ 
	char *login;
	char pwd[1024];
	FILE *file1;
	FILE *file2;
	int c;
    if (strcmp(args[0], "help")==0){
	
    	Help();
		return 1;
	}
    else if (strcmp(args[0], "cd")==0){
    	chdir(args[1]);
    	return 1;
	}
	else if (strcmp(args[0], "exit")==0){
		exit(0);
		
	}
	else if (strcmp(args[0], "whoami")==0){
		login = getenv("USER");
		printf("\nYour login is ");
		
		printf("%s\n", login);
		
		return 1;
	}
	else if (strcmp(args[0], "pwd")==0){
		getcwd(pwd, sizeof(pwd));
        printf("Your current directory is " );
        
        printf("%s\n", pwd);
        
		return 1;
	}
	else if (strcmp(args[0], "cp")==0){
		if ((file1=fopen(args[2], "w")) && (file2=fopen(args[1], "r"))){
			while ((c=getc(file2))!= EOF)
				putc(c,file1);
			fclose(file1);
			fclose(file2);
		}
		return 1;
	}
    else if (strcmp(args[0], "rm")==0){
    	file1=fopen(args[1], "w");
    	c=remove(args[1]);
    	if(c != 0){
    		
    		printf("Nastapil blad w usuwaniu.\n");
		}
    	return 1;
	}
	else if (strcmp(args[0], "touch")==0){
		c=creat(args[1], 0640);
		return 1;
	}
	else if (strcmp(args[0], "changecolor")==0){
		char *color;
		printf("Which color do you want?\n");
		printf("Wpisz jako polecenie:\nred\nblue\nyellow\ngreen\nmagenta\ncyan\nreset\n");
		color=readline("> ");
		if (strcmp(color, "red")==0){
			printf("\033[0;31m");
		}
		else if (strcmp(color, "yellow")==0){
			printf("\033[0;33m");
		}
		else if (strcmp(color, "blue")==0){
			printf("\033[0;34m");
		}
		else if (strcmp(color, "green")==0){
			printf("\033[0;32m");
		}
		else if (strcmp(color, "magenta")==0){
			printf("\033[0;35m");
		}
		else if (strcmp(color, "cyan")==0){
			printf("\033[0;36m");
		}
		else if (strcmp(color, "reset")==0){
			printf("\033[0m");
		}
		else{
			printf("Nie ma takiego coloru\n");
		}
		return 1;
	}
	
    return 0; 
} 
  



int wykonanie(char* linia, char** args) 
{ 
  	int i;
    for(i=0; i < 100; i++){
            args[i]=strsep(&linia, " ");
            if (args[i]==NULL)
                    break;
            if (strlen(args[i])==0)
                    i--;
    }
    if (wlasnepolecenia(args)) 
        return 0; 
    else
    	return 1;

} 
void Help(){
        printf("\nThis Microshell was created by Mikhail Ronchyk (s449058)\n");
        printf("Funkcjonalnosci:\n");
        printf(" exit\n help\n cd\n cp\n pwd\n whoami\n rm\n touch\n changecolor\n");
        printf("Takze program: \n Obsluguje historie polecen\n");
        printf(" Wyswietla sciezke biezacego katalogu\n");
        printf(" Wypisuje komunikat bledu gdy niemozliwe jest poprawne zinterpetowanie polecenia\n");
}


int main(int argc, char **argv){
        char s='#';
        printf("\033[0;33m");
        printf("\n#################################################\n");
        printf("%c\t\t\t\t\t\t%c\n%c\t\t\t\t\t\t%c\n%c  \t  ",s,s,s,s,s);
        printf("\033[0;32m");
        printf(" Michal Ronchyk Production ");
        printf("\033[0;33m");
        printf("\t\t%c\n%c\t\t\t\t\t\t%c\n%c\t\t\t\t\t\t%c\n%c  \t\t  ",s,s,s,s,s,s);
        printf("\033[1;34m");
        printf("MICRONSHELL");
        printf("\033[0;33m");
        printf("\t\t\t%c\n",s);
        printf("%c\t\t\t\t\t\t%c\n%c\t\t\t\t\t\t%c\n",s, s,s,s);
        printf("#################################################\n");
        printf("\033[0m");

        char *args[100];
        
        char cwd[1024];
        int status = 0;
        char linia[1000];
        while(1){
        		
                getcwd(cwd, sizeof(cwd));
                printf("[%s] $ ", cwd);
                
				char *buffer;
				buffer = readline(""); 
   				if (strlen(buffer) != 0) { 
        			add_history(buffer); 
        			strcpy(linia, buffer);  
    			} else
				{ 
        			continue; 
    			} 
                status = wykonanie(linia, args);
                if (status == 1){
				
                    pid_t pid = fork();  
  
    				if (pid == -1) { 
       					printf("\nNastapil blad w fork..\n"); 
        						 
   					} 
					else if (pid == 0) { 
   						if (execvp(args[0], args) < 0) { 
            					printf("\nNie ma takiego polecenia lub polecenie nie moze byc wykonane\n"); 
        				} 
        				exit(0); 
    				}
					else 
					{         
    				    wait(NULL);  
       
    				} 

   				}
		}
	return 0;
}
