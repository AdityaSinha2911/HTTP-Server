# C++ HTTP Server from Scratch

A web browser does not communicate directly with a C++ program. It communicates using the **HTTP (HyperText Transfer Protocol)**. An **HTTP server** is software that listens for HTTP requests, processes them, and sends HTTP responses containing webpages, images, JavaScript, CSS, JSON, or other content.

The goal of this project is to build an **HTTP/1.1 web server completely from scratch in C++**, without using web frameworks or HTTP server libraries.

The project focuses on understanding how web servers work internally — from low-level TCP socket communication to HTTP request parsing, routing, static file serving, MIME type detection, security, and HTTP response generation.



---

## Current Progress

The following features have been implemented so far:

* Create a TCP IPv4 socket using `socket()`
* Configure the server using `AF_INET`
* Use TCP communication with `SOCK_STREAM`
* Bind the server to a local address and port using `bind()`
* Listen for incoming client connections using `listen()`
* Accept client connections using `accept()`
* Receive HTTP requests using `recv()`
* Send HTTP responses using `send()`
* Properly close client and server sockets using `close()`
* Parse HTTP/1.1 request lines
* Extract HTTP method from requests
* Extract URL/path from requests
* Extract HTTP version from requests
* Parse HTTP headers
* Represent requests using an `HttpRequest` model
* Represent responses using an `HttpResponse` model
* Build HTTP responses with status lines and headers
* Generate `Content-Length` automatically
* Implement HTTP request routing
* Map requested URLs to files
* Serve static files from the `public/` directory
* Read files using C++ `ifstream`
* Implement a dedicated `FileReader` module
* Serve `index.html` through the `/` route
* Implement MIME type detection
* Set appropriate `Content-Type` headers
* Support common static file types:

  * HTML
  * CSS
  * JavaScript
  * JSON
  * TXT
  * PNG
  * JPG
  * JPEG
  * GIF
  * SVG
* Implement custom `404 Not Found` responses
* Add basic directory traversal protection
* Handle multiple sequential client connections
* Test the server using a web browser
* Test HTTP endpoints using `curl`

---

## Technologies Used

* C++
* POSIX Socket API
* Linux / Ubuntu
* TCP/IP
* HTTP/1.1
* GCC / G++
* Standard C++ Library
* `ifstream`
* `curl`

---

## Architecture

```text
Client / Browser
       |
       v
     TCP
       |
       v
   accept()
       |
       v
     recv()
       |
       v
  HTTP Parser
       |
       v
  HttpRequest
       |
       v
     Router
       |
       +----------------+
       |                |
       v                v
  FileReader        MimeTypes
       |                |
       v                v
  File Content      Content-Type
       |                |
       +-------+--------+
               |
               v
        HttpResponse
               |
               v
       ResponseBuilder
               |
               v
             send()
               |
               v
             Client
```

---

## Project Structure

```text
http-server/
|
├── main.cpp
|
├── models/
│   ├── HttpRequest.h
│   └── HttpResponse.h
|
├── parser/
│   ├── HttpParser.h
│   └── HttpParser.cpp
|
├── router/
│   ├── Router.h
│   └── Router.cpp
|
├── response/
│   ├── ResponseBuilder.h
│   └── ResponseBuilder.cpp
|
├── file/
│   ├── FileReader.h
│   └── FileReader.cpp
|
├── utils/
│   ├── MimeTypes.h
│   ├── MimeTypes.cpp
│   ├── PathUtils.h
│   └── PathUtils.cpp
|
└── public/
    ├── index.html
    ├── about.html
    ├── contact.html
    ├── style.css
    └── script.js
```

---

## Module Overview

### `main.cpp`

* Creates the server socket
* Configures the server address
* Binds the socket
* Starts listening
* Accepts client connections
* Receives HTTP requests
* Passes requests through the processing pipeline
* Sends generated HTTP responses
* Closes client connections

### `models/`

Contains the basic data structures used by the server.

