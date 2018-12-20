/*

This is going to be one shitty parser, so a
rewrite is going to be scheduled.... maybe.

*/

#define GET 0 //3
#define POST 1 //4

#define NOTFOUND 404 //8 //404
#define IMNOTATEAPOT 418 //12 //418
#define FORBIDDEN 403 //9 //403
#define OK 200 //2 //200
#define MOVED 301 //5 //301
#define SERVERFAULT 501 //11 //501

#define OK_STRING "OK"
#define NOTFOUND_STRING "NOT_FOUND"
#define SERVERFAULT_STRING "INTERNAL_ERROR"

#define OK_LENGTH 2
#define NOTFOUND_LENGTH 9
#define SERVERFAULT_LENGTH 14

#define SENDSPACE (client->cliwrite(SPACE, 1))
#define CRLF "\r\n"
#define CR '\r'
#define LF '\n'
#define SPACE " "
#define SENDCRLF (client->cliwrite(CRLF, 2))
#define SENDCR (client->cliwrite('\r', 1))
#define SENDLF (client->cliwrite('\n', 1))

#define CONTENTLENGTH(x) (client->cliwrite(_CONTENTLENGTH, 16));\
		std::string str = /*std::to_string(x)*/"fix me http/httpbodgeparser.h";\
		(client->cliwrite(str.c_str(), str.length()))
#define _CONTENTLENGTH		"content-length: "
#define _CONTENTLENGTH_LENGTH 16
#define _CONTENTTYPE		"content-type: "
#define _CONTENTTYPE_LENGTH 14

#define EXT_HTML ".html"
#define NUM_HTML 1
#define EXT_HTM ".htm"
#define EXT_BMP ".bmp"
#define NUM_BMP 2
#define EXT_CSS ".css"
#define NUM_CSS 3
#define EXT_CSV ".csv"
#define NUM_CSV 4
#define EXT_GIF ".gif"
#define NUM_GIF 5
#define EXT_ICO ".ico"
#define NUM_ICO 6
#define EXT_JPEG ".jpeg"
#define NUM_JPEG 7
#define EXT_JPG ".jpg"
#define NUM_JPG 8
#define EXT_JS ".js"
#define NUM_JS 9
#define EXT_PNG ".png"
#define NUM_PNG 10
#define MIME_HTML		"text/html"
#define MIME_HTML_LENGTH 9
#define MIME_CSS		"text/css"
#define MIME_CSS_LENGTH 8
#define MIME_CSV		"text/csv"
#define MIME_GIF		"image/gif"
#define MIME_ICO		"image/x-icon"
#define MIME_JPG		"image/jpeg"
#define MIME_JS			"application/json"
#define MIME_PNG		"image/png"
#define MIME_PNG_LENGTH 10
#define MIME_BIN		"application/octet-stream"
#define MIME_BIN_LENGTH 24

#define HTTP1 1
#define HTTP1_1 2
#define HTTP2 3

#define HTTP1_STRING "HTTP/1.0"
#define HTTP1_1_STRING "HTTP/1.1"
#define HTTP2_STRING "HTTP/2.0"

#define HTTP1_LENGTH 8
#define HTTP1_1_LENGTH 8
#define HTTP2_LENGTH 8

#include <string.h>
#include <iostream>
#include "tcpclient.h"
#include <stdio.h>
#include <stdlib.h>
#include "itoa.h"


struct httpbodgehead {
char contenttype;
size_t contentlength;
};

struct httpbodgemessage : httpbodgehead {
char* content;
};

//RANDOM
char rando[] = "<html><head><title>SUBSCRIBE TO PEWDIEPIE</title></head><body><h1>SUBSCRIBE TO PEWDIEPIE</h1></body></html>";

//REQUEST
struct httpbodgerequest : httpbodgemessage {

};

//RESPONSE
struct httpbodgeresponse : httpbodgemessage {
unsigned short statuscode;
char httpversion;
};

int sendmessage(tcpclient* client, httpbodgemessage* message) {
if (message->contentlength > 0) {
client->cliwrite(_CONTENTTYPE, _CONTENTTYPE_LENGTH);
switch (message->contenttype) {
case NUM_HTML:
client->cliwrite(MIME_HTML, MIME_HTML_LENGTH);
break;
case NUM_PNG:
client->cliwrite(MIME_PNG, MIME_PNG_LENGTH);
break;
default:
client->cliwrite(MIME_BIN, MIME_BIN_LENGTH);
break;
}
SENDCRLF;
}
CONTENTLENGTH(message->contentlength);
SENDCRLF;
SENDCRLF;
std::cout << &message->content << std::endl;
client->cliwrite(message->content, message->contentlength);
return 0;
}

//"SERIALIZATION"
int send(tcpclient* client, httpbodgeresponse* response) {
	int ret = 0;
	static char buf[10];
	//HTTP VERSION
	switch (response->httpversion)
	{
	case HTTP1:
		client->cliwrite(HTTP1_STRING, HTTP1_LENGTH);
		SENDSPACE;
		break;
	case HTTP1_1:
		client->cliwrite(HTTP1_1_STRING, HTTP1_1_LENGTH);
		SENDSPACE;
		break;
	case HTTP2:
		client->cliwrite(HTTP2_STRING, HTTP2_LENGTH);
		SENDSPACE;
		break;
	default:
		client->cliwrite(HTTP1_STRING, HTTP1_LENGTH);
		SENDSPACE;
		ret |= 2;
		break;
	}
	//STATUS CODE
	switch (response->statuscode)
	{
	case OK:
		itoa(OK, &*buf, 10);
		client->cliwrite(&buf, 3);
		SENDSPACE;
		client->cliwrite(OK_STRING, OK_LENGTH);
		SENDCRLF;
		break;
	case NOTFOUND:
		itoa(NOTFOUND, &*buf, 10);
		client->cliwrite(&buf, 3);
		SENDSPACE;
		client->cliwrite(NOTFOUND_STRING, NOTFOUND_LENGTH);
		SENDCRLF;
		break;
	default:
		itoa(SERVERFAULT, &*buf, 10);
		client->cliwrite(&buf, 3);
		SENDSPACE;
		client->cliwrite(SERVERFAULT_STRING, SERVERFAULT_LENGTH);
		SENDCRLF;
		ret |= 1;
		break;

	}
return (ret | sendmessage(client, (httpbodgemessage*)response));
}

int recievehttpheader(tcpclient* client, httpbodgerequest& request){
char* buffer = new char[256];
char* buf2 = new char[256];
char b = 0;
int pos = 0;
int pos2 = 0;
int s = 0;
while (1) {
while (b != CR && b != LF) {
client->cliread((char*)&b, 1);
buffer[pos++] = b;
}
while (b == CR || b == LF) {
client->cliread((char*)&b, 1);

}
//PARSE THE REQUEST SECTION
pos = 0;
if (s < 1) {
while ((b = buffer[pos++]) != ' '){
buf2[-1];
}
s++;
} else
//PARSE THE PARAMETERS
{

}

}
}

int recievehttpmessage(tcpclient* client, httpbodgerequest& request) {

}

int httpbodgeparser(const char* buffer, size_t length, httpbodgerequest& request) {

return 0;
}
