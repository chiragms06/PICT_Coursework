import socket
import threading

def receive_msg(client_socket):
    while True:
        #receive
        data = client_socket.recv(1024)
        if not data:
            break
        print(f"Server :{data.decode()}")

def main():
    #create socket
    s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    port = 12345
    #connect
    s.connect(('127.0.0.1', port))
    print("Connected to server.....(type 'exit' to quit)")
    receive_handler = threading.Thread(target = receive_msg, args = (s,))
    receive_handler.start()
    msg = ""
    while msg != "bye":
        msg = input()
        s.send(msg.encode())
    s.close()

if __name__ == "__main__":
    main()