* `HttpRequest`

  * Stores HTTP method
  * Stores requested path
  * Stores HTTP version
  * Stores request headers

* `HttpResponse`

  * Stores status code
  * Stores status message
  * Stores response headers
  * Stores response body

### `parser/`

Responsible for converting raw HTTP request data into structured information.

* Parses the request line
* Extracts HTTP method
* Extracts URL/path
* Extracts HTTP version
* Parses HTTP headers
* Produces an `HttpRequest` object

### `router/`

Responsible for deciding what resource should be served for a requested path.

Examples:

```text
/              -> public/index.html
/about.html    -> public/about.html
/contact.html  -> public/contact.html
/style.css     -> public/style.css
/script.js     -> public/script.js
```

### `response/`

Responsible for constructing HTTP responses.

* Generates status lines
* Adds HTTP headers
* Calculates `Content-Length`
* Adds `Content-Type`
* Appends response body
* Produces the final HTTP response sent to the client

### `file/`

Responsible for reading static files from the filesystem.

* Opens requested files
* Reads file contents
* Handles missing or unreadable files
* Returns file content to the response pipeline

### `utils/`

Contains reusable helper functionality.

#### `MimeTypes`

Maps file extensions to MIME types.

Examples:

```text
.html  -> text/html
.css   -> text/css
.js    -> application/javascript
.json  -> application/json
.txt   -> text/plain
.png   -> image/png
.jpg   -> image/jpeg
.gif   -> image/gif
.svg   -> image/svg+xml
```

#### `PathUtils`

Handles path-related validation and security checks.

* Validates requested paths
* Helps prevent directory traversal
* Keeps requested resources inside the intended public directory

---

## HTTP Request Flow

When a browser requests a webpage, the server processes the request through several stages:

```text
1. Client connects
       |
       v
2. accept()
       |
       v
3. recv()
       |
       v
4. Raw HTTP Request
       |
       v
5. HTTP Parser
       |
       v
6. HttpRequest
       |
       v
7. Router
       |
       v
8. FileReader
       |
       v
9. MIME Type Detection
       |
       v
10. HttpResponse
       |
       v
11. ResponseBuilder
       |
       v
12. send()
       |
       v
13. Client receives response
```

---

## Example HTTP Request

A browser may send a request similar to:

```http
GET /index.html HTTP/1.1
Host: localhost:8081
User-Agent: Mozilla/5.0
Accept: text/html
Connection: keep-alive
```

The parser converts this raw request into structured information:

```text
Method: GET
Path: /index.html
Version: HTTP/1.1

Headers:
    Host: localhost:8081
    User-Agent: Mozilla/5.0
    Accept: text/html
    Connection: keep-alive
```

---

## Example HTTP Response

The server generates a response similar to:

```http
HTTP/1.1 200 OK
Content-Type: text/html
Content-Length: 120

<html>
    <body>
        <h1>Hello from my HTTP Server!</h1>
    </body>
</html>
```

---

## Static File Serving

The server can serve files from the `public/` directory.

Example:

```text
Browser Request
      |
      v
GET /style.css
      |
      v
Router
      |
      v
public/style.css
      |
      v
FileReader
      |
      v
MimeTypes
      |
      v
Content-Type: text/css
      |
      v
HTTP Response
```

This allows the server to serve complete static webpages containing:

* HTML
* CSS
* JavaScript
* Images
* JSON
* Text files

---

## Routing

The server maps HTTP paths to resources inside the `public/` directory.

Examples:

```text
/                  -> public/index.html
/about.html        -> public/about.html
/contact.html      -> public/contact.html
/style.css         -> public/style.css
/script.js         -> public/script.js
```

The default `/` route serves:

```text
public/index.html
```

---

## MIME Type Detection

The server determines the appropriate `Content-Type` from the requested file extension.

Examples:

```text
.html  -> text/html
.css   -> text/css
.js    -> application/javascript
.json  -> application/json
.txt   -> text/plain
.png   -> image/png
.jpg   -> image/jpeg
.jpeg  -> image/jpeg
.gif   -> image/gif
.svg   -> image/svg+xml
```

