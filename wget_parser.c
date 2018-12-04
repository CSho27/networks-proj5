//Christopher Shorter
//wget parser
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>

#define EMPTY_LINE "\r\n"
#define BUFLEN 4092

int main(){
	FILE* file = fopen("http.html", "r");
    if(file == NULL){
    	printf("ERROR: couldn't open file\n");
        return -1;
    }
    else{
	    FILE *data = fopen("data.csv", "ab");
	    if (data == NULL){
	        return false;
	    }

	    unsigned char buffer[BUFLEN];
	    bzero(buffer, BUFLEN);
	    int current = 1;
	    char resp[BUFLEN];
	    char header[BUFLEN];
	    char value[BUFLEN];


	    current = 0;
	    bool next = false;
	    bzero(resp, BUFLEN);
	    int not_empty = 0;
	   	while((not_empty = fread(buffer, 1, 1, file)) > 0 && buffer[0] != '\n'){
	    	resp[current] = buffer[0];
	    	current++;
	    	bzero(buffer, BUFLEN);
	    }
	    resp[current] = '\0';

	    if(not_empty>0){
			fwrite(resp, 1, strlen(resp), data);
		    next = false;    
		    bool done = false;
		    while(!done){
		        bzero(header, BUFLEN);
		        bzero(value, BUFLEN);
		        current = 0;
		        next = false;
		        while(!next){
		        	bzero(buffer, BUFLEN);
		        	fread(buffer, 1, 1, file);
		        	if(buffer[0] == ':'){
		        		next = true;
		        		header[current] = '\0';
		        	}
		        	else{   	
			        	header[current] = buffer[0];
			        	current++;
		        	}

		        	if(strstr(header, EMPTY_LINE) != NULL){
		        		done = true;
		        		next = true;
		        	}

		        }

		        next = false;
		        current = 0;
		        fread(buffer, 1, 1, file);
		       	while(!next){

		       		if(done){
		       			next = true;
		       		}
		       		else{
			        	bzero(buffer, BUFLEN);
			        	fread(buffer, 1, 1, file);
			        	if(buffer[0] == '\n'){
			        		next = true;
			        		value[current] = '\0';
			        	}
			        	else{   	
				        	value[current] = buffer[0];
				        	current++;
			        	}
			        }
		        }
		        if(!done){
		        	char line[BUFLEN];
		        	sprintf(line, "%s,%s\n", header, value);
		        	fwrite(line, 1, strlen(line), data);
		        }
		        
		    }
		    fclose(file);
		    fclose(data);
		}
		else{
			char* empty = "NOT-ACCESSED,NULL\n";
			fwrite(empty, 1, strlen(empty), data);
			fclose(file);
			fclose(data);
		}
	}
	return 0;
}

