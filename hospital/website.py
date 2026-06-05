import json
import os
from http.server import HTTPServer,SimpleHTTPRequestHandler
from urllib.parse import urlparse


class handler(SimpleHTTPRequestHandler):
    def do_GET(self):
        parsed=self.path
        if parsed=="/":
            self.send_response(200)
            self.send_header("Content-type", "text/html")
            self.end_headers()
            with open("index.html","r",encoding="utf_8")as p:
                html=p.read()
            self.wfile.write(html.encode())
        elif parsed=="/records":
            self.send_response(200)
            self.send_header("Content-type","application/json")
            self.send_header("Cache-Control","no-Cache,must-revalidate")
            self.end_headers()
            with open("data.json","r",encoding="utf_8")as f:
                data=json.load(f)
            self.wfile.write(json.dumps(data).encode())


def run_tha_server_twin(port=8080):
    server_adress=("",port)
    httpd=HTTPServer(server_adress,handler)
    print(f"the server is running in god knows where.(http://localhost:{port})")
    httpd.serve_forever()

if __name__== "__main__":
    run_tha_server_twin();