This allows browsers to correctly interpret the returned resources.

---

## Error Handling

The server handles missing resources using a custom:

```http
HTTP/1.1 404 Not Found
```

response.

Example:

```text
GET /does-not-exist.html
        |
        v
     Router
        |
        v
   File not found
        |
        v
   404 Response
```

---

## Security

Basic directory traversal protection has been implemented.

A malicious request such as:

```text
GET /../../secret.txt HTTP/1.1
```

should not be allowed to access files outside the server's intended public directory.

The server validates requested paths before attempting to read files.

---

## Multiple Client Connections

The server is capable of handling multiple client connections sequentially.

The current flow is:

```text
accept()
   |
   v
recv()
   |
   v
process request
   |
   v
send response
   |
   v
close client
   |
   v
accept next client
```

This allows multiple browser requests and `curl` requests to be processed one after another.

---

## Testing

The server can be tested using a web browser.

Start the server:

```bash
./server
```

Then open:

```text
http://localhost:8081
```

or:

```text
http://127.0.0.1:8081
```

---

## Testing with curl

Basic request:

```bash
curl http://localhost:8081/
```

Request a specific page:

```bash
curl http://localhost:8081/about.html
```

Request CSS headers:

```bash
curl -I http://localhost:8081/style.css
```

Test a missing resource:

```bash
curl -i http://localhost:8081/does-not-exist.html
```

---

## Prerequisites

Install the required development tools on Ubuntu:

```bash
sudo apt update
sudo apt install build-essential g++ gdb valgrind curl
```

---

## Compile

Compile the project using:

```bash
g++ main.cpp \
parser/HttpParser.cpp \
router/Router.cpp \
response/ResponseBuilder.cpp \
file/FileReader.cpp \
utils/MimeTypes.cpp \
utils/PathUtils.cpp \
-o server
```

Run the compiled server:

```bash
./server
```

---

## Concepts Covered

### Networking

* TCP/IP
* Client-server architecture
* IPv4
* TCP connections
* Ports
* Network byte order
* `htons()`
* `htonl()`

### POSIX Socket Programming

* `socket()`
* `bind()`
* `listen()`
* `accept()`
* `recv()`
* `send()`
* `close()`

### HTTP

* HTTP/1.1
* HTTP request structure
* HTTP response structure
* Request line
* HTTP methods
* URL paths
* HTTP versions
* HTTP headers
* Status codes
* Status messages
* `Content-Length`
* `Content-Type`
* MIME types

### C++ Programming

* Classes
* Structures
* Header files
* Source files
* Modular programming
* File handling
* `ifstream`
* Strings
* Maps
* Error handling
* Separation of concerns

### Web Server Architecture

* Request parsing
* Routing
* Static file serving
* Response generation
* MIME type detection
* File system interaction
* Client connection handling

### Security

* Directory traversal
* Path validation
* Restricting file access to the public directory

---

## What I Learned

Through this project, I am learning how high-level web servers are built on top of low-level networking concepts.

Instead of using frameworks that hide the networking layer, this project requires implementing the fundamental pieces manually:

```text
TCP Socket
    |
    v
HTTP Request
    |
    v
Request Parser
    |
    v
Router
    |
    v
File System
    |
    v
MIME Detection
    |
    v
HTTP Response
    |
    v
TCP Socket
```

This provides a practical understanding of what happens internally when a browser requests a webpage from a server.

---

## Project Goals

The project is still under development.

Planned improvements include:

* Improve HTTP request handling
* Improve connection management
* Handle more HTTP methods
* Improve HTTP error handling
* Add more HTTP status codes
* Improve security validation
* Add better request and response abstractions
* Improve performance
* Add concurrent client handling
* Add more HTTP/1.1 functionality
* Improve testing and robustness

---

## Author

**Aditya Kumar Sinha**
