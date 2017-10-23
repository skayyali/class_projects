
const char * usage = "ERROR: please use the following format: ./myhttpd [-f|-t|-p] [<port>]\n";


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>
#include <time.h>
#include <dirent.h>
#include <fcntl.h>
#include <pthread.h>


int QueueLength = 5;

// Processes time request
void processTimeRequest( int socket );
void processResponse( char*, char*, int, int );
void *processRequestThread(void*);
void * poolProcessRequest(void*);
void processCGIreq(char*, char*, int);

pthread_mutex_t mutex;


int
main( int argc, char ** argv )
{
	// Print usage if not enough arguments
	int port, proc, thread, pool;
	if ( argc == 3 ) {
		port = atoi( argv[2] );
		proc = 0;
		thread = 0;
		pool = 0;
		switch(argv[1][1])
		{
		case 'f':
			proc = 1;
		break;
		case 't':
			thread = 1;
		break;
		case 'p':
			pool = 1;
		break;
		default:
			fprintf( stderr, "%s", usage );
			exit( -1 );
		break;
		}
	}
	else if (argc == 2) {
		port = atoi( argv[1] );
		proc = 0;
		thread = 0;
		pool = 0;
	}
	else if (argc ==1) {
		port = 8999;
		proc = 0;
		thread = 0;
		pool = 0;
	}
	else{
		printf("%s\n", usage);
		exit(-1);
	}

	pthread_mutex_init(&mutex, NULL);
	// Get the port from the arguments
	
	// Set the IP address and port for this server
	struct sockaddr_in serverIPAddress; 
	memset( &serverIPAddress, 0, sizeof(serverIPAddress) );
	serverIPAddress.sin_family = AF_INET;
	serverIPAddress.sin_addr.s_addr = INADDR_ANY;
	serverIPAddress.sin_port = htons((u_short) port);

	// Allocate a socket
	int masterSocket =  socket(PF_INET, SOCK_STREAM, 0);
	if ( masterSocket < 0) {
		perror("socket");
		exit( -1 );
	}

	// Set socket options to reuse port. Otherwise we will
	// have to wait about 2 minutes before reusing the sae port number
	int optval = 1; 
	int err = setsockopt(masterSocket, SOL_SOCKET, SO_REUSEADDR, 
		       (char *) &optval, sizeof( int ) );

	// Bind the socket to the IP address and port
	int error = bind( masterSocket,
		    (struct sockaddr *)&serverIPAddress,
		    sizeof(serverIPAddress) );
	if ( error ) {
		perror("bind");
		exit( -1 );
	}

	// Put socket in listening mode and set the 
	// size of the queue of unprocessed connections
	error = listen( masterSocket, QueueLength);
	if ( error ) {
		perror("listen");
		exit( -1 );
	}
	if(pool == 1)
	{
		pthread_t tid[5];
		for(int i = 0; i<5; i++){
			pthread_create(&(tid[i]), NULL, &poolProcessRequest, (void*) masterSocket);
		}
		pthread_join(tid[0], NULL);
		
	}
	//////
	else if(pool == 0 && proc == 0 && thread == 0){
		struct sockaddr_in clientIPAddress;
		int alen = sizeof( clientIPAddress );
		
		while(1){
			int slaveSocket = accept( masterSocket,(struct sockaddr *)&clientIPAddress,(socklen_t*)&alen);
			processTimeRequest( slaveSocket );
			close(slaveSocket);
			//printf("here\n");
		}
	
	}
	//////
	else
	{
		while ( 1 ) {

			// Accept incoming connections
			struct sockaddr_in clientIPAddress;
			int alen = sizeof( clientIPAddress );
			int slaveSocket = accept( masterSocket,(struct sockaddr *)&clientIPAddress,(socklen_t*)&alen);

			if ( slaveSocket < 0 )
			{
				perror( "accept" );
				exit( -1 );
			}
			if(proc == 1)
			{
			
				int pid = fork();
				if(pid == 0)
				{
			
					processTimeRequest( slaveSocket );
					exit(EXIT_SUCCESS);
				}
				close( slaveSocket );
				wait3(0,0,NULL);
				while(waitpid(-1,NULL,WNOHANG) > 0);
			}
			if(thread == 1)
			{
				pthread_t thread;
				pthread_create(&thread, NULL, &processRequestThread, (void*)slaveSocket);
			
			}
			else if (thread == 0 && proc == 0 && pool == 0){
				processTimeRequest(slaveSocket);
			}
		
		}
	}
}
void * poolProcessRequest(void* socket)
{
	int masterSocket = (intptr_t)socket;
	while(1)
	{
		struct sockaddr_in clientIPAddress;
		int alen = sizeof( clientIPAddress );
		pthread_mutex_lock(&mutex);
		int slaveSocket = accept( masterSocket,(struct sockaddr *)&clientIPAddress,(socklen_t*)&alen);
		pthread_mutex_unlock(&mutex);
		processTimeRequest(slaveSocket);
		close(slaveSocket);
		

	}
}
void * processRequestThread(void* input)
{
	int slaveSocket = (intptr_t)input;
	processTimeRequest( slaveSocket );
	close(slaveSocket);
}
void
processTimeRequest( int fd )
{
	// Buffer used to store the name received from the client
	const int MaxName = 1024;
	char name[ MaxName + 1 ];
	int nameLength = 0;
	int n;
	int x = 0;

	// Currently character read
	char getWord[4];
	read( fd, &getWord, 3*sizeof(char) );
	getWord[3] = '\0';
	if (strcmp(getWord, "GET")){
		return;
	}

	unsigned char newChar = 0;
  	// Last character read
  	unsigned char lastChar = 0;

	//Abandon the first Space after the GET request
	read( fd, &newChar, sizeof(newChar) );

	// If there is no space for some reason, abandon the request.
	if(newChar != ' ')
		return;

	while ( nameLength < MaxName &&( n = read( fd, &newChar, sizeof(newChar) ) ) > 0 ) 
	{
		if(newChar == ' ')
		{
			break;
		}
		name[ nameLength ] = newChar;
		nameLength++;
	}
	name[ nameLength ] = '\0';
	char protocol[24];
	int protocolLen = 0;
	int maxProtocol = 24;
    
	while ( protocolLen < maxProtocol &&( n = read( fd, &newChar, sizeof(newChar) ) ) > 0 ) 
	{
	
		if ( lastChar == '\013' && newChar == '\010' ) 
		{
			// Discard previous <CR> from protocol
			protocolLen--;
			break;
		}

		protocol[ protocolLen ] = newChar;
		protocolLen++;

		lastChar = newChar;
	}

	protocol[ protocolLen ] = '\0';
	int done = 0;
	while ( (n = read( fd, &newChar, sizeof(newChar) ) ) > 0 && !done) 
	{
		if ( lastChar == '\r' && newChar == '\n') 
		{
			read( fd, &newChar, sizeof(newChar));
			if(newChar == '\r')
			{
				lastChar = newChar;
				read( fd, &newChar, sizeof(newChar));
				if(newChar == '\n')
				{
					done = 1;
					break;
				}
				lastChar = newChar;
			}
			lastChar = newChar;
		}
		lastChar = newChar;

	}
	char cwd[256] = {0};
	getcwd(cwd,256);
	char* path= (char*)malloc(sizeof(char)*1024);
	strcpy(path, "");
	char* extension = (char*)malloc(sizeof(char)*1024);
	strcpy(extension, "");
	strcat(path,cwd);
	strcat(path,"/http-root-dir");
	if(!strcmp(name, "/"))
	{
		strcat(path,"/htdocs/index.html");
		strcat(extension,"html");
	}
	else if(strstr(name, "/icons") == name || strstr(name, "/htdocs") == name)
	{
		strcat(path,name);
	}
	

	else if(strstr(name, "/cgi-bin") == name)
	{
		int varLen = 0;
		int varMaxLen = 256;		
		char var[varMaxLen+1];
		unsigned char temp;
		int i = 0;
		int j = 0;
		while (i<strlen(name) && name[i] !='?'){
			name[i] = name[i];
			i++;
		}
		i++;
		while(i<strlen(name) && name[i] != ' '){
			var[j] = name [i];
			j++; i++;
		}
		i=0;
		while (i<strlen(name) && name[i] !='?'){
			name[i] = name[i];
			i++;
		}
		name[i] = 0;
		strcat(cwd, "/http-root-dir");
		strcat(cwd, name);
		i++;

		processCGIreq(cwd, var, fd);
		return;
		
	}
	else
	{
		strcat(path,"/htdocs");
		strcat(path,name);
	}

	char* extensionPtr = strchr(path, '.');
	extensionPtr++;
	strcat(extension,extensionPtr);

	if(opendir(path))
	{
		
	}
	else
	{
		if(open(path, O_RDONLY) > 0){
			processResponse(path, extension, 200, fd);
		}
		else
		{
			processResponse(path, extension, 404, fd);
		}
	}

}
void processCGIreq(char* path, char* var, int socket)
{
	int out = dup(1);
	dup2(socket, 1);

	int pid = fork();
	if(pid == 0)
	{
		setenv("REQUEST_METHOD", "GET", 1);
		if(strlen(var) != 0)
		{
			setenv("QUERY_STRING", var, 1);
			//fprintf(stderr, "reached here\n");
		}
		
		write(socket, "HTTP/1.0 200 Document follows", strlen("HTTP/1.0 200 Document follows"));
		write(socket,"\r\n", 2);
		write(socket, "Server: CS 252 lab5", strlen("Server: CS 252 lab5"));
		write(socket,"\r\n", 2);
		
		execvp(path, NULL);
	}
	dup2(out, 1);
	close( out );
	
	
	
}
void processResponse(char* path, char* extension, int status, int socket)
{
	write(socket, "HTTP/1.0 ", 9);
	if(status == 200)
	{
		write(socket, "200 Document follows", 20);
	}
	else if(status == 404)
	{
		write(socket, "404 File Not Found", 18);
	}
	write(socket, "\r\nServer: CS 252 lab5\r\nContent-type: ", 37);
	switch (extension[0]) {
		case 'g' : write(socket, "image/gif", 9);
		break;
		case 'j' : write(socket, "image/jpeg", 10);
		break;
		case 't' : write(socket, "text/plain", 10);
		break;
		case 'h' : write(socket, "text/html", 9);
		break;
		case 'i' : write(socket, "image/x-icon", 12);
		break;
		default : write(socket, "text/plain", 10);
		break;
	}
	write(socket,"\r\n\r\n", 4);
	if(status == 200)
	{
		char* buff[256];
		FILE* file = fopen(path, "rb");
		int count;
		while(count = fread(buff, sizeof(char), 256, file))
		{
			if(count<1)
				break;
			write(socket, buff, count);
			if(count<256)
				break;
		}
		fclose(file);
	}
	else if(status == 404)
	{
		write(socket, "File could not be found!", 24);
		
	}
}
