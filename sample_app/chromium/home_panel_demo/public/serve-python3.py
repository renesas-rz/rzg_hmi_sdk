import os
import sys
from urllib.parse import urlparse
from http.server import SimpleHTTPRequestHandler
from http.server import HTTPServer

# Helper function to copy only the requested byte range
def copy_range_bytes(infile, outfile, start, end):
    infile.seek(start)
    buffer_size = 64 * 1024
    remain = end - start + 1
    while remain > 0:
        chunk = infile.read(min(remain, buffer_size))
        if not chunk:
            break
        outfile.write(chunk)
        remain -= len(chunk)

class Handler(SimpleHTTPRequestHandler):
    def do_GET(self):
        url = urlparse(self.path)
        request_file_path = url.path.strip('/')

        # 1. Fallback to index.html if the requested file does not exist
        if not os.path.exists(request_file_path) or os.path.isdir(request_file_path):
            self.path = 'index.html'
            return SimpleHTTPRequestHandler.do_GET(self)

        # 2. Check for Range request header
        range_header = self.headers.get('Range')
        if not range_header or not range_header.startswith('bytes='):
            # Handle as standard request (200 OK) if no Range header is present
            return SimpleHTTPRequestHandler.do_GET(self)

        # 3. Parse the requested byte range (e.g., "bytes=1000000-")
        try:
            file_size = os.path.getsize(request_file_path)
            range_val = range_header.split('=')[1]
            start_str, end_str = range_val.split('-')

            start = int(start_str) if start_str else 0
            end = int(end_str) if end_str else file_size - 1

            if start >= file_size or end >= file_size or start > end:
                raise ValueError
        except (ValueError, IndexError):
            self.send_error(416, "Requested Range Not Satisfiable")
            return

        # 4. Serve the file as HTTP 206 Partial Content
        try:
            f = open(request_file_path, 'rb')
        except OSError:
            self.send_error(404, "File not found")
            return

        self.send_response(206) # Respond with 206 Partial Content
        self.send_header('Content-Type', self.guess_type(request_file_path))
        self.send_header('Accept-Ranges', 'bytes') # Inform the browser that seeking is supported
        self.send_header('Content-Range', f'bytes {start}-{end}/{file_size}')
        self.send_header('Content-Length', str(end - start + 1))
        self.send_header('Last-Modified', self.date_time_string(os.path.getmtime(request_file_path)))
        self.end_headers()

        # Transmit only the requested chunk of data
        try:
            copy_range_bytes(f, self.wfile, start, end)
        finally:
            f.close()

host = '0.0.0.0'
try:
    port = int(sys.argv[1])
except IndexError:
    port = 8000
httpd = HTTPServer((host, port), Handler)

print('Serving HTTP on %s port %d ...' % (host, port))
httpd.serve_forever()
