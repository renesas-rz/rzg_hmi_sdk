import os
import sys
from urllib.parse import urlparse
from http.server import SimpleHTTPRequestHandler
from http.server import HTTPServer

class Handler(SimpleHTTPRequestHandler):
    def do_GET(self):
        url = urlparse(self.path)
        request_file_path = url.path.strip('/')

        if not os.path.exists(request_file_path):
            self.path = 'index.html'

        return SimpleHTTPRequestHandler.do_GET(self)

host = '0.0.0.0'
port = int(sys.argv[1]) if len(sys.argv) > 1 else 8000

httpd = HTTPServer((host, port), Handler)
print(f'Serving HTTP on {host} port {port} ...')
httpd.serve_forever()