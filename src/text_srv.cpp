

#include <cstring>
#include <cstdio>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
 #include <arpa/inet.h>
constexpr int BACKLOG = 100;	
 char response[4096] = 
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=utf-8\r\n";
const char html_page[] = "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>Paschal Ahanmisi - Home Page</title><style>body{font-family:\"Times New Roman\",Times,Georgia,serif;background-color:#fff;color:#000;max-width:800px;margin:40px auto;padding:0 20px;line-height:1.4}h1{font-size:1.8em;font-weight:bold;margin-bottom:5px}h2{font-size:1.3em;font-weight:bold;border-bottom:1px solid #000;padding-bottom:2px;margin-top:30px}a{color:#0000ee;text-decoration:underline}a:visited{color:#551a8b}ul{list-style-type:square;padding-left:20px}li{margin-bottom:8px}.news-date{font-weight:bold}footer{margin-top:50px;font-size:.9em;border-top:1px solid #ccc;padding-top:10px}</style></head><body><h1>Paschal Ahanmisi</h1><p>Software Engineer &amp; Systems Researcher</p><h2>Software &amp; Projects</h2><ul><li><a href=\"#\">MicroC</a> - A minimal C compiler targetting RISC-V in under 1,000 lines of code.</li><li><a href=\"#\">FastMath</a> - An arbitrary-precision arithmetic library optimized for SIMD architectures.</li><li><a href=\"#\">TinyJS</a> - A lightweight JavaScript engine designed for embedded systems with limited RAM.</li><li><a href=\"#\">NetEmu</a> - A user-space network emulator for testing packet loss and high latency.</li></ul><h2>News &amp; Updates</h2><ul><li><span class=\"news-date\">2026-02-10:</span> Released MicroC version 0.4 with improved register allocation.</li><li><span class=\"news-date\">2025-11-18:</span> Published paper on fast floating-point conversions.</li><li><span class=\"news-date\">2025-06-02:</span> Initial public source code commit for FastMath.</li></ul><h2>Publications &amp; Notes</h2><ul><li><a href=\"#\">Optimizing Register Allocation in Tiny Compilers</a> (2025) [pdf]</li><li><a href=\"#\">Notes on Computation of Pi via Spigot Algorithms</a> (2023) [html]</li></ul><footer><p>Contact: alex [at] example [dot] org | <a href=\"#\">PGP Key</a></p></footer></body></html>";
int main(){
	struct sockaddr_in srvadr; 
	int sockfd ;
	int clientfd ;
	const size_t strsz = std::strlen(html_page);
	char temp[100]; 
	snprintf(temp, 100,"Content-Length: %lu \r\n Connection: close\r\n\r\n" , strsz );
	std::strcat(response , temp);
	std::strcat(response , html_page);
	const size_t sz = std::strlen(response);
	ssize_t r1 ; 
	
	if ((sockfd = socket(AF_INET , SOCK_STREAM , 0)) == -1 ){
		fprintf(stderr , "Could not connect to socket()");
		return -1;
	}
	int opt = 1;
    	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	std::memset(reinterpret_cast<void*>(&srvadr) , 0x00 , sizeof(struct sockaddr_in));
	srvadr.sin_family = AF_INET ; 
	srvadr.sin_port = htons(8080);
	srvadr.sin_addr.s_addr = INADDR_ANY;
	// Bind the address now to the socket
	if(bind(sockfd , reinterpret_cast<const struct sockaddr*>(&srvadr) , sizeof(struct sockaddr_in)) == -1){
		std::fprintf(stderr ,"Sevrer bind() failed ");
		return -1;
	}

	// listening on port 
	if(listen(sockfd,BACKLOG) == -1){
		std::fprintf(stderr , "Listen() failed ");
		return -1;
	}

	std::printf("Listeinng on port 8080 on all ports \n");
	
	for(;;){
		clientfd = accept(sockfd, nullptr , nullptr);
		if(clientfd == -1) {
			std::fprintf(stderr , "Failed to make connection with server\n");
			continue;
		}
		r1 = write(clientfd , response ,sz );
		std::printf("Written %ld bytes to client /n" , r1);
		close(clientfd) ; 
	}
	close(sockfd);
}
