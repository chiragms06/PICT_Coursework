import socket
import threading

def handle_client(client_socket,addr):
    while True:
        #receive
        data = client_socket.recv(1024)
        if not data:
            break
        print(f"Client message from {addr} : {data.decode()}")
        msg = input()
        #send
        client_socket.send(msg.encode())
    client_socket.close()

def main():
    #create socket
    s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    #bind
    s.bind(('', 12345)) 
    #listen
    s.listen(5)
    print(f"Server listening at port {12345}")
    while True:
        #accept
        client, addr = s.accept()
        print(f"Accepting connection from {addr}")
        client_handler = threading.Thread(target = handle_client, args = (client,addr))
        client_handler.start()
        
if __name__ == "__main__":
    main()
