import socket
import time

def start_server(port=13):
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(('', port))
    server_socket.listen(1)
    
    print(f"Server is listening on port {port}")
    
    while True:
        conn, addr = server_socket.accept()
        print(f"Connected by {addr}")
        current_time = time.ctime()
        conn.send(current_time.encode() + b'\n')
        conn.close()

if __name__ == "__main__":
    start_server()
